#include "mesaHW.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

#define angle 24.9547f


MesaHW::MesaHW(Vector2 ta) {
	img = LoadImage("assets/mesaHW.png");
	a1 = ta;
	GerarParalelogramo();
}

MesaHW::~MesaHW() {
	UnloadImage(img);
}

void MesaHW::GerarParalelogramo() {
	b1.x = a1.x + 340;
	b1.y = a1.y;

	c1.x = 32 / tan(angle * DEG2RAD) + a1.x;
	c1.y = a1.y + 32;

	d1.x = 32 / tan(angle * DEG2RAD) - b1.x;
	d1.y = c1.y;
}

