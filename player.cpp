#include "player.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

#define angle 24.9547f
#define P_ATK_COOLDOWN 5

Player::Player() {
    largura = 47;
    altura = 126;
    speed = 5;
    speed_dash = 10;
    vida = 100.0f;
    vivo = true;
    ganhou = false;
    p_atk_timer = 0;;
};

Player::~Player() {};

// Desenhar player
void Player::DrawPlayer() {
    DrawTexture(playerNOW, x, y, WHITE);
}

bool Player::CollisionMesas() {
    if ((15 <= x && x <= 354) && (490 <= y && y <= 495)) return true;
    else if ((575 <= x && x <= 865) && (487 <= y && y <= 492)) return true;     

    else if ((150 <= x && x <= 500) && (165 <= y && y <= 170)) return true;
    else if ((740 <= x && x <= 1021) && (163 <= y && y <= 168)) return true;     

    else if ((110 <= x && x <= 445) && (270 <= y && y <= 275)) return true;
    else if ((664 <= x && x <= 999) && (269 <= y && y <= 287)) return true; 

    else if ((50  <= x && x <= 400) && (380 <= y && y <= 385)) return true;
    else if ((640 <= x && x <= 930) && (364 <= y && y <= 387)) return true;

    else if ((55 >= x) && (470 <= y && y <= 571)) return true; // Mesa Jailson

    else return false;
}

void Player::check_hitbox()
{
	if (IsKeyDown(KEY_P) && p_atk_timer == 0)
        {
                p_atk_timer += 0.8;
		//DrawCircle(x + 20,y + 50,50,RED); //hitbox em questão.
                //if ((S.posicaoSD.x - at_x)(S.posicaoSD.x - at_x) + (S.posicaoSD.y - at_y)(S.posicaoSD.y - at_y) <= 2500);
                //else if ((S.x - at1_x)(S.posicaoSD.x - at1_x) + (S.posicaoSD.y - at1_y)(S.posicaoSD.y - at1_y) <= 2500)
                //else if ((S.x - at2_x)(S.posicaoSD.x - at2_x) + (S.posicaoSD.y - at2_y)(S.posicaoSD.y - at2_y) <= 2500)

        }
        else if (p_atk_timer > 0) p_atk_timer += 0.8;
        if (p_atk_timer >= P_ATK_COOLDOWN) p_atk_timer = 0;
}

void Player::UpdatePlayer(int i) {

    frameCounter++;

    float qtdMovX = 0;
    float qtdMovY = 0;

    Vector2 dir = { (float)sin(angle * DEG2RAD), -(float)cos(angle * DEG2RAD) };

    if (dash_t > 10) dash_t++;  // Se o timer do dash for maior que 10, o player terá que esperar o timer chegar a 150 para poder usá-lo de novo
    if (dash_t >= 150) dash_t = 0; // Reset do timer do dash


    if (i != 5 && vivo == true) {
        // ============================== CIMA ================================ //
        if (IsKeyDown(KEY_W)) {
		sword_x = 0;
		sword_y = -5;
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
        else if (IsKeyDown(KEY_A)) {
            sword_x = -5;
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
        else if (IsKeyDown(KEY_S)) {
            sword_y = 5;
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
        else if (IsKeyDown(KEY_D)) {
            sword_x = 5;
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
	if (sword_x*sword_x == sword_y*sword_y && sword_x*sword_x == 25)
	{
		sword_x = (5.0/(1.4))*(sword_x/(abs(sword_x)));
		sword_y = (5.0/(1.4))*(sword_y/(abs(sword_y)));
	}
    }

    else {
        playerNOW = playerDOWN;
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
