#include "raylib.h"
#include "boss.hpp"
#include "mesaHW.hpp"
#include "player.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

/*
Texto para iniciar a fase:

Agora xxxxx precisa enfrentar o terror das quintas-feiras: o laboratório de hardware!
Lembre de pegar a caixa de fios de Jailson para poder combater o boss!
*/


// FUNÇÕES ================= //
void Init();
void DesenhoPlayerMesas();
void DeterminarBackground();
void MudarEtapa();
void Etapas();
void Liberar();
void InitPlayer();
void InitCenario();
void VitoriaOuDerrota();
void GIFsBack();
// ========================== //




// VARIÁVEIS INICIAIS ============ //
chicote vec;
Texture2D background_SD;
Texture2D mesas_SD;
Texture2D mesaJailson;
Texture2D spritesheet_choque;
Texture2D background_SD_MapaK_Vazio;
Texture2D spritesheet_final;
Texture2D equacao;

Image background_SD_img;
Image mesas_SD_img;
Image mesaJailson_img;
Image background_SD_MapaK_Vazio_img;
Image equacao_img;

Rectangle sourceRecChoque;
Rectangle destRecChoque;

Rectangle sourceRecFinal;
Rectangle destRecFinal;

float angle_deg = 24.9547f;

int currentFrameChoque;
int frameCounterChoque;
int frameDelayChoque;

int currentFrameFinal;
int frameCounterFinal;
int frameDelayFinal;

// =============================== //




// INICIALIZAÇÃO DOS OBJETOS ======== //
BossSD boss;
Player player;
MesaHW mesa1,
       mesa2,
       mesa3,
       mesa4,
       mesa5,
       mesa6,
       mesa7;
// ================================= //




int main() {

        InitWindow(Hres, Vres, "Boss SD");
        SetTargetFPS(60);

        Init();

        while (!WindowShouldClose()) {

                player.UpdatePlayer(boss.etapa);

                GIFsBack();

                BeginDrawing();

                        ClearBackground(BLACK);

                        DeterminarBackground();
                        DesenhoPlayerMesas();
                        boss.DrawSD();
			//boss.Chicotada(player, &vec);
                        boss.AtaqueSD(player, &vec);
                        MudarEtapa();
                        Etapas();
                        VitoriaOuDerrota();

                        std::cout << "TIMER: " << boss.timer << std::endl;
                        std::cout << "ETAPA: " << boss.etapa << std::endl;

                        // Posição do player (tirar depois)
                        std::cout << "Posicao: " << player.x  << ", " << player.y << std::endl;

                EndDrawing();
        }

        Liberar();
        CloseWindow();

        return 0;
}


void Init() {

        InitPlayer();
        InitCenario();
	vec.reverse = 1;
	vec.cx = boss.positionSD.x;
	vec.cy = boss.positionSD.y;
	vec.dex = player.x;
	vec.dey = player.y;
	boss.timer_chicotada = 0;

}

void DesenhoPlayerMesas() {
        if (player.y <= mesa1.y) player.DrawPlayer();
        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa1.texture, mesa1.x, mesa1.y, WHITE);
        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa4.texture, mesa4.x, mesa4.y, WHITE);
        if (player.y > mesa1.y && player.y <= mesa2.y) player.DrawPlayer();

        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa2.texture, mesa2.x, mesa2.y, WHITE);
        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa5.texture, mesa5.x, mesa5.y, WHITE);
        if (player.y > mesa2.y && player.y <= mesa3.y) player.DrawPlayer();

        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa3.texture, mesa3.x, mesa3.y, WHITE);
        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa6.texture, mesa6.x, mesa6.y, WHITE);
        if (player.y > mesa3.y && player.y <= mesa7.y) player.DrawPlayer();

        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesa7.texture, mesa7.x, mesa7.y, WHITE);
        if (boss.etapa == 0 || boss.etapa == 1) DrawTexture(mesaJailson, 0, 492, WHITE);
        if (player.y >= mesa7.y) player.DrawPlayer();
}

void DeterminarBackground() {
        if (boss.etapa == 0 || boss.etapa == 1 || boss.etapa == 3) DrawTexture(background_SD, 0, 0, WHITE); // Fundo normal
                      
        else if (boss.etapa == 2)  DrawTexturePro(spritesheet_choque, sourceRecChoque, destRecChoque, {0, 0}, 0.0f, WHITE);

        else if (boss.etapa == 4) DrawTexture(background_SD_MapaK_Vazio, 0, 0, WHITE);

        
        else if (boss.etapa == 5) DrawTexturePro(spritesheet_final, sourceRecFinal, destRecFinal, {0, 0}, 0.0f, WHITE);


}

