#include <stdio.h>
#include "som.h"

#define NUM_SONS 13

static Sound sons[NUM_SONS];
static Music musica_intro;
static int carregado = 0;

static const char *caminhos_sons[] = {
    NULL,                                        /* índice 0 — não usado     */
    "assets/sounds/TrocaItemInventario.wav",     /* 1  */
    "assets/sounds/PegouPa.wav",                 /* 2  */
    "assets/sounds/PegouMoeda.flac",             /* 3  */
    "assets/sounds/ColisaoGarrafa.wav",          /* 4  */
    "assets/sounds/ColisaoPonte.wav",            /* 5  */
    "assets/sounds/AtivacaoEscudo.flac",         /* 6  */
    "assets/sounds/Remando.wav",                 /* 7  */
    "assets/sounds/ColisaoSacola.wav",           /* 8  */
    "assets/sounds/PegouEscudo.wav",             /* 9  */
    "assets/sounds/PegouPeixe.wav",              /* 10 */
    "assets/sounds/ColisaoTronco.wav",           /* 11 */
    "assets/sounds/ColisaoPedra.wav",            /* 12 */
};

void sons_carregar(void) {
    for (int i = 1; i <= NUM_SONS - 1; i++) {
        sons[i] = LoadSound(caminhos_sons[i]);
        if (sons[i].stream.buffer == NULL)
            printf("ERRO: nao foi possivel carregar som: %s\n", caminhos_sons[i]);
    }
    musica_intro = LoadMusicStream("assets/sounds/MusicaIntro.wav");
    PlayMusicStream(musica_intro);
    carregado = 1;
}

void sons_descarregar(void) {
    if (!carregado) return;
    for (int i = 1; i <= NUM_SONS - 1; i++)
        UnloadSound(sons[i]);
    UnloadMusicStream(musica_intro);
    carregado = 0;
}

void tocar_som(TipoSom tipo) {
    if (!carregado) return;
    if (tipo == SOM_MUSICA_INTRO) {
        PlayMusicStream(musica_intro);
        return;
    }
    if (tipo < 1 || tipo > NUM_SONS - 1) return;
    PlaySound(sons[tipo]);
}

void atualizar_musica(void) {
    if (!carregado) return;
    UpdateMusicStream(musica_intro);
}