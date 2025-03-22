#include "raylib.h"
#include <cmath>
#include <stdio.h>

#define Hres 1080
#define Vres 720

class Player {
public:
	int x, y;
	float speed;
	int dash_t;
	float radius_player = 20;

	// Desenhar player (por enquanto um círculo)
	void Draw() {
		DrawCircle(x, y, radius_player, WHITE);
	}

	// Atualizar posição do player
	void Update() {

		if (dash_t > 10) dash_t++;	// Se o timer do dash for maior que 10, o player terá que esperar o timer chegar a 150 para poder usá-lo de novo			                
		if (dash_t >= 150) dash_t = 0; // Reset do timer do dash		              

		if (IsKeyDown(KEY_W)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
				y -= 20;
				dash_t++;
			}
			else y -= 4;
		}

		if (IsKeyDown(KEY_A)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))	
			{
				x -= 20;
				dash_t++;
			}
			else x -= 4;
		}

		if (IsKeyDown(KEY_S)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))	
			{
				y += 20;
				dash_t++;
			}
			else y += 4;
		}

		if (IsKeyDown(KEY_D)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
				x += 20;
				dash_t++;
			}
			else x += 4;
		}

		// Colisões com as bordas
		if (x <= radius_player) {
			x = radius_player;
		}
		if (x >= Hres - radius_player) {
			x = Hres - radius_player;
		}
		if (y <= radius_player) {
			y = radius_player;
		}
		if (y >= Vres - radius_player) {
			y = Vres - radius_player;
		}
	}
};


class BossSD {
protected:
	void chicotada() {

	}

public:
	float lifeBar = 100.00;
	float speed = 0.4;
	int posX, posY;

	Vector2 center = { (GetScreenWidth() - (GetScreenWidth() - float(posX)), GetScreenHeight() - (GetScreenHeight() - float(posY))) };

	void Draw() {
		DrawRectangle(posX, posY, 50, 50, WHITE);
	}

	// Movimentação do Boss
	void Update(float x_player, float y_player) {

	}

	void comportamento(float x_player, float y_player) { //nessa função quero incluir todos os ataques do Boss de SD
		if (fabs(pow((x_player - posX), 2) + pow((y_player - posY), 2)) <= 400) {
			//distancia entre o player e o Boss de SD de 200 (ataque perto)
			DrawCircleSector(center, 300, 180, 30, 100, Fade(MAROON, 0.3f));
		}
	}
};

BossSD boss;
Player player;

void init() {
	boss.posX = Hres / 2 - 25;
	boss.posY = 200;

	player.dash_t = 0;
}

int main() {

	InitWindow(Hres, Vres, "Boss SD");
	SetTargetFPS(60);

	init();

	while (!WindowShouldClose()) {

		boss.Update(player.x, player.y);
		player.Update();

		BeginDrawing();

			ClearBackground(BLACK);
			boss.Draw();
			player.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
