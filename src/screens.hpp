#ifndef SCREENS_HPP
#define SCREENS_HPP

#include <iostream> using namespace std;
#include <vector>
#include <string>

#include "raylib.h"
#include "player.hpp"
#include "gameplay.hpp"
#include "sd_game.hpp"

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
	std::string name;
}   OptionFonts;

typedef struct GameFonts {
    std::string name;
}   GameFonts;

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

        int state;
        float alpha;
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
        //void Init();
        void DrawPlayerMesas();
        void DeterminarBackground();
        void DesenhoPlayerMesas();
        void MudarEtapa();
        void Etapas();
        void Liberar();
        void InitPlayer();
        void InitCenario();
        void VitoriaOuDerrota();
        void GIFsBack();
        void Jogo();

        
    private:
        Texture2D background;

        Dialog dialogText;
		GameFonts fontGame[4];

        int currentIndexFontGame;

        int framesCounter;
        bool finishScreen;
		int state;
        int lastState;

        int frameCounterInicial;
        int frameDelayInicial;
        int currentFrameInicial;
        int colFrameInicial;
        int rowFrameInicial;

        BossSD boss;
        Player player;
        MesaHW	mesa1,
            mesa2,
            mesa3,
            mesa4,
            mesa5,
            mesa6,
            mesa7;

        Texture2D background_SD;
        Texture2D mesas_SD;
        Texture2D mesaJailson;
        Texture2D background_SD_MapaK_Vazio;
        Texture2D tela_gameover_SD;

        Texture2D spritesheet_choque;
        Texture2D spritesheet_final;
        Texture2D spritesheet_equacao;
        Texture2D spritesheet_inicial;

        Texture2D bossNormal;
        Texture2D bossMorto;

        Image background_SD_img;
        Image mesas_SD_img;
        Image mesaJailson_img;
        Image background_SD_MapaK_Vazio_img;
        Image tela_gameover_SD_img;

        Rectangle sourceRecChoque;
        Rectangle destRecChoque;

        Rectangle sourceRecEquacao;
        Rectangle destRecEquacao;

        Rectangle sourceRecFinal;
        Rectangle destRecFinal;

        Rectangle sourceRecInicial;
        Rectangle destRecInicial;

        chicote vec;

        Sound som_choque;
        Sound som_jequiti;
        Sound som_vitoria;
        Sound som_gameover;

        float angle_deg = 24.9547f;

        int currentFrameChoque;
        int frameCounterChoque;
        int frameDelayChoque;

        int currentFrameEquacao;
        int frameCounterEquacao;
        int frameDelayEquacao;

        int currentFrameFinal;
        int frameCounterFinal;
        int frameDelayFinal;

        int totalFramesInicial;
        int framesPerRowInicial;
        int frameWidthInicial;
        int frameHeightInicial;

        int estadoAnterior;
        int qualTela; // 0 - Inicial // 1 - Jogo // 2 - Transição

        bool tocouChoque;
        bool tocouJequiti;
        bool tocouVitoria;
        bool tocouGameOver;
        bool foiZerado;
        bool finalGIF;


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
        Texture2D credits;
        
        int framesCounter;
        bool finishScreen;
        float alpha;

        int state;
};

#endif // SCREENS_HPP