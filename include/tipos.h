# tipos.h - Tipos compartilhados entre modulos
#ifndef TIPOS_H
#define TIPOS_H

/* Trecho do rio (usado na fila) */
typedef struct {
    int  id;
    char descricao[64];
    int  dificuldade;
} Trecho;

#endif /* TIPOS_H */
