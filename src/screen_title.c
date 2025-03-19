#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

static int index_select = 0;

static int state = 0;

static int size_ref_options = 0;

static int option_width = 0;
static int option_height = 0;

static int screen_select[3] = { 0, 0, 0 };

static Vector2 pos_title = { 0, 0 };

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;

	index_select = 0;

    state = 0;

    size_ref_options = 80;

    option_width = 200;
    option_height = 70;

	screen_select[0] = GAMEPLAY;
	screen_select[1] = OPTIONS;
	screen_select[2] = ENDING;
	//screen_select[3] = EXIT;

    static Vector2 pos_title = { 10, 20 };
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    if (state == 0) {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT)) {
            //som
            index_select = (index_select - 1 + 3) % 3;
        }
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT)) {
            //som
            index_select = (index_select + 1) % 3;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            PlaySound(fxCoin);
            state = 1;
        }
    }
    else if (state == 1) {
		framesCounter++;

		if (framesCounter == 3 * GetFPS())
            finishScreen = index_select;
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    //DrawTextEx(font, "GAME CRAZY", (Vector2) { GetScreenWidth() / 2, 50 }, font.baseSize * 3.0f, 4, DARKGREEN);
    
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


    DrawText("GAME CRAZY", GetScreenWidth() / 2 - 50, 50, 20, DARKGREEN);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{

}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}