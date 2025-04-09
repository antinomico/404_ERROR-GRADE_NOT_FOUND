#include "raylib.h"
#include "raymath.h"
#include "screens.hpp"
#include "animation.hpp"

#define Hres 1080
#define Vres 720


typedef enum GameplayScreens {
	GAME_OVER = -2,
    PAUSE = -1,
    PROLOGUE = 0,
    SD_BATTLE = 1,
	TRANSITION = 2,
    AL_BATTLE = 3,
    EPILOGUE = 4
}   GameplayScreens;

GameplayScreen::GameplayScreen() :
    framesCounter(0), finishScreen(0), state(PROLOGUE), lastState(PROLOGUE) {
	Dialog dialogText = Dialog(font, 20);
	SDGAME SDGame;
}

GameplayScreen::~GameplayScreen() {
    Unload();
}

void GameplayScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
	
	currentIndexFontGame = 0;

	fontGame[0].name = "Mais um dia estava prestes a se iniciar na vida de Cintio";
	fontGame[1].name = "Na ultima semana de seu periodo, Cintio se via ha dias sem dormir";
	fontGame[2].name = "Precisando recuperar nota, mal esperava o que lhe viria em seguida";
	fontGame[3].name = "Ate que ele sentiria um fedor de curto-circuito...";
	
	dialogText.Init(fontGame[0].name.c_str(),
		{(float) GetScreenWidth() / 2 - (float) MeasureText(fontGame[0].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f});

	frameCounterInicial = 0;
	frameDelayInicial = 20;
	currentFrameInicial = 0;
	colFrameInicial = 0;
	rowFrameInicial = 0;

	background = LoadTexture("rsc/inicio_sd.png");

    InitPlayer();
    InitCenario();

    vec.reverse = 1;
    vec.cx = boss.positionSD.x;
    vec.cy = boss.positionSD.y;
    vec.dex = player.x;
    vec.dey = player.y;
    boss.timer_chicotada = 0;

    estadoAnterior = 0;
    qualTela = 0;

    bossNormal = LoadTexture("assets/bmo_boss.png");
    bossMorto = LoadTexture("assets/bmo_dano.png");

    boss.spriteSD = bossNormal;
}

