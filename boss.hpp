#pragma once
#include "raylib.h"

class BossSD {
public:
	BossSD();
	~BossSD();
	void DrawSD();
	void AtaqueSD();
	void Chicotada();
	void ContagemChoque();
	void ContagemMapaK();
	Vector2 positionSD;
	int timer;
	int timer_choque;
	int etapa; // 0 - FUNDO NORMAL (CHICOTADA) // 1 - CONTAGEM // 2 - CHOQUE // 3 - FUNDO SEM MESAS // 4 - MAPA K VAZIO // 5 - MAPA K PREENCHIDO

private:
	Texture2D spriteSD;
	float lifeBarSD = 100.00;
	float speedSD = 0.4;
};
