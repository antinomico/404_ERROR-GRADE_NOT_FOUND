#include "raylib.h"
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;

static int widthLogo = 0;
static int heightLogo = 0;

static int state = 0;

static float scale = 0.0f;
static float fadeSpeed = 0.0f;
static float alpha = 0.0f;

static Image cin_image;
static Texture2D texture;

static float visibleWidth = 0.0f;
static float revealSpeed = 0.0f;

void InitLogoCINScreen(void) {
    finishScreen = 0;
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

void UpdateLogoCINScreen(void) {
    if (state == 0) {

        if (visibleWidth < (float) texture.width / 3) {
            visibleWidth += revealSpeed;
        }
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
            RAYWHITE
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
            RAYWHITE
        );
    }
    else if (state == 2) {
        DrawTextureRec(
            texture,
            (Rectangle) {
            0, 0, texture.width, texture.height
        },
            (Vector2) {
            (GetScreenWidth() - texture.width) / 2, (GetScreenHeight() - texture.height) / 2
        },
            RAYWHITE
        );

        DrawRectangle(
            0, 0, GetScreenWidth(), GetScreenHeight(),
            Fade(RAYWHITE, alpha)
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
