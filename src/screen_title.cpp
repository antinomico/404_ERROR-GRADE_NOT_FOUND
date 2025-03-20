#include "raylib.h"
#include "screens.hpp"

TitleScreen::TitleScreen() :
    framesCounter(0), finishScreen(false),
    index_select(0), state(0),
    size_ref_options(80), option_width(200), option_height(70), pos_title({ 10, 20 }) {
    screen_select[0] = GAMEPLAY;
    screen_select[1] = OPTIONS;
    screen_select[2] = ENDING;
}

TitleScreen::~TitleScreen() {
	Unload();
}

void TitleScreen::Init() {
    framesCounter = 0;
    finishScreen = false;

    index_select = 0;

    state = 0;

    size_ref_options = 80;

    option_width = 200;
    option_height = 70;

    screen_select[0] = GAMEPLAY;
    screen_select[1] = OPTIONS;
    screen_select[2] = ENDING;

    pos_title = { 10, 20 };
}

void TitleScreen::Update() {
    if (state == 0) {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT)) {
            //som
            index_select = (index_select - 1 + 3) % 3;
        }
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT)) {
            //som
            index_select = (index_select + 1) % 3;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            PlaySound(fxCoin);
            state = 1;
        }
    }
    else if (state == 1) {
        framesCounter++;

        if (framesCounter == 3 * GetFPS()) {
            finishScreen = screen_select[index_select];
        }
    }
}

void TitleScreen::Draw() {
    if (state == 0) {
        for (int i = 0; i < 3; i++) {
            if (i == index_select) {
                DrawRectangle(GetScreenWidth() / 2 - option_width / 2, GetScreenHeight() / 2 - option_height / 2 + i * size_ref_options, option_width, option_height, RED);
            }
            else {
                DrawRectangle(GetScreenWidth() / 2 - option_width / 2, GetScreenHeight() / 2 - option_height / 2 + i * size_ref_options, option_width, option_height, BLUE);
            }
        }
    }
    else if (state == 1) {
        for (int i = 0; i < 3; i++) {
            if (i == index_select) {
                DrawRectangle(GetScreenWidth() / 2 - option_width / 2, GetScreenHeight() / 2 - option_height / 2 + i * size_ref_options, option_width, option_height, YELLOW);
            }
            else {
                DrawRectangle(GetScreenWidth() / 2 - option_width / 2, GetScreenHeight() / 2 - option_height / 2 + i * size_ref_options, option_width, option_height, BLUE);
            }
        }
    }

    DrawText("CRAZY GAME", GetScreenWidth() / 2 - 50, 50, 20, DARKGREEN);
}

void TitleScreen::Unload() {

}

int TitleScreen::Finish() {
    return index_select;
}
