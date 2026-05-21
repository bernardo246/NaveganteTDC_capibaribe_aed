// serve pra fazer a comunicacao entre os itens e o inventario, basicamente eu vou checar se houve colisao do item e do personagem, eu vou verificar o tipo do item e em seguida eu vou remover o item da tela e adicionar o item no inventario do jogador,



// basicamente eu vou checar se houve colisao do item e do personagem, eu vou verificar o tipo do item e em seguida eu vou remover o item da tela e adicionar o item no inventario do jogador,


// serve pra fazer a comunicacao entre os itens e o inventario, basicamente eu vou checar se houve colisao do item e do personagem, eu vou verificar o tipo do item e em seguida eu vou remover o item da tela e adicionar o item no inventario do jogador,

#include "mecanicaItensInventario.h"
#include "mecanicaGeracaoItens.h"

// basicamente eu vou checar se houve colisao do item e do personagem, eu vou verificar o tipo do item e em seguida eu vou remover o item da tela e adicionar o item no inventario do jogador,


int check_colisao_item_jogador(jogador *jogador, Item *item) {
    Rectangle rJogador = {
        jogador->pos.x - jogador->hitbox.largura/2.0f,
        jogador->pos.y - jogador->hitbox.altura/2.0f,
        jogador->hitbox.largura,
        jogador->hitbox.altura
    };
    Rectangle rItem = {
        item->pos.x - item->hitbox.largura/2.0f,
        item->pos.y - item->hitbox.altura/2.0f,
        item->hitbox.largura,
        item->hitbox.altura
    };

    return CheckCollisionRecs(rJogador, rItem);
}

void checarColeta_item(jogador *jogador, Linkedlist_item *lista_itens, Item *item) {
    if (check_colisao_item_jogador(jogador, item)) {
        // adiciona o item no inventario do jogador
        add_item(jogador->inventario, item->tipo, item->valor);
        
        // remove o item do mapa
        
    }
}