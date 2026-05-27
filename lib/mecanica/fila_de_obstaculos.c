#include "fila_de_obstaculos.h"
#include "movimentacao.h"

static double tempo_inicio_invencivel = -1.0;
static double tempo_inicio_jogo = -1.0;
static double ultimo_spawn_obstaculo = -1.0;
static int velocidade_atual_obstaculos = 1;
static const char *TIPOS_OBSTACULO[6] = {
    "Tronco",
    "Garrafa no rio",
    "Sacola no rio",
    "Pedra pequena",
    "Pedra grande",
    "Barco"
};

void set_obstacle_profile(obstaculo *obstaculo, const char *nome) {
    if (strcmp(nome, "Tronco") == 0) {
        strcpy(obstaculo->nome, TRONCO_PADRAO.nome);
        strcpy(obstaculo->descricao, TRONCO_PADRAO.descricao);
        obstaculo->velocidade = TRONCO_PADRAO.velocidade;
        obstaculo->hitbox = TRONCO_PADRAO.hitbox;
        obstaculo->animacao_andar = TRONCO_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Garrafa no rio") == 0) {
        strcpy(obstaculo->nome, LIXO_NO_RIO_GARRAFA_PADRAO.nome);
        strcpy(obstaculo->descricao, LIXO_NO_RIO_GARRAFA_PADRAO.descricao);
        obstaculo->velocidade = LIXO_NO_RIO_GARRAFA_PADRAO.velocidade;
        obstaculo->hitbox = LIXO_NO_RIO_GARRAFA_PADRAO.hitbox;
        obstaculo->animacao_andar = LIXO_NO_RIO_GARRAFA_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Sacola no rio") == 0) {
        strcpy(obstaculo->nome, LIXO_NO_RIO_SACOLA_PADRAO.nome);
        strcpy(obstaculo->descricao, LIXO_NO_RIO_SACOLA_PADRAO.descricao);
        obstaculo->velocidade = LIXO_NO_RIO_SACOLA_PADRAO.velocidade;
        obstaculo->hitbox = LIXO_NO_RIO_SACOLA_PADRAO.hitbox;
        obstaculo->animacao_andar = LIXO_NO_RIO_SACOLA_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Pedra pequena") == 0) {
        strcpy(obstaculo->nome, PEDRA1_PADRAO.nome);
        strcpy(obstaculo->descricao, PEDRA1_PADRAO.descricao);
        obstaculo->velocidade = PEDRA1_PADRAO.velocidade;
        obstaculo->hitbox = PEDRA1_PADRAO.hitbox;
        obstaculo->animacao_andar = PEDRA1_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Pedra grande") == 0) {
        strcpy(obstaculo->nome, PEDRA2_PADRAO.nome);
        strcpy(obstaculo->descricao, PEDRA2_PADRAO.descricao);
        obstaculo->velocidade = PEDRA2_PADRAO.velocidade;
        obstaculo->hitbox = PEDRA2_PADRAO.hitbox;
        obstaculo->animacao_andar = PEDRA2_PADRAO.animacao_andar;
        return;
    }

    if (strcmp(nome, "Barco") == 0) {
        strcpy(obstaculo->nome, BARCO_PADRAO.nome);
        strcpy(obstaculo->descricao, BARCO_PADRAO.descricao);
        obstaculo->velocidade = BARCO_PADRAO.velocidade;
        obstaculo->hitbox = BARCO_PADRAO.hitbox;
        obstaculo->animacao_andar = BARCO_PADRAO.animacao_andar;
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

void iniciar_spawn_obstaculos(void) {
    ultimo_spawn_obstaculo = GetTime() - 2.0;
}

void spawn_obstaculo(Fila *obstaculos_ativos) {
    if (obstaculos_ativos == NULL) return;

    obstaculo *novo_obstaculo = (obstaculo *)malloc(sizeof(obstaculo));
    if (novo_obstaculo == NULL) return;

    const char *tipo = TIPOS_OBSTACULO[GetRandomValue(0, 5)];
    init_obstacle(novo_obstaculo, tipo);
    novo_obstaculo->pos.x = 1280 + novo_obstaculo->hitbox.largura;

    if (!fila_enfileirar(obstaculos_ativos, novo_obstaculo)) {
        free(novo_obstaculo);
    }
}

void atualizar_spawn_obstaculos(Fila *obstaculos_ativos) {// aqui eu consigo alterar a velocidade de spawn
    if (obstaculos_ativos == NULL) return;
    if (ultimo_spawn_obstaculo < 0.0) {
        iniciar_spawn_obstaculos();
    }

    double agora = GetTime();
    double intervalo_spawn = 3.0 - (tempo_desde_inicio_jogo() * 0.03);// 3 é o intervalo inicial e 0.03 a medida que passa ele vai reduzindo isso
    if (intervalo_spawn < 0.25) {
        intervalo_spawn = 0.25;
    }


    if ((agora - ultimo_spawn_obstaculo) >= intervalo_spawn) {
        spawn_obstaculo(obstaculos_ativos);
        ultimo_spawn_obstaculo = agora;
    }
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
int get_velocidade_atual_obstaculos(void) {
    return velocidade_atual_obstaculos;
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

// Fator de escala da hitbox em relação ao sprite (0.0 a 1.0).
// Valores menores = hitbox menor = mais fácil de desviar.
#define ESCALA_HITBOX_JOGADOR    0.50f
#define ESCALA_HITBOX_OBSTACULO  0.60f

// retorna 1 se houve colisão, 0 caso contrário. Se o jogador tiver o escudo ativo, ele absorve o impacto e não sofre dano, se ele tiver a pa ativa ele consegue remover o lixo do caminho, se ele tiver a pa ativa e colidir com um lixo no rio, ele é invencivel e não sofre dano, caso contrário, ele sofre dano normalmente
int colisao_jogador_X_obstaculo(jogador *jogador,obstaculo *obstaculo){
    tempo_invencivel(jogador);

    float jw = jogador->hitbox.largura * ESCALA_HITBOX_JOGADOR;
    float jh = jogador->hitbox.altura  * ESCALA_HITBOX_JOGADOR;
    Rectangle rJogador = {
        jogador->pos.x + (jogador->hitbox.largura - jw) / 2.0f,
        jogador->pos.y + (jogador->hitbox.altura  - jh) / 2.0f,
        jw,
        jh
    };

    float ow = obstaculo->hitbox.largura * ESCALA_HITBOX_OBSTACULO;
    float oh = obstaculo->hitbox.altura  * ESCALA_HITBOX_OBSTACULO;
    Rectangle rObstaculo = {
        obstaculo->pos.x - ow / 2.0f,
        obstaculo->pos.y - oh / 2.0f,
        ow,
        oh
    };

    // checando colisao e em caso de poderes especiais ativados:
    if (CheckCollisionRecs(rJogador, rObstaculo) ){

        if (jogador->poderes.pa && (strcmp(obstaculo->nome, "Garrafa no rio") == 0 || strcmp(obstaculo->nome, "Sacola no rio") == 0)){ // a pa protege o jogador do lixo no rio, mas não de outros obstaculos, entao se o jogador tiver a pa ativa e colidir com um lixo no rio, ele é invencivel e não sofre dano, caso contrário, ele sofre dano normalmente
            return 1;
        }

        // checa os poderes especiais, se o jogador tiver o escudo ativo, ele absorve o impacto e não sofre dano, se ele tiver a pa ativa, ele é invencível e não sofre dano, caso contrário, ele sofre dano normalmente
        if (jogador->poderes.escudo){
            jogador->poderes.escudo = false; // desativa o escudo
            jogador->invencivel=1;
            tempo_inicio_invencivel = GetTime();
            return 1;
        }


        if (!jogador->invencivel){
            jogador->vida -=40;
            jogador->invencivel=1;
            tempo_inicio_invencivel = GetTime();
            return 1;
        }
    }

 return 0;
}
