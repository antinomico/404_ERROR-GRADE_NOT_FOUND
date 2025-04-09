#include "boss.hpp"
#include "player.hpp"
#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

#define P_ATK_COOLDOWN 5;

BossSD::BossSD() {
	positionSD.x = 588;
	positionSD.y = 115;
	etapa = 0; // Inicia na fase da chicotada
	timer = 0;
	timer_chicotada = 0;
	timer_choque = 0;
	n_chicotada = 0;
	//spriteBoss = LoadTexture("");
}

BossSD::~BossSD() {
	//UnloadTexture(spriteBoss);
}

void BossSD::Health(Player P)
{
	float t_x = P.x + 20;
	float t_y = P.x + 50; //configurar timer!
	if (((positionSD.x - P.x)*(positionSD.x - P.x) + (positionSD.y - P.y)*(positionSD.y - P.y) <= 10000) && IsKeyDown(KEY_P) && p_atk_timer == 0) {
		lifeBarSD = lifeBarSD - 5; 
		p_atk_timer++;
		std:: cout << "hit" << std::endl;
	}
	std::cout << p_atk_timer << std::endl;
	if (p_atk_timer > 0) p_atk_timer += 0.8;
	if (p_atk_timer >= 15) p_atk_timer = 0;
	DrawRectangle(998, 34, lifeBarSD/1.3, 10, RED);
}

void BossSD::DrawSD() {
    DrawRectangle(585, 148, 50, 50, BLUE);
	//DrawTexture(spriteBoss, 0, 0, WHITE);
}


void BossSD::AtaqueSD(chicote* vec) {

	if (etapa == 0){ 
		Chicotada(vec);
	}
	else if (etapa == 1) ContagemChoque();
	else if (etapa == 4) ContagemMapaK();

}

// Fazer chicotada por 1min (?)
// A cada x segundos, o boss dá uma chicotada alternando entre cima, baixo, esquerda e direita, e o player precisa se esquivar e tentar atacar o boss
void BossSD::Chicotada(chicote* vec){
	if (timer_chicotada == 0 && vec->reverse == 0) {
        float dx = -167;
        float dy =  412;

        if (vec->cx <= positionSD.x && vec->cy <= positionSD.y) vec->reverse  = 0;

        if (vec->reverse == 0)
        {
                float mod = 0.1*sqrt(dx*dx + dy*dy);
                vec->cx += dx/mod;
                vec->cy += dy/mod;
                std::cout << vec->cx << ", " << vec->cy << std::endl;
                if (((positionSD.x - vec->cx)*(positionSD.x - vec->cx) + (positionSD.y - vec->cy)*(positionSD.y - vec->cy)) >= (dx*dx + dy*dy)) vec->reverse = 1;

                if (collide(vec->cx, vec->cy))
                {
                        vec->reverse = 1;
                        vec->cx = positionSD.x;
                        vec->cy = positionSD.y;
                        std::cout << "colidiu" << std::endl;
                }
        }
        else
        {
                vec->reverse = 0;
                vec->cx = positionSD.x;
                vec->cy = positionSD.y;
        }

        if (vec->reverse == 0) DrawLine(positionSD.x, positionSD.y, vec->cx, vec->cy, RED);
    }
    else if (vec->reverse == 1)
    {
            timer_chicotada += 1;
            vec->cx = positionSD.x;
            vec->cy = positionSD.y;
            //vec->dex = P.x;
            //vec->dey = P.y;
            if (timer_chicotada >= 30) {timer_chicotada = 0; vec->reverse = 0; n_chicotada++;}
    }

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
		DrawText("RÁPIDO! PISE NO 1! 10", 235, 80, 50, RED);
	}
	else if (timer < 120) {
		DrawText("RÁPIDO! PISE NO 1! 9", 235, 80, 50, RED);
	}
	else if (timer < 180) {
		DrawText("RÁPIDO! PISE NO 1! 8", 235, 80, 50, RED);
	}
	else if (timer < 240) {
		DrawText("RÁPIDO! PISE NO 1! 7", 235, 80, 50, RED);
	}
	else if (timer < 300) {
		DrawText("RÁPIDO! PISE NO 1! 6", 235, 80, 50, RED);
	}
	else if (timer < 360) {
		DrawText("RÁPIDO! PISE NO 1! 5", 235, 80, 50, RED);
	}
	else if (timer < 420) {
		DrawText("RÁPIDO! PISE NO 1! 4", 235, 80, 50, RED);
	}
	else if (timer < 480) {
		DrawText("RÁPIDO! PISE NO 1! 3", 235, 80, 50, RED);
	}
	else if (timer < 540) {
		DrawText("RÁPIDO! PISE NO 1! 2", 235, 80, 50, RED);
	}
	else if (timer < 600) {
		DrawText("RÁPIDO! PISE NO 1! 1", 235, 80, 50, RED);
	}


}
