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
    Posicao pos;

    Hitbox hitbox;

    Animacao animacao_andar;

    Linkedlist_obstaculo* all_obstaculos; 
    Linkedlist_obstaculo* obstaculos_ativos;

} obstaculo;

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
