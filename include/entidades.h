// objetos do jogo, exemplo: personagem, inimigos, itens, etc.
#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "default_structs.h"
#include "item.h"
#include "../lib/inventario/inventario.h"


// no topo do entidades.h, no lugar do #include de inventario
typedef struct Poderes Poderes;
typedef struct Inventario Inventario;
typedef struct Linkedlist_obstaculo Linkedlist_obstaculo;
typedef struct Linkedlist_item Linkedlist_item;

// estruturas do obstaculo;
typedef struct {

    char nome[32];
    char descricao[128];
    int velocidade;
    Posicao pos;

    Hitbox hitbox;

    Animacao animacao_andar;

    Linkedlist_obstaculo* all_obstaculos;
    Linkedlist_obstaculo* obstaculos_ativos;

} obstaculo;



static const obstaculo TRONCO_PADRAO = {
    .nome = "Tronco",
    .descricao = "Detritos naturais arrastados pela correnteza",
    .velocidade = 1,
    .hitbox = {.largura = 256, .altura = 88},
    .animacao_andar = {
        .num_frames = 9,
        .frames = {
            "assets/sprites/obstaculos/tronco/trunk1.png",
            "assets/sprites/obstaculos/tronco/trunk2.png",
            "assets/sprites/obstaculos/tronco/trunk3.png",
            "assets/sprites/obstaculos/tronco/trunk4.png",
            "assets/sprites/obstaculos/tronco/trunk5.png",
            "assets/sprites/obstaculos/tronco/trunk4.png",
            "assets/sprites/obstaculos/tronco/trunk3.png",
            "assets/sprites/obstaculos/tronco/trunk2.png",
            "assets/sprites/obstaculos/tronco/trunk1.png"
        },
        .frame_atual = 0,
        .intervalo_frame = 0.08f,
        .anim_timer = 0.0f
    }
};

static const obstaculo LIXO_NO_RIO_GARRAFA_PADRAO = {
    .nome = "Garrafa no rio",
    .descricao = "Garrafas plasticas descartadas no Capibaribe",
    .velocidade = 1,
    .hitbox = {.largura = 65, .altura = 65},
    .animacao_andar = {
        .num_frames = 1,
        .frames = {
            "assets/sprites/obstaculos/lixo/garrafa_1.png"
        },
        .frame_atual = 0,
        .intervalo_frame = 0.0f,
        .anim_timer = 0.0f
    }
};

static const obstaculo LIXO_NO_RIO_SACOLA_PADRAO = {
    .nome = "Sacola no rio",
    .descricao = "Sacolas plasticas que poluem as aguas do rio",
    .velocidade = 1,
    .hitbox = {.largura = 100, .altura = 75},
    .animacao_andar = {
        .num_frames = 3,
        .frames = {
            "assets/sprites/obstaculos/lixo/sacola1.png",
            "assets/sprites/obstaculos/lixo/sacola2.png",
            "assets/sprites/obstaculos/lixo/sacola1.png"
        },
        .frame_atual = 0,
        .intervalo_frame = 0.08f,
        .anim_timer = 0.0f
    }
};

static const obstaculo PEDRA1_PADRAO = {
    .nome = "Pedra pequena",
    .descricao = "Rochas menores espalhadas pelo leito do rio",
    .velocidade = 1,
    .hitbox = {.largura = 50, .altura = 50},
    .animacao_andar = {
        .num_frames = 1,
        .frames = {"assets/sprites/obstaculos/pedra/pedra_1.png"},
        .frame_atual = 0,
        .intervalo_frame = 0.0f,
        .anim_timer = 0.0f
    }
};

static const obstaculo PEDRA2_PADRAO = {
    .nome = "Pedra grande",
    .descricao = "Grandes rochas emergindo das aguas do Capibaribe",
    .velocidade = 1,
    .hitbox = {.largura = 112, .altura = 92},
    .animacao_andar = {
        .num_frames = 1,
        .frames = {"assets/sprites/obstaculos/pedra/pedra_2.png"},
        .frame_atual = 0,
        .intervalo_frame = 0.0f,
        .anim_timer = 0.0f
    }
};

static const obstaculo BARCO_PADRAO = {
    .nome = "Barco",
    .descricao = "Embarcacoes em movimento cruzando a rota",
    .velocidade = 2,
    .hitbox = {.largura = 180, .altura = 165},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};


struct Linkedlist_obstaculo {
    obstaculo* next;
    obstaculo* prev;
};

// fim da estrutura do obstaculo

typedef struct Poderes {
    bool escudo;
    double tempo_escudo;

    bool pa;
    double tempo_pa;

} Poderes;


typedef struct jogador {
    char nome[32];
    int vida;
    int pontuacao;
    int velocidade;
    int invencivel; // 0 para não invencível, 1 para invencível

    int nivel_velocidade; // 0-3, tier do sprite (só aumenta)
    int dir_x;            // -1=esquerda, 0=parado, 1=direita
    int dir_y;            // -1=cima, 0=parado, 1=baixo

    Poderes poderes;
    Inventario *inventario;

    Hitbox hitbox;
    Animacao animacao_andar;
    Posicao pos;

} jogador;


// estados que o jogador vai ta, adaptar as funcoes de fila obstaculo de acordo com isso



struct Linkedlist_item {
    Item* next;
    Item* prev;
};




#endif /* ENTIDADES_H */
