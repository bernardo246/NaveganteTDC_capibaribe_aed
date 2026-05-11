// objetos do jogo, exemplo: personagem, inimigos, itens, etc.
#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tipos.h"
#include "default_structs.h"

typedef struct Arvore Arvore;
typedef struct Linkedlist_obstaculo Linkedlist_obstaculo;
typedef struct Linkedlist_item Linkedlist_item;
typedef struct Item Item;

// estruturas do obstaculo;
typedef struct {

    char nome[32];
    char descricao[128];
    Posicao pos;

    Hitbox hitbox;

    Animacao animacao_andar;

    Linkedlist_obstaculo* all_obstaculos; 
    Linkedlist_obstaculo* obstaculos_ativos;

} obstaculo;

typedef struct {
    char nome[32];
    char descricao[128];
    Hitbox hitbox;
    Animacao animacao_andar;
} Tronco;

typedef struct {
    char nome[32];
    char descricao[128];
    Hitbox hitbox;
    Animacao animacao_andar;
} LixoNoRio;

typedef struct {
    char nome[32];
    char descricao[128];
    Hitbox hitbox;
    Animacao animacao_andar;
} PilastraDePonte;

typedef struct {
    char nome[32];
    char descricao[128];
    Hitbox hitbox;
    Animacao animacao_andar;
} BarcoParado;

static const Tronco TRONCO_PADRAO = {
    .nome = "Tronco",
    .descricao = "Detritos naturais arrastados pela correnteza",
    .hitbox = {.largura = 96, .altura = 28},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

static const LixoNoRio LIXO_NO_RIO_PADRAO = {
    .nome = "Lixo no rio",
    .descricao = "Residuos urbanos que poluem o Capibaribe",
    .hitbox = {.largura = 48, .altura = 48},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

static const PilastraDePonte PILASTRA_DE_PONTE_PADRAO = {
    .nome = "Pilastra de ponte",
    .descricao = "Estruturas das pontes historicas no caminho",
    .hitbox = {.largura = 80, .altura = 180},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

static const BarcoParado BARCO_PARADO_PADRAO = {
    .nome = "Barco parado",
    .descricao = "Embarcacoes ancoradas bloqueando a rota",
    .hitbox = {.largura = 160, .altura = 70},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

struct Linkedlist_obstaculo {
    obstaculo* next;
    obstaculo* prev;
};

// fim da estrutura do obstaculo


typedef struct jogador {
    char nome[32];
    int vida;
    int pontuacao;
    int velocidade;

    Arvore *inventario; // Arvore de itens coletados


    Hitbox hitbox;
    Animacao animacao_andar;
    Posicao pos;
    
} jogador;




struct Item {

    int     id;
    char    tipo[16];  /* ex: "moeda", "power-up", "obstaculo" */
    int     valor;

    Hitbox hitbox;
    Animacao animacao;

    Posicao pos;

    Linkedlist_item* all_itens;
    Linkedlist_item* itens_ativos;

};

struct Linkedlist_item {
    Item* next;
    Item* prev;
};






#endif /* ENTIDADES_H */
