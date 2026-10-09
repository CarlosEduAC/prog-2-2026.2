# Especificação do Projeto Integrador: Space Defender — Retro Edition (Raylib 2D)

- **Disciplina:** Programação de Computadores 2
- **Interface Gráfica:** Raylib (C Puro)
- **Tipo de Entregável:** Aplicação Desktop Completa (Código-Fonte + Documentação)
- **Modalidade:** Em duplas ou individual

## 1. Visão Geral do Projeto

O Space Defender — Retro Edition é um jogo de defesa e combate espacial em arena fixa 2D (uma única tela estática sem rolagem), desenvolvido em C puro com a biblioteca Raylib. O jogador controla um canhão defensor na borda inferior da tela, movendo-se lateralmente para neutralizar ondas de naves agressoras que descendem em formação, gerenciar disparos e pontuações, e utilizar mecanismos táticos de reversão temporal.

Este projeto funciona como a avaliação prática integradora final da disciplina. Seu propósito é exercitar de forma direta, simples e focada todos os conceitos abordados ao longo do curso: alocação dinâmica no Heap, ponteiros e ponteiros opacos, recursão, estruturas de dados lineares (Listas Duplamente Encadeadas, Pilhas e Filas), Tipos Abstratos de Dados (TADs), modularização em bibliotecas (.h/.c), persistência em arquivos (texto e binário) e algoritmos de ordenação interna.

```txt

                            SPACE DEFENDER - RETRO EDITION
                                       │
    ┌──────────────────┬───────────────┼───────────────┬──────────────────┐
    ▼                  ▼               ▼               ▼                  ▼
[Fila FIFO]       [Pilha LIFO]   [Lista Dupla]   [Arquivos .bin]     [QuickSort]
Ondas de Inimigos  Histórico de   Tiros e Defesa   Salvar Estado do   Ranking de High
 (Spawn Queue)    Ações (Rewind)  em Tela (Nodes)   Jogo em Disco     Scores em Tela

```

## 2. Requisitos Funcionais e Técnicos

O projeto deve obrigatoriamente implementar as seguintes funcionalidades e restrições técnicas de arquitetura de software:

### 2.1. Estruturas de Dados Lineares

- **Gerenciamento de Tiros e Projéteis (Lista Duplamente Encadeada):**

Todos os tiros disparados pelo canhão defensor (e projéteis retaliatórios dos inimigos) ativos na tela devem ser mantidos em uma Lista Duplamente Encadeada. Quando um tiro sai do limite superior/inferior da tela ou atinge um alvo, o nó correspondente deve ser removido da lista em tempo $O(1)$ e sua memória devidamente liberada com free().

- **Fila de Spawn de Inimigos (Fila Dinâmica FIFO):**

A entrada de inimigos na arena deve ser controlada por uma Fila Dinâmica (SpawnQueue). A fila é carregada na inicialização de cada fase/onda e esvaziada ordenadamente (FIFO) à medida que os inimigos são inseridos no campo de batalha.

- **Reversão de Estado / Escudo Temporal (Pilha Dinâmica LIFO):**

O canhão defensor possui um recurso especial ativado via teclado (tecla Z). Essa funcionalidade utiliza uma Pilha Dinâmica que armazena os últimos $N$ estados/posições do defensor. Ao ativar o recurso, o jogo desempilha os estados em sequência LIFO, fazendo o canhão recuar no tempo e restaurar a integridade da estrutura.

- **Destruição e Explosão em Cadeia (Recursividade):**

Inimigos do tipo "Aglomerado" ao serem destruídos devem acionar uma função recursiva que verifica e causa dano/fragmentação em inimigos vizinhos adjacentes dentro de um raio de proximidade.

### 2.2. TADs e Modularização em Bibliotecas

- **Encapsulamento Rígido:**

O código não pode ser escrito em um único arquivo .c. Ele deve ser dividido em módulos funcionais separados com seus respectivos arquivos de cabeçalho (.h) e de implementação (.c).

- **Ponteiros Opacos (Opaque Pointers):**

