# tipos.h - Tipos compartilhados entre modulos
#ifndef TIPOS_H
#define TIPOS_H

/* Ponto de posicao no rio */
typedef struct {
    float x;
    float y;
} Posicao;

/* Estado do jogador */
typedef struct {
    char    nome[32];
    int     pontuacao;
    int     vidas;
    Posicao pos;
} Jogador;

/* Item coletavel no rio */
typedef struct {
    int     id;
    char    tipo[16];  /* ex: "moeda", "power-up", "obstaculo" */
    int     valor;
    Posicao pos;
} Item;

/* Trecho do rio (usado na fila) */
typedef struct {
    int  id;
    char descricao[64];
    int  dificuldade;
} Trecho;

#endif /* TIPOS_H */
