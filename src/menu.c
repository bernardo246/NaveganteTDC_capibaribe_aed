/* menu.c - Menu e loop principal do jogo (Dev 4) */

#include <stdio.h>
#include "menu.h"
#include "jogo.h"

void menu_iniciar(void) {
    int opcao;
    do {
        menu_exibir();
        opcao = menu_ler_opcao();
        switch (opcao) {
            case 1: jogo_iniciar(); break;
            case 2: /* ver ranking */ break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menu_exibir(void) {
    printf("\n=== Navegador Capibaribe ===\n");
    printf("1. Novo Jogo\n");
    printf("2. Ver Ranking\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int menu_ler_opcao(void) {
    int op;
    scanf("%d", &op);
    return op;
}
