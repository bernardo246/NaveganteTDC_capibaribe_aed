# 🚣 Navegante TDC do Capibaribe 🌊

> **Jogo em C — Vibe: Pontes e Rios do Recife**
> Projeto de Estrutura de Dados — AED 2026.1

---

## Sobre o Jogo

**Navegante TDC do Capibaribe** é um **Endless Runner aquático** desenvolvido em **C**, inspirado no Rio Capibaribe e na identidade cultural de Recife — a *"Veneza Brasileira"*, com sua rede de rios, canais e mais de 50 pontes.

O jogador controla uma embarcação descendo o Rio Capibaribe, desviando de obstáculos típicos dos rios recifenses e coletando itens da cultura local.

### Elementos do Jogo

- 🌊 Rio Capibaribe como cenário principal
- 🪵 Obstáculos: troncos, garrafas, sacolas, pedras, barcos
- 🎒 Itens coletáveis: moeda, escudo, peixe, pá
- ⚡ Velocidade da correnteza aumenta progressivamente
- 🌧️ Sistema de clima em tempo real via API (Open-Meteo)
- 🔊 Efeitos sonoros e música de fundo
- 🪙 Moedas coletadas definem a pontuação no ranking

---

## Dependências

### Linux / WSL (Ubuntu)

```bash
sudo apt install libcurl4-openssl-dev
sudo apt install libcjson-dev
```

### Raylib

```bash
# Linux / WSL
sudo apt install libraylib-dev

# macOS
brew install raylib
```

---

## Como Compilar

```bash
make
```

### Como Executar

```bash
./navegador-capibaribe
```

### Compilar teste de hitbox

```bash
make test_hitbox_obstaculo
./test_hitbox_obstaculo
```

---

## Estruturas de Dados

### Fila (Lista Encadeada) — Obstáculos no Rio

Controla os obstáculos que chegam pelo rio. Cada nó contém um obstáculo ativo. É a espinha dorsal da mecânica — sem ela, o rio não flui.

### Lista Duplamente Encadeada Circular — Inventário

Gerencia os itens coletados pelo jogador. Suporta scroll circular para seleção e uso de itens. Limitada por capacidade de tipos diferentes.

### Lista Encadeada + Merge Sort — Ranking

Armazena as pontuações dos jogadores. Ao fim de cada partida, a quantidade de **moedas coletadas** é registrada e ordenada com **Merge Sort** para exibir o **Top 5 Navegantes do Capibaribe**.

---

## Obstáculos

| Obstáculo | Descrição |
|-----------|-----------|
| 🪵 Tronco | Detritos naturais arrastados pela correnteza |
| 🍶 Garrafa no rio | Resíduos plásticos que poluem o Capibaribe |
| 🛍️ Sacola no rio | Sacolas plásticas flutuando nas águas |
| 🪨 Pedra pequena | Rochas menores espalhadas pelo leito do rio |
| 🪨 Pedra grande | Grandes rochas emergindo das águas |
| ⛵ Barco | Embarcações em movimento cruzando a rota |

---

## Itens Coletáveis

| Item | Efeito |
|------|--------|
| 🪙 Moeda | Pontuação — quantidade define o ranking |
| 🛡️ Escudo | Invencibilidade temporária (5s) |
| 🐟 Peixe | Recupera vida |
| 🪛 Pá | Poder especial (10s) |

---

## Sistema de Clima

O jogo usa a API **Open-Meteo** para buscar dados climáticos reais do Marco Zero de Recife a cada 15 minutos:

- `rain > 0` → ativa efeito visual de chuva na tela
- `is_day` → detecta se é dia ou noite
- Atualização automática sem travar o loop do jogo

---

## Organização do Repositório

```
NaveganteTDC_capibaribe_aed/
├── src/                        ← lógica do jogo
│   ├── main.c                  ← ponto de entrada
│   ├── menu.c / .h             ← menu principal
│   ├── jogo.c / .h             ← loop e lógica principal
│   ├── hud.c / .h              ← interface do jogador
│   ├── clima.c / .h            ← integração com API de clima
│   ├── clima_visual.c          ← efeitos visuais de chuva
│   ├── som.c / .h              ← sistema de áudio
│   └── test_hitbox_obstaculo.c ← ferramenta de debug de hitbox
├── lib/                        ← estruturas de dados
│   ├── fila.c / .h             ← fila de obstáculos
│   ├── lista.c / .h            ← lista encadeada
│   ├── ranking.c / .h          ← recordes + merge sort
│   ├── inventario/
│   │   ├── inventario.c/h
│   │   └── scrollInventario.c/h
│   └── mecanica/               ← mecânicas do jogo
│       ├── movimentacao.c/h
│       ├── fila_de_obstaculos.c/h
│       └── mecanicaItens/
│           ├── mecanicaGeracaoItens.c/h
│           ├── mecanicaItensInventario.c/h
│           └── mecanicaUsoItens.c/h
├── include/                    ← tipos e headers compartilhados
│   ├── entidades.h
│   ├── default_structs.h
│   ├── item.h
│   └── clima.h
├── assets/                     ← recursos do jogo
│   ├── sprites/                ← imagens e animações
│   └── sounds/                 ← efeitos sonoros e música
├── docs/                       ← documentação
├── Makefile                    ← compilação automática
└── README.md
```

---

## Estrutura de Branches

```
● main        ← versão final entregável
└─ ● develop  ← integração geral
   ├─ marcelo
   ├─ bernardo
   ├─ LuizEduardo
   ├─ rodrigo
   └─ malu
```

## Fluxo de Trabalho

```
sua branch → commit → push → merge na develop → main (versão final)
```

---

## Regras do Time

- 🚫 Nunca commitar direto na `main` ou na `develop`
- ✅ Sempre trabalhar na sua própria branch
- 📝 Mensagem de commit descritiva: `"adiciona função X"`
- 🔄 Antes de começar: `git pull origin develop`
- 🏁 Merge na `main` só quando o jogo estiver 100% funcionando

---

*🚣 Navegante TDC do Capibaribe — AED 2026.1 — Recife, PE*