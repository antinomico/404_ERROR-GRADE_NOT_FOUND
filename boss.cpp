#include "boss.hpp"
#include "player.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

BossSD::BossSD() {
	positionSD.x = Hres / 2 - 25;
	positionSD.y = 200;
	etapa = 3; // Inicia na fase da chicotada
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

	if (etapa == 0) Chicotada();
	else if (etapa == 1) ContagemChoque();
	else if (etapa == 4) ContagemMapaK();

}

// Fazer chicotada por 1min (?)
// A cada x segundos, o boss dá uma chicotada alternando entre cima, baixo, esquerda e direita, e o player precisa se esquivar e tentar atacar o boss
void BossSD::Chicotada(){

}


void BossSD::ContagemChoque(){

	if (timer_choque >= 0 && timer_choque < 60) {
		DrawText("CHOQUE NAS MESAS EM 3", 235, 80, 50, RED);
	}

	else if (timer_choque >= 60 && timer_choque < 120) {
		DrawText("CHOQUE NAS MESAS EM 2", 235, 80, 50, RED);
	}

	else if (timer_choque >= 120 && timer_choque < 180) {
		DrawText("CHOQUE NAS MESAS EM 1", 235, 80, 50, RED);
	}

	else if (timer_choque >= 180 && timer_choque < 240) {
		DrawText("CHOQUE NAS MESAS EM 0", 235, 80, 50, RED);

	}
	else if (timer_choque >= 240) {
		etapa = 2;
	}
	timer_choque++;
}

void BossSD::ContagemMapaK(){

	if (timer < 60) {
		DrawText("RÁPIDO! PISE NO 1! 15", 235, 80, 50, RED);
	}
	else if (timer < 120) {
		DrawText("RÁPIDO! PISE NO 1! 14", 235, 80, 50, RED);
	}
	else if (timer < 180) {
		DrawText("RÁPIDO! PISE NO 1! 13", 235, 80, 50, RED);
	}
	else if (timer < 240) {
		DrawText("RÁPIDO! PISE NO 1! 12", 235, 80, 50, RED);
	}
	else if (timer < 300) {
		DrawText("RÁPIDO! PISE NO 1! 11", 235, 80, 50, RED);
	}
	else if (timer < 360) {
		DrawText("RÁPIDO! PISE NO 1! 10", 235, 80, 50, RED);
	}
	else if (timer < 420) {
		DrawText("RÁPIDO! PISE NO 1! 9", 235, 80, 50, RED);
	}
	else if (timer < 480) {
		DrawText("RÁPIDO! PISE NO 1! 8", 235, 80, 50, RED);
	}
	else if (timer < 540) {
		DrawText("RÁPIDO! PISE NO 1! 7", 235, 80, 50, RED);
	}
	else if (timer < 600) {
		DrawText("RÁPIDO! PISE NO 1! 6", 235, 80, 50, RED);
	}
	else if (timer < 660) {
		DrawText("RÁPIDO! PISE NO 1! 5", 235, 80, 50, RED);
	}
	else if (timer < 720) {
		DrawText("RÁPIDO! PISE NO 1! 4", 235, 80, 50, RED);
	}
	else if (timer < 780) {
		DrawText("RÁPIDO! PISE NO 1! 3", 235, 80, 50, RED);
	}
	else if (timer < 840) {
		DrawText("RÁPIDO! PISE NO 1! 2", 235, 80, 50, RED);
	}
	else if (timer < 900) {
		DrawText("RÁPIDO! PISE NO 1! 1", 235, 80, 50, RED);
	}



}
