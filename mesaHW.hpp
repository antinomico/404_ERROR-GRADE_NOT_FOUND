#pragma once
#include "raylib.h"

class MesaHW {
    public:
        MesaHW(Vector2 ta);
        ~MesaHW();
        void GerarParalelogramo();
        float x, y;
		Image img;
		Texture2D texture;
		Vector2 a1, b1, c1, d1;
    };
    