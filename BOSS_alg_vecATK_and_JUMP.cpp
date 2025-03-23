#include "raylib.h"
#include <cmath>
#include <stdio.h>

#define Hres 1080
#define Vres 720

#define CENTER_x Hres/2
#define CENTER_y Vres/2

#define inicio_player_x 540
#define inicio_player_y 630

#define ATK_COOLDOWN_vec 1

//-----------------------------------------------------------//

struct coords {
    float x;
    float y;
}; typedef struct coords coords;

struct Player {
    coords posicao;
    float raio_do_player = 20.0f;
    int vida_jogador = 100;

    bool morto = false;
}; typedef struct Player player; player P;

struct Sapo {
    coords posicao;
    coords posicao_inicial;
    coords posicao_do_pulo;

    bool linguada = false;
    bool pulando = false;
    bool porradao = false;
    bool reduzir_linguadas = true;
    bool tempo_antes_de_pular = false;
    bool tempo_antes_do_porradao = false;
    bool tempo_antes_da_linguada = true;

    bool dano_porradao_aplicado = false;
    bool dano_de_linguada_aplicado = false;

    int quantidade_de_linguadas = 5;
    int linguadas_restantes;
    int vida_boss = 100;

    float cooldown_ataque = 0.1;
    float acompanhar_cd_atk = 0.0;

    float cooldown_antes_de_pular = 2.0;
    float acompanhar_cd_pulo = 0.0;

    float cooldown_antes_do_porradao = 2.0;
    float acompanhar_cd_porradao = 0.0;

    float cooldown_antes_da_linguada = 2.0;
    float acompanhar_cd_antes_da_linguada = 0.0;

    float velocidade_do_pulo = 1500.0;
    float raio_do_sapo = 40.0;
    float altura_do_pulo = 100.0;

    float duracao_do_pulo = 0.0;
    float duracao_porradao = 0.0;

}; typedef struct Sapo sapo; sapo S;

typedef struct {
    float cx;
    float cy;
    float dex;
    float dey;
    int reverse;
} weapon_1; weapon_1 vec;

int dash_t;
int ATK1_COOLDOWNt;
int it;

//-----------------------------------------------------------//

void init()
{
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

//-----------------------------------------------------------//

void movement()
{
    if (dash_t > 10) dash_t++;				                //timer do dash, ele é empregado de modo que o jogador não possa ficar usando o dash indefinidamente
    if (dash_t >= 150) dash_t = 0;			                //se o dash_timer for maior que o intervalo de tempo de espera, resete ele, o jogador pode usar o dash 

    if (IsKeyDown(KEY_W))
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((P.posicao.y - P.raio_do_player - 20) < 50) P.posicao.y = 50 + P.raio_do_player;

            else P.posicao.y -= 20;

            dash_t++;
        }

        else if ((P.posicao.y - P.raio_do_player - 4) > 50) P.posicao.y -= 4;
    }

    if (IsKeyDown(KEY_A))
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((P.posicao.x - P.raio_do_player - 20) < 0) P.posicao.x = P.raio_do_player;

            else P.posicao.x -= 20;

            dash_t++;
        }

        else if ((P.posicao.x - P.raio_do_player - 4) > 0) P.posicao.x -= 4;;
    }

    if (IsKeyDown(KEY_S))
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((Vres - P.posicao.y - P.raio_do_player) < 20) P.posicao.y += (Vres - P.posicao.y - P.raio_do_player);

            else P.posicao.y += 20;

            dash_t++;
        }

        else if ((P.posicao.y + P.raio_do_player + 4) < Vres) P.posicao.y += 4;
    }

    if (IsKeyDown(KEY_D))
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((Hres - P.posicao.x - P.raio_do_player) < 20) P.posicao.x += (Hres - P.posicao.x - P.raio_do_player);

            else P.posicao.x += 20;

            dash_t++;
        }

        else if ((P.posicao.x + P.raio_do_player + 4) < Hres) P.posicao.x += 4;
    }
}

//-----------------------------------------------------------//

