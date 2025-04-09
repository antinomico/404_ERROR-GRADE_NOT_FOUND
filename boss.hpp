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
	void Health(Player P);
	void DrawSD();
	void AtaqueSD(chicote* vec);
	void Chicotada(chicote* vec);
	void ContagemChoque();
	void ContagemMapaK();
	Vector2 positionSD;
	int timer_chicotada;
	int timer;
	int timer_choque;
	int n_chicotada;
	float p_atk_timer = 0;
	float lifeBarSD = 100;
	int etapa; // 0 - FUNDO NORMAL (CHICOTADA) 
			   // 1 - CONTAGEM 
			   // 2 - CHOQUE 
			   // 3 - FUNDO SEM MESAS 
			   // 4 - MAPA K VAZIO 
			   // 5 - MAPA K PREENCHIDO
			   // 6 - TELA TRANSICAO
			   // 7 - TELA DERROTA

	Texture2D spriteSD;
	float speedSD = 0.4;	   

};
