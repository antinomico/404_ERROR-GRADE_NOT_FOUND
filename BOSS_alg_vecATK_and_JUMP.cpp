#include "raylib.h"
#include <cmath>
#include <stdio.h>

#define Hres 1080
#define Vres 720

#define CENTER_x Hres/2
#define CENTER_y Vres/2

#define ATK_COOLDOWN_vec 1

//-----------------------------------------------------------//

struct coords
{
    float x;
    float y;
}; typedef struct coords coords;

struct Player {
    coords posicao;
    float raio_do_player = 20.0f;
};typedef struct Player player; player P;

struct Sapo {
    coords posicao;
    coords posicao_inicial;
    coords posicao_do_pulo;

    bool linguada = true;
    bool pulando = false;
    bool porradao = false;
    bool reduzir_linguadas = true;
    bool tempo_antes_de_pular = false;

    int quantidade_de_linguadas = 5;
    int linguadas_restantes;

    float cooldown_ataque = 0.1f;
    float acompanhar_cd_atk = 0.0f;

    float cooldown_antes_de_pular = 2.0f;
    float acompanhar_cd_pulo = 0.0f;

    float velocidade_do_pulo = 1500.0f;
    float raio_do_sapo = 40.0f;
    float altura_do_pulo = 100.0f;
    float duracao_do_pulo = 0.0f;
}; typedef struct Sapo sapo; sapo S;

typedef struct
{
    float cx;
    float cy;
    float dex;
    float dey;
    int reverse;
}weapon_1; weapon_1 vec;

int dash_t;
int ATK1_COOLDOWNt;
int it;

//-----------------------------------------------------------//

void init()
{
    it = 0;
    dash_t = 0;
    ATK1_COOLDOWNt = 0;

    P.posicao.x = rand() % 1080;
    P.posicao.y = rand() % 720;
    S.posicao.x = CENTER_x;
    S.posicao.y = CENTER_y;

    vec.dex = 0;
    vec.dey = 0;
    vec.cx = 0;
    vec.cy = 0;
    vec.reverse = 0;

    S.posicao_inicial = S.posicao;
    S.acompanhar_cd_atk == S.cooldown_ataque;
    S.linguadas_restantes = S.quantidade_de_linguadas;
}

//-----------------------------------------------------------//

void movement()
{
    if (dash_t > 10) dash_t++;				                //timer do dash, ele é empregado de modo que o jogador não possa ficar usando o dash indefinidamente
    if (dash_t >= 150) dash_t = 0;			                //se o dash_timer for maior que o intervalo de tempo de espera, resete ele, o jogador pode usar o dash 

    if (IsKeyDown(KEY_W)) 
    {  
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            P.posicao.y -= 20;
            dash_t++;
        }
        else P.posicao.y -= 4;
    }
    if (IsKeyDown(KEY_A)) 
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            P.posicao.x -= 20;
            dash_t++;
        }
        else P.posicao.x -= 4;
    }
    if (IsKeyDown(KEY_S)) 
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            P.posicao.y += 20;
            dash_t++;
        }
        else P.posicao.y += 4;
    }
    if (IsKeyDown(KEY_D)) 
    {
        if (dash_t <= 10 && IsKeyDown(KEY_LEFT_CONTROL))		//dash timer <= 50 é para que o dash seja perceptível e suave para o jogador.
        {
            P.posicao.x += 20;
            dash_t++;
        }
        else P.posicao.x += 4;
    }
}

//-----------------------------------------------------------//

void vectoratk()
{
    float dx = vec.dex - S.posicao.x;
    float dy = vec.dey - S.posicao.y;
    DrawLine(S.posicao.x, S.posicao.y, vec.cx, vec.cy, YELLOW);
    if (vec.reverse == 0)
    {
        float mod = 0.01 * sqrt(dx * dx + dy * dy);
        vec.cx += dx / mod;
        vec.cy += dy / mod;
        if (sqrt((vec.cx - S.posicao.x) * (vec.cx - S.posicao.x) + (vec.cy - S.posicao.y) * (vec.cy - S.posicao.y)) >= sqrt(dx * dx + dy * dy)) vec.reverse = 1;
    }
    else
    {
        float mod = 0.06 * sqrt(dx * dx + dy * dy);
        vec.cx -= dx / mod;
        vec.cy -= dy / mod;
        if ((vec.dex > S.posicao.x && vec.dey > S.posicao.y) && (vec.cx <= S.posicao.x || vec.cy <= S.posicao.y)) { vec.reverse = 0;
        S.linguadas_restantes--;it = -1;
        }
        else if ((vec.dex > S.posicao.x && vec.dey < S.posicao.y) && (vec.cx <= S.posicao.x || vec.cy >= S.posicao.y)) { vec.reverse = 0;
        S.linguadas_restantes--;it = -1;
        }
        else if ((vec.dex  < S.posicao.x && vec.dey > S.posicao.y) && (vec.cx >= S.posicao.x || vec.cy <= S.posicao.y)) { vec.reverse = 0;
        S.linguadas_restantes--;it = -1;
        }
        else if ((vec.dex < S.posicao.x && vec.dey < S.posicao.y) && (vec.cx >= S.posicao.x || vec.cy >= S.posicao.y)) { vec.reverse = 0;
        S.linguadas_restantes--; it = -1;
        }
    }
}

