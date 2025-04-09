
#include "raylib.h"
#include <cmath>
#include <stdio.h>
#include "globals.hpp"
#include "atks_sapo.hpp"
#include "movement.hpp"

//-----------------------------------------------------------//

void init()
{
    p_atk_timer = 0;
    it = 0;
    dash_t = 0;
    ATK1_COOLDOWNt = 0;

    P.posicao.x = inicio_player_x;
    P.posicao.y = inicio_player_y;
    P.vida_jogador = 100;

    S.posicao.x = CENTER_x;
    S.posicao.y = CENTER_y;
    S.vida_boss = 100;

    vec.dex = 0;
    vec.dey = 0;
    vec.cx = 0;
    vec.cy = 0;
    vec.reverse = 0;

    S.posicao_inicial = S.posicao;
    S.acompanhar_cd_antes_da_linguada = S.cooldown_antes_da_linguada;
    S.linguadas_restantes = S.quantidade_de_linguadas;
}

//------------------------------------------------------------//

void barras_vida() {
    // do jogador
    DrawRectangle(20, 20, 200, 20, GRAY);

    float vida_jogador_width = (P.vida_jogador / 100.0) * 200;

    DrawRectangle(20, 20, vida_jogador_width, 20, GREEN);

    // do boss
    DrawRectangle(Hres - 220, 20, 200, 20, GRAY);

    float vida_boss_width = (S.vida_boss / 100.0) * 200;

    DrawRectangle(Hres - 220, 20, vida_boss_width, 20, RED);
}

//-----------------------------------------------------------//


//-------------------		ROTINA PARA VERIFICAR AS COLISÕES COM A HITBOX DA ESPADA	-------------------------//

void sword_hitbox_check(float fps_routine)
{
    float at_x = P.posicao.x + 6 * P.sword.x;
    float at_y = P.posicao.y + 6 * P.sword.y;
    float at1_x = 6 * P.sword.x * cos(PI / 12) - 6 * P.sword.y * sin(PI / 12) + P.posicao.x;
    float at1_y = 6 * P.sword.x * sin(PI / 12) + 6 * P.sword.y * cos(PI / 12) + P.posicao.y;
    float at2_x = 6 * P.sword.x * cos(PI / 12) + 6 * P.sword.y * sin(PI / 12) + P.posicao.x;
    float at2_y = -6 * P.sword.x * sin(PI / 12) + 6 * P.sword.y * cos(PI / 12) + P.posicao.y;
    //var1: (S.posicao.x - at_x)² + (S.posicao.y - at_y)²

    if (IsKeyDown(KEY_P) && p_atk_timer == 0)
    {
        p_atk_timer += fps_routine;
        if ((S.posicao.x - at_x) * (S.posicao.x - at_x) + (S.posicao.y - at_y) * (S.posicao.y - at_y) <= S.raio_do_sapo * S.raio_do_sapo) S.vida_boss -= 10;
        else if ((S.posicao.x - at1_x) * (S.posicao.x - at1_x) + (S.posicao.y - at1_y) * (S.posicao.y - at1_y) <= S.raio_do_sapo * S.raio_do_sapo) S.vida_boss -= 10;
        else if ((S.posicao.x - at2_x) * (S.posicao.x - at2_x) + (S.posicao.y - at2_y) * (S.posicao.y - at2_y) <= S.raio_do_sapo * S.raio_do_sapo) S.vida_boss -= 10;
    }
    else if (p_atk_timer > 0) p_atk_timer += fps_routine;
    if (p_atk_timer >= P_ATK_COOLDOWN) p_atk_timer = 0;
}

//-----------------------------------------------------------//

