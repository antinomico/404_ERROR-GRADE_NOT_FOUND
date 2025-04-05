#include "boss.hpp"
#include "player.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

BossSD::BossSD() {
	positionSD.x = Hres / 2 - 25;
	positionSD.y = 200;
	fase = 0; // 0 - CHICOTADA // 1 - CHOQUE // 2 - MAPA K
	timer = 0;
	timer_choque = 0;



	//spriteBoss = LoadTexture("");
}

BossSD::~BossSD() {
	//UnloadTexture(spriteBoss);
}

void BossSD::DrawSD() {
    DrawRectangle(585, 148, 50, 50, BLUE);
	//DrawTexture(spriteBoss, 0, 0, WHITE);
}


void BossSD::AtaqueSD() {

	if (fase == 0) Chicotada();
	else if (fase == 1) ChoqueMesas();
	else if (fase == 2) MapaK();

}

// Fazer chicotada por 1min (?)
// A cada x segundos, o boss dá uma chicotada alternando entre cima, baixo, esquerda e direita, e o player precisa se esquivar e tentar atacar o boss
void BossSD::Chicotada(){

}


void BossSD::ChoqueMesas(){

	

	// 3 segundos
	if (timer_choque == 0) {
		// contagem: 3
	}

	else if (timer_choque == 60) {
		// contagem: 2
	}

	else if (timer_choque == 120) {
		// contagem: 1
	}

	else if (timer_choque == 180) {
		// contagem: 0

		// trocar background por gif de choque
	}


	timer_choque++;

}

void BossSD::MapaK(){

}
