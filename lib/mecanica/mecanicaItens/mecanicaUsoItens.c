// vou ter varias funcoes de itens diferentes, pq cada um tem uma animacacao e mecanica diferente, isso serve basicamente pra eu fazer as funcoes de mecanica de cada item quando ativado pelo jogador



bool checar_item_usavel(jogador* player, int tipo_item) {
    // exemplo de funcao para checar se o item pode ser usado, basicamente eu vou verificar se o jogador tem o item no inventario e se ele pode ser usado (por exemplo, se o jogador ja esta invencivel, ele nao pode usar outro escudo)
    if (tipo_item == ITEM_ESCUDO && player->invencivel) {
        return false; // jogador ja esta invencivel, nao pode usar outro escudo
    }

    if (fetch_item(player->inventario, tipo_item) == false) {
        return false; // jogador nao tem o item no inventario
    }

    // aqui voce pode adicionar outras verificacoes dependendo do tipo do item
    return true; // item pode ser usado
}

//exemplo de funcao de uso do item, nesse caso do escudo, ele vai deixar o jogador invencivel por um tempo
void usar_item(jogador* player, int tipo_item) {
    if (!checar_item_usavel(player, tipo_item)) {
        printf("Item nao pode ser usado!\n");
        return;
    }

    // aqui voce pode adicionar a logica de uso do item dependendo do tipo
    if (tipo_item == ITEM_ESCUDO) {
        player->invencivel = 1; // ativa o escudo
        desativar_poder(player, tipo_item); // chama a funcao para desativar o poder depois de um tempo
    }
    else if (tipo_item == ITEM_PA) {
        player->poderes->pa = true; // ativa a pa
        desativar_poder(player, tipo_item); // chama a funcao para desativar o poder depois de um tempo
    }

    // aqui voce pode adicionar outras logicas de uso para outros tipos de itens

    remove_item(player->inventario, tipo_item, 1); // remove 1 unidade do item do inventario
}

void desativar_poder(jogador* player, int tipo_item) {
    // exemplo de funcao para desativar o poder do item depois de um tempo, nesse caso do escudo, ele vai deixar o jogador invencivel por 5 segundos
    if (tipo_item == ITEM_ESCUDO) {
        player->invencivel = 0; // desativa o escudo
    }
    else if (tipo_item == ITEM_PA) {
        player->poderes->pa = false; // desativa a pa
    }
 // aqui voce pode adicionar outras logicas de desativacao para outros tipos de itens
}