#include "raylib.h"
#include <stdio.h>
#include <cmath>
#include "globals.hpp"

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
