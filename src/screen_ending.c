#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    // TODO: Initialize ENDING screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // TODO: Update ENDING screen variables here!

    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);

    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "ENDING SCREEN", pos, font.baseSize*3.0f, 4, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    // TODO: Unload ENDING screen variables here!
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}