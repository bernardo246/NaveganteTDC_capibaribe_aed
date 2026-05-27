
#ifndef CLIMA_H
#define CLIMA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    CLIMA_SOL = 1,
    CLIMA_CHUVA = 2,
} TipoClima;

typedef struct Clima {
    bool noite;

    TipoClima tipo;
    int intensidade; // intensidade do clima, por exemplo, para chuva pode ser a quantidade de gotas
} Clima;

void atualizar_clima(Clima* clima);
void print_request();

//funcoes de desenho
void desenhar_chuva(Clima *clima);

#endif /* CLIMA_H */