void MudarEtapa() {
        // CHICOTADA (1min) -> CONTAGEM
        if (boss.timer >= 500 && boss.etapa == 0) {
                boss.etapa = 1;
                boss.timer = 0;
        }
        // CONTAGEM (3seg) -> CHOQUE
        if (boss.timer >= 240 && boss.etapa == 1) {
                boss.etapa = 2;
                boss.timer = 0;
        }
        // CHOQUE (5seg) -> SEM MESAS
        if (boss.timer >= 300 && boss.etapa == 2) {
                boss.etapa = 3;
                boss.timer = 0;
        }
        // SEM MESAS (5seg) -> MAPA K VAZIO
        if (boss.timer >= 300 && boss.etapa == 3) {
                boss.etapa = 4;
                boss.timer = 0;
        }
        // MAPA K VAZIO (15seg) -> MAPA K PREENCHIDO
        if (boss.timer >= 900 && boss.etapa == 4) {
                boss.etapa = 5;
                boss.timer = 0;
        }
                
}

void Etapas() {
        // Choque
        if (boss.etapa == 2) {
                if (player.EntreMesas()) {
                        player.vivo = false;
                }
        }

        if (boss.etapa == 3) {
                if (boss.timer < 30) {
                        
                }
        }

        // Fim do Mapa K
        if (boss.etapa == 5) {
                // Colocar áudio de vitória

                // Primeiro 1
                if ((player.y <= ((0.0488f * player.x) + 186.502f)) &&
                    (player.y >= ((0.02765f * player.x) + 109.907f)) &&
                    (player.x >= ((-0.20181f * player.y) + 538.26)) &&
                    (player.x <= ((-0.2472f * player.y) + 716.59))) {
                        
                        player.ganhou = 1;
                }

                // Segundo 1
                else if ((player.x >= ((-0.16984f * player.y) + 911.332f)) &&
                         (player.y >= ((0.0267f * player.x) + 200.941f)) &&
                         (player.y <= ((0.05027f * player.x) + 289.944f))) {

                        player.ganhou = 1;
                }

                // Terceiro 1
                else if ((player.x >= ((-0.30191f * player.y) + 370.339f)) &&
                         (player.x <= ((-0.28146f * player.y) + 552.163f)) &&
                         (player.y >= 323.734f) &&
                         (player.y <= ((0.06845f * player.x) + 411.675f))) {
                        
                        player.ganhou = 1;
                }

                // Quarto 1
                else if ((player.y >= ((-0.008635f * player.x) + 469.671f)) &&
                         (player.x >= ((-0.21909f * player.y) + 723.879f)) &&
                         (player.x <= ((-0.19657f * player.y) + 928.833))) {
                                
                        player.ganhou = 1;
                }

                // Colocar áudio de derrota
                else {
                        player.vivo = false;
                }


        }
        
}

void Liberar() {
        UnloadTexture(spritesheet_choque);
        UnloadTexture(background_SD);
        UnloadTexture(mesaJailson);
        UnloadTexture(player.playerUP);
        UnloadTexture(player.playerUP_L);
        UnloadTexture(player.playerUP_R);
        UnloadTexture(player.playerDOWN);
        UnloadTexture(player.playerDOWN_L);
        UnloadTexture(player.playerDOWN_R);
        UnloadTexture(player.playerRIGHT);
        UnloadTexture(player.playerRIGHT_L);
        UnloadTexture(player.playerRIGHT_R);
        UnloadTexture(player.playerLEFT);
        UnloadTexture(player.playerLEFT_L);
        UnloadTexture(player.playerLEFT_R);
        UnloadTexture(mesa1.texture);
        UnloadTexture(mesa2.texture);
        UnloadTexture(mesa3.texture);
        UnloadTexture(mesa4.texture);
        UnloadTexture(mesa5.texture);
        UnloadTexture(mesa6.texture);
        UnloadTexture(mesa7.texture);
        UnloadTexture(spritesheet_final);
        UnloadTexture(background_SD_MapaK_Vazio);
        UnloadImage(background_SD_MapaK_Vazio_img);


        UnloadImage(background_SD_img);
        UnloadImage(mesaJailson_img);
        UnloadImage(player.playerUP_img);
        UnloadImage(player.playerUP_L_img);
        UnloadImage(player.playerUP_R_img);
        UnloadImage(player.playerDOWN_img);
        UnloadImage(player.playerDOWN_L_img);
        UnloadImage(player.playerDOWN_R_img);
        UnloadImage(player.playerRIGHT_img);
        UnloadImage(player.playerRIGHT_L_img);
        UnloadImage(player.playerRIGHT_R_img);
        UnloadImage(player.playerLEFT_img);
        UnloadImage(player.playerLEFT_L_img);
        UnloadImage(player.playerLEFT_R_img);
        UnloadImage(mesa1.img);
        UnloadImage(mesa2.img);
        UnloadImage(mesa3.img);
        UnloadImage(mesa4.img);
        UnloadImage(mesa5.img);
        UnloadImage(mesa6.img);
        UnloadImage(mesa7.img);
}

