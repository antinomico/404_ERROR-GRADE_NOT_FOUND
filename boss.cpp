#include "boss.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

BossSD::BossSD() {
	positionSD.x = Hres / 2 - 25;
	positionSD.y = 200;
	//spriteBoss = LoadTexture(""); // 
}

BossSD::~BossSD() {
	//UnloadTexture(spriteBoss);
}

void BossSD::DrawSD() {
    DrawRectangle(585, 148, 50, 50, BLUE);
	//DrawTexture(spriteBoss, 0, 0, WHITE);
}

void BossSD::Chicotada(){}
void BossSD::JogarCI(){}
void BossSD::ChoqueMesas(){}
void BossSD::MapaK(){}
