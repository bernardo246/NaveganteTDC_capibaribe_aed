/* ranking.c - Implementacao dos recordes com merge sort (Dev 3) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

Ranking *ranking_criar(void) {
    Ranking *r = (Ranking *)malloc(sizeof(Ranking));
    if (!r) return NULL;
    r->quantidade = 0;
    return r;
}

void ranking_destruir(Ranking *r) {
    free(r);
}

int ranking_inserir(Ranking *r, const char *nome, int pontuacao) {
    if (r->quantidade >= RANKING_MAX) return 0;
    strncpy(r->entradas[r->quantidade].nome, nome, 31);
    r->entradas[r->quantidade].nome[31] = '\0';
    r->entradas[r->quantidade].pontuacao = pontuacao;
    r->quantidade++;
    ranking_ordenar(r);
    return 1;
}

static void merge(Recorde *arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Recorde *L = (Recorde *)malloc(n1 * sizeof(Recorde));
    Recorde *R = (Recorde *)malloc(n2 * sizeof(Recorde));
    if (!L || !R) { free(L); free(R); return; }
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].pontuacao >= R[j].pontuacao)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

static void merge_sort(Recorde *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void ranking_ordenar(Ranking *r) {
    if (r->quantidade > 1)
        merge_sort(r->entradas, 0, r->quantidade - 1);
}

void ranking_exibir(const Ranking *r) {
    printf("\n=== Ranking ===\n");
    for (int i = 0; i < r->quantidade; i++)
        printf("%d. %-20s %d pts\n", i + 1, r->entradas[i].nome, r->entradas[i].pontuacao);
}
