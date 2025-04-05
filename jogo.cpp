#include "raylib.h"
#include "boss.hpp"
#include "mesaHW.hpp"
#include "player.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720


// VARIÁVEIS INICIAIS ============ //
Image background_SD_img;
Texture2D background_SD;
Image mesas_SD_img;
Texture2D mesas_SD;
Image mesaJailson_img;
Texture2D mesaJailson;

float angle_deg = 24.9547f;

int BackGroundCourrentFrame = 0;
int BAckGroundFrameSpeed = 1;
int BackGroundFramesCounter = 0;
int BackgroundX = 0;
int BackgroundY = 0;
Rectangle BackgroundFrameRec = { 0.0f, 0.0f, (float)1080/2, (float)720 };
Vector2 BackgroundPosition =  {BackgroundX, BackgroundY};

Texture2D spritesheet_choque;
Rectangle sourceRec;
Rectangle destRec;
int currentFrame;
int frameCounter;
int frameDelay;
// =============================== //



// INICIALIZAÇÃO DOS OBJETOS ======== //
BossSD boss;
Player player;
MesaHW mesa1({180, 212}),
       mesa2({133, 314}),
       mesa3({83, 419}),
       mesa4({35, 531}),
       mesa5({676, 274}),
       mesa6({626, 382}),
       mesa7({576, 492});
// ================================= //
    



void init() {

        // VARIÁVEIS DO PLAYER ======== //
        player.x = Hres / 2;
        player.y = Vres / 2;
        player.dash_t = 0;
        player.frameCounter = 0;
        player.currentFrame = 0;
        player.frameSpeed = 8;
        player.lastPos = 0;
        // ============================ //


        // BACKGROUND =========================================== //
        background_SD_img = LoadImage("assets/backSD.png");
        ImageResize(&background_SD_img, Hres, Vres);
        background_SD = LoadTextureFromImage(background_SD_img);

        spritesheet_choque = LoadTexture("assets/backSDchoque.png");
        sourceRec = { 0.0f, 0.0f, 540.0f, 360.0f };
        destRec = { 0.0f, 0.0f, Hres, Vres };
        currentFrame = 0;
        frameCounter = 0;
        frameDelay = 15;
        // ====================================================== //


        // MESA JAILSON ========================================= //
        mesaJailson_img = LoadImage("assets/mesaJailson.png");
        mesaJailson = LoadTextureFromImage(mesaJailson_img);
        mesaJailson.width *= 2;
        mesaJailson.height *= 2;
        // ====================================================== //



        // SPRITES DO PLAYER ============================================= //

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



        // MESAS HW ----------------------------------------- //
        mesa1.texture = LoadTextureFromImage(mesa1.img);
        mesa1.texture.width *= 2;
        mesa1.texture.height *= 2;
        mesa1.x = 156;
        mesa1.y = 168;

        mesa2.texture = LoadTextureFromImage(mesa1.img);
        mesa2.texture.width *= 2;
        mesa2.texture.height *= 2;
        mesa2.x = 106;
        mesa2.y = 274;

        mesa3.texture = LoadTextureFromImage(mesa1.img);
        mesa3.texture.width *= 2;
        mesa3.texture.height *= 2;
        mesa3.x = 56;
        mesa3.y = 382;

        mesa4.texture = LoadTextureFromImage(mesa1.img);
        mesa4.texture.width *= 2;
        mesa4.texture.height *= 2;
        mesa4.x = 726;
        mesa4.y = 168;

        mesa5.texture = LoadTextureFromImage(mesa1.img);
        mesa5.texture.width *= 2;
        mesa5.texture.height *= 2;
        mesa5.x = 676;
        mesa5.y = 274;

        mesa6.texture = LoadTextureFromImage(mesa1.img);
        mesa6.texture.width *= 2;
        mesa6.texture.height *= 2;
        mesa6.x = 626;
        mesa6.y = 382;

        mesa7.texture = LoadTextureFromImage(mesa1.img);
        mesa7.texture.width *= 2;
        mesa7.texture.height *= 2;
        mesa7.x = 576;
        mesa7.y = 492;

        // ------------------------------------------------------ //
}


