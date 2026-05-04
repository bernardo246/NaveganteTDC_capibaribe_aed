# 🌊 Surfista do Pina 🏄

> **Jogo em C — Praia do Pina, Recife-PE**  
> Projeto de Estrutura de Dados

---

## Sobre o Jogo

**Surfista do Pina** é um jogo **Endless Runner vertical** desenvolvido em **C**, ambientado na famosa Praia do Pina, em Recife-PE. O jogador controla um surfista descendo as ondas, desviando de obstáculos e coletando itens típicos da cultura praiana recifense.

### Mecânica Principal

| Ação | Descrição |
|------|-----------|
| Posição | O surfista fica fixo na base da tela |
| Obstáculos | Ondas com jet-skis, rochas e bandeiras de interdição descem continuamente |
| Movimentação | Teclas **A** (esquerda) e **D** (direita) para desviar |
| Coleta | Itens como 🥥 coco e 🥟 pastel concedem pontos |
| Progressão | A velocidade aumenta com o tempo |
| Game Over | Colisão com obstáculo encerra a partida e registra a pontuação |

---

## Estruturas de Dados

### 2.1 Fila (Lista Encadeada) — Ondas do Jogo

A fila representa as ondas chegando na tela. Cada nó contém uma onda com seus obstáculos e itens. É a espinha dorsal da mecânica do jogo — sem ela, não há ondas, não há jogo.

### 2.2 Árvore Binária de Busca (BST) — Sistema de Itens

A BST gerencia todos os itens coletáveis. Cada item tem um código numérico e é armazenado na árvore pelo seu valor. Ao coletar um item, a BST é consultada para retornar a pontuação correspondente.

```
         [coco = 10]
        /            \
   [alga = 5]    [pastel = 20]
   /                       \
[lixo = -5]         [prancha = 50]
```

### 2.3 Lista Encadeada — Ranking de Recordes

Armazena as pontuações dos jogadores. Ao fim de cada partida, a pontuação é inserida e a lista é ordenada com **Merge Sort** para exibir o **Top 5 Surfistas do Pina**.

---

## Algoritmo de Ordenação

**Merge Sort / Insertion Sort** aplicado na lista de recordes.

1. Ao fim de cada partida, a pontuação é inserida na lista de recordes
2. O algoritmo reordena a lista do **maior para o menor**
3. O menu exibe o **Top 5** com nome do jogador e pontuação

---

## Menu do Jogo

```
==============================
      🌊 SURFISTA DO PINA 🌊
==============================
  1. Jogar
  2. Ver Recordes
  3. Como Jogar
  4. Sair
```

---

## Resumo das Estruturas

| Estrutura | Aplicação |
|-----------|-----------|
| Fila (Lista Encadeada) | Geração e controle das ondas na tela |
| Árvore Binária de Busca (BST) | Gerenciamento e pontuação dos itens coletáveis |
| Lista Encadeada + Merge Sort | Ranking dos recordes (Top 5) |

---

*🌊 Surfista do Pina — Projeto de Estrutura de Dados | Recife, PE*
