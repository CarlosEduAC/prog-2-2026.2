# O Modificador static e Ocultação de Símbolos no Linker

## A Tabela de Símbolos do Linker

Quando compilamos defensor.c e inimigo.c separadamente, o compilador gera tabelas de símbolos para cada arquivo. Por padrão, em C, toda função global escrita em um arquivo .c é exportada publicamente para a tabela de símbolos do Linker. Se dois arquivos .c criarem uma função utilitária com o mesmo nome — como calcular_distancia() —, o Linker falhará ao juntá-los.

Exemplo de Conflito de Colisão de Símbolos (Multiple Definition Error)

```txt

[ defensor.o ]                           [ inimigo.o ]
┌──────────────────────────┐             ┌──────────────────────────┐
│ Símbolos Exportados:     │             │ Símbolos Exportados:     │
│  - defensor_criar        │             │  - inimigo_criar         │
│  - checar_limites        │ <──ERRO!──> │  - checar_limites        │ (Nomes idênticos!)
└──────────────────────────┘             └──────────────────────────┘
                                │
                                ▼
               Linker (ld): "error: duplicate symbol 'checar_limites'"

```

## Ligação Externa vs. Ligação Interna

### 1. Ligação Externa (External Linkage — Padrão)

Funções e variáveis sem a palavra static possuem alcance global no executável. Qualquer outro arquivo .c pode acessá-las usando a declaração extern ou incluindo o arquivo de cabeçalho (.h).

### 2. Ligação Interna (Internal Linkage — com static)

Ao adicionar a palavra static antes de uma função ou variável no nível de arquivo em src/modulo.c, você instrui o compilador a não exportar esse símbolo para a Tabela do Linker.

- O símbolo torna-se estritamente privado daquele arquivo objeto (.o).

- Nenhum outro arquivo do projeto conseguirá enxergar ou chamar essa função.

- Não haverá erro de colisão se outro módulo .c criar uma função static de mesmo nome!

```c

// src/defensor.c

// FUNÇÃO PRIVADA DO MÓDULO: Ninguém fora de defensor.c consegue enxergar
static bool validar_posicao(float x, int largura_tela) {
    return (x >= 0 && x <= largura_tela - 40);
}

// FUNÇÃO PÚBLICA DO MÓDULO: Declarada no defensor.h e exportada no Linker
void defensor_atualizar(Defensor *d, int largura_tela) {
    if (validar_posicao(d->x, largura_tela)) {
        // ...
    }
}

```

## Funções Auxiliares Privadas no Projeto

O uso do static é vital no desenvolvimento de jogos e bibliotecas modulares em C:

1. Algoritmos Internos de Ordenação: Funções como particionar() no QuickSort do módulo de ranking.

2. Rotinas de Liberação/Limpeza: Funções auxiliares para liberar nós específicos de uma Lista Dupla ou Fila.

3. Cálculos Matemáticos Específicos de um TAD: Verificação de colisões geométricas internas.

## Prática Guiada

Vamos refatorar o módulo ranking.c para garantir que o algoritmo QuickSort exporga apenas a função pública de contrato no .h, ocultando a função de particionamento com static.

### 1. Interface Pública (include/ranking.h)

```c

#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char nome[20];
    int pontos;
} RegistroScore;

// APENAS esta função é exposta para o Linker e para o main.c
void ranking_ordenar_quicksort(RegistroScore *vetor, int inicio, int fim);

#endif

```

### 2. Implementação Privada (src/ranking.c)

```c

#include "ranking.h"
#include <string.h>

// FUNÇÃO ESTÁTICA PRIVADA: Oculta do Linker
static int particionar(RegistroScore *v, int inicio, int fim) {
    int pivo = v[fim].pontos;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j].pontos >= pivo) { // Ordenação decrescente
            i++;
            RegistroScore temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }
    RegistroScore temp = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = temp;
    return i + 1;
}

// FUNÇÃO PÚBLICA DO TAD
void ranking_ordenar_quicksort(RegistroScore *vetor, int inicio, int fim) {
    if (inicio < fim) {
        // Chama a função estática privada de particionamento
        int p = particionar(vetor, inicio, fim);
        ranking_ordenar_quicksort(vetor, inicio, p - 1);
        ranking_ordenar_quicksort(vetor, p + 1, fim);
    }
}

```
