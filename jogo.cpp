#include "raylib.h"
#include "boss.hpp"

#include <cmath>
#include <iostream>

#define Hres 1080
#define Vres 720

Image background_SD_img;
Texture2D background_SD;
Image mesas_SD_img;
Texture2D mesas_SD;

Image mesaJailson_img;
Texture2D mesaJailson;


class Player {
public:
	float x, y;
	float speed = 5;
	float speed_dash = 10;
	int dash_t;
	float radius_player = 20;
	float angle_deg = 24.9547f;

	// Desenhar player (por enquanto um círculo)
	void DrawPlayer() {
		DrawCircle(x, y, radius_player, RED);
	}

	// Atualizar posição do player
	void UpdatePlayer() {

		Vector2 dir = { sin(angle_deg * DEG2RAD), -1.0f * cos(angle_deg * DEG2RAD) };

		if (dash_t > 10) dash_t++;	// Se o timer do dash for maior que 10, o player terá que esperar o timer chegar a 150 para poder usá-lo de novo			                
		if (dash_t >= 150) dash_t = 0; // Reset do timer do dash		              

		if (IsKeyDown(KEY_W)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
				y += speed_dash * dir.y;				
				x += speed_dash * dir.x;
				dash_t++;
			}
			else {
				y += dir.y * speed; 
				x += dir.x * speed;
			}
		}

		if (IsKeyDown(KEY_A)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))	
			{
				x -= speed_dash;
				dash_t++;
			}
			else x -= speed;
		}

		if (IsKeyDown(KEY_S)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))	
			{
				y -= dir.y * speed_dash;
				x -= dir.x * speed_dash;
				dash_t++;
			}
			else {
				y -= dir.y * speed; 
				x -= dir.x * speed;
			}
		}

		if (IsKeyDown(KEY_D)) {
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
				x += speed_dash;
				dash_t++;
			}
			else x += speed;
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

		// Colisões com a parede da frente
		if (y <= ((6 * x) + 51542) / 433) {
			y = ((6 * x) / 433) + (51542 / 433);
		}

		// Colisões com a parede lateral
		if (x <= (66646 - (106 * y)) / 251) {
			x = (66646 - (106 * y)) / 251;
		}
	}


};

class MesaHW {
public:
	float x, y;
	Image img = LoadImage("assets/mesaHW.png");
	Texture2D texture;
};


BossSD boss;
Player player;
MesaHW mesa1, mesa2, mesa3, mesa4, mesa5, mesa6, mesa7;

void init() {

	player.x = Hres / 2;
	player.y = Vres / 2;
	player.dash_t = 0;

	// Background
	background_SD_img = LoadImage("assets/backSD.png");
	ImageResize(&background_SD_img, Hres, Vres);
	background_SD = LoadTextureFromImage(background_SD_img);

	// Mesa Jailson
	mesaJailson_img = LoadImage("assets/mesaJailson.png");
	mesaJailson = LoadTextureFromImage(mesaJailson_img);
	mesaJailson.width *= 2;
	mesaJailson.height *= 2;

	// MesasHW -------------- MODULARIZAR !!!!!
	mesa1.texture = LoadTextureFromImage(mesa1.img);
	mesa1.texture.width *= 2;
	mesa1.texture.height *= 2;
	mesa1.x = 156;
	mesa1.y = 168;

	mesa2.texture = LoadTextureFromImage(mesa1.img);
	mesa2.texture.width *= 2;
	mesa2.texture.height *= 2;
	mesa2.x = 106;
	mesa2.y = 274;

	mesa3.texture = LoadTextureFromImage(mesa1.img);
	mesa3.texture.width *= 2;
	mesa3.texture.height *= 2;
	mesa3.x = 56;
	mesa3.y = 382;

	mesa4.texture = LoadTextureFromImage(mesa1.img);
	mesa4.texture.width *= 2;
	mesa4.texture.height *= 2;
	mesa4.x = 726;
	mesa4.y = 168;

	mesa5.texture = LoadTextureFromImage(mesa1.img);
	mesa5.texture.width *= 2;
	mesa5.texture.height *= 2;
	mesa5.x = 676;
	mesa5.y = 274;

	mesa6.texture = LoadTextureFromImage(mesa1.img);
	mesa6.texture.width *= 2;
	mesa6.texture.height *= 2;
	mesa6.x = 626;
	mesa6.y = 382;

	mesa7.texture = LoadTextureFromImage(mesa1.img);
	mesa7.texture.width *= 2;
	mesa7.texture.height *= 2;
	mesa7.x = 576;
	mesa7.y = 492;
}
	

int main() {

	InitWindow(Hres, Vres, "Boss SD");
	SetTargetFPS(60);


	init();

	while (!WindowShouldClose()) {

		player.UpdatePlayer();

		BeginDrawing();

			ClearBackground(BLACK);
			DrawTexture(background_SD, 0, 0, WHITE);

			DrawTexture(mesa1.texture, mesa1.x, mesa1.y, WHITE);
			DrawTexture(mesa2.texture, mesa2.x, mesa2.y, WHITE);
			DrawTexture(mesa3.texture, mesa3.x, mesa3.y, WHITE);
			DrawTexture(mesa4.texture, mesa4.x, mesa4.y, WHITE);
			DrawTexture(mesa5.texture, mesa5.x, mesa5.y, WHITE);
			DrawTexture(mesa6.texture, mesa6.x, mesa6.y, WHITE);
			DrawTexture(mesa7.texture, mesa7.x, mesa7.y, WHITE);

			DrawTexture(mesaJailson, 0, 492, WHITE);

			boss.DrawSD();
			player.DrawPlayer();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