As estruturas de dados dos TADs principais (ex: Defensor, Inimigo, Ranking, Engine) devem ter suas definções concretas ocultas nos arquivos .c, expondo apenas ponteiros opacos nos arquivos .h.

### 2.3. Persistência de Dados em Arquivos

- **Configurações Globais (Arquivo Texto - config.txt):**

Na inicialização, o jogo deve ler um arquivo de texto (config.txt) contendo parâmetros de exibição e áudio (resolução da janela, volume, dificuldade). Se o arquivo não existir, o sistema deve criá-lo com valores padrão via fprintf().

- **Sistema de Save/Load do Jogo (Arquivo Binário - savegame.bin):**

O jogador pode pausar e salvar o estado do jogo. A gravação deve ser realizada em um arquivo binário via fwrite(), salvando a estrutura do defensor, pontuação e fase atual. O carregamento restaura o estado via fread().

### 2.4. Ordenação Interna e Tabela de Pontuação

- **Ranking de High Scores em Tela:**

O jogo deve manter um arquivo de recordes (ranking.bin). Ao final de uma partida, se a pontuação do jogador estiver entre as melhores, seu nome e pontos devem ser salvos.

- **Ordenação por QuickSort ou InsertionSort:**

Antes de renderizar a tela de recordes, o vetor/lista de pontuações deve ser ordenado em ordem decrescente utilizando o algoritmo QuickSort ou InsertionSort implementado manualmente (é proibido usar o qsort padrão da biblioteca C).

## 3. Arquitetura do Sistema e Módulos do Código

A base de código deve obrigatoriamente respeitar a seguinte estrutura modular de arquivos:

```txt

space_defender/
│
├── main.c                   # Game Loop principal e gerenciador de telas (Raylib)
├── Makefile                 # Script de compilação modular (GCC + Raylib)
├── assets/                  # Texturas, sons e fontes (opcional)
│
├── config.txt               # Arquivo de configuração em texto plano
├── savegame.bin             # Arquivo binário de salvamento de estado
├── ranking.bin              # Arquivo binário de pontuações de recordes
│
└── include/ e src/
    ├── defensor.h / defensor.c     # TAD Canhão Defensor e Pilha de Reversão
    ├── tiro.h / tiro.c             # TAD Lista Dupla de Projéteis
    ├── inimigo.h / inimigo.c       # TAD Fila de Inimigos (Spawn Queue) e Explosão Recursiva
    ├── save.h / save.c             # Módulo de Leitura/Escrita de Arquivos (.txt / .bin)
    └── ranking.h / ranking.c       # Módulo de Ranking e Algoritmo de Ordenação (QuickSort ou InsertionSort)

```

## 4. Requisitos de Interface Gráfica e Loop de Jogo (Raylib)

O ciclo de execução principal no main.c deve gerenciar os estados da aplicação através de uma Máquina de Estados Finita:

```c

typedef enum {
    TELA_MENU,
    TELA_JOGO,
    TELA_PAUSA,
    TELA_RANKING,
    TELA_GAME_OVER
} EstadoJogo;

```

Elementos Gráficos Mínimos Exigidos:

1. Menu Principal: Botões navegáveis para "Iniciar Jogo", "Carregar Save", "Ranking" e "Sair".

2. HUD (Heads-Up Display): Exibição em tempo real da barra de vida da nave, pontuação atual, quantidade de elementos na fila de inimigos restantes e indicador de Cooldown da habilidade de Dobra Temporal (Pilha).

3. Game Over / Vitória: Exibição da pontuação final e campo de entrada de texto (usando funções de entrada da Raylib) para captura do nome do jogador caso ele entre no Ranking.

## Entregáveis

1. Arquivo .zip contendo:

- Código-fonte completo na estrutura de pastas (src/, include/, main.c, Makefile).

- Arquivo README.md com instruções de compilação e dependências da Raylib.

2. Apresentação Prática (Defesa em Laboratório):

- Defesa em laboratório com apresentação de 20 minutos, além de discussão sobre o código e as estruturas de dados implementadas.
