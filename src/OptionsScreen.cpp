#include "raylib.h"
#include "screens.hpp"

OptionsScreen::OptionsScreen() :
    framesCounter(0), finishScreen(0) {
}

OptionsScreen::~OptionsScreen() {
	Unload();
}

void OptionsScreen::Init() {
    framesCounter = 0;
    finishScreen = 0;
}

void OptionsScreen::Update() {
}

void OptionsScreen::Draw() {
}

void OptionsScreen::Unload() {
}

bool OptionsScreen::Finish() const {
    return finishScreen;
}
