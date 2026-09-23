# Aula 6

Em Prog 1, se precisássemos calcular a média de 50 notas, declarávamos n1, n2, n3... ou usávamos um vetor. Mas o que o C FAZ FISICAMENTE na memória quando você escreve int notas[50]? Por que o primeiro elemento é SEMPRE o índice [0] e não [1]?

notas[0] -> *notas + 0
notas[1] ->* notas + 1
notas[2] -> *notas + 2
...
...
...
notas[49] ->* notas + 49

## Vetores Unidimensionais

### O Que É um Vetor na RAM?

Um vetor é um bloco homogêneo e contínuo de memória. Quando declaramos int vet[4] = {10, 20, 30, 40};, o compilador reserva 16 bytes seguidos (elementos x 4 bytes).

                    O VETOR 'vet[4]' NA MEMÓRIA RAM (STACK)

  ENDEREÇO HEX      ÍNDICE       VALOR GUARDADO      EQUIVALENTE EM PONTEIRO
 ┌──────────────┬─────────────┬───────────────────┬───────────────────────────┐
 │  0x7FFF1000  │   vet[0]    │        10         │ *(vet + 0)  <-- BASE      │
 ├──────────────┼─────────────┼───────────────────┼───────────────────────────┤
 │  0x7FFF1004  │   vet[1]    │        20         │* (vet + 1) (+4 bytes)     │
 ├──────────────┼─────────────┼───────────────────┼───────────────────────────┤
 │  0x7FFF1008  │   vet[2]    │        30         │ *(vet + 2) (+8 bytes)     │
 ├──────────────┼─────────────┼───────────────────┼───────────────────────────┤
 │  0x7FFF100C  │   vet[3]    │        40         │* (vet + 3) (+12 bytes)    │
 └──────────────┴─────────────┴───────────────────┴───────────────────────────┘

### A Equação Mágica do Índice

vet[i] = *(vet + i)

- O nome vet isolado avalia para o endereço do primeiro elemento (&vet[0]).
- O índice 0 significa: "A partir da base, desloque 0 casas". Por isso começamos no zero!

## Matrizes Bidimensionais

### O Desenho no Papel vs. A Realidade na RAM

Quando declaramos int mat[2][3]:

Visão Conceitual (2 Linhas x 3 Colunas):
       Col 0   Col 1   Col 2
 Lin 0 [  1  ][  2  ][  3  ]
 Lin 1 [  4  ][  5  ][  6  ]

 Realidade na Memória RAM (Mapeamento Linha-Maior / Row-Major Order):
 ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
 │ mat[0][0]│ mat[0][1]│ mat[0][2]│ mat[1][0]│ mat[1][1]│ mat[1][2]│
 │   1      │    2     │     3    │     4    │     5    │     6    │
 └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
  0x1000        0x1004      0x1008  0x100C    0x1010     0x1014

### A Fórmula de Acesso Interno

Endereço(matriz[i][j]) = Base + ((i * NumColunas) + j) * sizeof(tipo)

- Base: A posição inicial de memória onde a matriz começa (o endereço de mat[0][0]).
- i (Índice da Linha): Quantas linhas completas você precisa "pular".
- NumColunas: Quantos elementos existem dentro de cada linha.
- j (Índice da Coluna): Quantas casas andar para a direita dentro da linha atual.
- sizeof(Tipo): O tamanho em bytes de cada elemento (ex: int = 4 bytes).
- Para acessar mat[1][1] em uma matriz de 3 colunas: 1 X 3 + 1 = índice 4 na memória contínua.

'''c
    int mat[2][3] = {
        {10, 20, 30},  // Linha 0
        {40, 50, 60}   // Linha 1
    };
'''

Suponha que o sistema operacional alocou essa matriz a partir do Endereço Base 1000 na RAM.

Posição 1D na RAM:    [0]    [1]    [2]    [3]    [4]    [5]
 Conteúdo:           [ 10 ] [ 20 ] [ 30 ] [ 40 ] [ 50 ] [ 60 ]
 Matriz 2D:         mat[0][0] [0][1] [0][2] [1][0] [1][1] [1][2]
 Endereço HEX:       1000   1004   1008   1012   1016   1020
                     └────── Linha 0 ─────┘ └────── Linha 1 ─────┘