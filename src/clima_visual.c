// clima_visual.c
#include <raylib.h>
#include "../include/clima.h"


// clima_visual.c
#include <raylib.h>
#include <stdlib.h>
#include "../include/clima.h"

#define MAX_GOTAS 300

typedef struct {
    float x;
    float y;
    float velocidade;
} Gota;

static Gota gotas[MAX_GOTAS];
static bool gotas_iniciadas = false;

static void iniciar_gotas(void) {
    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();

    for (int i = 0; i < MAX_GOTAS; i++) {
        gotas[i].x = rand() % screen_w;
        gotas[i].y = rand() % screen_h;
        gotas[i].velocidade = 5.0f + (rand() % 5);
    }
    gotas_iniciadas = true;
}

void desenhar_chuva(Clima *clima) {
    if (clima->tipo != CLIMA_CHUVA) return;

    if (!gotas_iniciadas) iniciar_gotas();

    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();

    int quantidade;
    int largura;
    int altura;

    float rain = (float)clima->intensidade;

    if (rain <= 2.5f) {
        quantidade = 50;
        largura = 2;
        altura = 6;
    } else if (rain <= 10.0f) {
        quantidade = 150;
        largura = 2;
        altura = 8;
    } else {
        quantidade = 300;
        largura = 3;
        altura = 10;
    }

    for (int i = 0; i < quantidade; i++) {
        gotas[i].y += gotas[i].velocidade;

        if (gotas[i].y > screen_h) {
            gotas[i].y = 0;
            gotas[i].x = rand() % screen_w;
        }

        DrawRectangle((int)gotas[i].x, (int)gotas[i].y, largura, altura, Fade(BLUE, 0.6f));
    }
}