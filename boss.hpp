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
private:
	Texture2D spriteSD;
	float lifeBarSD = 100.00;
	float speedSD = 0.4;
};
