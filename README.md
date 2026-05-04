# 🚣 Navegador do Capibaribe 🌊

> **Jogo em C — Vibe: Pontes e Rios do Recife**
> Projeto de Estrutura de Dados — AED 2026.1

---

## Sobre o Jogo

**Navegador do Capibaribe** é um **Endless Runner aquático** desenvolvido em **C**, inspirado no Rio Capibaribe, nos igarapés e nas pontes históricas que definem a paisagem e a identidade de Recife — a *"Veneza Brasileira"*, com sua rede de rios, canais e mais de 50 pontes.

O jogador controla uma jangada/canoa descendo o Rio Capibaribe, desviando de obstáculos típicos dos rios recifenses e coletando itens da cultura local.

### Elementos Culturais

- 🌊 Rio Capibaribe e igarapés como cenário principal
- 🌉 Pontes icônicas de Recife como marcos de fase *(Ponte Duarte Coelho, Ponte Buarque de Macedo)*
- 🪵 Obstáculos: troncos, lixo no rio, pilastras de pontes, barcos parados
- 🐟 Itens coletáveis: tainha, flor de mangue, botijão, remo extra
- ⚡ Velocidade da correnteza aumenta progressivamente
- 💀 Colisão encerra a partida e registra pontuação no ranking

---

## Justificativa da Vibe

O Rio Capibaribe é símbolo histórico de Recife — presente na literatura, música e arte pernambucana. A vibe **"Pontes e Rios do Recife"** tem forte identidade cultural e diferencia o projeto das demais propostas com temática de praia, homenageando a relação da cidade com a água de forma lúdica e educativa.

---

## Estruturas de Dados

### 3.1 Fila (Lista Encadeada) — Obstáculos no Rio

A fila representa os obstáculos e itens chegando pelo rio. Cada nó contém um trecho do rio com seus elementos. É a espinha dorsal da mecânica — sem ela, o rio não flui.

### 3.2 Árvore Binária de Busca (BST) — Catálogo de Itens

A BST gerencia todos os itens coletáveis. Cada item tem um código e é armazenado pela pontuação. Ao coletar um item, a BST retorna o valor correspondente.

```
          [tainha = 10]
         /             \
   [flor = 5]     [botijao = 20]
   /                          \
[lixo = -5]           [remo extra = 50]
```

### 3.3 Lista Encadeada — Ranking de Recordes

Armazena as pontuações dos jogadores. Ao fim de cada partida, a pontuação é inserida e ordenada com **Merge Sort** para exibir o **Top 5 Navegadores do Capibaribe**.

---

## Obstáculos

| Obstáculo | Descrição |
|-----------|-----------|
| 🪵 Tronco | Detritos naturais arrastados pela correnteza |
| 🗑️ Lixo no rio | Resíduos urbanos que poluem o Capibaribe |
| 🏛️ Pilastra de ponte | Estruturas das pontes históricas no caminho |
| ⛵ Barco parado | Embarcações ancoradas bloqueando a rota |

---

## Algoritmo de Ordenação — Merge Sort

Aplicado na lista de recordes ao fim de cada partida.

1. A pontuação é inserida na lista de recordes
2. O Merge Sort reordena do **maior para o menor**
3. O menu exibe o **Top 5** com nome do jogador e pontuação

---

## Menu do Jogo

```
================================
   🚣 NAVEGADOR DO CAPIBARIBE 🌊
================================
  1. Jogar
  2. Ver Recordes (Top 5)
  3. Como Jogar / Itens
  4. Sair
```

---

## Resumo das Estruturas

| Estrutura | Aplicação |
|-----------|-----------|
| Fila (Lista Encadeada) | Geração e controle dos obstáculos no rio |
| Árvore Binária de Busca (BST) | Catálogo e pontuação dos itens coletáveis |
| Lista Encadeada + Merge Sort | Ranking dos recordes (Top 5) |

---

## Organização do Repositório

```
navegador-capibaribe/
├── src/               ← lógica do jogo
│   ├── main.c         ← integração geral (Dev 5)
│   ├── menu.c / .h    ← menu + loop do jogo (Dev 4)
│   └── jogo.c / .h    ← lógica principal (Dev 4)
├── lib/               ← estruturas genéricas reutilizáveis
│   ├── fila.c / .h    ← fila de trechos do rio (Dev 1)
│   ├── arvore.c / .h  ← BST de itens coletáveis (Dev 2)
│   └── ranking.c / .h ← recordes + merge sort (Dev 3)
├── assets/            ← recursos do jogo
│   ├── sprites/       ← imagens e animações
│   ├── sounds/        ← efeitos sonoros e música
│   └── maps/          ← mapas e fases do rio
├── include/           ← tipos e headers compartilhados
│   └── tipos.h
├── docs/              ← documentação do projeto
├── Makefile           ← compilação automática (Dev 5)
└── README.md
```

### Como compilar

```bash
make
```

### Como executar

```bash
./navegador-capibaribe
```

---

*🌊 Navegador do Capibaribe — Vibe: Pontes e Rios do Recife | AED 2026.1*
