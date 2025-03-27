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

float angle_deg = 24.9547f;

class Player {
public:
	float x, y;
	float largura = 47;
	float altura = 126;
	float speed = 5;
	float speed_dash = 10;
	int dash_t;
	Texture2D playerUP;
	Texture2D playerDOWN;
	Texture2D playerRIGHT;
	Texture2D playerLEFT;
	Texture2D playerNOW;
	Image playerUP_img;
	Image playerDOWN_img;
	Image playerRIGHT_img;
	Image playerLEFT_img;

	// Desenhar player (por enquanto um círculo)
	void DrawPlayer() {
		DrawTexture(playerNOW, x, y, WHITE);
	}
	
	// Colisao com mesas
	bool ColissionWithQuad(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 pos) {
		if (pos.x >= a.x && pos.x >= c.x && pos.x <= b.x && pos.x <= d.x) {
			if (pos.y >= a.y && pos.y >= b.y && pos.y <= c.y && pos.y <= d.y) {
				return true;
			}
		}
		return false;
	}

	bool CollisionMesas() {
		if (ColissionWithQuad())  // Mesa 1
			
		return true; 
		return false;
	}
	
	// Atualizar posição do player
	void UpdatePlayer() {

		float qtdMovX = 0;
		float qtdMovY = 0;

		Vector2 dir = { sin(angle_deg * DEG2RAD), -1.0f * cos(angle_deg * DEG2RAD) };

		if (dash_t > 10) dash_t++;	// Se o timer do dash for maior que 10, o player terá que esperar o timer chegar a 150 para poder usá-lo de novo			                
		if (dash_t >= 150) dash_t = 0; // Reset do timer do dash		              

		if (IsKeyDown(KEY_W)) {
			playerNOW = playerUP;
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
				y += speed_dash * dir.y;				
				x += speed_dash * dir.x;
				qtdMovX += speed_dash * dir.x;
				qtdMovY += speed_dash * dir.y;
				dash_t++;
			}
			else {
				y += dir.y * speed; 
				x += dir.x * speed;
				qtdMovX += speed * dir.x;
				qtdMovY += speed * dir.y;
			}
		}

		if (IsKeyDown(KEY_A)) {
			playerNOW = playerLEFT;
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))	
			{
				x -= speed_dash;
				qtdMovX -= speed_dash;
				dash_t++;
			}
			else x -= speed;
			qtdMovX -= speed;
		}

		if (IsKeyDown(KEY_S)) {
			playerNOW = playerDOWN;
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))	
			{
				y -= dir.y * speed_dash;
				x -= dir.x * speed_dash;
				dash_t++;
				qtdMovX -= speed_dash * dir.x;
				qtdMovY -= speed_dash * dir.y;
			}
			else {
				y -= dir.y * speed; 
				x -= dir.x * speed;
				qtdMovX -= speed * dir.x;
				qtdMovY -= speed * dir.y;
			}
		}

		if (IsKeyDown(KEY_D)) {
			playerNOW = playerRIGHT;
			if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL)) {
				x += speed_dash;
				qtdMovX += speed_dash;
				dash_t++;
			}
			else {
				x += speed;
				qtdMovX += speed;
			}
		}

		// Colisões com as bordas
		if (x <= 0) {
			x = 0;
		}
		if (x >= Hres - largura) {
			x = Hres - largura;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y >= Vres - altura) {
			y = Vres - altura;
		}

		// Colisões com a parede da frente
		if (y + 100 <= ((6 * x) + 51542) / 433) {
			y = (((6 * x) / 433) + (51542 / 433)) - 100;
		}

		// Colisões com a parede lateral
		if (x <= (66646 - (106 * (y+100))) / 251) {
			x = (66646 - (106 * (y+100))) / 251;
		}

		// Colisoes com as mesas
		if (CollisionMesas()) {
			x -= qtdMovX;
			y -= qtdMovY;
		}
		
	}
};

class MesaHW {
public:
	float x, y;
	Image img = LoadImage("assets/mesaHW.png");
	Texture2D texture;
	Vector2 a1, b1, c1, d1;

	MesaHW(Vector2 ta) {
		a1 = ta;
		GerarParalelogramo(a1, b1, c1, d1);
	}

	void GerarParalelogramo(Vector2 a, Vector2 &b, Vector2 &c, Vector2 &d) {
		b.x = a.x + 340;
		b.y = a.y;
	
		c.x = 32 / tan(angle_deg * DEG2RAD) + a.x;
		c.y = a.y + 32;
	
		d.x = 32 / tan(angle_deg * DEG2RAD) - b.x;
		d.y = c.y;
	}
};


BossSD boss;
Player player;
MesaHW mesa1({180, 212}), 
	   mesa2({133, 314}), 
	   mesa3({83, 419}), 
	   mesa4({35, 531}), 
	   mesa5, 
	   mesa6,
	   mesa7;
	   

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

			Vector2 posmouse = GetMousePosition();

			std::cout << "Posicao: " << posmouse.x  << ", " << posmouse.y << std::endl;

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
