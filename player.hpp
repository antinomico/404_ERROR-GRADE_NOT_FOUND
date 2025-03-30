#pragma once
#include "raylib.h"
#include "mesaHW.hpp"

class Player {
    
public:

	Player();

	~Player();

    float x, y;
    float largura;
    float altura;
    float speed;
    float speed_dash;
    int dash_t;
    Texture2D playerUP, playerDOWN, playerRIGHT, playerLEFT, playerNOW;

    void DrawPlayer();
    bool ColissionWithQuad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 pos);
    bool CollisionMesas(MesaHW &mesa);
    void UpdatePlayer(MesaHW &mesa);
    bool PointInQuad(Vector2 p, Vector2 a, Vector2 b, Vector2 c, Vector2 d);
    Image playerUP_img, playerDOWN_img, playerRIGHT_img, playerLEFT_img;
};