void InitPlayer() {

        // VARIÁVEIS ================= //
        player.x = Hres / 2;
        player.y = Vres / 2;
        player.dash_t = 0;
        player.frameCounter = 0;
        player.currentFrame = 0;
        player.frameSpeed = 8;
        player.lastPos = 0;
        // ============================ //


        // SPRITES =========================================================== //

        // Player andando para cima
        player.playerUP_img = LoadImage("assets/playercima.png");
        player.playerUP_L_img = LoadImage("assets/playercima_left.png");
        player.playerUP_R_img = LoadImage("assets/playercima_right.png");

        // Player andando para baixo
        player.playerDOWN_img = LoadImage("assets/playerbaixo.png");
        player.playerDOWN_L_img = LoadImage("assets/playerbaixo_left.png");
        player.playerDOWN_R_img = LoadImage("assets/playerbaixo_right.png");

        // Player andando para direita
        player.playerRIGHT_img = LoadImage("assets/playerdir.png");
        player.playerRIGHT_L_img = LoadImage("assets/playerdir_left.png");
        player.playerRIGHT_R_img = LoadImage("assets/playerdir_right.png");

        // Player andando para esquerda
        player.playerLEFT_img = LoadImage("assets/playeresq.png");
        player.playerLEFT_L_img = LoadImage("assets/playeresq_left.png");
        player.playerLEFT_R_img = LoadImage("assets/playeresq_right.png");


        // Redimensionamento das imagens
        ImageResize(&player.playerUP_img, 47, 126);
        ImageResize(&player.playerUP_L_img, 60, 126);
        ImageResize(&player.playerUP_R_img, 60, 126);

        ImageResize(&player.playerDOWN_img, 47, 126);
        ImageResize(&player.playerDOWN_L_img, 60, 126);
        ImageResize(&player.playerDOWN_R_img, 60, 126);

        ImageResize(&player.playerLEFT_img, 47, 126);
        ImageResize(&player.playerLEFT_L_img, 60, 126);
        ImageResize(&player.playerLEFT_R_img, 60, 126);

        ImageResize(&player.playerRIGHT_img, 47, 126);
        ImageResize(&player.playerRIGHT_L_img, 60, 126);
        ImageResize(&player.playerRIGHT_R_img, 60, 126);

        // Carregamento das texturas
        player.playerUP = LoadTextureFromImage(player.playerUP_img);
        player.playerUP_L = LoadTextureFromImage(player.playerUP_L_img);
        player.playerUP_R = LoadTextureFromImage(player.playerUP_R_img);

        player.playerDOWN = LoadTextureFromImage(player.playerDOWN_img);
        player.playerDOWN_L = LoadTextureFromImage(player.playerDOWN_L_img);
        player.playerDOWN_R = LoadTextureFromImage(player.playerDOWN_R_img);

        player.playerRIGHT = LoadTextureFromImage(player.playerRIGHT_img);
        player.playerRIGHT_L = LoadTextureFromImage(player.playerRIGHT_L_img);
        player.playerRIGHT_R = LoadTextureFromImage(player.playerRIGHT_R_img);

        player.playerLEFT = LoadTextureFromImage(player.playerLEFT_img);
        player.playerLEFT_L = LoadTextureFromImage(player.playerLEFT_L_img);
        player.playerLEFT_R = LoadTextureFromImage(player.playerLEFT_R_img);

        // ====================================================================== //
}

