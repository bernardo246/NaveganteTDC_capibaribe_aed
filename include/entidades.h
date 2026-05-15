// objetos do jogo, exemplo: personagem, inimigos, itens, etc.
#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tipos.h"
#include "default_structs.h"
#include "item.h"

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

typedef struct {
    char nome[32];
    char descricao[128];
    int velocidade;
    Hitbox hitbox;
    Animacao animacao_andar;
} Tronco;

typedef struct {
    char nome[32];
    char descricao[128];
    int velocidade;
    Hitbox hitbox;
    Animacao animacao_andar;
} LixoNoRio;

typedef struct {
    char nome[32];
    char descricao[128];
    int velocidade;
    Hitbox hitbox;
    Animacao animacao_andar;
} PilastraDePonte;

typedef struct {
    char nome[32];
    char descricao[128];
    int velocidade;
    Hitbox hitbox;
    Animacao animacao_andar;
} BarcoParado;

static const Tronco TRONCO_PADRAO = {
    .nome = "Tronco",
    .descricao = "Detritos naturais arrastados pela correnteza",
    .velocidade = 1,
    .hitbox = {.largura = 96, .altura = 28},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

static const LixoNoRio LIXO_NO_RIO_PADRAO = {
    .nome = "Lixo no rio",
    .descricao = "Residuos urbanos que poluem o Capibaribe",
    .velocidade = 1,
    .hitbox = {.largura = 48, .altura = 48},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

static const PilastraDePonte PILASTRA_DE_PONTE_PADRAO = {
    .nome = "Pilastra de ponte",
    .descricao = "Estruturas das pontes historicas no caminho",
    .velocidade = 1,
    .hitbox = {.largura = 80, .altura = 180},
    .animacao_andar = {.num_frames = 0, .frame_atual = 0}
};

static const BarcoParado BARCO_PARADO_PADRAO = {
    .nome = "Barco parado",
    .descricao = "Embarcacoes ancoradas bloqueando a rota",
    .velocidade = 1,
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
    int invencivel; // 0 para não invencível, 1 para invencível

    
    poderes *poderes;
    inventario *inventario;

    Hitbox hitbox;
    Animacao animacao_andar;
    Posicao pos;
    
} jogador;


// estados que o jogador vai ta, adaptar as funcoes de fila obstaculo de acordo com isso
typedef struct poderes {
    bool escudo;
    bool pa;

} poderes;



struct Linkedlist_item {
    Item* next;
    Item* prev;
};






#endif /* ENTIDADES_H */
