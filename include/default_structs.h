#ifndef DEFAULT_STRUCTS_H

typedef struct {
    float x;
    float y;
} Posicao;


typedef struct {
    int num_frames;
    char frames[num_frames][64]; // lista de frames, tem o caminho de cada imagem
    int frame_atual;

} Animacao;

typedef struct hitbox {
    float largura;
    float altura;
} Hitbox;





#define DEFAULT_STRUCTS_H