//-----------------------------------------------------------//

void ataques_sapo(float controle_de_tempo) //mudar isso, a função ta muito grande e deve ser modularizada de modo a facilitar a legibilidade do codigo.
{
    //-----------------------------------------------------// LINGUADA:
    if (S.linguada == true) {
        if (S.linguadas_restantes <= 0) {
            S.linguada = false;
            S.tempo_antes_de_pular = true;
            S.acompanhar_cd_pulo = S.cooldown_antes_de_pular;
        }

        else {
            if (it == 50)
            {
                vec.cx = (S.posicao.x);
                vec.cy = (S.posicao.y);
                vec.dex = (P.posicao.x);
                vec.dey = (P.posicao.y);
            }
            else if (it > 50) 
            {
                if (S.posicao.y == P.posicao.y) S.posicao.y += 1;
                if (S.posicao.x == P.posicao.x) S.posicao.x += 1;
                vectoratk(); 
            }
            it++;
        }
    }
    //-----------------------------------------------------// PULO / PORRADÃO:

    if (S.tempo_antes_de_pular == true) {
        S.acompanhar_cd_pulo -= controle_de_tempo;

        if (S.acompanhar_cd_pulo <= 0.0f) {
            S.tempo_antes_de_pular = false;
            S.pulando = true;

            S.posicao_do_pulo = P.posicao;
            S.posicao_inicial = S.posicao;

            S.duracao_do_pulo = 0.0f;
        }
    }

    if (S.pulando == true) {
        S.duracao_do_pulo += controle_de_tempo * 1.5f;

        float fator_mult = S.duracao_do_pulo / 0.7f;

        if (fator_mult > 1.0f) {
            fator_mult = 1.0f;
        }

        // EIXO X:
        S.posicao.x = S.posicao_inicial.x + (S.posicao_do_pulo.x - S.posicao_inicial.x) * fator_mult;

        // EIXO Y:
        float altura = -4 * pow((fator_mult - 0.5f), 2) + 1;

        S.posicao.y = S.posicao_inicial.y - (altura * S.altura_do_pulo) + (S.posicao_do_pulo.y - S.posicao_inicial.y) * fator_mult;

        if (fator_mult >= 1.0f) { // garantir que vai parar na posição certa
            S.posicao.y = S.posicao_do_pulo.y;

            S.pulando = false;
            S.porradao = true;
        }

        // FAZER DANO DE QUEDA
    }

    if (S.porradao == true) {
        // FAZER DANO DO PORRADÃO

        S.porradao = false;
        S.linguada = true;

        S.acompanhar_cd_atk = S.cooldown_ataque;

        if (S.reduzir_linguadas == true) {
            S.quantidade_de_linguadas--;

            if (S.quantidade_de_linguadas < 1) {
                S.quantidade_de_linguadas = 1;

                S.reduzir_linguadas = false;
            }
        }

        S.linguadas_restantes = S.quantidade_de_linguadas;
    }

    //-----------------------------------------------------//

}

//-----------------------------------------------------------//

int main() {
    InitWindow(Hres, Vres, "sapo");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) {
        float controle_de_tempo = GetFrameTime();

        ataques_sapo(controle_de_tempo);
        movement();

        BeginDrawing();
        //
        ClearBackground(BLACK);
        DrawCircle(P.posicao.x, P.posicao.y, P.raio_do_player, BLUE);
        DrawCircle(S.posicao.x, S.posicao.y, S.raio_do_sapo, RED);
        //
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

//-----------------------------------------------------------//