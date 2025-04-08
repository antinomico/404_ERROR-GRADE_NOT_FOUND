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
}

GameplayScreen::~GameplayScreen() {
    Unload();
}

void GameplayScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
	Player player({ 400.0f, 255.0f }, 100.0f, 5.0f, 5.0f, 20.0f, 20.0f, RED);
}

void GameplayScreen::Update() {
    if (IsKeyPressed(KEY_ESCAPE)) {
		if (state == PAUSE)
			state = lastState;
		else
			state = PAUSE;
        PlaySound(fxCoin);
    }
    else {
        if (state == PAUSE)
            state = PAUSE;
        else if (state == PROLOGUE) {
            // se o player pressionar qualquer tecla tirando o ESC 
			state = lastState = SD_BATTLE;
        }
        else if (state == SD_BATTLE) {
            // se o player ou boss morrerem
        }
		else if (state == TRANSITION) {
			// se o player pressionar qualquer tecla tirando o ESC
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
    if (state == PAUSE) {
        // tela de pausee
    }
	else if (state == PROLOGUE) {
		// tela de prologo
	}
	else if (state == SD_BATTLE) {
		// tela de batalha
		player.PosUpdate();
		player.AnimUpdate();
		player.Draw();
	}
	else if (state == TRANSITION) {
		// tela de transição e init do player
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
