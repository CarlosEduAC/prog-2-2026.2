# Gabarito

## Solução do Exercício 1

1. Explicação da Falha:

O compilador compila cada arquivo .c de forma isolada. Por padrão em C, funções sem o modificador static têm ligação externa (external linkage) e são exportadas para a tabela de símbolos do arquivo objeto (.o). Como validar_posicao não tinha static, tanto defensor.o quanto inimigo.o exportaram o mesmo símbolo global. Quando o Linker (ld) tentou unir os objetos, encontrou duas definições com o mesmo nome e interrompeu a geração do executável.

2. Correção:

Adicionar a palavra-chave static antes da assinatura de cada função. Isso diz ao compilador para não exportar o símbolo para o Linker, tornando a função local e privada de seu próprio arquivo.

src/defensor.c:

```c

#include "defensor.h"

// Torna a função local ao arquivo defensor.c
static bool validar_posicao(float x, float y) {
    return (x >= 0 && x <= 800 && y >= 0 && y <= 600);
}

```

src/inimigo.c:

```c

#include "inimigo.h"

// Torna a função local ao arquivo inimigo.c
static bool validar_posicao(float x, float y) {
    return (x >= -50 && x <= 850 && y >= -50 && y <= 650);
}

```

## Solução do Exercício 2

src/tiro.c (Implementação com Funções Auxiliares Estáticas)

```c

#include "tiro.h"
#include <stdlib.h>

// Estruturas concretas ocultas do cliente
typedef struct NoTiro {
    float x, y;
    float vel_y;
    struct NoTiro *anterior;
    struct NoTiro *proximo;
} NoTiro;

struct GerenciadorTiros {
    NoTiro *head;
    NoTiro *tail;
    int qtd;
};

// -----------------------------------------------------------------------------
// FUNÇÕES AUXILIARES PRIVADAS (STATIC) - Invisíveis fora deste arquivo
// -----------------------------------------------------------------------------
static NoTiro* alocar_no_tiro(float x, float y, float vel_y) {
    NoTiro *novo = (NoTiro *) malloc(sizeof(NoTiro));
    if (novo == NULL) return NULL; // Teste defensivo de alocação

    novo->x = x;
    novo->y = y;
    novo->vel_y = vel_y;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

static void remover_no_tiro(GerenciadorTiros *gt, NoTiro *no) {
    if (gt == NULL || no == NULL) return;

    if (no->anterior) no->anterior->proximo = no->proximo;
    else gt->head = no->proximo;

    if (no->proximo) no->proximo->anterior = no->anterior;
    else gt->tail = no->anterior;

    free(no);
    gt->qtd--;
}

// -----------------------------------------------------------------------------
// FUNÇÃO PÚBLICA EXPOSTA NO CABEÇALHO (tiro.h)
// -----------------------------------------------------------------------------
void tiros_adicionar(GerenciadorTiros *gt, float x, float y, float vel_y) {
    if (gt == NULL) return;

    // Usa a função estática privada de alocação
    NoTiro *novo = alocar_no_tiro(x, y, vel_y);
    if (novo == NULL) return;

    // Insere no fim da Lista Duplamente Encadeada
    if (gt->tail == NULL) {
        gt->head = novo;
        gt->tail = novo;
    } else {
        novo->anterior = gt->tail;
        gt->tail->proximo = novo;
        gt->tail = novo;
    }
    gt->qtd++;
}

```

## Solução do Exercício 3

src/logger.c

```c

#include <stdio.h>

// VARIÁVEL ESTÁTICA NO NÍVEL DE ARQUIVO:
// Ela reside na memória global do programa, mas o Linker esconde seu nome.
// Nenhum outro arquivo .c consegue acessá-la via extern int contador_logs!
static int contador_logs = 0;

void logger_registrar(const char *mensagem) {
    if (mensagem == NULL) return;

    contador_logs++;
    printf("[LOG #%d] %s\n", contador_logs, mensagem);
}

int logger_get_total(void) {
    return contador_logs; // Leitura pública controlada
}

```
