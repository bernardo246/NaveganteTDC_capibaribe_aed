// vou ter varias funcoes de itens diferentes, pq cada um tem uma animacacao e mecanica diferente, isso serve basicamente pra eu fazer as funcoes de mecanica de cada item quando ativado pelo jogador
#include <raylib.h>
#include "mecanicaUsoItens.h"


static double tempo_escudo = 5;
static double tempo_pa = 10;


bool checar_item_usavel(jogador* player, TipoItem tipo_item) {
    // exemplo de funcao para checar se o item pode ser usado, basicamente eu vou verificar se o jogador tem o item no inventario e se ele pode ser usado (por exemplo, se o jogador ja esta invencivel, ele nao pode usar outro escudo)
    if (tipo_item == ITEM_ESCUDO && player->poderes.escudo) {
        return false; // jogador ja esta invencivel, nao pode usar outro escudo
        printf("Item Escudo ja esta ativo e nao pode ser usado novamente!\n");
    }
    if (tipo_item == ITEM_PA && player->poderes.pa) {
        return false; // jogador ja tem a pa ativa, nao pode usar outra
        printf("Item PA ja esta ativo e nao pode ser usado novamente!\n");
    }
    

    if (fetch_item(player->inventario, tipo_item) == false) {
        return false; // jogador nao tem o item no inventario
    }

    // aqui voce pode adicionar outras verificacoes dependendo do tipo do item
    return true; // item pode ser usado
}

//exemplo de funcao de uso do item, nesse caso do escudo, ele vai deixar o jogador invencivel por um tempo
bool usar_item(jogador* player, TipoItem tipo_item) {
    if (!checar_item_usavel(player, tipo_item)) {
        printf("Item nao pode ser usado!\n");
        return false; // item nao pode ser usado  
    }


    // se quiser pode adicionar a logica de desativar o poder depois de um tempo usando a funcao desativar_poder, por exemplo, o escudo deixa o jogador invencivel por 5 segundos, entao eu posso usar a funcao desativar_poder para desativar o escudo depois de 5 segundos
    // aqui voce pode adicionar a logica de uso do item dependendo do tipo

    
    if (tipo_item == ITEM_ESCUDO) {
        player->poderes.escudo = true; // ativa o escudo
        player->poderes.tempo_escudo = GetTime(); // define o tempo do escudo para 5 segundos
    }
    else if (tipo_item == ITEM_PA) {
        player->poderes.pa = true; // ativa a pa
        player->poderes.tempo_pa = GetTime(); // define o tempo da pa para 10 segundos
    }
    else if (tipo_item == ITEM_PEIXE) {
        player->vida += 20; // exemplo de efeito do item peixe, ele cura o jogador em 20 de vida
        if (player->vida > 100) player->vida = 100; // limita

    }

    // aqui voce pode adicionar outras logicas de uso para outros tipos de itens

    remove_item(player->inventario, tipo_item, 1); // remove 1 unidade do item do inventario
    return true; // item usado com sucesso
}

void desativar_poder(jogador* player, TipoItem tipo_item) {
    // exemplo de funcao para desativar o poder do item depois de um tempo, nesse caso do escudo, ele vai deixar o jogador invencivel por 5 segundos
    if (tipo_item == ITEM_ESCUDO) {
        player->poderes.escudo = false; // desativa o escudo
    }
    else if (tipo_item == ITEM_PA) {
        player->poderes.pa = false; // desativa a pa
    }
 // aqui voce pode adicionar outras logicas de desativacao para outros tipos de itens
}

void atualizar_poderes(jogador *player) {

    if (player->poderes.escudo && GetTime() - player->poderes.tempo_escudo >= tempo_escudo) {
        desativar_poder(player, ITEM_ESCUDO);
    }
    if (player->poderes.pa && GetTime() - player->poderes.tempo_pa >= tempo_pa) {
        desativar_poder(player, ITEM_PA);
    }
}
