#include "raylib.h"
#include "screens.hpp"

EndingScreen::EndingScreen() :
    framesCounter(0), finishScreen(0) {
}

EndingScreen::~EndingScreen() {
	Unload();
}

void EndingScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
}

void EndingScreen::Update() {
    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

void EndingScreen::Draw() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);

    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "ENDING SCREEN", pos, font.baseSize * 3.0f, 4, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
}

void EndingScreen::Unload() {

}

bool EndingScreen::Finish() const {
    return finishScreen;
}
