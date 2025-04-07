#define Hres 1080
#define Vres 720

#define CENTER_x Hres/2
#define CENTER_y Vres/2

#define inicio_player_x 540
#define inicio_player_y 630

#define ATK_COOLDOWN_vec 1

#define P_ATK_COOLDOWN 0.5

struct coords {
    float x;
    float y;
}; typedef struct coords coords;

struct Player {
    coords posicao;
    coords sword; //armazena os dx e dy da espada
    float raio_do_player = 20.0f;
    int vida_jogador = 100;

    bool morto = false;
}; typedef struct Player player;// player P;
struct Sapo {
    coords posicao;
    coords posicao_inicial;
    coords posicao_do_pulo;

    bool linguada = false;
    bool pulando = false;
    bool porradao = false;
    bool reduzir_linguadas = true;
    bool tempo_antes_de_pular = false;
    bool tempo_antes_do_porradao = false;
    bool tempo_antes_da_linguada = true;

    bool dano_porradao_aplicado = false;
    bool dano_de_linguada_aplicado = false;

    int quantidade_de_linguadas = 5;
    int linguadas_restantes;
    int vida_boss = 100;

    float cooldown_ataque = 0.1;
    float acompanhar_cd_atk = 0.0;

    float cooldown_antes_de_pular = 2.0;
    float acompanhar_cd_pulo = 0.0;

    float cooldown_antes_do_porradao = 2.0;
    float acompanhar_cd_porradao = 0.0;

    float cooldown_antes_da_linguada = 2.0;
    float acompanhar_cd_antes_da_linguada = 0.0;

    float velocidade_do_pulo = 1500.0;
    float raio_do_sapo = 40.0;
    float altura_do_pulo = 100.0;

    float duracao_do_pulo = 0.0;
    float duracao_porradao = 0.0;

}; typedef struct Sapo sapo; //sapo S;
typedef struct {
    float cx;
    float cy;
    float dex;
    float dey;
    int reverse;
} weapon_1; //weapon_1 vec;

extern player P;
extern sapo S;
extern weapon_1 vec;

extern int dash_t;
extern int ATK1_COOLDOWNt;
extern int it;
extern float p_atk_timer;
