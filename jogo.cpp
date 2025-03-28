#include "raylib.h"
#include "boss.hpp"
#include "mesaHW.hpp"
#include "player.hpp"

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

float angle_deg = 24.9547f;


BossSD boss;
Player player;
MesaHW mesa1({180, 212}), 
	   mesa2({133, 314}), 
	   mesa3({83, 419}), 
	   mesa4({35, 531}); 
 

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

	player.playerUP_img = LoadImage("assets/playercima.png");
	player.playerDOWN_img = LoadImage("assets/playerbaixo.png");
	player.playerRIGHT_img = LoadImage("assets/playerdir.png");
	player.playerLEFT_img = LoadImage("assets/playeresq.png");

	ImageResize(&player.playerUP_img, 47, 126);
	ImageResize(&player.playerDOWN_img, 47, 126);
	ImageResize(&player.playerLEFT_img, 47, 126);
	ImageResize(&player.playerRIGHT_img, 47, 126);

	player.playerUP = LoadTextureFromImage(player.playerUP_img);
	player.playerDOWN = LoadTextureFromImage(player.playerDOWN_img);
	player.playerRIGHT = LoadTextureFromImage(player.playerRIGHT_img);
	player.playerLEFT = LoadTextureFromImage(player.playerLEFT_img);


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

	/*
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

	*/
}
	


int main() {

	InitWindow(Hres, Vres, "Boss SD");
	SetTargetFPS(60);

	init();

	while (!WindowShouldClose()) {

		player.UpdatePlayer(mesa1);

		BeginDrawing();

			ClearBackground(BLACK);
			DrawTexture(background_SD, 0, 0, WHITE);

			DrawTexture(mesa1.texture, mesa1.x, mesa1.y, WHITE);
			DrawTexture(mesa2.texture, mesa2.x, mesa2.y, WHITE);
			DrawTexture(mesa3.texture, mesa3.x, mesa3.y, WHITE);
			DrawTexture(mesa4.texture, mesa4.x, mesa4.y, WHITE);
			/*
			DrawTexture(mesa5.texture, mesa5.x, mesa5.y, WHITE);
			DrawTexture(mesa6.texture, mesa6.x, mesa6.y, WHITE);
			DrawTexture(mesa7.texture, mesa7.x, mesa7.y, WHITE);
			*/

			DrawTexture(mesaJailson, 0, 492, WHITE);

			boss.DrawSD();
			player.DrawPlayer();

			Vector2 posmouse = GetMousePosition();

			std::cout << "Posicao: " << posmouse.x  << ", " << posmouse.y << std::endl;

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
