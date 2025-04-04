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
};

Player::~Player() {};

// Desenhar player (por enquanto um círculo)
void Player::DrawPlayer() {
    DrawTexture(playerNOW, x, y, WHITE);
}

// Nova colisao
bool Player::PointInQuad(Vector2 p, Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
    auto area = [](Vector2 p1, Vector2 p2, Vector2 p3) {
        return fabs((p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y) + p3.x*(p1.y - p2.y)) / 2.0f);
    };

    float quadArea = area(a, b, c) + area(a, c, d);
    float pointArea = area(p, a, b) + area(p, b, c) + area(p, c, d) + area(p, d, a);

    return fabs(quadArea - pointArea) < 0.01f;
}
bool Player::CollisionMesas() { // AJEITAR AQUI
    if ((57 <= x && x <= 354) && (490 <= y && y <= 495)) return true;
    else if ((575 <= x && x <= 865) && (487 <= y && y <= 492)) return true;     //table7

    else if ((150 <= x && x <= 500) && (165 <= y && y <= 170)) return true;
    else if ((740 <= x && x <= 1021)&& (163 <= y && y <= 168)) return true;     //table4

    else if ((110 <= x && x <= 445) && (270 <= y && y <= 275)) return true;
    else if ((664 <= x && x <= 999)&& (269 <= y && y <= 287)) return true;      //table5

    else if ((50  <= x && x <= 400) && (380 <= y && y <= 385)) return true;
    else if ((640 <= x && x <= 930) && (364 <= y && y <= 387)) return true;     //table6

    else return false;
}


// Atualizar posição do player
void Player::UpdatePlayer() { // AJEITAR AQUI

    float qtdMovX = 0;
    float qtdMovY = 0;

    Vector2 dir = { (float)sin(angle * DEG2RAD), -(float)cos(angle * DEG2RAD) };

    if (dash_t > 10) dash_t++;  // Se o timer do dash for maior que 10, o player terá que esperar o timer chegar a 150 para poder usá-lo de novo
    if (dash_t >= 150) dash_t = 0; // Reset do timer do dash

    if (IsKeyDown(KEY_W)) {
        playerNOW = playerUP;
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
    }
if (IsKeyDown(KEY_A)) {
        playerNOW = playerLEFT;
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))
        {
            x -= speed_dash;
            qtdMovX -= speed_dash;
            dash_t++;
        }
        else x -= speed;
        qtdMovX -= speed;
    }

    if (IsKeyDown(KEY_S)) {
        playerNOW = playerDOWN;
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
    }

    if (IsKeyDown(KEY_D)) {
        playerNOW = playerRIGHT;
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
            x += speed_dash;
            qtdMovX += speed_dash;
            dash_t++;
        }
        else {
            x += speed;
            qtdMovX += speed;
        }
    }
// Colisões com as bordas
    if (x <= 0) x = 0;

    if (x >= Hres - largura) x = Hres - largura;

    if (y <= 0) y = 0;

    if (y >= Vres - altura) y = Vres - altura;

    // Colisões com a parede da frente
    if (y + 100 <= ((6 * x) + 51542) / 433) y = (((6 * x) / 433) + (51542 / 433)) - 100;


    // Colisões com a parede lateral
    if (x <= (66646 - (106 * (y+100))) / 251) x = (66646 - (106 * (y+100))) / 251;


    // Colisoes com as mesas
    if (CollisionMesas()) {
        std::cout << "COLIDIU" << std::endl;
        x -= qtdMovX;
        y -= qtdMovY;
    }
};
