#include "player.hpp"
#include "mesaHW.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

#define angle 24.9547f


Player::Player() {
    largura = 47;
    altura = 126;
    speed = 5;
    speed_dash = 10;
    vida = 100.0f;
    vivo = true;
    ganhou = false;
};

Player::~Player() {};

// Desenhar player
void Player::DrawPlayer() {
    DrawTexture(playerNOW, x, y, WHITE);
}

bool Player::CollisionMesas() {return collide(x,y);}

void Player::UpdatePlayer(int i) {

    frameCounter++;

    float qtdMovX = 0;
    float qtdMovY = 0;

    Vector2 dir = { (float)sin(angle * DEG2RAD), -(float)cos(angle * DEG2RAD) };

    if (dash_t > 10) dash_t++;  // Se o timer do dash for maior que 10, o player terá que esperar o timer chegar a 150 para poder usá-lo de novo
    if (dash_t >= 150) dash_t = 0; // Reset do timer do dash



    // ============================== CIMA ================================ //
    if (IsKeyDown(KEY_W)) {

        lastPos = 0;
        // POSIÇÃO =============================================== //
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
            y += speed_dash * dir.y;
            x += speed_dash * dir.x;
            qtdMovX += speed_dash * dir.x;
            qtdMovY += speed_dash * dir.y;
            dash_t++;
        }
        else {
            y += dir.y * speed;
            x += dir.x * speed;
            qtdMovX += speed * dir.x;
            qtdMovY += speed * dir.y;
        }

        // SPRITE ================================================ //
        if (frameCounter >= 60/frameSpeed) {
            
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > 3) currentFrame = 0;

            if (currentFrame == 0) playerNOW = playerUP_L;
            else if (currentFrame == 1) playerNOW = playerUP;
            else if (currentFrame == 2) playerNOW = playerUP_R;
            else if (currentFrame == 3) playerNOW = playerUP;
        }
    }



    // ========================= ESQUERDA ======================== //
    if (IsKeyDown(KEY_A)) {
        
        lastPos = 2;
        // POSIÇÃO ======================================== //
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))
        {
            x -= speed_dash;
            qtdMovX -= speed_dash;
            dash_t++;
        }
        else x -= speed;
        qtdMovX -= speed;
    

        // SPRITE ================================================ //
        if (frameCounter >= 60/frameSpeed) {
                
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > 3) currentFrame = 0;

            if (currentFrame == 0) playerNOW = playerLEFT_L;
            else if (currentFrame == 1) playerNOW = playerLEFT;
            else if (currentFrame == 2) playerNOW = playerLEFT_R;
            else if (currentFrame == 3) playerNOW = playerLEFT;
        }

    }

    // =========================== BAIXO ============================= //
    if (IsKeyDown(KEY_S)) {
        lastPos = 1;
        // POSIÇÃO ===================================== //
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))
        {
            y -= dir.y * speed_dash;
            x -= dir.x * speed_dash;
            dash_t++;
            qtdMovX -= speed_dash * dir.x;
            qtdMovY -= speed_dash * dir.y;
        }
        else {
            y -= dir.y * speed;
            x -= dir.x * speed;
            qtdMovX -= speed * dir.x;
            qtdMovY -= speed * dir.y;
        }

        // SPRITE ================================================ //
        if (frameCounter >= 60/frameSpeed) {
            
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > 3) currentFrame = 0;

            if (currentFrame == 0) playerNOW = playerDOWN_L;
            else if (currentFrame == 1) playerNOW = playerDOWN;
            else if (currentFrame == 2) playerNOW = playerDOWN_R;
            else if (currentFrame == 3) playerNOW = playerDOWN;
        }
    }



    // ============================ DIREITA ================================= //
    if (IsKeyDown(KEY_D)) {
        lastPos = 3;
        // POSIÇÃO =============================================== //
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
            x += speed_dash;
            qtdMovX += speed_dash;
            dash_t++;
        }
        else {
            x += speed;
            qtdMovX += speed;
        }

        // SPRITE ================================================ //
        if (frameCounter >= 60/frameSpeed) {
            
            frameCounter = 0;
            currentFrame++;

            if (currentFrame > 3) currentFrame = 0;

            if (currentFrame == 0) playerNOW = playerRIGHT_L;
            else if (currentFrame == 1) playerNOW = playerRIGHT;
            else if (currentFrame == 2) playerNOW = playerRIGHT_R;
            else if (currentFrame == 3) playerNOW = playerRIGHT;
        }
    }
    // ===================================================================== //


    else {
        if (lastPos == 0) playerNOW = playerUP;
        else if (lastPos == 1) playerNOW = playerDOWN;
        else if (lastPos == 2) playerNOW = playerLEFT;
        else if (lastPos == 3) playerNOW = playerRIGHT;
    }

    // ================================= COLISÕES ======================================= //
    
    // Bordas
    if (x <= 0) x = 0;
    if (x >= Hres - largura) x = Hres - largura;
    if (y <= 0) y = 0;
    if (y >= Vres - altura) y = Vres - altura;

    // Parede da Frente
    if (y + 100 <= ((6 * x) + 51542) / 433) y = (((6 * x) / 433) + (51542 / 433)) - 100;

    // Parede Lateral
    if (x <= (66646 - (106 * (y+100))) / 251) x = (66646 - (106 * (y+100))) / 251;

    // Mesas
    if (CollisionMesas() && ((i == 0) || (i == 1) || (i == 2))) {
        x -= qtdMovX;
        y -= qtdMovY;
    }
    // ================================================================================== //

};

bool Player::EntreMesas() {
    if ((x <= ((-0.4739f * y) + 549.193f) || x >= ((-0.4785f * y) + 802.222f)) && (y >= 160.539f)) return true;
    else return false;
}
