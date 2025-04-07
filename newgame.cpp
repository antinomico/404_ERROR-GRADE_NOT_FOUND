#include "raylib.h"
#include <cmath>
#include <stdio.h>
#include "globals.hpp"
#include "atks_sapo.hpp"
#include "movement.hpp"

//-----------------------------------------------------------//

void init()
{
    p_atk_timer = 0;
    it = 0;
    dash_t = 0;
    ATK1_COOLDOWNt = 0;

    P.posicao.x = inicio_player_x;
    P.posicao.y = inicio_player_y;
    P.vida_jogador = 100;

    S.posicao.x = CENTER_x;
    S.posicao.y = CENTER_y;
    S.vida_boss = 100;

    vec.dex = 0;
    vec.dey = 0;
    vec.cx = 0;
    vec.cy = 0;
    vec.reverse = 0;

    S.posicao_inicial = S.posicao;
    S.acompanhar_cd_antes_da_linguada = S.cooldown_antes_da_linguada;
    S.linguadas_restantes = S.quantidade_de_linguadas;
}

//------------------------------------------------------------//

void barras_vida() {
    // do jogador
    DrawRectangle(20, 20, 200, 20, GRAY);

    float vida_jogador_width = (P.vida_jogador / 100.0) * 200;

    DrawRectangle(20, 20, vida_jogador_width, 20, GREEN);

    // do boss
    DrawRectangle(Hres - 220, 20, 200, 20, GRAY);

    float vida_boss_width = (S.vida_boss / 100.0) * 200;

    DrawRectangle(Hres - 220, 20, vida_boss_width, 20, RED);
}

//-----------------------------------------------------------//

void acompanhar_cd() {
    if (S.tempo_antes_de_pular) {
        DrawText("PULO CARREGANDO", 20, 680, 20, WHITE);
    }

    if (S.tempo_antes_do_porradao) {
        DrawText("PORRADÃO CARREGANDO", 20, 680, 20, WHITE);
    }

    if (S.tempo_antes_da_linguada) {
        DrawText("LINGUADA CARREGANDO", 20, 680, 20, WHITE);
    }

    if (P.morto) {
        DrawText("MORREU", 500, 20, 20, WHITE);
    }
}


//-------------------		ROTINA PARA VERIFICAR AS COLISÕES COM A HITBOX DA ESPADA	-------------------------//

void sword_hitbox_check(float fps_routine)
{
	float at_x = P.posicao.x + 6*P.sword.x;
	float at_y = P.posicao.y + 6*P.sword.y;
	float at1_x = 6*P.sword.x*cos(PI/12) - 6*P.sword.y*sin(PI/12) + P.posicao.x;
	float at1_y = 6*P.sword.x*sin(PI/12) + 6*P.sword.y*cos(PI/12) + P.posicao.y;
	float at2_x = 6*P.sword.x*cos(PI/12) + 6*P.sword.y*sin(PI/12) + P.posicao.x;
	float at2_y =-6*P.sword.x*sin(PI/12) + 6*P.sword.y*cos(PI/12) + P.posicao.y;
	//var1: (S.posicao.x - at_x)² + (S.posicao.y - at_y)²
	if (IsKeyDown(KEY_P) && p_atk_timer == 0)
	{ 
		p_atk_timer += fps_routine;
		if ((S.posicao.x - at_x)*(S.posicao.x - at_x) + (S.posicao.y - at_y)*(S.posicao.y - at_y) <= S.raio_do_sapo*S.raio_do_sapo) S.vida_boss-=5;
		else if ((S.posicao.x - at1_x)*(S.posicao.x - at1_x) + (S.posicao.y - at1_y)*(S.posicao.y - at1_y) <= S.raio_do_sapo*S.raio_do_sapo) S.vida_boss-=5;
		else if ((S.posicao.x - at2_x)*(S.posicao.x - at2_x) + (S.posicao.y - at2_y)*(S.posicao.y - at2_y) <= S.raio_do_sapo*S.raio_do_sapo) S.vida_boss-=5;
	}
	else if (p_atk_timer > 0) p_atk_timer += fps_routine;
	if (p_atk_timer >= P_ATK_COOLDOWN) p_atk_timer = 0;
}

//-----------------------------------------------------------//

int main() {
    InitWindow(Hres, Vres, "sapo");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) {
        float controle_de_tempo = GetFrameTime();

        ataques_sapo(controle_de_tempo);
        movement();
	sword_hitbox_check(controle_de_tempo);

        BeginDrawing();
        //
        ClearBackground(BLACK);

        barras_vida();
        acompanhar_cd();

        DrawCircle(P.posicao.x, P.posicao.y, P.raio_do_player, BLUE);
        DrawCircle(S.posicao.x, S.posicao.y, S.raio_do_sapo, RED);

        if (S.porradao && S.duracao_porradao > 0) {
            DrawCircleLines(S.posicao.x, S.posicao.y, 2.5 * S.raio_do_sapo, ORANGE);
        }

        //
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
