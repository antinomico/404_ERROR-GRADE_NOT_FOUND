#pragma once
#include "raylib.h"

bool collide(float x, float y);
class MesaHW {
    public:
        MesaHW();
        ~MesaHW();
        float x, y;
                Image img;
                Texture2D texture;
                Vector2 a1, b1, c1, d1;
    };

