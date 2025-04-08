#include "raylib.h"
#include "screens.hpp"

TitleScreen::TitleScreen() :
    framesCounter(0), finishScreen(-1),
    index_select(0), state(0),
    size_ref_options(80), option_width(200), option_height(70), pos_title({ 10, 20 }) {
    screen_select[0] = GAMEPLAY;
    screen_select[1] = ENDING;
}

TitleScreen::~TitleScreen() {
	//Unload();
}

void TitleScreen::Init() {

	title_image = LoadImage("rsc/fundomenu.png");
	buttons_image = LoadImage("rsc/buttonss.png");
    
    texture_title = LoadTextureFromImage(title_image);
    texture_buttons = LoadTextureFromImage(buttons_image);

	ImageResize(&buttons_image, 5 * buttons_image.width, 5 * buttons_image.height);

    framesCounter = 0;
    finishScreen = -1;

    index_select = 0;

    state = 0;

    size_ref_options = 130;

    option_width = 300 * 1.5;
    option_height = 100 * 1.5;

    screen_select[0] = GAMEPLAY;
    screen_select[1] = OPTIONS;
	screen_select[2] = ENDING;

	option_fonts[0].name = "PLAY";
	option_fonts[1].name = "OPTIONS";
	option_fonts[2].name = "EXIT";

    pos_title = { 10, 20 };
}

void TitleScreen::Update() {
    if (state == 0) {
		index_select = -1;
        
        for (int i = 0; i < 3; i++)
			if (CheckCollisionPointRec(GetMousePosition(), { (float) GetScreenWidth() / 2 - 5 * texture_buttons.width / 2, (float) GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options, (float) 5 * texture_buttons.width, (float) 5 * texture_buttons.height / 3 })) {
                Color pixel = GetImageColor(buttons_image, GetMouseX() - GetScreenWidth() / 2 + buttons_image.width / 2, GetMouseY() - GetScreenHeight() / 2 + buttons_image.height / 6 - i * size_ref_options);
                
                TraceLog(LOG_INFO, "cor do pixel central: r=%d, g=%d, b=%d, a=%d",
                    pixel.r, pixel.g, pixel.b, pixel.a);

				if (pixel.a >= 250) {
					index_select = i;

					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						PlaySound(fxCoin);
						state = 1;
					}
				}
			}
        /*
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT)) {
            //som
            index_select = (index_select - 1 + 3) % 3;
        }
        else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT)) {
            //som
            index_select = (index_select + 1) % 3;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            PlaySound(fxCoin);
            state = 1;
        }
        */
    }
    else if (state == 1) {
        framesCounter++;

        if (framesCounter == 2 * GetFPS()) {
            finishScreen = screen_select[index_select];
        }
    }
}

void TitleScreen::Draw() const {
    DrawTextureEx(texture_title, { 0, 0 }, 0.0f, 2.0f, WHITE);
    
    if (state == 0) {
        for (int i = 0; i < 3; i++) {
			Vector2 fontSize = MeasureTextEx(font, option_fonts[i].name, 50, 4);

            if (i == index_select) {
                DrawTexturePro(texture_buttons,
                    { 0, (float) texture_buttons.height / 3 , (float) texture_buttons.width, (float) texture_buttons.height / 3 },
                    { (float) GetScreenWidth() / 2 - 5 * texture_buttons.width / 2, (float) GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options, (float) 5 * texture_buttons.width, (float) 5 * texture_buttons.height / 3 },
                    { 0, 0 }, 0.0f, WHITE);
            }
            else {
                DrawTexturePro(texture_buttons,
                    { 0, 0, (float) texture_buttons.width, (float) texture_buttons.height / 3 },
                    { (float) GetScreenWidth() / 2 - 5 * texture_buttons.width / 2, (float) GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options, (float) 5 * texture_buttons.width, (float) 5 * texture_buttons.height / 3 },
                    { 0, 0 }, 0.0f, WHITE);
            }

            DrawTextEx(font, option_fonts[i].name, { (float)GetScreenWidth() / 2 - fontSize.x / 2, (float)GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options + fontSize.y / 2 }, 50, 4, { 75, 29, 31, 255 });
        }
    }
    else if (state == 1) {
        for (int i = 0; i < 3; i++) {
            Vector2 fontSize = MeasureTextEx(font, option_fonts[i].name, 50, 4);

            if (i == index_select) {
                DrawTexturePro(texture_buttons,
                    { 0, (float) 2 * texture_buttons.height / 3 , (float) texture_buttons.width, (float)texture_buttons.height / 3},
                    { (float)GetScreenWidth() / 2 - 5 * texture_buttons.width / 2, (float)GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options, (float) 5 * texture_buttons.width, (float) 5 * texture_buttons.height / 3 },
                    { 0, 0 }, 0.0f, WHITE);
                DrawTextEx(font, option_fonts[i].name, { (float)GetScreenWidth() / 2 - fontSize.x / 2, (float)GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options + fontSize.y / 2 }, 50, 4, { 247, 183, 186, 255 });
            }
            else {
                DrawTexturePro(texture_buttons,
                    { 0, 0, (float)texture_buttons.width, (float)texture_buttons.height / 3 },
                    { (float)GetScreenWidth() / 2 - 5 * texture_buttons.width / 2, (float)GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options, (float)5 * texture_buttons.width, (float)5 * texture_buttons.height / 3 },
                    { 0, 0 }, 0.0f, WHITE);
                DrawTextEx(font, option_fonts[i].name, { (float)GetScreenWidth() / 2 - fontSize.x / 2, (float)GetScreenHeight() / 2 - 5 * texture_buttons.height / 6 + i * size_ref_options + fontSize.y / 2 }, 50, 4, { 75, 29, 31, 255 });

            }
        }
    }
    
}

void TitleScreen::Unload() {
	UnloadImage(title_image);
	UnloadImage(buttons_image);
	UnloadTexture(texture_title);
	UnloadTexture(texture_buttons);
	UnloadSound(fxCoin);
}

int TitleScreen::Finish() {
    return finishScreen;
}
