/* ranking.c - Implementacao dos recordes com merge sort (Dev 3) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

static const char *RANKING_ARQUIVO = "ranking.txt";

static void ranking_limpar(Ranking *r) {
    r->quantidade = 0;
}

static void ranking_carregar_arquivo(Ranking *r) {
    FILE *f = fopen(RANKING_ARQUIVO, "r");
    if (!f) return;

    ranking_limpar(r);
    while (r->quantidade < RANKING_MAX) {
        char nome[32];
        int pontuacao;
        if (fscanf(f, "%31s %d", nome, &pontuacao) != 2) break;
        strncpy(r->entradas[r->quantidade].nome, nome, 31);
        r->entradas[r->quantidade].nome[31] = '\0';
        r->entradas[r->quantidade].pontuacao = pontuacao;
        r->quantidade++;
    }
    fclose(f);
    ranking_ordenar(r);
}

Ranking *ranking_criar(void) {
    Ranking *r = (Ranking *)malloc(sizeof(Ranking));
    if (!r) return NULL;
    ranking_limpar(r);
    ranking_carregar_arquivo(r);
    return r;
}

void ranking_destruir(Ranking *r) {
    free(r);
}

int ranking_inserir(Ranking *r, const char *nome, int pontuacao) {
    if (!r) return 0;

    FILE *f = fopen(RANKING_ARQUIVO, "a");
    if (!f) return 0;
    fprintf(f, "%s %d\n", nome, pontuacao);
    fclose(f);

    ranking_carregar_arquivo(r);
    return 1;
}

static void intercala(int inicio, int meio, int fim, Recorde v[]) {
    int inicio_v01 = inicio, inicio_v02 = meio + 1, poslivre = 0;
    Recorde aux[RANKING_MAX];

    while (inicio_v01 <= meio && inicio_v02 <= fim) {
        if (v[inicio_v01].pontuacao >= v[inicio_v02].pontuacao)
            aux[poslivre++] = v[inicio_v01++];
        else
            aux[poslivre++] = v[inicio_v02++];
    }
    while (inicio_v01 <= meio)
        aux[poslivre++] = v[inicio_v01++];
    while (inicio_v02 <= fim)
        aux[poslivre++] = v[inicio_v02++];
    for (inicio_v01 = inicio; inicio_v01 <= fim; inicio_v01++)
        v[inicio_v01] = aux[inicio_v01 - inicio];
}

static void mergesort_recordes(int inicio, int fim, Recorde v[]) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergesort_recordes(inicio, meio, v);
        mergesort_recordes(meio + 1, fim, v);
        intercala(inicio, meio, fim, v);
    }
}

void ranking_ordenar(Ranking *r) {
    if (r->quantidade > 1)
        mergesort_recordes(0, r->quantidade - 1, r->entradas);
}

void ranking_exibir(const Ranking *r) {
    printf("\n=== Ranking ===\n");
    for (int i = 0; i < r->quantidade; i++)
        printf("%d. %-20s %d pts\n", i + 1, r->entradas[i].nome, r->entradas[i].pontuacao);
}