void InitCenario() {

        // BACKGROUND =========================================== //
        background_SD_img = LoadImage("assets/backSD.png");
        ImageResize(&background_SD_img, Hres, Vres);
        background_SD = LoadTextureFromImage(background_SD_img);

        background_SD_MapaK_Vazio_img = LoadImage("assets/backSDMapaVazio.png");
        ImageResize(&background_SD_MapaK_Vazio_img, Hres, Vres);
        background_SD_MapaK_Vazio = LoadTextureFromImage(background_SD_MapaK_Vazio_img);

        spritesheet_choque = LoadTexture("assets/backSDchoque.png");
        sourceRecChoque = { 0.0f, 0.0f, 540.0f, 360.0f };
        destRecChoque = { 0.0f, 0.0f, Hres, Vres };
        currentFrameChoque = 0;
        frameCounterChoque = 0;
        frameDelayChoque = 15;

        
        spritesheet_final = LoadTexture("assets/backSDfinal.png");
        sourceRecFinal = { 0.0f, 0.0f, 540.0f, 360.0f };
        destRecFinal = { 0.0f, 0.0f, Hres, Vres };
        currentFrameFinal = 0;
        frameCounterFinal = 0;
        frameDelayFinal = 15;

        equacao_img = LoadImage("assets/equacao.png");
        ImageResize(&equacao_img, Hres, Vres);
        equacao = LoadTextureFromImage(equacao_img);
        // ====================================================== //


        // MESA JAILSON ========================================= //
        mesaJailson_img = LoadImage("assets/mesaJailson.png");
        mesaJailson = LoadTextureFromImage(mesaJailson_img);
        mesaJailson.width *= 2;
        mesaJailson.height *= 2;
        // ====================================================== //


        // MESAS HW ============================================= //
        mesa1.texture = LoadTextureFromImage(mesa1.img);
        mesa1.texture.width *= 2;
        mesa1.texture.height *= 2;
        mesa1.x = 156;
        mesa1.y = 168;

        mesa2.texture = LoadTextureFromImage(mesa2.img);
        mesa2.texture.width *= 2;
        mesa2.texture.height *= 2;
        mesa2.x = 106;
        mesa2.y = 274;

        mesa3.texture = LoadTextureFromImage(mesa3.img);
        mesa3.texture.width *= 2;
        mesa3.texture.height *= 2;
        mesa3.x = 56;
        mesa3.y = 382;

        mesa4.texture = LoadTextureFromImage(mesa4.img);
        mesa4.texture.width *= 2;
        mesa4.texture.height *= 2;
        mesa4.x = 726;
        mesa4.y = 168;

        mesa5.texture = LoadTextureFromImage(mesa5.img);
        mesa5.texture.width *= 2;
        mesa5.texture.height *= 2;
        mesa5.x = 676;
        mesa5.y = 274;

        mesa6.texture = LoadTextureFromImage(mesa6.img);
        mesa6.texture.width *= 2;
        mesa6.texture.height *= 2;
        mesa6.x = 626;
        mesa6.y = 382;

        mesa7.texture = LoadTextureFromImage(mesa7.img);
        mesa7.texture.width *= 2;
        mesa7.texture.height *= 2;
        mesa7.x = 576;
        mesa7.y = 492;

        // ===================================================== //
}

void VitoriaOuDerrota() {
        if (player.vivo == false) {
                // Ir para tela de derrota
                DrawText("MORREU", 360, 100, 30, RED); // Para debug
        }

        if (player.ganhou == true) {
                // Ir para tela de vitória
                DrawText("GANHOU", 360, 100, 30, RED); // Para debug
        }
}

void GIFsBack() {
        frameCounterChoque++;
        if (frameCounterChoque >= frameDelayChoque) {
                frameCounterChoque = 0;
                currentFrameChoque = (currentFrameChoque + 1) % 2;
                sourceRecChoque.x = (float)(currentFrameChoque * 540.0f);
        }
        boss.timer++;


        frameCounterFinal++;
        if (frameCounterFinal > frameDelayFinal) {
                frameCounterFinal = 0;
                currentFrameFinal = (currentFrameFinal + 1) % 2;
                sourceRecFinal.x = (float)(currentFrameFinal * 540.0f); 
        }

        
}
