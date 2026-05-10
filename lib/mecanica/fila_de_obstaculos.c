#include "fila_de_obstaculos.h"
#include "movimentacao.h"

void init_obstacle(obstaculo *obstaculo, const char *nome){
    int min = OBSTACULO_POS_MIN;
    int max = OBSTACULO_POS_MAX;
    int posicao_aleatoria = min + rand() % (max - min + 1);

    strcpy(obstaculo->nome,nome);
    obstaculo->pos.x = 1280;
    obstaculo->pos.y = posicao_aleatoria;
    obstaculo->hitbox.largura = 0;
    obstaculo->hitbox.altura = 0;
    obstaculo->animacao_andar.num_frames = 0;
    obstaculo->animacao_andar.frame_atual = 0;
    obstaculo->all_obstaculos = NULL;
    obstaculo->obstaculos_ativos = NULL;
}

void atualizar_obstaculos(Fila *obstaculos_ativos) {
    int quantidade_obstaculos = fila_tamanho(obstaculos_ativos);

    for (int i = 0; i < quantidade_obstaculos; i++) {
        obstaculo *obstaculo_atual = (obstaculo *)fila_desenfileirar(obstaculos_ativos);
        mov_obstacle(obstaculo_atual);

        if (obstaculo_atual->pos.x <= 0) {
            free(obstaculo_atual);
            continue;
        }

        fila_enfileirar(obstaculos_ativos, obstaculo_atual);
    }
}
