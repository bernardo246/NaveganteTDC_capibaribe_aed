#ifndef DEFAULT_STRUCTS_H
#define DEFAULT_STRUCTS_H

typedef struct {
    int x;
    int y;
} Posicao;

typedef struct {
    int num_frames;
    char frames[16][64]; // lista de frames, tem o caminho de cada imagem
    int frame_atual;
} Animacao;

typedef struct hitbox {
    int largura;
    int altura;
} Hitbox;

#endif /* DEFAULT_STRUCTS_H */