void vectoratk()
{
    float dx = vec.dex - S.posicao.x;
    float dy = vec.dey - S.posicao.y;

    float hitbox = 20.0;
    float distancia_colisao = sqrt(pow(vec.cx - P.posicao.x, 2) + pow(vec.cy - P.posicao.y, 2));

    if ((distancia_colisao <= hitbox) && (S.dano_de_linguada_aplicado == false)) {
        P.vida_jogador -= 12;

        if (P.vida_jogador <= 0) {
            P.vida_jogador = 0;

            P.morto = true;
        }

        S.dano_de_linguada_aplicado = true;

        vec.reverse = 1;
    }

    DrawLine(S.posicao.x, S.posicao.y, vec.cx, vec.cy, YELLOW);

    if (vec.reverse == 0)
    {
        float mod = 0.01 * sqrt(dx * dx + dy * dy);
        vec.cx += dx / mod;
        vec.cy += dy / mod;
        if (sqrt((vec.cx - S.posicao.x) * (vec.cx - S.posicao.x) + (vec.cy - S.posicao.y) * (vec.cy - S.posicao.y)) >= sqrt(dx * dx + dy * dy)) {
            vec.reverse = 1;
            float distancia = sqrt(pow(P.posicao.x - vec.dex, 2) + pow(P.posicao.y - vec.dey, 2));
        }
    }
    else
    {
        float mod = 0.06 * sqrt(dx * dx + dy * dy);
        vec.cx -= dx / mod;
        vec.cy -= dy / mod;

        if ((vec.dex > S.posicao.x && vec.dey > S.posicao.y) && (vec.cx <= S.posicao.x || vec.cy <= S.posicao.y)) {
            vec.reverse = 0;
            S.linguadas_restantes--;it = -1;
            S.dano_de_linguada_aplicado = false;
        }
        else if ((vec.dex > S.posicao.x && vec.dey < S.posicao.y) && (vec.cx <= S.posicao.x || vec.cy >= S.posicao.y)) {
            vec.reverse = 0;
            S.linguadas_restantes--;it = -1;
            S.dano_de_linguada_aplicado = false;
        }
        else if ((vec.dex  < S.posicao.x && vec.dey > S.posicao.y) && (vec.cx >= S.posicao.x || vec.cy <= S.posicao.y)) {
            vec.reverse = 0;
            S.linguadas_restantes--;it = -1;
            S.dano_de_linguada_aplicado = false;
        }
        else if ((vec.dex < S.posicao.x && vec.dey < S.posicao.y) && (vec.cx >= S.posicao.x || vec.cy >= S.posicao.y)) {
            vec.reverse = 0;
            S.linguadas_restantes--; it = -1;
            S.dano_de_linguada_aplicado = false;
        }
    }
}

//-----------------------------------------------------------//