int main() {

        InitWindow(Hres, Vres, "Boss SD");
        SetTargetFPS(60);

        init();

        while (!WindowShouldClose()) {

                player.UpdatePlayer(boss.fase);

                frameCounter++;
                if (frameCounter >= frameDelay) {
                        frameCounter = 0;
                        currentFrame = (currentFrame + 1) % 2;
                        sourceRec.x = (float)(currentFrame * 540.0f);
                }
                boss.timer++;

                BeginDrawing();

                        ClearBackground(BLACK);

                        

                        // DETERMINAR BACKGROUND ====================================================== //
                        if (boss.fase == 0 || boss.fase == 1 || boss.fase == 3) DrawTexture(background_SD, 0, 0, WHITE); // Fundo normal

                        /*
                        else if (boss.fase == 2) { // Fundo choque computadores
                                Texture2D Background = LoadTexture("assets/backSDChoque.png");
                                if (BackGroundFramesCounter >= (60/BAckGroundFrameSpeed)){
                                        BackGroundFramesCounter = 0;
                                        BackGroundCourrentFrame++;
                                        if (BackGroundCourrentFrame > 1){
                                                BackGroundCourrentFrame = 0;
                                        }

                                        BackgroundFrameRec.x = (float)BackGroundCourrentFrame * ((float)(1080/2));
                                }
                                DrawTextureRec(Background, BackgroundFrameRec, BackgroundPosition, WHITE);
                        
                                
                                
                        }
                        */
                      
                        else if (boss.fase == 2) {
                                DrawTexturePro(spritesheet_choque, sourceRec, destRec, {0, 0}, 0.0f, WHITE);
                        }
                        // 4 - Mapa K vazio
                        // 5 - Mapa K preenchido

                        // =========================================================================== //






                        // DETERMINANDO A ORDEM COM A QUAL DEVEMOS DESENHAR O PLAYER ========= //
                        if (player.y <= mesa1.y) player.DrawPlayer();
                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa1.texture, mesa1.x, mesa1.y, WHITE);
                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa4.texture, mesa4.x, mesa4.y, WHITE);
                        if (player.y > mesa1.y && player.y <= mesa2.y) player.DrawPlayer();

                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa2.texture, mesa2.x, mesa2.y, WHITE);
                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa5.texture, mesa5.x, mesa5.y, WHITE);
                        if (player.y > mesa2.y && player.y <= mesa3.y) player.DrawPlayer();

                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa3.texture, mesa3.x, mesa3.y, WHITE);
                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa6.texture, mesa6.x, mesa6.y, WHITE);
                        if (player.y > mesa3.y && player.y <= mesa7.y) player.DrawPlayer();

                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesa7.texture, mesa7.x, mesa7.y, WHITE);
                        if (boss.fase == 0 || boss.fase == 1) DrawTexture(mesaJailson, 0, 492, WHITE);
                        if (player.y >= mesa7.y) player.DrawPlayer();
                        // ================================================================= //



                        boss.DrawSD();


                        boss.AtaqueSD();




                        // MUDANÇA DE ETAPA DA FASE ===================================================== //

                        // CHICOTADA (1min)
                        if (boss.timer >= 3600 && boss.fase == 0) {
                                boss.fase = 1;
                                boss.timer = 0;
                        }
                        // CONTAGEM (3seg)
                        if (boss.timer >= 240 && boss.fase == 1) {
                                boss.fase = 2;
                                boss.timer = 0;
                        }
                        // CHOQUE (5seg)
                        if (boss.timer >= 300 && boss.fase == 2) {
                                boss.fase = 3;
                                boss.timer = 0;
                        }
                        // MESAS VAZIAS (20seg)
                        if (boss.timer >= 600 && boss.fase == 3) {

                        }

                        // 15 segundos mostrando a equação + 5 segundos mostrando Mapa K
                        if (boss.timer >= 1200 && boss.fase == 2) {
                                /*

                                se o player estiver em lugar seguro e com vida maior que 0 -> tela de vitória
                                se o player estiver em lugar inseguro ou com vida menor que 0 -> tela de derrota

                                */
                        }
                        //=============================================================================== //



                        // Posição do player (tirar depois)
                        std::cout << "Posicao: " << player.x  << ", " << player.y << std::endl;

                EndDrawing();
        }

        UnloadTexture(spritesheet_choque);
        CloseWindow();

        return 0;
}
