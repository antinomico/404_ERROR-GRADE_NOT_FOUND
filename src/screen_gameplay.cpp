#include "raylib.h"
#include "screens.hpp"

GameplayScreen::GameplayScreen() :
    framesCounter(0), finishScreen(0) {
}

GameplayScreen::~GameplayScreen() {
    Unload();
}

void GameplayScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
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