void ataques_sapo(float controle_de_tempo) //mudar isso, a função ta muito grande e deve ser modularizada de modo a facilitar a legibilidade do codigo.
{

    //---------------------- LINGUADA ----------------------//

    if (S.tempo_antes_da_linguada == true) {
        S.acompanhar_cd_antes_da_linguada -= controle_de_tempo;

        if (S.acompanhar_cd_antes_da_linguada <= 0.0) {
            S.tempo_antes_da_linguada = false;
            S.linguada = true;
            S.acompanhar_cd_atk = S.cooldown_ataque;
        }
    }

    if (S.linguada == true) {
        if (S.linguadas_restantes <= 0) {
            S.linguada = false;
            S.tempo_antes_de_pular = true;
            S.acompanhar_cd_pulo = S.cooldown_antes_de_pular;
        }

        else {
            if (it == 50)
            {
                vec.cx = (S.posicao.x);
                vec.cy = (S.posicao.y);
                vec.dex = (P.posicao.x);
                vec.dey = (P.posicao.y);
            }
            else if (it > 50)
            {
                if (S.posicao.y == P.posicao.y) S.posicao.y += 1;
                if (S.posicao.x == P.posicao.x) S.posicao.x += 1;
                vectoratk();
            }
            it++;
        }
    }


    //------------------------ PULO ------------------------//

    if (S.tempo_antes_de_pular == true) {
        S.acompanhar_cd_pulo -= controle_de_tempo;

        if (S.acompanhar_cd_pulo <= 0.0) {
            S.tempo_antes_de_pular = false;
            S.pulando = true;

            S.posicao_do_pulo = P.posicao;
            S.posicao_inicial = S.posicao;

            S.duracao_do_pulo = 0.0;
        }

    }

    if (S.pulando == true) {
        S.duracao_do_pulo += controle_de_tempo * 1.5;

        float fator_mult = S.duracao_do_pulo / 0.7;

        if (fator_mult > 1.0) {
            fator_mult = 1.0;
        }

        // EIXO X:
        S.posicao.x = S.posicao_inicial.x + (S.posicao_do_pulo.x - S.posicao_inicial.x) * fator_mult;

        // EIXO Y:
        float altura = -4 * pow((fator_mult - 0.5), 2) + 1;

        S.posicao.y = S.posicao_inicial.y - (altura * S.altura_do_pulo) + (S.posicao_do_pulo.y - S.posicao_inicial.y) * fator_mult;

        if (fator_mult >= 1.0) { // garantir que vai parar na posição certa
            S.posicao.y = S.posicao_do_pulo.y;

            S.pulando = false;
            S.tempo_antes_do_porradao = true;

            S.acompanhar_cd_porradao = S.cooldown_antes_do_porradao;

            // Dano de queda

            float distancia = sqrt(pow(P.posicao.x - S.posicao.x, 2) + pow(P.posicao.y - S.posicao.y, 2));

            if (distancia <= S.raio_do_sapo) {
                P.vida_jogador -= 40;

                if (P.vida_jogador < 0) {
                    P.vida_jogador = 0;
                    P.morto = true;
                }
            }
        }
    }

    //---------------------- PORRADÃO ----------------------//
    if (S.tempo_antes_do_porradao == true) {
        S.acompanhar_cd_porradao -= controle_de_tempo;

        if (S.acompanhar_cd_porradao <= 0.0) {
            S.tempo_antes_do_porradao = false;
            S.porradao = true;
            S.duracao_porradao = 0.3;
        }
    }

    if (S.porradao) {
        S.duracao_porradao -= controle_de_tempo;

        if (S.duracao_porradao > 0.0f) {

            if (S.dano_porradao_aplicado == false) {
                float distancia = sqrt(pow(P.posicao.x - S.posicao.x, 2) + pow(P.posicao.y - S.posicao.y, 2));

                if (distancia + P.raio_do_player <= 3.5 * S.raio_do_sapo) {
                    P.vida_jogador -= 25;

                    if (P.vida_jogador < 0) {
                        P.vida_jogador = 0;
                        P.morto = true;
                    }
                }

                S.dano_porradao_aplicado = true;
            }
        }

        else {
            S.porradao = false;
            S.tempo_antes_da_linguada = true;

            S.acompanhar_cd_antes_da_linguada = S.cooldown_antes_da_linguada;

            S.dano_porradao_aplicado = false;

            if (S.reduzir_linguadas == true) {
                S.quantidade_de_linguadas--;

                S.cooldown_antes_da_linguada -= 0.1;
                S.cooldown_antes_do_porradao -= 0.1;
                S.cooldown_antes_de_pular -= 0.1;

                if (S.quantidade_de_linguadas < 1) {
                    S.quantidade_de_linguadas = 1;

                    S.cooldown_antes_da_linguada = 1.5;
                    S.cooldown_antes_do_porradao = 1.5;
                    S.cooldown_antes_de_pular = 1.5;

                    S.reduzir_linguadas = false;
                }
            }

            S.linguadas_restantes = S.quantidade_de_linguadas;
        }
    }
}

//-----------------------------------------------------------//

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

void acompanhar_cd() {
    if (S.tempo_antes_de_pular) {
        DrawText("PULO CARREGANDO", 20, 680, 20, WHITE);
    }

    if (S.tempo_antes_do_porradao) {
        DrawText("PORRADÃO CARREGANDO", 20, 680, 20, WHITE);
    }

    if (S.tempo_antes_da_linguada) {
        DrawText("LINGUADA CARREGANDO", 20, 680, 20, WHITE);
    }

    if (P.morto) {
        DrawText("MORREU", 500, 20, 20, WHITE);
    }
}

//-----------------------------------------------------------//

int main() {
    InitWindow(Hres, Vres, "sapo");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) {
        float controle_de_tempo = GetFrameTime();

        ataques_sapo(controle_de_tempo);
        movement();

        BeginDrawing();
        //
        ClearBackground(BLACK);

        barras_vida();
        acompanhar_cd();

        DrawCircle(P.posicao.x, P.posicao.y, P.raio_do_player, BLUE);
        DrawCircle(S.posicao.x, S.posicao.y, S.raio_do_sapo, RED);

        if (S.porradao && S.duracao_porradao > 0) {
            DrawCircleLines(S.posicao.x, S.posicao.y, 2.5 * S.raio_do_sapo, ORANGE);
        }

        //
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
