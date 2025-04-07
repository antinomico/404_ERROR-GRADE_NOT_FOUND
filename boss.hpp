#pragma once
#include "raylib.h"
#include "player.hpp"

struct chicote
{
	int reverse;
	float dex, dey;
	float cx, cy;
}; typedef struct chicote chicote;

class BossSD {
public:
	BossSD();
	~BossSD();
	void DrawSD();
	void AtaqueSD(Player P, chicote* vec);
	void Chicotada(Player P, chicote* vec);
	void ContagemChoque();
	void ContagemMapaK();
	Vector2 positionSD;
	int timer_chicotada;
	int timer;
	int timer_choque;
	int n_chicotada;
	int etapa; // 0 - FUNDO NORMAL (CHICOTADA) // 1 - CONTAGEM // 2 - CHOQUE // 3 - FUNDO SEM MESAS // 4 - MAPA K VAZIO // 5 - MAPA K PREENCHIDO

private:
	Texture2D spriteSD;
	float lifeBarSD = 100.00;
	float speedSD = 0.4;
};
