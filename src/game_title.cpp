#include "raylib.h"
#include "raymath.h"
#include "screens.hpp"

LogoRLScreen logoScreenRL;
LogoCINScreen logoScreenCIN;
TitleScreen titleScreen;
OptionsScreen optionsScreen;
GameplayScreen gameplayScreen;
EndingScreen endingScreen;

GameScreen currentScreen = LOGO_RL;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

static const int screenWidth = 1280;
static const int screenHeight = 720;

static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

static void ChangeToScreen(GameScreen screen);
static void TransitionToScreen(GameScreen screen);
static void UpdateTransition(void);
static void DrawTransition(void);
static void UpdateDrawFrame(void);

int main(void) {
    InitWindow(screenWidth, screenHeight, "Project PI");

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("rsc/mecha.png");
    //music = LoadMusicStream("resources/ambient.ogg");
    fxCoin = LoadSound("rsc/coin.wav");

    //SetMusicVolume(music, 1.0f);
    //PlayMusicStream(music);

    // Setup and init first screen
    currentScreen = GAMEPLAY;
    gameplayScreen.Init();
    //logoScreenRL.Init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    // Unload global data loaded
    UnloadFont(font);
    //UnloadMusicStream(music);
    UnloadSound(fxCoin);

    CloseWindow();
    return 0;
}

static void ChangeToScreen(GameScreen screen) {

    switch (currentScreen) {
        case LOGO_RL: logoScreenRL.Unload(); break;
        case LOGO_CIN: logoScreenCIN.Unload(); break;
        case TITLE: titleScreen.Unload(); break;
        case OPTIONS: optionsScreen.Unload(); break;
        case GAMEPLAY: gameplayScreen.Unload(); break;
        case ENDING: endingScreen.Unload(); break;
        default: break;
    }

    switch (screen) {
        case LOGO_RL: logoScreenRL.Init(); break;
        case LOGO_CIN: logoScreenCIN.Init(); break;
        case TITLE: titleScreen.Init(); break;
        case OPTIONS: optionsScreen.Init(); break;
        case GAMEPLAY: gameplayScreen.Init(); break;
        case ENDING: endingScreen.Init(); break;
        default: break;
    }

    currentScreen = screen;
}

static void TransitionToScreen(GameScreen screen) {
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

static void UpdateTransition(void) {
    if (!transFadeOut) {
        transAlpha += 0.05f;

        if (transAlpha > 1.01f) {
            transAlpha = 1.0f;

            switch (transFromScreen) {
                case LOGO_RL: logoScreenRL.Unload(); break;
                case LOGO_CIN: logoScreenCIN.Unload(); break;
                case TITLE: titleScreen.Unload(); break;
                case OPTIONS: optionsScreen.Unload(); break;
                case GAMEPLAY: gameplayScreen.Unload(); break;
                case ENDING: endingScreen.Unload(); break;
                default: break;
            }

            switch (transToScreen) {
                case LOGO_RL: logoScreenRL.Init(); break;
                case LOGO_CIN: logoScreenCIN.Init(); break;
                case TITLE: titleScreen.Init(); break;
                case OPTIONS: optionsScreen.Init(); break;
                case GAMEPLAY: gameplayScreen.Init(); break;
                case ENDING: endingScreen.Init(); break;
                default: break;
            }

            currentScreen = transToScreen;
            transFadeOut = true;
        }
    }
    else {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f) {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN;
        }
    }
}

static void DrawTransition(void) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

static void UpdateDrawFrame(void) {
    if (!onTransition) {
        switch (currentScreen) {
            case LOGO_RL:
                logoScreenRL.Update();
                if (logoScreenRL.Finish())
                    TransitionToScreen(LOGO_CIN);
                break;

            case LOGO_CIN:
                logoScreenCIN.Update();
                if (logoScreenCIN.Finish())
                    TransitionToScreen(TITLE);
                break;

            case TITLE:
                titleScreen.Update();
                if (titleScreen.Finish() == GAMEPLAY)
                    TransitionToScreen(GAMEPLAY);
                else if (titleScreen.Finish() == OPTIONS)
                    TransitionToScreen(OPTIONS);
                break;

            case OPTIONS:
                optionsScreen.Update();
                if (optionsScreen.Finish())
                    TransitionToScreen(TITLE);
                break;

            case GAMEPLAY:
                gameplayScreen.Update();
                if (gameplayScreen.Finish())
                    TransitionToScreen(ENDING);
                break;

            case ENDING:
                endingScreen.Update();
                if (endingScreen.Finish())
                    TransitionToScreen(TITLE);
                break;

            default: break;
        }
    }
    else
        UpdateTransition();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (currentScreen) {
        case LOGO_RL: logoScreenRL.Draw(); break;
        case LOGO_CIN: logoScreenCIN.Draw(); break;
        case TITLE: titleScreen.Draw(); break;
        case OPTIONS: optionsScreen.Draw(); break;
        case GAMEPLAY: gameplayScreen.Draw(); break;
        case ENDING: endingScreen.Draw(); break;
        default: break;
    }

    if (onTransition)
        DrawTransition();
    
    EndDrawing();
}
