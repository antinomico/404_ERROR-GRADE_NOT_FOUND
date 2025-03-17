#include "raylib.h"

//#if defined(PLATFORM_WEB)
//    #include <emscripten/emscripten.h>
//#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Project PI");

    Texture2D texture = LoadTexture("rsc\\HC.png");

    float scale = 0.2f;

    //InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    //font = LoadFont("resources/mecha.png");
    //music = LoadMusicStream("resources/ambient.ogg"); // TODO: Load music
    //fxCoin = LoadSound("resources/coin.wav");

    //SetMusicVolume(music, 1.0f);
    //PlayMusicStream(music);

    // Setup and init first screen
    //currentScreen = LOGO_RL;
    //InitLogoRLScreen();

#if defined(PLATFORM_WEB)
//    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureEx(texture, (Vector2) { screenWidth / 16, screenHeight / 4}, 0.0f, scale, WHITE);

        EndDrawing();
        //UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    //switch (currentScreen)
    //{
    //    case LOGO: UnloadLogoScreen(); break;
    //    case TITLE: UnloadTitleScreen(); break;
    //    case OPTIONS: UnloadOptionsScreen(); break;
    //    case GAMEPLAY: UnloadGameplayScreen(); break;
    //    case ENDING: UnloadEndingScreen(); break;
    //    default: break;
    //}

    // Unload global data loaded
    //UnloadFont(font);
    //UnloadMusicStream(music);
    //UnloadSound(fxCoin);

    //CloseAudioDevice();     // Close audio context
    UnloadTexture(texture);

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
