// objetos do jogo, exemplo: personagem, inimigos, itens, etc.
#ifndef entidades_H
#define entidades_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tipos.h"
#include "default_structs.h"
#include "arvore.h"

// estruturas do obstaculo;
typedef struct {

    char nome[32];
    Posicao pos;

    Hitbox hitbox;

    Animacao animacao_andar;

    Linkedlist_obstaculo* all_obstaculos; 
    Linkedlist_obstaculo* obstaculos_ativos;

} obstaculo;

typedef struct {
    obstaculo* next;
    obstaculo* prev;
} Linkedlist_obstaculo;

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




typedef struct {

    int     id;
    char    tipo[16];  /* ex: "moeda", "power-up", "obstaculo" */
    int     valor;

    Hitbox hitbox;
    Animacao animacao;

    Posicao pos;

    Linkedlist_item* all_itens;
    Linkedlist_item* itens_ativos;

} Item;

typedef struct {
    obstaculo* next;
    obstaculo* prev;
} Linkedlist_item;






#endif entidades_H