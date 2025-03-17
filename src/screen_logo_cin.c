#include "raylib.h"
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;

static int logoPositionX = 0;
static int logoPositionY = 0;

static int state = 0;
static float alpha = 1.0f;
static float scale = 1.0f;
static float fadeSpeed = 1.0f;

static Texture2D texture;
//static RenderTexture2D mask;

void InitLogoCINScreen(void) {
    finishScreen = 0;
    framesCounter = 0;

    logoPositionX = GetScreenWidth() / 16;
    logoPositionY = GetScreenHeight() / 4;

    state = 0;
    alpha = 1.0f;
    scale = 0.2f;
    fadeSpeed = 0.01f;

    texture = LoadTexture("rsc\\HC.png");
    //RenderTexture2D mask = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void UpdateLogoCINScreen(void) {
    if (state == 0) {
        framesCounter++;

        if (framesCounter == GetFPS() * 5) {
            state = 1;
            framesCounter = 0;
        }
    }
    else if (state == 1) {
        finishScreen = 1;
    }
}

void DrawLogoCINScreen(void) {
    if (state == 0) {
        DrawTextureEx(texture, (Vector2) { logoPositionX, logoPositionY }, 0.0f, scale, WHITE);
    }
}

void UnloadLogoCINScreen(void) {
    UnloadTexture(texture);
}

int FinishLogoCINScreen(void) {
    return finishScreen;
}
