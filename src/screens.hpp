#ifndef SCREENS_HPP
#define SCREENS_HPP

#include "raylib.h"
#include "gameplay.hpp"

// enumeração para identificar as telas
typedef enum GameScreen {
    UNKNOWN = -1,
    LOGO_RL = 0,
    LOGO_CIN = 1,
    TITLE = 2,
    OPTIONS = 3,
    GAMEPLAY = 4,
    ENDING = 5
};

typedef struct OptionFonts {
	const char* name;
}   OptionFonts;

// variáveis globais (compartilhadas entre as telas)
extern GameScreen currentScreen;
extern Font font;
extern Music music;
extern Sound fxCoin;

// tela de logo do Raylib
class LogoRLScreen {
    public:
        LogoRLScreen();
		~LogoRLScreen();
        
        void Init();
        void Update();
        void Draw();
        void Unload();
        bool Finish() const;

    private:
        int framesCounter;
        bool finishScreen;

        int logoPositionX;
        int logoPositionY;

        int lettersCount;

        int topSideRecWidth;
        int leftSideRecHeight;
        int bottomSideRecWidth;
        int rightSideRecHeight;

        int state;              // Logo animation states
        float alpha;            // Useful for fading
};

// tela de logo do CIn
class LogoCINScreen {
    public:
		LogoCINScreen();
		~LogoCINScreen();
        
        void Init();
        void Update();
        void Draw();
        void Unload();
        bool Finish() const;

    private:
        Image cin_image;
        Texture2D texture;

        int framesCounter;
        bool finishScreen;

        int widthLogo;
        int heightLogo;

        int state;

        float scale;
        float fadeSpeed;
        float alpha;

        float visibleWidth;
        float revealSpeed;
};

// tela do menu principal
class TitleScreen {
    public:
		TitleScreen();
		~TitleScreen();
        
        void Init();
        void Update();
        void Draw() const;
        void Unload();
        int Finish();

    private:
        Vector2 pos_title;

		Image title_image;
		Image buttons_image;

		Texture2D texture_title;
		Texture2D texture_buttons;

        OptionFonts option_fonts[3];

        int framesCounter;
        int finishScreen;

        int index_select;

        int state;

        int size_ref_options;

        int option_width;
        int option_height;

        int screen_select[3];
};

// tela de opções
class OptionsScreen {
    public:
		OptionsScreen();
		~OptionsScreen();
        
        void Init();
        void Update();
        void Draw();
        void Unload();
        bool Finish() const;

    private:
	    int framesCounter;
	    bool finishScreen;

};

// tela de gameplay
class GameplayScreen {
    public:
		GameplayScreen();
		~GameplayScreen();
        
        void Init();
        void Update();
        void Draw();
        void Unload();
        bool Finish() const;
        
    private:
        Player player;

        int framesCounter;
        bool finishScreen;
		int state;
        int lastState;
};

// tela de finalização
class EndingScreen {
    public:
		EndingScreen();
		~EndingScreen();
        
        void Init();
        void Update();
        void Draw();
        void Unload();
        bool Finish() const;

    private:
        int framesCounter;
        bool finishScreen;
};

#endif // SCREENS_HPP