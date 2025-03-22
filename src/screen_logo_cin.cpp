#include "raylib.h"
#include "screens.hpp"

LogoCINScreen::LogoCINScreen() :
    finishScreen(false), framesCounter(0),
    widthLogo(0), heightLogo(0),
    state(0), scale(0.2f), fadeSpeed(0.0f), alpha(0.0f),
    visibleWidth(0.0f), revealSpeed(2.0f),
    cin_image(), texture() {
}

LogoCINScreen::~LogoCINScreen() {
    //Unload();
}

void LogoCINScreen::Init() {
    finishScreen = false;
    framesCounter = 0;

    widthLogo = 0;
    heightLogo = 0;

    state = 0;
    scale = 0.2f;
    alpha = 0.0f;

    visibleWidth = 0.0f;
    revealSpeed = 2.0f;

    cin_image = LoadImage("rsc\\HC.png");
    ImageResize(&cin_image, scale * cin_image.width, scale * cin_image.height);
    texture = LoadTextureFromImage(cin_image);
}

void LogoCINScreen::Update() {
    if (state == 0) {
        if (visibleWidth < (float) texture.width / 3)
            visibleWidth += revealSpeed;
        else
            state = 1;
    }
    else if (state == 1) {
        framesCounter++;

        if (framesCounter == 2 * GetFPS())
            state = 2;
    }
    else if (state == 2) {
        alpha += 0.01f;

        if (alpha >= 1.0f)
            finishScreen = true;
    }
}

void LogoCINScreen::Draw() {
    if (state == 0) {
        DrawTextureRec(
            texture,
            { 0, 0, visibleWidth, (float) texture.height },
            { (float) (GetScreenWidth() - texture.width) / 2, (float) (GetScreenHeight() - texture.height) / 2 },
            RAYWHITE
        );
    }
    else if (state == 1) {
        DrawTextureRec(
            texture,
            { 0, 0, (float) texture.width, (float) texture.height },
            { (float) (GetScreenWidth() - texture.width) / 2, (float) (GetScreenHeight() - texture.height) / 2 },
            RAYWHITE
        );
    }
    else if (state == 2) {
        DrawTextureRec(
            texture,
            { 0, 0, (float) texture.width, (float) texture.height },
            { (float) (GetScreenWidth() - texture.width) / 2, (float) (GetScreenHeight() - texture.height) / 2 },
            RAYWHITE
        );

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, alpha));
    }
}

void LogoCINScreen::Unload() {
    UnloadImage(cin_image);
    UnloadTexture(texture);
}

bool LogoCINScreen::Finish() const {
    return finishScreen;
}
