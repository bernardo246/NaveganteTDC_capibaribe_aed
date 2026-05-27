#ifndef SOM_H
#define SOM_H

#include <raylib.h>

typedef enum {
    SOM_TROCA_ITEM_INVENTARIO = 1,
    SOM_PEGOU_PA              = 2,
    SOM_PEGOU_MOEDA           = 3,
    SOM_COLISAO_GARRAFA       = 4,
    SOM_COLISAO_PONTE         = 5,
    SOM_ATIVACAO_ESCUDO       = 6,
    SOM_REMANDO               = 7,
    SOM_COLISAO_SACOLA        = 8,
    SOM_PEGOU_ESCUDO          = 9,
    SOM_PEGOU_PEIXE           = 10,
    SOM_COLISAO_TRONCO        = 11,
    SOM_COLISAO_PEDRA         = 12,
    SOM_MUSICA_INTRO          = 13
} TipoSom;

void sons_carregar(void);
void sons_descarregar(void);
void tocar_som(TipoSom tipo);
void atualizar_musica(void);

#endif /* SOM_H */