void GameplayScreen::Update() {
    if (IsKeyPressed(KEY_ESCAPE) && state != PROLOGUE && state != TRANSITION && state != EPILOGUE) {
		if (state == PAUSE)
			state = lastState;
		else
			state = PAUSE;
        PlaySound(fxCoin);
    }
    else {
        if (state == PAUSE)
            state = PAUSE;
		else if (state == GAME_OVER) {
			if (GetKeyPressed()) {
				PlaySound(fxCoin);

				if (lastState == SD_BATTLE) {
					state = SD_BATTLE;
				}
				else if (lastState == AL_BATTLE) {
					state = AL_BATTLE;
				}
			}
		}
        else if (state == PROLOGUE) {
			if (currentIndexFontGame <= 3) {
				for (int i = 0; i <= currentIndexFontGame; i++) {
					if (GetKeyPressed() && dialogText.IsFinished()) {
						currentIndexFontGame++;
						dialogText.Init(fontGame[currentIndexFontGame].name.c_str(),
							{ (float)GetScreenWidth() / 2 - (float)MeasureText(fontGame[currentIndexFontGame].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f });
					}
					else if (!dialogText.IsFinished()) {
						dialogText.Update(5);
					}

				}
			}

			
			else {
				frameCounterInicial++;
				if (currentFrameInicial < 33) {
					if (frameCounterInicial >= frameDelayInicial) {
						frameCounterInicial = 0;
						currentFrameInicial = (currentFrameInicial + 1) % 34;

						colFrameInicial = currentFrameInicial % 10;
						rowFrameInicial = currentFrameInicial / 10;
					}
				}
				else if (GetKeyPressed()) { // proximo estado
					state = lastState = SD_BATTLE;

					background = LoadTexture("rsc/inicio_al.png");

					currentIndexFontGame = 0;

					frameCounterInicial = 0;
					frameDelayInicial = 20;
					currentFrameInicial = 0;
					colFrameInicial = 0;
					rowFrameInicial = 0;

					fontGame[0].name = "UUUGGGGHHH!! Cintio conseguira escapar do choque do laboratorio de hardware";
					fontGame[1].name = "Desesperado, decidiu buscar ajuda a um conhecido professor de algebra linear";
					fontGame[2].name = "Querendo entender o que tinha ocorrido no CIn, finalmente ele chega � sua sala...";
					fontGame[3].name = "Porem logo escutara um barulho estranho... MAS O QUE?!!!";

					dialogText.Init(fontGame[0].name.c_str(),
						{ (float)GetScreenWidth() / 2 - (float)MeasureText(fontGame[0].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f });
				}
			}
        }
        else if (state == SD_BATTLE) {
			player.UpdatePlayer(boss.etapa);

		    GIFsBack();










        }
		else if (state == TRANSITION) {
			if (currentIndexFontGame <= 3) {
				for (int i = 0; i <= currentIndexFontGame; i++) {
					if (GetKeyPressed() && dialogText.IsFinished()) {
						currentIndexFontGame++;
						dialogText.Init(fontGame[currentIndexFontGame].name.c_str(),
							{ (float)GetScreenWidth() / 2 - (float)MeasureText(fontGame[currentIndexFontGame].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f });
					}
					else if (!dialogText.IsFinished()){
						dialogText.Update(5);
					}
				}
			}
			else {
				frameCounterInicial++;
				if (currentFrameInicial < 14) {
					if (frameCounterInicial >= frameDelayInicial) {
						frameCounterInicial = 0;
						currentFrameInicial = (currentFrameInicial + 1) % 14;
					}
				}
			}
		}
		else if (state == AL_BATTLE) {
			// se o player ou boss morrerem







		}
		else if (state == EPILOGUE) {
			// se o player pressionar qualquer tecla tirando o ESC



		}
    }
}

void GameplayScreen::Draw() {
	if (state == GAME_OVER) {
		DrawTextureEx(background, { 0, 0 }, 0.0f, 2.0f, WHITE);
	}
	else if (state == PAUSE) {
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
		DrawText("PAUSE", GetScreenWidth() / 2 - MeasureText("PAUSE", 40) / 2, GetScreenHeight() / 2 - 20, 40, WHITE);
		DrawText("Pressione ESC para continuar", GetScreenWidth() / 2 - MeasureText("Pressione ESC para continuar", 20) / 2, GetScreenHeight() / 2 + 20, 20, WHITE);
	}
	else if (state == PROLOGUE) {		
		DrawTexturePro(background,
			{ (float)(colFrameInicial * 540), (float)(rowFrameInicial * 360), 540.0f, 360.0f },
			{ 0.0f, 0.0f, (float) GetScreenWidth(), (float) GetScreenHeight()},
			{ 0, 0 }, 0.0f, WHITE);
		
		if (currentIndexFontGame <= 3) {
			DrawRectangle(20.0f + 90.0f, GetScreenHeight() - 90.0f, GetScreenWidth() - 40.0f - 180.0f, 75.0f, Fade(BLACK, 0.5f));
			dialogText.Draw();

			if (dialogText.IsFinished()) {
				float timer = sin(2 * GetTime()) > 0 ? 1 : 0;
				DrawText("-->", GetScreenWidth() - 140, GetScreenHeight() - 40, 20, Fade(RAYWHITE, timer));
			}
		}
	}
	else if (state == SD_BATTLE) {
		// tela de batalha
			boss.timer++;
            Jogo();




	}
	else if (state == TRANSITION) {
		DrawTexturePro(background,
			{ (float)(colFrameInicial * 540), (float)(rowFrameInicial * 360), 540.0f, 360.0f },
			{ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() },
			{ 0, 0 }, 0.0f, WHITE);

		if (currentIndexFontGame <= 3) {
			DrawRectangle(20.0f + 90.0f, GetScreenHeight() - 90.0f, GetScreenWidth() - 40.0f - 180.0f, 75.0f, Fade(BLACK, 0.5f));
			dialogText.Draw();

			if (dialogText.IsFinished()) {
				float timer = sin(2 * GetTime()) > 0 ? 1 : 0;
				DrawText("-->", GetScreenWidth() - 140, GetScreenHeight() - 40, 20, Fade(RAYWHITE, timer));
			}
		}
	}
	else if (state == AL_BATTLE) {
		// tela de batalha





	}
	else if (state == EPILOGUE) {
		DrawTextureEx(background, { 0, 0 }, 0.0f, 2.0f, WHITE);
	}
}

void GameplayScreen::Unload() {

}

bool GameplayScreen::Finish() const {
    return finishScreen;
}

void GameplayScreen::DrawPlayerMesas() {
    if (player.y <= mesa1.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa1.texture, mesa1.x, mesa1.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa4.texture, mesa4.x, mesa4.y, WHITE);
    if (player.y > mesa1.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();

    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa2.texture, mesa2.x, mesa2.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa5.texture, mesa5.x, mesa5.y, WHITE);
    if (player.y > mesa2.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();

    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa3.texture, mesa3.x, mesa3.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa6.texture, mesa6.x, mesa6.y, WHITE);
    if (player.y > mesa3.y && player.y <= mesa7.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();

    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa7.texture, mesa7.x, mesa7.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesaJailson, 0, 492, WHITE);
    if (player.y >= mesa7.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();
}

void GameplayScreen::DeterminarBackground() {
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(background_SD, 0, 0, WHITE); // Fundo normal

    else if (boss.etapa == 2 || (boss.etapa == 7 && boss.timer < 300 && estadoAnterior == 2)) DrawTexturePro(spritesheet_choque, sourceRecChoque, destRecChoque, { 0, 0 }, 0.0f, WHITE);

    else if (boss.etapa == 3 || (boss.etapa == 7 && boss.timer < 300 && estadoAnterior == 3)) DrawTexturePro(spritesheet_equacao, sourceRecEquacao, destRecEquacao, { 0, 0 }, 0.0f, WHITE);

    else if (boss.etapa == 4 || (boss.etapa == 7 && boss.timer < 300 && estadoAnterior == 4)) DrawTexture(background_SD_MapaK_Vazio, 0, 0, WHITE);

    else if (boss.etapa == 5 || (boss.etapa == 7 && boss.timer < 300 && estadoAnterior == 5)) DrawTexturePro(spritesheet_final, sourceRecFinal, destRecFinal, { 0, 0 }, 0.0f, WHITE);

    // Vitoria --------------- ALTERAR AQUI ---------------------------
    else if (boss.etapa == 6) DrawTexture(tela_gameover_SD, 0, 0, WHITE);

    // Derrota
    else if (boss.etapa == 7 && boss.timer >= 300) {
        DrawTexture(tela_gameover_SD, 0, 0, WHITE);
    }
}

void GameplayScreen::DesenhoPlayerMesas() {
    if (player.y <= mesa1.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa1.texture, mesa1.x, mesa1.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa4.texture, mesa4.x, mesa4.y, WHITE);
    if (player.y > mesa1.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();

    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa2.texture, mesa2.x, mesa2.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa5.texture, mesa5.x, mesa5.y, WHITE);
    if (player.y > mesa2.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();

    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa3.texture, mesa3.x, mesa3.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa6.texture, mesa6.x, mesa6.y, WHITE);
    if (player.y > mesa3.y && player.y <= mesa7.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();

    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesa7.texture, mesa7.x, mesa7.y, WHITE);
    if (boss.etapa == 0 || boss.etapa == 1 || (boss.etapa == 7 && boss.timer < 300 && (estadoAnterior == 0 || estadoAnterior == 1))) DrawTexture(mesaJailson, 0, 492, WHITE);
    if (player.y >= mesa7.y && ((boss.etapa != 6 && boss.etapa != 7) || (boss.etapa == 7 && boss.timer < 300))) player.DrawPlayer();
}

void GameplayScreen::MudarEtapa() {
    // CHICOTADA (1min) -> CONTAGEM
    if ((boss.lifeBarSD <= 0 || boss.timer >= 1800) && boss.etapa == 0) {
        estadoAnterior = 0;
        boss.etapa = 1;
        boss.timer = 0;
    }
    // CONTAGEM (3seg) -> CHOQUE
    if (boss.timer >= 240 && boss.etapa == 1) {
        estadoAnterior = 1;
        boss.etapa = 2;
        boss.timer = 0;
    }
    // CHOQUE (5seg) -> SEM MESAS
    if (boss.timer >= 300 && boss.etapa == 2) {
        estadoAnterior = 2;
        boss.etapa = 3;
        boss.timer = 0;
    }
    // SEM MESAS (5seg) -> MAPA K VAZIO
    if (boss.timer >= 300 && boss.etapa == 3) {
        estadoAnterior = 3;
        boss.etapa = 4;
        boss.timer = 0;
    }
    // MAPA K VAZIO (15seg) -> MAPA K PREENCHIDO
    if (boss.timer >= 600 && boss.etapa == 4) {
        estadoAnterior = 4;
        boss.etapa = 5;
        boss.timer = 0;
    }
    // MAPA K PREENCHIDO -> TELA TRANSICAO
    if (boss.timer >= 180 && boss.etapa == 5 && player.ganhou == true) {
        estadoAnterior = 5;
        boss.etapa = 6;
        boss.timer = 0;
    }

    // QUALQUER FASE -> TELA GAME OVER
    if (player.vivo == false && foiZerado == false) {
        estadoAnterior = boss.etapa;
        foiZerado = true;
        boss.etapa = 7;
        boss.timer = 0;
    }
}

void GameplayScreen::Etapas() {


    // Contagem
    if (boss.etapa == 1) {
        if (boss.lifeBarSD > 0) {
            player.vivo = false;
        }
    }

    // Choque
    else if (boss.etapa == 2) {

        if (player.EntreMesas()) {
            player.vivo = false;
        }

        if (tocouChoque == false) {
            PlaySound(som_choque);
            tocouChoque = true;
        }
    }

    // Mostrar equa��o
    if (boss.etapa == 3) {
        if (boss.timer < 30) {

        }
    }

    // Contagem do Mapa K
    if (boss.etapa == 4) {

        if (tocouJequiti == false) {
            PlaySound(som_jequiti);
            tocouJequiti = true;
        }
    }

    // Fim do Mapa K
    if (boss.etapa == 5) {
        // Colocar �udio de vit�ria

        // Primeiro 1
        if ((player.y <= ((0.0488f * player.x) + 186.502f)) &&
            (player.y >= ((0.02765f * player.x) + 109.907f)) &&
            (player.x >= ((-0.20181f * player.y) + 538.26)) &&
            (player.x <= ((-0.2472f * player.y) + 716.59))) {

            player.ganhou = 1;
        }

        // Segundo 1
        else if ((player.x >= ((-0.16984f * player.y) + 911.332f)) &&
            (player.y >= ((0.0267f * player.x) + 200.941f)) &&
            (player.y <= ((0.05027f * player.x) + 289.944f))) {

            player.ganhou = 1;
        }

        // Terceiro 1
        else if ((player.x >= ((-0.30191f * player.y) + 370.339f)) &&
            (player.x <= ((-0.28146f * player.y) + 552.163f)) &&
            (player.y >= 323.734f) &&
            (player.y <= ((0.06845f * player.x) + 411.675f))) {

            player.ganhou = 1;
        }

        // Quarto 1
        else if ((player.y >= ((-0.008635f * player.x) + 469.671f)) &&
            (player.x >= ((-0.21909f * player.y) + 723.879f)) &&
            (player.x <= ((-0.19657f * player.y) + 928.833f))) {

            player.ganhou = 1;
        }

        // Colocar �udio de derrota
        else {
            player.vivo = false;
        }
    }
}

void GameplayScreen::Liberar() {
    UnloadTexture(spritesheet_choque);
    UnloadTexture(background_SD);
    UnloadTexture(mesaJailson);
    UnloadTexture(player.playerUP);
    UnloadTexture(player.playerUP_L);
    UnloadTexture(player.playerUP_R);
    UnloadTexture(player.playerDOWN);
    UnloadTexture(player.playerDOWN_L);
    UnloadTexture(player.playerDOWN_R);
    UnloadTexture(player.playerRIGHT);
    UnloadTexture(player.playerRIGHT_L);
    UnloadTexture(player.playerRIGHT_R);
    UnloadTexture(player.playerLEFT);
    UnloadTexture(player.playerLEFT_L);
    UnloadTexture(player.playerLEFT_R);
    UnloadTexture(mesa1.texture);
    UnloadTexture(mesa2.texture);
    UnloadTexture(mesa3.texture);
    UnloadTexture(mesa4.texture);
    UnloadTexture(mesa5.texture);
    UnloadTexture(mesa6.texture);
    UnloadTexture(mesa7.texture);
    UnloadTexture(spritesheet_final);
    UnloadTexture(background_SD_MapaK_Vazio);
    UnloadImage(background_SD_MapaK_Vazio_img);


    UnloadImage(background_SD_img);
    UnloadImage(mesaJailson_img);
    UnloadImage(player.playerUP_img);
    UnloadImage(player.playerUP_L_img);
    UnloadImage(player.playerUP_R_img);
    UnloadImage(player.playerDOWN_img);
    UnloadImage(player.playerDOWN_L_img);
    UnloadImage(player.playerDOWN_R_img);
    UnloadImage(player.playerRIGHT_img);
    UnloadImage(player.playerRIGHT_L_img);
    UnloadImage(player.playerRIGHT_R_img);
    UnloadImage(player.playerLEFT_img);
    UnloadImage(player.playerLEFT_L_img);
    UnloadImage(player.playerLEFT_R_img);
    UnloadImage(mesa1.img);
    UnloadImage(mesa2.img);
    UnloadImage(mesa3.img);
    UnloadImage(mesa4.img);
    UnloadImage(mesa5.img);
    UnloadImage(mesa6.img);
    UnloadImage(mesa7.img);


    UnloadSound(som_choque);
    UnloadSound(som_jequiti);
}

void GameplayScreen::InitPlayer() {

    // VARI�VEIS ================= //
    player.x = Hres / 2;
    player.y = Vres / 2;
    player.dash_t = 0;
    player.frameCounter = 0;
    player.currentFrame = 0;
    player.frameSpeed = 8;
    player.lastPos = 0;
    // ============================ //


    // SPRITES =========================================================== //

    // Player andando para cima
    player.playerUP_img = LoadImage("assets/playercima.png");
    player.playerUP_L_img = LoadImage("assets/playercima_left.png");
    player.playerUP_R_img = LoadImage("assets/playercima_right.png");

    // Player andando para baixo
    player.playerDOWN_img = LoadImage("assets/playerbaixo.png");
    player.playerDOWN_L_img = LoadImage("assets/playerbaixo_left.png");
    player.playerDOWN_R_img = LoadImage("assets/playerbaixo_right.png");

    // Player andando para direita
    player.playerRIGHT_img = LoadImage("assets/playerdir.png");
    player.playerRIGHT_L_img = LoadImage("assets/playerdir_left.png");
    player.playerRIGHT_R_img = LoadImage("assets/playerdir_right.png");

    // Player andando para esquerda
    player.playerLEFT_img = LoadImage("assets/playeresq.png");
    player.playerLEFT_L_img = LoadImage("assets/playeresq_left.png");
    player.playerLEFT_R_img = LoadImage("assets/playeresq_right.png");


    // Redimensionamento das imagens
    ImageResize(&player.playerUP_img, 47, 126);
    ImageResize(&player.playerUP_L_img, 60, 126);
    ImageResize(&player.playerUP_R_img, 60, 126);

    ImageResize(&player.playerDOWN_img, 47, 126);
    ImageResize(&player.playerDOWN_L_img, 60, 126);
    ImageResize(&player.playerDOWN_R_img, 60, 126);

    ImageResize(&player.playerLEFT_img, 47, 126);
    ImageResize(&player.playerLEFT_L_img, 60, 126);
    ImageResize(&player.playerLEFT_R_img, 60, 126);

    ImageResize(&player.playerRIGHT_img, 47, 126);
    ImageResize(&player.playerRIGHT_L_img, 60, 126);
    ImageResize(&player.playerRIGHT_R_img, 60, 126);

    // Carregamento das texturas
    player.playerUP = LoadTextureFromImage(player.playerUP_img);
    player.playerUP_L = LoadTextureFromImage(player.playerUP_L_img);
    player.playerUP_R = LoadTextureFromImage(player.playerUP_R_img);

    player.playerDOWN = LoadTextureFromImage(player.playerDOWN_img);
    player.playerDOWN_L = LoadTextureFromImage(player.playerDOWN_L_img);
    player.playerDOWN_R = LoadTextureFromImage(player.playerDOWN_R_img);

    player.playerRIGHT = LoadTextureFromImage(player.playerRIGHT_img);
    player.playerRIGHT_L = LoadTextureFromImage(player.playerRIGHT_L_img);
    player.playerRIGHT_R = LoadTextureFromImage(player.playerRIGHT_R_img);

    player.playerLEFT = LoadTextureFromImage(player.playerLEFT_img);
    player.playerLEFT_L = LoadTextureFromImage(player.playerLEFT_L_img);
    player.playerLEFT_R = LoadTextureFromImage(player.playerLEFT_R_img);

    // ====================================================================== //
}

void GameplayScreen::InitCenario() {

    // BACKGROUND =========================================== //
    background_SD_img = LoadImage("assets/backSD.png");
    ImageResize(&background_SD_img, Hres, Vres);
    background_SD = LoadTextureFromImage(background_SD_img);

    background_SD_MapaK_Vazio_img = LoadImage("assets/backSDMapaVazio.png");
    ImageResize(&background_SD_MapaK_Vazio_img, Hres, Vres);
    background_SD_MapaK_Vazio = LoadTextureFromImage(background_SD_MapaK_Vazio_img);

    tela_gameover_SD_img = LoadImage("assets/gameover_sd.png");
    ImageResize(&tela_gameover_SD_img, Hres, Vres);
    tela_gameover_SD = LoadTextureFromImage(tela_gameover_SD_img);

    spritesheet_choque = LoadTexture("assets/backSDchoque.png");
    sourceRecChoque = { 0.0f, 0.0f, 540.0f, 360.0f };
    destRecChoque = { 0.0f, 0.0f, Hres, Vres };
    currentFrameChoque = 0;
    frameCounterChoque = 0;
    frameDelayChoque = 15;

    spritesheet_final = LoadTexture("assets/backSDfinal.png");
    sourceRecFinal = { 0.0f, 0.0f, 540.0f, 360.0f };
    destRecFinal = { 0.0f, 0.0f, Hres, Vres };
    currentFrameFinal = 0;
    frameCounterFinal = 0;
    frameDelayFinal = 15;

    spritesheet_equacao = LoadTexture("assets/equacao.png");
    sourceRecEquacao = { 0.0f, 0.0f, 540.0f, 360.0f };
    destRecEquacao = { 0.0f, 0.0f, Hres, Vres };
    currentFrameEquacao = 0;
    frameCounterEquacao = 0;
    frameDelayEquacao = 15;

    spritesheet_inicial = LoadTexture("assets/inicio_sd.png");
    sourceRecInicial = { 0.0f, 0.0f, 540.0f, 360.0f };
    destRecInicial = { 0.0f, 0.0f, Hres, Vres };
    totalFramesInicial = 34;
    framesPerRowInicial = 10;
    frameWidthInicial = 540;
    frameHeightInicial = 360;
    frameCounterInicial = 0;
    frameDelayInicial = 20;


    foiZerado = false;
    finalGIF = false;
    // ====================================================== //


    // MESA JAILSON ========================================= //
    mesaJailson_img = LoadImage("assets/mesaJailson.png");
    mesaJailson = LoadTextureFromImage(mesaJailson_img);
    mesaJailson.width *= 2;
    mesaJailson.height *= 2;
    // ====================================================== //


    // MESAS HW ============================================= //
    mesa1.texture = LoadTextureFromImage(mesa1.img);
    mesa1.texture.width *= 2;
    mesa1.texture.height *= 2;
    mesa1.x = 156;
    mesa1.y = 168;

    mesa2.texture = LoadTextureFromImage(mesa2.img);
    mesa2.texture.width *= 2;
    mesa2.texture.height *= 2;
    mesa2.x = 106;
    mesa2.y = 274;

    mesa3.texture = LoadTextureFromImage(mesa3.img);
    mesa3.texture.width *= 2;
    mesa3.texture.height *= 2;
    mesa3.x = 56;
    mesa3.y = 382;

    mesa4.texture = LoadTextureFromImage(mesa4.img);
    mesa4.texture.width *= 2;
    mesa4.texture.height *= 2;
    mesa4.x = 726;
    mesa4.y = 168;

    mesa5.texture = LoadTextureFromImage(mesa5.img);
    mesa5.texture.width *= 2;
    mesa5.texture.height *= 2;
    mesa5.x = 676;
    mesa5.y = 274;

    mesa6.texture = LoadTextureFromImage(mesa6.img);
    mesa6.texture.width *= 2;
    mesa6.texture.height *= 2;
    mesa6.x = 626;
    mesa6.y = 382;

    mesa7.texture = LoadTextureFromImage(mesa7.img);
    mesa7.texture.width *= 2;
    mesa7.texture.height *= 2;
    mesa7.x = 576;
    mesa7.y = 492;

    // ===================================================== //



    // �UDIOS ============================================== //
    som_choque = LoadSound("assets/audio_choque.wav");
    som_jequiti = LoadSound("assets/audio_jequiti.wav");
    som_vitoria = LoadSound("assets/audio_vitoria.wav");
    som_gameover = LoadSound("assets/audio_gameover.wav");

    tocouChoque = false;
    tocouJequiti = false;
    tocouVitoria = false;
    tocouGameOver = false;
    // ===================================================== //
}

void GameplayScreen::VitoriaOuDerrota() {
    if (player.vivo == false) {

        // �udio de derrota
        if (tocouGameOver == false) {
            PlaySound(som_gameover);
            tocouGameOver = true;
        }

        // Anima��o bonequinho dead

    }

    if (player.ganhou == true) {

        // �udio de vit�ria
        if (tocouVitoria == false) {
            PlaySound(som_vitoria);
            tocouVitoria = true;
        }

        // Bonequinho vira GIF
    }
}

void GameplayScreen::GIFsBack() {
    frameCounterChoque++;
    if (frameCounterChoque >= frameDelayChoque) {
        frameCounterChoque = 0;
        currentFrameChoque = (currentFrameChoque + 1) % 2;
        sourceRecChoque.x = (float)(currentFrameChoque * 540.0f);
    }

    frameCounterFinal++;
    if (frameCounterFinal > frameDelayFinal) {
        frameCounterFinal = 0;
        currentFrameFinal = (currentFrameFinal + 1) % 2;
        sourceRecFinal.x = (float)(currentFrameFinal * 540.0f);
    }

    frameCounterEquacao++;
    if (frameCounterEquacao > frameDelayEquacao) {
        frameCounterEquacao = 0;
        currentFrameEquacao = (currentFrameEquacao + 1) % 4;
        sourceRecEquacao.x = (float)(currentFrameEquacao * 540.0f);
    }

    frameCounterInicial++;
    if (frameCounterInicial > frameDelayInicial) {
        frameCounterInicial = 0;


        if (currentFrameInicial < 33) {


            // Avan�a o frame atual com looping
            currentFrameInicial = (currentFrameInicial + 1) % totalFramesInicial;



            // Calcula coluna e linha na nova grade
            int col = currentFrameInicial % framesPerRowInicial;
            int row = currentFrameInicial / framesPerRowInicial;

            // Atualiza a regi�o de origem (sourceRec)
            sourceRecInicial.x = (float)(col * frameWidthInicial);
            sourceRecInicial.y = (float)(row * frameHeightInicial);

        }

        else {
            qualTela = 1;
        }
    }
}

void GameplayScreen::Jogo() {
    DeterminarBackground();
    DesenhoPlayerMesas();

    if (boss.etapa == 0 || (boss.etapa == 1 && boss.timer <= 180)) boss.DrawSD();

    if (boss.lifeBarSD <= 0 && boss.timer <= 300) {
        boss.spriteSD = bossMorto;
    }
    else if (boss.lifeBarSD > 0) {
        boss.spriteSD = bossNormal;
    }

    boss.AtaqueSD(&vec);
    if ((player.x - vec.cx) * (player.x - vec.cx) + (player.y - vec.cy) * (player.y - vec.cy) <= 900 && boss.etapa == 0) player.vivo = false;
    else if (boss.etapa != 0) { vec.cx = boss.positionSD.x; vec.cy = boss.positionSD.y; }
    Etapas();
    MudarEtapa();
    VitoriaOuDerrota();

    // Para fins debugu�sticos
    std::cout << "TIMER: " << boss.timer << std::endl;
    //std::cout << "ETAPA: " << boss.etapa << std::endl;

    boss.Health(player);
}