int main() {
    InitWindow(Hres, Vres, "sapo");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("assets/backALG_LIN.png");

    Rectangle fonte = {0.0, 0.0, (float)background.width, (float)background.height };
    Rectangle destino = { 0.0, 0.0, (float)Hres, (float)Vres };
    Vector2 origem = {0.0, 0.0 };
    float ang_rot = 0.0;

    Image playerUP, playerUPL, playerUPR;
    Image playerDOWN, playerDOWNL, playerDOWNR;
    Image playerRIGHT, playerRIGHTL, playerRIGHTR;
    Image playerLEFT, playerLEFTL, playerLEFTR;

    Image IDLEC, IDLED, IDLEE, IDLEF;
    Image LINGC, LINGD, LINGE, LINGF;
    Image PORRC, PORRD, PORRE, PORRF;
    Image PULOC, PULOD, PULOE, PULOF;

    playerUP = LoadImage("assets/playerfrente.png");
    playerUPR = LoadImage("assets/playerfrente_right.png");
    playerUPL = LoadImage("assets/playerfrente_left.png");

    playerDOWN = LoadImage("assets/playercostas.png");
    playerDOWNR = LoadImage("assets/playercostas_right.png");
    playerDOWNL = LoadImage("assets/playercostas_left.png");

    playerRIGHT = LoadImage("assets/playerdir.png");
    playerRIGHTR = LoadImage("assets/playerdir_right.png");
    playerRIGHTL = LoadImage("assets/playerdir_left.png");

    playerLEFT = LoadImage("assets/playeresq.png");
    playerLEFTR = LoadImage("assets/playeresq_right.png");
    playerLEFTL = LoadImage("assets/playeresq_left.png");

    IDLEC = LoadImage("assets/sapo_anda_costas");
    IDLED = LoadImage("assets/sapo_anda_direita");
    IDLEE = LoadImage("assets/sapo_anda_esquerda");
    IDLEF = LoadImage("assets/sapo_anda_frente");

    LINGC = LoadImage("assets/sapo_linguada_costas");
    LINGD = LoadImage("assets/sapo_linguada_direita");
    LINGE = LoadImage("assets/sapo_linguada_esquerda");
    LINGF = LoadImage("assets/sapo_linguada_frente");

    PORRC = LoadImage("assets/sapo_porradao_costas");
    PORRD = LoadImage("assets/sapo_porradao_direita");
    PORRE = LoadImage("assets/sapo_porradao_esquerda");
    PORRF = LoadImage("assets/sapo_porradao_frente");

    PULOC = LoadImage("assets/sapo_pulando_costas");
    PULOD = LoadImage("assets/sapo_pulando_direita");
    PULOE = LoadImage("assets/sapo_pulando_esquerda");
    PULOF = LoadImage("assets/sapo_pulando_frente");

    ImageResize(&playerUP, 25, 50);
    ImageResize(&playerUPL, 25, 50);
    ImageResize(&playerUPR, 25, 50);

    ImageResize(&playerDOWN, 25, 50);
    ImageResize(&playerDOWNR, 25, 50);
    ImageResize(&playerDOWNL, 25, 50);

    ImageResize(&playerRIGHT, 25, 50);
    ImageResize(&playerRIGHTR, 25, 50);
    ImageResize(&playerRIGHTL, 25, 50);

    ImageResize(&playerLEFT, 25, 50);
    ImageResize(&playerLEFTR, 25, 50);
    ImageResize(&playerLEFTL, 25, 50);

    ImageResize(&IDLEC, 71, 71);
    ImageResize(&IDLEF, 71, 71);
    ImageResize(&IDLED, 71, 71);
    ImageResize(&IDLEE, 71, 71);

    ImageResize(&LINGC, 71, 71);
    ImageResize(&LINGF, 71, 71);
    ImageResize(&LINGD, 71, 71);
    ImageResize(&LINGE, 71, 71);

    ImageResize(&PORRC, 71, 71);
    ImageResize(&PORRF, 71, 71);
    ImageResize(&PORRD, 71, 71);
    ImageResize(&PORRE, 71, 71);

    ImageResize(&PULOC, 71, 71);
    ImageResize(&PULOF, 71, 71);
    ImageResize(&PULOD, 71, 71);
    ImageResize(&PULOE, 71, 71);

    Texture2D player_frente = LoadTextureFromImage(playerUP);
    Texture2D player_frente_dir = LoadTextureFromImage(playerUPR);
    Texture2D player_frente_esq = LoadTextureFromImage(playerUPL);

    Texture2D player_costas = LoadTextureFromImage(playerDOWN);
    Texture2D player_costas_dir = LoadTextureFromImage(playerDOWNR);
    Texture2D player_costas_esq = LoadTextureFromImage(playerDOWNL);

    Texture2D player_direita = LoadTextureFromImage(playerRIGHT);
    Texture2D player_direita_dir = LoadTextureFromImage(playerRIGHTR);
    Texture2D player_direita_esq = LoadTextureFromImage(playerRIGHTL);

    Texture2D player_esquerda = LoadTextureFromImage(playerLEFT);
    Texture2D player_esquerda_dir = LoadTextureFromImage(playerLEFTR);
    Texture2D player_esquerda_esq = LoadTextureFromImage(playerLEFTL);

    Texture2D sapo_IDLE_costas = LoadTextureFromImage(IDLEC);
    Texture2D sapo_IDLE_frente = LoadTextureFromImage(IDLEF);
    Texture2D sapo_IDLE_dir = LoadTextureFromImage(IDLED);
    Texture2D sapo_IDLE_esq = LoadTextureFromImage(IDLEE);

    Texture2D sapo_linguada_costas = LoadTextureFromImage(LINGC);
    Texture2D sapo_linguada_frente = LoadTextureFromImage(LINGF);
    Texture2D sapo_linguada_dir = LoadTextureFromImage(LINGD);
    Texture2D sapo_linguada_esq = LoadTextureFromImage(LINGE);

    Texture2D sapo_porradao_costas = LoadTextureFromImage(PORRC);
    Texture2D sapo_porradao_frente = LoadTextureFromImage(PORRF);
    Texture2D sapo_porradao_dir = LoadTextureFromImage(PORRD);
    Texture2D sapo_porradao_esq = LoadTextureFromImage(PORRE);

    Texture2D sapo_pulando_costas = LoadTextureFromImage(PULOC);
    Texture2D sapo_pulando_frente = LoadTextureFromImage(PULOF);
    Texture2D sapo_pulando_dir = LoadTextureFromImage(PULOD);
    Texture2D sapo_pulando_esq = LoadTextureFromImage(PULOE);

    init();

    while (!WindowShouldClose()) {
        float controle_de_tempo = GetFrameTime();

        ataques_sapo(controle_de_tempo);
        movement();
        sword_hitbox_check(controle_de_tempo);

        BeginDrawing();
        //
        ClearBackground(BLACK);

        DrawTexturePro(background, fonte, destino, origem, ang_rot, WHITE);

        barras_vida();

        DrawCircle(P.posicao.x, P.posicao.y, P.raio_do_player, BLUE);
        DrawCircle(S.posicao.x, S.posicao.y, S.raio_do_sapo, RED);

        if (S.porradao && S.duracao_porradao > 0) {
            DrawCircleLines(S.posicao.x, S.posicao.y, 2.5 * S.raio_do_sapo, ORANGE);
        }

        Texture2D sprite_atual;

        switch (P.dirAtual) {
            case FRENTE:
                if (P.frame == 0) sprite_atual = player_frente;
                else if (P.frame == 1) sprite_atual = player_frente_dir;
                else sprite_atual = player_frente_esq;
                break;

            case COSTAS:
                if (P.frame == 0) sprite_atual = player_costas;
                else if (P.frame == 1) sprite_atual = player_costas_dir;
                else sprite_atual = player_costas_esq;
                break;

            case DIREITA:
                if (P.frame == 0) sprite_atual = player_direita;
                else if (P.frame == 1) sprite_atual = player_direita_dir;
                else sprite_atual = player_direita_esq;
                break;

            case ESQUERDA:
                if (P.frame == 0) sprite_atual = player_esquerda;
                else if (P.frame == 1) sprite_atual = player_esquerda_dir;
                else sprite_atual = player_esquerda_esq;
                break;
        }

        DrawTexture(sprite_atual, P.posicao.x - sprite_atual.width / 2, P.posicao.y - sprite_atual.height / 2, WHITE);

        //
        EndDrawing();
    }

    UnloadTexture(background);

    UnloadTexture(player_frente);
    UnloadTexture(player_frente_dir);
    UnloadTexture(player_frente_esq);

    UnloadTexture(player_costas);
    UnloadTexture(player_costas_dir);
    UnloadTexture(player_costas_esq);

    UnloadTexture(player_direita);
    UnloadTexture(player_direita_dir);
    UnloadTexture(player_direita_esq);

    UnloadTexture(player_esquerda);
    UnloadTexture(player_esquerda_dir);
    UnloadTexture(player_esquerda_esq);

    UnloadTexture(sapo_IDLE_costas);
    UnloadTexture(sapo_IDLE_dir);
    UnloadTexture(sapo_IDLE_esq);
    UnloadTexture(sapo_IDLE_frente);

    UnloadTexture(sapo_linguada_costas);
    UnloadTexture(sapo_linguada_dir);
    UnloadTexture(sapo_linguada_esq);
    UnloadTexture(sapo_linguada_frente);

    UnloadTexture(sapo_porradao_costas);
    UnloadTexture(sapo_porradao_dir);
    UnloadTexture(sapo_porradao_esq);
    UnloadTexture(sapo_porradao_frente);

    UnloadTexture(sapo_pulando_costas);
    UnloadTexture(sapo_pulando_dir);
    UnloadTexture(sapo_pulando_esq);
    UnloadTexture(sapo_pulando_frente);

    CloseWindow();

    return 0;
}
