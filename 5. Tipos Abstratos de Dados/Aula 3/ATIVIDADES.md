# Atividades

## Exercício 1: Abstração, Encapsulamento e Ocultação de Dados

Explique a diferença fundamental entre uma struct pública (declarada inteiramente em um arquivo .h) e um Tipo Abstrato de Dados (TAD) implementado com ponteiro opaco em C. Quais são as principais vantagens dessa abordagem para a manutenção e evolução de um software de grande porte ou jogo como o Space Defender?

## Exercício 2: Quebra de Encapsulamento

Considere o seguinte trecho de código de um aluno que tentou criar um TAD de gerenciamento de munição:


```c

// municao.h
typedef struct Municao {
    int projeteis_restantes;
    int capacidade_maxima;
} Municao;

// main.c
#include "municao.h"

void recarregar(Municao *m) {
    m->projeteis_restantes += 10;
}

```

1. Identifique os problemas de arquitetura e encapsulamento na declaração acima.

2. Reescreva a declaração em municao.h e a implementação em municao.c utilizando o padrão de ponteiro opaco.

## Exercício 3: Validação e Resiliência

O que é uma Invariante de Estado em um TAD? Considere o TAD Defensor do projeto Space Defender, que possui os campos internos x (posição na tela), vida (integridade do canhão, entre 0 e 100) e pilha_undo (ponteiro para o histórico de posições).

Escreva a função void defensor_causar_dano(Defensor *d, int dano) garantindo a preservação rigorosa de todas as invariantes do TAD, mesmo se o cliente passar ponteiros nulos ou valores de dano negativos/excessivos.

## Exercício 4: Construtores com Rollback

Por que todo construtor de TAD que aloca múltiplos blocos dinâmicos no Heap deve implementar um mecanismo de rollback?

Escreva o código em C de um construtor seguro FilaInimigos* fila_inimigos_criar(void) que aloca o TAD de controle e inicializa seus ponteiros inicio e fim com NULL e o contador qtd com 0, demonstrando o tratamento defensivo completo para alocação no Heap.

## Exercício 5: O Erro de Tipo Incompleto

Um programador tenta compilar o seguinte código no main.c:

```c

// main.c
#include "defensor.h"

int main(void) {
    Defensor *d = defensor_criar(400, 500, 5.0f);
    printf("Vida da nave: %d\n", d->vida); // ERRO DE COMPILAÇÃO
    return 0;
}

```

1. Qual é a mensagem exata de erro emitida pelo compilador (GCC/Clang) na linha do printf e por que ela ocorre?

2. Como o código do main.c deve ser corrigido para obter o valor da vida respeitando o contrato do TAD?
