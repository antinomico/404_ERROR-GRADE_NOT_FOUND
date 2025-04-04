#include "raylib.h"
#include "movement.hpp"
#include "globals.hpp"
#include <stdio.h>
#include <cmath>

void movement()
{
    if (dash_t > 10) dash_t++;                                          //timer do dash, ele é empregado de modo que o jogador não possa ficar usando o dash indefinidamente
    if (dash_t >= 150) dash_t = 0;                                      //se o dash_timer for maior que o intervalo de tempo de espera, resete ele, o jogador pode usar o dash

    if (IsKeyDown(KEY_W))
    {
        P.sword.y = -5;
        P.sword.x = 0;
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))                //dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((P.posicao.y - P.raio_do_player - 20) < 50) P.posicao.y = 50 + P.raio_do_player;

            else P.posicao.y -= 20;

            dash_t++;
        }

        else if ((P.posicao.y - P.raio_do_player - 4) > 50) P.posicao.y -= 4;
    }

    if (IsKeyDown(KEY_A))
    {
        if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) P.sword.y = 0;
        P.sword.x = -5;
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))                //dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((P.posicao.x - P.raio_do_player - 20) < 0) P.posicao.x = P.raio_do_player;

            else P.posicao.x -= 20;

            dash_t++;
        }

        else if ((P.posicao.x - P.raio_do_player - 4) > 0) P.posicao.x -= 4;
    }

    if (IsKeyDown(KEY_S))
    {
        if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) P.sword.x = 0;
        P.sword.y = 5;
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))                //dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((Vres - P.posicao.y - P.raio_do_player) < 20) P.posicao.y += (Vres - P.posicao.y - P.raio_do_player);

            else P.posicao.y += 20;

            dash_t++;
        }

        else if ((P.posicao.y + P.raio_do_player + 4) < Vres) P.posicao.y += 4;
    }

    if (IsKeyDown(KEY_D))
    {
        if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) P.sword.y = 0;
        P.sword.x = 5;
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))                //dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            if ((Hres - P.posicao.x - P.raio_do_player) < 20) P.posicao.x += (Hres - P.posicao.x - P.raio_do_player);

            else P.posicao.x += 20;

            dash_t++;
        }

        else if ((P.posicao.x + P.raio_do_player + 4) < Hres) P.posicao.x += 4;
    }
    if (P.sword.x*P.sword.x == P.sword.y*P.sword.y && P.sword.x*P.sword.x == 25)
    {
            P.sword.x = (5.0/(1.4))*(P.sword.x/(abs(P.sword.x)));
            P.sword.y = (5.0/(1.4))*(P.sword.y/(abs(P.sword.y)));
    }
    float x_center = P.posicao.x + 6*P.sword.x;
    float y_center = P.posicao.y + 6*P.sword.y; 
    if (p_atk_timer > 0)
    {
	DrawCircle(x_center, y_center, 5, RED);
    	DrawCircle(6*P.sword.x*cos(PI/12) - 6*P.sword.y*sin(PI/12) + P.posicao.x, 6*P.sword.x*sin(PI/12) + 6*P.sword.y*cos(PI/12) + P.posicao.y, 5, RED);
    	DrawCircle(6*P.sword.x*cos(PI/12) + 6*P.sword.y*sin(PI/12) + P.posicao.x,-6*P.sword.x*sin(PI/12) + 6*P.sword.y*cos(PI/12) + P.posicao.y, 5, RED);
    }
}

