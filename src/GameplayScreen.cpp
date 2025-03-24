#include "raylib.h"
#include "screens.hpp"
#include "animation.hpp"
#include "gameplay.hpp"

GameplayScreen::GameplayScreen() :
    framesCounter(0), finishScreen(0) {
}

GameplayScreen::~GameplayScreen() {
    Unload();
}

void GameplayScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
	Player player({ 400, 225 }, 100.0f, 5.0f, 20.0f, WHITE, Animation("rsc/player_idle.png", 4, 0.1f, 0.2f), Animation("rsc/player_run.png", 4, 0.1f, 0.2f), Animation("rsc/player_dash.png", 4, 0.1f, 0.2f), Animation("rsc/player_attack.png", 4, 0.1f, 0.2f), Animation("rsc/player_die.png", 4, 0.1f, 0.2f));
}

void GameplayScreen::Update() {
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

void GameplayScreen::Draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize * 3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

void GameplayScreen::Unload() {

}

bool GameplayScreen::Finish() const {
    return finishScreen;
}
