/* ranking.h - Recordes e merge sort (Dev 3) */

#ifndef RANKING_H
#define RANKING_H

#define RANKING_MAX 10

typedef struct {
    char nome[32];
    int  pontuacao;
} Recorde;

typedef struct {
    Recorde entradas[RANKING_MAX];
    int     quantidade;
} Ranking;

Ranking *ranking_criar(void);
void     ranking_destruir(Ranking *r);
int      ranking_inserir(Ranking *r, const char *nome, int pontuacao);
void     ranking_ordenar(Ranking *r);
void     ranking_exibir(const Ranking *r, Texture2D fundo);

#endif /* RANKING_H */
