#include "raylib.h"
#include "screens.hpp"

EndingScreen::EndingScreen() :
	framesCounter(0), finishScreen(0), credits{ 0 }, alpha(0), state(0) {
}

EndingScreen::~EndingScreen() {
}

void EndingScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
    alpha = 0.0f;
    state = 0;

	credits = LoadTexture("rsc/creditos.png");
}

void EndingScreen::Update() {
    if (state == 0) {
		framesCounter++;
		if (framesCounter > 120)
			state = 1;
    }
	else if (state == 1) {
		alpha += 0.01f;
		if (alpha >= 1.0f) {
			alpha = 1.0f;
			state = 2;
		}
	}
    else if (state == 2) {
        if (GetKeyPressed()) {
            finishScreen = 1;
            PlaySound(fxCoin);
        }
    }
}

void EndingScreen::Draw() {
    DrawTextureEx(credits, { 0, 0 }, 0.0f, 2.0f, WHITE);
	DrawText("Pressione qualquer tecla para voltar", 10, 10, 20, Fade(WHITE, alpha));
}

void EndingScreen::Unload() {
    UnloadTexture(credits);
}

bool EndingScreen::Finish() const {
    return finishScreen;
}
