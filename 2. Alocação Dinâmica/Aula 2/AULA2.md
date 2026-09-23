# Alocação Dinâmica de Vetores e Matrizes

## De 1 Elemento para N Elementos (Vetores)

Na aula passada alocamos espaço para 1 elemento:

```c

int *ponteiro = malloc(sizeof(int));

```

Para alocar um vetor dinâmico de N elementos, apenas multiplicamos a quantidade pelo tamanho do tipo:

```c

int *vetor = malloc(N_elementos * sizeof(int)); // Acesso contíguo: v[0], v[1], ..., v[N-1]

```

## Duas Novas Ferramentas da <stdlib.h>

1. *calloc(N, sizeof(tipo)):* Igual ao malloc, mas zera todos os bytes alocados (evita lixo de memória).

```c

// calloc: Aloca 3 inteiros. Diferente do malloc, ele zera a memória!
int *vetor = (int *) calloc(tam_inicial, sizeof(int));

```

2. realloc(ponteiro, novo_tamanho): Redimensiona um bloco já alocado no Heap sem perder os dados existentes.

```c

// Boa prática: usar ponteiro auxiliar ao fazer realloc
int *temp = (int *) realloc(vetor, novo_tam * sizeof(int));

```

As boas práticas usadas no malloc se aplicam aqui. Sempre que alocar memória, libere no final. E sempre verifique se o ponteiro da alocação é nulo, se sim finalize o programa de forma segura.

[Exemplo 1](main.c)
[Exemplo 2](vetor.c)

## Matrizes no Heap (Ponteiros de Ponteiros)

Como o Heap é um bloco linear, uma matriz de Linhas×Colunas exige um vetor de ponteiros (tipo **), onde cada posição aponta para uma linha alocada no Heap:

```txt

STACK                  HEAP (Passo 1)                   HEAP (Passo 2)

┌─────────┐            ┌──────────────┐                 ┌─────────────────┐
│ matriz  │ ─────────► │ matriz[0]    │ ──────────────► │ [10] [20] [30]  │
└─────────┘            ├──────────────┤                 └─────────────────┘
 (int **)              │ matriz[1]    │ ──────────────► │ [40] [50] [60]  │
                       └──────────────┘                 └─────────────────┘
                        (Vetor int *)                    (Vetores int)

```

> A Regra de Ouro da Matriz: Se alocou em 2 etapas (linhas depois colunas), você deve desalocar na ordem inversa (colunas depois linhas).

```c

    int linhas = 2;
    int colunas = 3;

    // 1. PASSO 1: Aloque o vetor de PONTEIROS (as linhas)
    // O tipo é (int **), usamos sizeof(int *) pois guarda endereços!
    int **matriz = (int **) malloc(linhas * sizeof(int *));

    if (matriz == NULL) {
        printf("Erro na alocação principal!\n");
        return 1;
    }

    // 2. PASSO 2: Para cada linha, aloque o vetor de VALORES (as colunas)
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));

        if (matriz[i] == NULL) {
            printf("Erro na alocação da linha %d!\n", i);
            return 1;
        }
    }

```

[Exemplo 3](matriz.c)

## Resumo de métodos de alocação de memória

| Característica     | malloc (Memory Allocation)                                              | calloc (Clear Allocation)                                                   | realloc (Re-Allocation)                                             |
|--------------------|-------------------------------------------------------------------------|-----------------------------------------------------------------------------|---------------------------------------------------------------------|
| Objetivo Principal | Alocar um bloco contíguo de bytes no Heap.                              | Alocar memória e inicializar todos os bytes com zero.                       | Alterar o tamanho de um bloco já alocado no Heap.                   |
| Sintaxe            | malloc(tamanho_bytes)                                                   | calloc(qtd_elementos, tamanho_tipo)                                         | realloc(ponteiro, novo_tamanho_bytes)                               |
| Parâmetros         | Recebe 1 argumento: total de bytes.                                     | Recebe 2 argumentos: quantidade e tamanho do tipo.                          | Recebe 2 argumentos: ponteiro atual e novo tamanho total.           |
| Estado da Memória  | Contém lixo de memória(valores indefinidos).                            | Garantidamente zerada($0$).                                                 | Preserva os dados antigos; a nova área expandida contém lixo.       |
| Desempenho         | Ligeiramente mais rápido (não gasta ciclo zerando).                     | Ligeiramente mais lento (executa a limpeza dos bytes).                      | Variável (pode apenas expandir ou precisar copiar o bloco inteiro). |
| Uso Típico         | Vetores/Estruturas onde todos os valores serão sobrescritos em seguida. | Vetores/Matrizes que precisam iniciar zerados (ex: contadores, acumulação). | Redimensionar vetores dinâmicos que encheram ou sobraram espaço.    |
| Retorno em Falha   | Retorna NULL.                                                           | Retorna NULL.                                                               | Retorna NULL (o ponteiro original continua válido no Heap).         |

## Exemplo Rápido de Assinatura

```c

// 10 inteiros com lixo de memória
int *v1 = (int *) malloc(10 * sizeof(int));

// 10 inteiros zerados (0, 0, 0...)
int *v2 = (int *) calloc(10, sizeof(int));

// Expande o vetor v1 para 20 inteiros
int *v1_novo = (int *) realloc(v1, 20 * sizeof(int));

```
