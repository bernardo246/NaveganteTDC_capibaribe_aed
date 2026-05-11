#include "fila_de_obstaculos.h"
#include "movimentacao.h"

void set_obstacle_profile(obstaculo *obstaculo, const char *nome) {
    if (strcmp(nome, "Tronco") == 0) {
        strcpy(obstaculo->nome, TRONCO_PADRAO.nome);
        strcpy(obstaculo->descricao, TRONCO_PADRAO.descricao);
        obstaculo->hitbox = TRONCO_PADRAO.hitbox;
        obstaculo->animacao_andar = TRONCO_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Lixo no rio") == 0) {
        strcpy(obstaculo->nome, LIXO_NO_RIO_PADRAO.nome);
        strcpy(obstaculo->descricao, LIXO_NO_RIO_PADRAO.descricao);
        obstaculo->hitbox = LIXO_NO_RIO_PADRAO.hitbox;
        obstaculo->animacao_andar = LIXO_NO_RIO_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Pilastra de ponte") == 0) {
        strcpy(obstaculo->nome, PILASTRA_DE_PONTE_PADRAO.nome);
        strcpy(obstaculo->descricao, PILASTRA_DE_PONTE_PADRAO.descricao);
        obstaculo->hitbox = PILASTRA_DE_PONTE_PADRAO.hitbox;
        obstaculo->animacao_andar = PILASTRA_DE_PONTE_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Barco parado") == 0) {
        strcpy(obstaculo->nome, BARCO_PARADO_PADRAO.nome);
        strcpy(obstaculo->descricao, BARCO_PARADO_PADRAO.descricao);
        obstaculo->hitbox = BARCO_PARADO_PADRAO.hitbox;
        obstaculo->animacao_andar = BARCO_PARADO_PADRAO.animacao_andar;
        return;
    }

    strcpy(obstaculo->nome, nome);
    strcpy(obstaculo->descricao, "Obstaculo sem perfil cadastrado");
    obstaculo->hitbox.largura = 0;
    obstaculo->hitbox.altura = 0;
    obstaculo->animacao_andar.num_frames = 0;
    obstaculo->animacao_andar.frame_atual = 0;
}

void init_obstacle(obstaculo *obstaculo, const char *nome){
    int min = OBSTACULO_POS_MIN;
    int max = OBSTACULO_POS_MAX;
    int posicao_aleatoria = min + rand() % (max - min + 1);

    set_obstacle_profile(obstaculo, nome);
    obstaculo->pos.x = 1280;
    obstaculo->pos.y = posicao_aleatoria;
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
