#ifndef SD_GAME
#define SD_GAME

#include "raylib.h"
#include "boss.hpp"
#include "mesaHW.hpp"
#include "player.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class SDGAME {
	public:
		SDGAME();
		void Init();
		void DrawPlayerMesas();
		void DeterminarBackground();
		void DesenhoPlayerMesas();
		void MudarEtapa();
		void Etapas();
		void Liberar();
		void InitPlayer();
		void InitCenario();
		void VitoriaOuDerrota();
		void GIFsBack();
		void Jogo();

	private:
		BossSD boss;
		Player player;
		MesaHW	mesa1,
			mesa2,
			mesa3,
			mesa4,
			mesa5,
			mesa6,
			mesa7;

		Texture2D background_SD;
		Texture2D mesas_SD;
		Texture2D mesaJailson;
		Texture2D background_SD_MapaK_Vazio;
		Texture2D tela_gameover_SD;

		Texture2D spritesheet_choque;
		Texture2D spritesheet_final;
		Texture2D spritesheet_equacao;
		Texture2D spritesheet_inicial;

		Texture2D bossNormal;
		Texture2D bossMorto;

		Image background_SD_img;
		Image mesas_SD_img;
		Image mesaJailson_img;
		Image background_SD_MapaK_Vazio_img;
		Image tela_gameover_SD_img;

		Rectangle sourceRecChoque;
		Rectangle destRecChoque;

		Rectangle sourceRecEquacao;
		Rectangle destRecEquacao;

		Rectangle sourceRecFinal;
		Rectangle destRecFinal;

		Rectangle sourceRecInicial;
		Rectangle destRecInicial;

		chicote vec;

		Sound som_choque;
		Sound som_jequiti;
		Sound som_vitoria;
		Sound som_gameover;

		float angle_deg = 24.9547f;

		int currentFrameChoque;
		int frameCounterChoque;
		int frameDelayChoque;

		int currentFrameEquacao;
		int frameCounterEquacao;
		int frameDelayEquacao;

		int currentFrameFinal;
		int frameCounterFinal;
		int frameDelayFinal;

		int currentFrameInicial;
		int totalFramesInicial;
		int framesPerRowInicial;
		int frameWidthInicial;
		int frameHeightInicial;
		int frameCounterInicial;
		int frameDelayInicial;

		int estadoAnterior;
		int qualTela; // 0 - Inicial // 1 - Jogo // 2 - Transição

		bool tocouChoque;
		bool tocouJequiti;
		bool tocouVitoria;
		bool tocouGameOver;
		bool foiZerado;
		bool finalGIF;
};


#endif // !SD_GAME