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

