#include "raylib.h"
#include "globals.hpp"
#include "linguada.hpp"
#include <cmath>
#include <stdio.h>

void ataques_sapo(float controle_de_tempo) //mudar isso, a função ta muito grande e deve ser modularizada de modo a facilitar a legibilidade do codigo.
{

    //---------------------- LINGUADA ----------------------//

    if (S.tempo_antes_da_linguada == true) {
        S.acompanhar_cd_antes_da_linguada -= controle_de_tempo;

        if (S.acompanhar_cd_antes_da_linguada <= 0.0) {
            S.tempo_antes_da_linguada = false;
            S.linguada = true;
            S.acompanhar_cd_atk = S.cooldown_ataque;
        }
    }

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
//------------------------ PULO ------------------------//

    if (S.tempo_antes_de_pular == true) {
        S.acompanhar_cd_pulo -= controle_de_tempo;

        if (S.acompanhar_cd_pulo <= 0.0) {
            S.tempo_antes_de_pular = false;
            S.pulando = true;

            S.posicao_do_pulo = P.posicao;
            S.posicao_inicial = S.posicao;

            S.duracao_do_pulo = 0.0;
        }

    }

    if (S.pulando == true) {
        S.duracao_do_pulo += controle_de_tempo * 1.5;

        float fator_mult = S.duracao_do_pulo / 0.7;

        if (fator_mult > 1.0) {
            fator_mult = 1.0;
        }

        // EIXO X:
        S.posicao.x = S.posicao_inicial.x + (S.posicao_do_pulo.x - S.posicao_inicial.x) * fator_mult;

        // EIXO Y:
        float altura = -4 * pow((fator_mult - 0.5), 2) + 1;

        S.posicao.y = S.posicao_inicial.y - (altura * S.altura_do_pulo) + (S.posicao_do_pulo.y - S.posicao_inicial.y) * fator_mult;

        if (fator_mult >= 1.0) { // garantir que vai parar na posição certa
            S.posicao.y = S.posicao_do_pulo.y;

            S.pulando = false;
            S.tempo_antes_do_porradao = true;

            S.acompanhar_cd_porradao = S.cooldown_antes_do_porradao;

            // Dano de queda

            float distancia = sqrt(pow(P.posicao.x - S.posicao.x, 2) + pow(P.posicao.y - S.posicao.y, 2));

            if (distancia <= S.raio_do_sapo) {
                P.vida_jogador -= 40;

                if (P.vida_jogador < 0) {
                    P.vida_jogador = 0;
                    P.morto = true;
                }
            }
        }
    }
    //---------------------- PORRADÃO ----------------------//
    if (S.tempo_antes_do_porradao == true) {
        S.acompanhar_cd_porradao -= controle_de_tempo;

        if (S.acompanhar_cd_porradao <= 0.0) {
            S.tempo_antes_do_porradao = false;
            S.porradao = true;
            S.duracao_porradao = 0.3;
        }
    }

    if (S.porradao) {
        S.duracao_porradao -= controle_de_tempo;

        if (S.duracao_porradao > 0.0f) {

            if (S.dano_porradao_aplicado == false) {
                float distancia = sqrt(pow(P.posicao.x - S.posicao.x, 2) + pow(P.posicao.y - S.posicao.y, 2));

                if (distancia + P.raio_do_player <= 3.5 * S.raio_do_sapo) {
                    P.vida_jogador -= 25;

                    if (P.vida_jogador < 0) {
                        P.vida_jogador = 0;
                        P.morto = true;
                    }
                }

                S.dano_porradao_aplicado = true;
            }
        }

        else {
            S.porradao = false;
            S.tempo_antes_da_linguada = true;

            S.acompanhar_cd_antes_da_linguada = S.cooldown_antes_da_linguada;

            S.dano_porradao_aplicado = false;

            if (S.reduzir_linguadas == true) {
                S.quantidade_de_linguadas--;

                S.cooldown_antes_da_linguada -= 0.1;
                S.cooldown_antes_do_porradao -= 0.1;
                S.cooldown_antes_de_pular -= 0.1;

                if (S.quantidade_de_linguadas < 1) {
                    S.quantidade_de_linguadas = 1;

                    S.cooldown_antes_da_linguada = 1.5;
                    S.cooldown_antes_do_porradao = 1.5;
                    S.cooldown_antes_de_pular = 1.5;

                    S.reduzir_linguadas = false;
                }
            }

            S.linguadas_restantes = S.quantidade_de_linguadas;
        }
    }
}


