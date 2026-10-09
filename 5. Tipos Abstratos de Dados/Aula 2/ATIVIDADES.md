# Atividades

## Exercício 1: Diagnóstico e Correção de Quebra de Invariantes

Considere o seguinte TAD ContaBancaria escrito de formaIngênua por um desenvolvedor iniciante.

Código Frágil (conta.c):

```c

#include <stdlib.h>

typedef struct {
    int numero_conta;
    float saldo;
    float limite_cheque_especial;
} ContaBancaria;

ContaBancaria* conta_criar(int numero, float limite) {
    ContaBancaria *c = (ContaBancaria *) malloc(sizeof(ContaBancaria));
    c->numero_conta = numero;
    c->saldo = 0.0f;
    c->limite_cheque_especial = limite;
    return c;
}

void conta_sacar(ContaBancaria *c, float valor) {
    c->saldo -= valor; // QUEBRA DE INVARIANTE!
}

```

Sua Tarefa:

1. Identifique as 3 falhas de invariante e segurança presentes no código acima.

2. Reescreva o construtor conta_criar e a função conta_sacar corrigindo todas as falhas. Invariantes do TAD:

- O ponteiro retornado pelo malloc nunca pode ser manipulado sem checagem de NULL.

- limite_cheque_especial deve ser sempre maior ou igual a zero.

- O saldo acumulado nunca pode ficar abaixo de -(limite_cheque_especial).

- O valor do saque deve ser estritamente positivo (valor > 0).

## Exercício 2: Construtor com Rollback e Alocação Múltipla

Em sistemas gráficos e de áudio, um TAD frequentemente precisa alocar a estrutura de controle e um ou mais buffers internos no Heap. Se qualquer uma das alocações falhar durante a inicialização, todas as alocações anteriores devem ser desfeitas (rollback) para evitar vazamentos de memória.

Implemente a função MatrizBuffer* matriz_buffer_criar(int linhas, int colunas) para a seguinte estrutura:

```c

typedef struct {
    int **matriz; // Vetor de ponteiros para as linhas
    int linhas;
    int colunas;
} MatrizBuffer;

```

Requisitos Obrigatórios:

- Valide se linhas > 0 e colunas > 0. Caso contrário, retorne NULL.
- Aloque a estrutura principal MatrizBuffer.
- Aloque o vetor de ponteiros matriz (de tamanho linhas *sizeof(int*)).
- Em um laço, aloque cada linha individualmente (de tamanho colunas * sizeof(int)).
- Mecanismo de Rollback: Se a alocação de qualquer linha $i$ falhar, o construtor deve desalocar em ordem todas as linhas $0 \dots i-1$ já alocadas, desalocar o vetor de ponteiros, desalocar a estrutura principal e finalmente retornar NULL.

## Exercício 3: TAD Múltiplo de Controle de Partículas

No motor de um jogo 2D, a estrutura do gerenciador de efeitos visuais aloca três blocos interdependentes no Heap:

```c

typedef struct {
    float x, y;
    float vida_util;
} Particula;

typedef struct {
    Particula *vetor_particulas; // Bloco 1
    char *nome_emissor;          // Bloco 2
    int capacidade;
    int ativas;
} EmissorEfeitos;

```

Escreva o construtor seguro EmissorEfeitos* emissor_criar(const char *nome, int capacidade_maxima) aplicando tratamento de erros completo:

1. Validação de Entrada: nome não pode ser NULL e capacidade_maxima deve ser maior que zero.

2. Alocação Faseada:

- Fase 1: Aloque a estrutura EmissorEfeitos.

- Fase 2: Aloque o vetor vetor_particulas com capacidade_maxima elementos.

- Fase 3: Aloque a string nome_emissor dinamicamente no Heap com tamanho strlen(nome) + 1 e copie o conteúdo usando strcpy.

3. Rollback Gradual: Garanta que, se a Fase 2 ou a Fase 3 falharem por falta de memória RAM, o construtor execute a liberação proporcional de tudo o que foi alocado nas fases anteriores antes de retornar NULL.