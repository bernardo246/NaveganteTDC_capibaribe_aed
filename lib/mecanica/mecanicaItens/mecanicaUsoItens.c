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
void usar_escudo(jogador* player) {
    if (checar_item_usavel(player, ITEM_ESCUDO)) {
        // aqui voce pode adicionar a logica para ativar o escudo, por exemplo, definir o jogador como invencivel por um tempo
        player->invencivel = 1; // exemplo de ativacao do escudo, definindo o jogador como invencivel
        remove_item(player->inventario, ITEM_ESCUDO, 1); // remove um escudo do inventario do jogador
    }
}