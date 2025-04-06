#include "mesaHW.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

#define angle 24.9547f


MesaHW::MesaHW() {
        img = LoadImage("assets/mesaHW.png");
}

MesaHW::~MesaHW() {
        UnloadImage(img);
}

bool collide(float x, float y)
{
        if ((0 <= x && x <= 354) && (490 <= y && y <= 495)) return true;
        else if ((575 <= x && x <= 865) && (487 <= y && y <= 492)) return true;

        else if ((0 <= x && x <= 505) && (110 <= y && y <= 200)) return true;
        else if ((740 <= x && x <= 1021)&& (163 <= y && y <= 168)) return true;

        else if ((0 <= x && x <= 445) && (270 <= y && y <= 275)) return true;
        else if ((664 <= x && x <= 999)&& (269 <= y && y <= 287)) return true;

        else if ((0  <= x && x <= 400) && (380 <= y && y <= 385)) return true;
        else if ((640 <= x && x <= 930) && (364 <= y && y <= 387)) return true;

        else return false;

}

