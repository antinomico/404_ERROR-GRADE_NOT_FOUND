#include "raylib.h"
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;

static int logoPositionX = 0;
static int logoPositionY = 0;

static int widthLogo = 0;
static int heightLogo = 0;

static int state = 0;
static float alpha = 1.0f;
static float scale = 1.0f;
static float fadeSpeed = 1.0f;

static Image cin_image;
static Texture2D texture;

static float visibleWidth = 0.0f;
static float revealSpeed = 2.0f;

void InitLogoCINScreen(void) {
    finishScreen = 0;
    framesCounter = 0;

    logoPositionX = GetScreenWidth() / 16;
    logoPositionY = GetScreenHeight() / 4;

    widthLogo = 0;
    heightLogo = 0;

    state = 0;
    alpha = 1.0f;
    scale = 0.2f;
    fadeSpeed = 0.001f;

    visibleWidth = 0.0f;
    revealSpeed = 3.0f;

    cin_image = LoadImage("rsc\\HC.png");
    ImageResize(&cin_image, scale * cin_image.width, scale * cin_image.height);
    texture = LoadTextureFromImage(cin_image);
}

void UpdateLogoCINScreen(void) {
    if (state == 0) {
        framesCounter++;

        if (visibleWidth < texture.width / 3) {
            visibleWidth += revealSpeed;
        }
        else {
            state = 1;
            framesCounter = 0;
        }
    }
    else if (state == 1) {
        framesCounter++;
        
        if (framesCounter == 5 * GetFPS())
            finishScreen = 1;
    }
}

void DrawLogoCINScreen(void) {

    if (state == 0) {
        DrawTextureRec(
            texture,
            (Rectangle) {
            0, 0, visibleWidth, texture.height
        },
            (Vector2) {
            (GetScreenWidth() - texture.width) / 2, (GetScreenHeight() - texture.height) / 2
        },
            WHITE
        );
    }
    else if (state == 1) {
        DrawTextureRec(
            texture,
            (Rectangle) {
            0, 0, texture.width, texture.height
        },
            (Vector2) {
            (GetScreenWidth() - texture.width) / 2, (GetScreenHeight() - texture.height) / 2
        },
            WHITE
        );
    }
}

void UnloadLogoCINScreen(void) {
    UnloadTexture(texture);
    UnloadImage(cin_image);
}

int FinishLogoCINScreen(void) {
    return finishScreen;
}
