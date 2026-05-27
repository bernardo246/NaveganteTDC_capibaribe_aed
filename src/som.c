#include <stdio.h>
#include "../include/som.h"

static Sound sons[SOM_TOTAL];
static Music musica_intro;
static int carregado = 0;

static const char *caminhos_sons[SOM_TOTAL] = {
    NULL,
    "assets/sounds/Remando.wav",
    "assets/sounds/TrocaItemInventario.wav",
    "assets/sounds/PegouPa.wav",
    "assets/sounds/PegouMoeda.flac",
    "assets/sounds/ColisaoGarrafa.wav",
    "assets/sounds/ColisaoPonte.wav",
    "assets/sounds/AtivacaoEscudo.flac",
    "assets/sounds/ColisaoSacola.wav",
    "assets/sounds/PegouEscudo.wav",
    "assets/sounds/PegouPeixe.wav",
    "assets/sounds/ColisaoTronco.wav",
    "assets/sounds/ColisaoPedra.wav",
    "assets/sounds/Curar.wav",
    "assets/sounds/MusicaIntro.wav"
};

void sons_carregar(void) {

    for (int i = 1; i < SOM_MUSICA_INTRO; i++) {

        sons[i] = LoadSound(caminhos_sons[i]);

        if (sons[i].frameCount == 0) {
            printf(
                "ERRO: nao foi possivel carregar som: %s\n",
                caminhos_sons[i]
            );
        }
        else {
            printf(
                "Som carregado: %s\n",
                caminhos_sons[i]
            );
        }
    }

    musica_intro =
        LoadMusicStream(
            caminhos_sons[SOM_MUSICA_INTRO]
        );

    if (musica_intro.frameCount == 0) {
        printf(
            "ERRO: nao foi possivel carregar musica: %s\n",
            caminhos_sons[SOM_MUSICA_INTRO]
        );
    }
    else {
        printf(
            "Musica carregada: %s\n",
            caminhos_sons[SOM_MUSICA_INTRO]
        );
    }

    carregado = 1;
}

void sons_descarregar(void) {

    if (!carregado) return;

    for (int i = 1; i < SOM_MUSICA_INTRO; i++) {

        if (sons[i].frameCount > 0) {
            UnloadSound(sons[i]);
        }
    }

    if (musica_intro.frameCount > 0) {
        UnloadMusicStream(musica_intro);
    }

    carregado = 0;
}

void tocar_som(TipoSom tipo) {

    if (!carregado) return;

    if (tipo == SOM_MUSICA_INTRO) {
        PlayMusicStream(musica_intro);
        return;
    }

    if (tipo <= SOM_NENHUM ||
        tipo >= SOM_MUSICA_INTRO)
        return;

    if (sons[tipo].frameCount > 0) {
        PlaySound(sons[tipo]);
    }
}

void atualizar_musica(void) {

    if (!carregado) return;

    if (musica_intro.frameCount > 0) {
        UpdateMusicStream(musica_intro);
    }
}