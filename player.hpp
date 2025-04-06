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
    int frameCounter, frameSpeed, currentFrame;
    int lastPos; // 0 - UP // 1 - DOWN // 2 - LEFT // 3 - RIGHT
    float vida;
    bool vivo;

    Texture2D playerUP, playerUP_R, playerUP_L;
    Texture2D playerDOWN, playerDOWN_R, playerDOWN_L;
    Texture2D playerRIGHT, playerRIGHT_L, playerRIGHT_R;
    Texture2D playerLEFT, playerLEFT_L, playerLEFT_R;
    Texture2D playerNOW;

    void DrawPlayer();
    bool CollisionMesas();
    void UpdatePlayer(int i);
    bool EntreMesas();
    Image playerUP_img, playerUP_L_img, playerUP_R_img;
    Image playerDOWN_img, playerDOWN_L_img, playerDOWN_R_img;
    Image playerRIGHT_img, playerRIGHT_L_img, playerRIGHT_R_img;
    Image playerLEFT_img, playerLEFT_L_img, playerLEFT_R_img;

    
};
