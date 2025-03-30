#pragma once
#include "raylib.h"

class BossSD {
public:
	BossSD();
	~BossSD();
	void DrawSD();
	void Chicotada();
	void JogarCI();
	void ChoqueMesas();
	void MapaK();
	Vector2 positionSD;
	int timer_chicotada;
	
	int fase; // 0 - CHICOTADA // 1 - JOGAR CI // 2 - CHOQUE MESAS // 3 - MAPA K

private:
	Texture2D spriteSD;
	float lifeBarSD = 100.00;
	float speedSD = 0.4;
};
