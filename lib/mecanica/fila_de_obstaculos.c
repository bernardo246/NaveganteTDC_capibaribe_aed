#include "fila_de_obstaculos.h"
#include "movimentacao.h"

static double tempo_inicio_invencivel = -1.0;
static double tempo_inicio_jogo = -1.0;
static int velocidade_atual_obstaculos = 1;

void set_obstacle_profile(obstaculo *obstaculo, const char *nome) {
    if (strcmp(nome, "Tronco") == 0) {
        strcpy(obstaculo->nome, TRONCO_PADRAO.nome);
        strcpy(obstaculo->descricao, TRONCO_PADRAO.descricao);
        obstaculo->velocidade = TRONCO_PADRAO.velocidade;
        obstaculo->hitbox = TRONCO_PADRAO.hitbox;
        obstaculo->animacao_andar = TRONCO_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Lixo no rio") == 0) {
        strcpy(obstaculo->nome, LIXO_NO_RIO_PADRAO.nome);
        strcpy(obstaculo->descricao, LIXO_NO_RIO_PADRAO.descricao);
        obstaculo->velocidade = LIXO_NO_RIO_PADRAO.velocidade;
        obstaculo->hitbox = LIXO_NO_RIO_PADRAO.hitbox;
        obstaculo->animacao_andar = LIXO_NO_RIO_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Pilastra de ponte") == 0) {
        strcpy(obstaculo->nome, PILASTRA_DE_PONTE_PADRAO.nome);
        strcpy(obstaculo->descricao, PILASTRA_DE_PONTE_PADRAO.descricao);
        obstaculo->velocidade = PILASTRA_DE_PONTE_PADRAO.velocidade;
        obstaculo->hitbox = PILASTRA_DE_PONTE_PADRAO.hitbox;
        obstaculo->animacao_andar = PILASTRA_DE_PONTE_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Barco parado") == 0) {
        strcpy(obstaculo->nome, BARCO_PARADO_PADRAO.nome);
        strcpy(obstaculo->descricao, BARCO_PARADO_PADRAO.descricao);
        obstaculo->velocidade = BARCO_PARADO_PADRAO.velocidade;
        obstaculo->hitbox = BARCO_PARADO_PADRAO.hitbox;
        obstaculo->animacao_andar = BARCO_PARADO_PADRAO.animacao_andar;
        return;
    }

    strcpy(obstaculo->nome, nome);
    strcpy(obstaculo->descricao, "Obstaculo sem perfil cadastrado");
    obstaculo->velocidade = 1;
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
    dificuldade_progressiva(obstaculo);
    obstaculo->pos.x = 1280;
    obstaculo->pos.y = posicao_aleatoria;
    obstaculo->all_obstaculos = NULL;
    obstaculo->obstaculos_ativos = NULL;
}

void iniciar_cronometro_jogo(void) {
    tempo_inicio_jogo = GetTime();
    velocidade_atual_obstaculos = 1;
}

double tempo_desde_inicio_jogo(void) {
    if (tempo_inicio_jogo < 0.0) {
        return 0.0;
    }
    return GetTime() - tempo_inicio_jogo;
}

void atualizar_velocidade_obstaculos(void) {
    int incremento = (int)(tempo_desde_inicio_jogo() / 10.0);
    int velocidade_nova = 1 + incremento;
    if (velocidade_nova > 10) {
        velocidade_nova = 10;
    }
    velocidade_atual_obstaculos = velocidade_nova;
}

void tempo_invencivel(jogador *jogador_atual) {
    if (jogador_atual == NULL || !jogador_atual->invencivel) return;

    if (tempo_inicio_invencivel < 0.0) {
        tempo_inicio_invencivel = GetTime();
    }

    if ((GetTime() - tempo_inicio_invencivel) >= 3.0) {
        jogador_atual->invencivel = 0;
        tempo_inicio_invencivel = -1.0;
    }
}
void dificuldade_progressiva(obstaculo *obstaculo) {
    atualizar_velocidade_obstaculos();
    if (obstaculo != NULL) {
        obstaculo->velocidade = velocidade_atual_obstaculos;
    }
}

void atualizar_obstaculos(Fila *obstaculos_ativos, jogador *jogador_atual) {
    if (obstaculos_ativos == NULL) return;
    atualizar_velocidade_obstaculos();

    No *no_atual = obstaculos_ativos->inicio;
    while (no_atual != NULL) {
        No *proximo = no_atual->proximo;
        obstaculo *obstaculo_atual = (obstaculo *)no_atual->dado;
        int remover_obstaculo = 0;

        mov_obstacle(obstaculo_atual);

        if (obstaculo_atual->pos.x <= 0) {
            remover_obstaculo = 1;
        }

        if (jogador_atual != NULL && colisao_jogador_X_obstaculo(jogador_atual, obstaculo_atual)) {
            remover_obstaculo = 1;
        }

        if (remover_obstaculo && fila_mover_no_para_inicio(obstaculos_ativos, obstaculo_atual)) {
            obstaculo *obstaculo_removido = (obstaculo *)fila_desenfileirar(obstaculos_ativos);
            free(obstaculo_removido);
        }

        no_atual = proximo;
    }
}


int colisao_jogador_X_obstaculo(jogador *jogador,obstaculo *obstaculo){
    tempo_invencivel(jogador);

    Rectangle rJogador = {
     jogador->pos.x - jogador->hitbox.largura/2.0f,
     jogador->pos.y - jogador->hitbox.altura/2.0f,
     jogador->hitbox.largura,
     jogador->hitbox.altura
    };
    Rectangle rObstaculo = {
     obstaculo->pos.x - obstaculo->hitbox.largura/2.0f,
     obstaculo->pos.y - obstaculo->hitbox.altura/2.0f,
     obstaculo->hitbox.largura,
     obstaculo->hitbox.altura
 };
 
 if(CheckCollisionRecs(rJogador, rObstaculo) && !jogador->invencivel){
    jogador->vida -=40;
    jogador->invencivel=1;
    tempo_inicio_invencivel = GetTime();
    return 1;
 }
 return 0;
}
