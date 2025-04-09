#include "raylib.h"
#include "raymath.h"
#include "screens.hpp"
#include "animation.hpp"
#include "gameplay.hpp"

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
}

GameplayScreen::~GameplayScreen() {
    Unload();
}

void GameplayScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;

	Player player({ 400.0f, 255.0f }, 100.0f, 5.0f, 5.0f, 20.0f, 20.0f, RED);

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
		
		}
        else if (state == PROLOGUE) {
			if (currentIndexFontGame <= 3) {
				for (int i = 0; i <= currentIndexFontGame; i++) {
					if (GetKeyPressed() && dialogText.IsFinished()) {
						currentIndexFontGame++;
						dialogText.Init(fontGame[currentIndexFontGame].name.c_str(),
							{ (float)GetScreenWidth() / 2 - (float)MeasureText(fontGame[currentIndexFontGame].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f });
					}
					else {
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
					state = lastState = TRANSITION;

					background = LoadTexture("rsc/inicio_al.png");

					currentIndexFontGame = 0;

					frameCounterInicial = 0;
					frameDelayInicial = 20;
					currentFrameInicial = 0;
					colFrameInicial = 0;
					rowFrameInicial = 0;

					fontGame[0].name = "UUUGGGGHHH!! Cintio conseguira escapar do choque do laboratorio de hardware";
					fontGame[1].name = "Desesperado, decidiu buscar ajuda a um conhecido professor de algebra linear";
					fontGame[2].name = "Querendo entender o que tinha ocorrido no CIn, finalmente ele chega à sua sala...";
					fontGame[3].name = "Porem logo escutara um barulho estranho... MAS O QUE?!!!";

					dialogText.Init(fontGame[0].name.c_str(),
						{ (float)GetScreenWidth() / 2 - (float)MeasureText(fontGame[0].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f });
				}
			}
        }
        else if (state == SD_BATTLE) {
            // se o player ou boss morrerem
        }
		else if (state == TRANSITION) {
			if (currentIndexFontGame <= 3) {
				for (int i = 0; i <= currentIndexFontGame; i++) {
					if (GetKeyPressed() && dialogText.IsFinished()) {
						currentIndexFontGame++;
						dialogText.Init(fontGame[currentIndexFontGame].name.c_str(),
							{ (float)GetScreenWidth() / 2 - (float)MeasureText(fontGame[currentIndexFontGame].name.c_str(), 24) / 2, GetScreenHeight() - 60.0f });
					}
					else {
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
		if (state == SD_BATTLE) {
			// tela de game over SD
		}
		else if (state == AL_BATTLE) {
			// tela de game over AL
		}
	}
	else if (state == PAUSE) {
        // tela de pausee
    }
	else if (state == PROLOGUE) {		
		DrawTexturePro(background,
			{ (float)(colFrameInicial * 540), (float)(rowFrameInicial * 360), 540.0f, 360.0f },
			{ 0.0f, 0.0f, (float) GetScreenWidth(), (float) GetScreenHeight()},
			{ 0, 0 }, 0.0f, WHITE);
		
		if (currentIndexFontGame <= 3) {
			DrawRectangle(20.0f + 90.0f, GetScreenHeight() - 90.0f, GetScreenWidth() - 40.0f - 180.0f, 75.0f, Fade(BLACK, 0.5f));
			dialogText.Draw();
		}

		// tela de prologo
	}
	else if (state == SD_BATTLE) {
		// tela de batalha
		player.PosUpdate();
		player.AnimUpdate();
		player.Draw();
	}
	else if (state == TRANSITION) {
		DrawTexturePro(background,
			{ (float)(currentFrameInicial * 540), 0.0f, 540.0f, 360.0f },
			{ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() },
			{ 0, 0 }, 0.0f, WHITE);

		dialogText.Draw();
	}
	else if (state == AL_BATTLE) {
		// tela de batalha
		player.PosUpdate();
		player.AnimUpdate();
		player.Draw();

	}
	else if (state == EPILOGUE) {
		// tela de epilogo
	}
}

void GameplayScreen::Unload() {

}

bool GameplayScreen::Finish() const {
    return finishScreen;
}
