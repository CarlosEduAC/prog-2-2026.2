# Introdução à Recursividade em C

## O Pensamento Recursivo

### A Analogia das Matrioscas (Bonecas Russas)

[Foto Bonecas Russas](./bonecas-russas.jpg)

"Para encontrar a menor boneca de todas, você abre a primeira. Dentro dela, há uma boneca menor. Você repete a mesma ação (abrir a boneca) até encontrar uma boneca sólida que não se abre mais. Esse ponto de parada é onde o processo termina."

### A Definição em Computação

Uma função é dita recursiva quando ela faz uma chamada a si mesma dentro do seu próprio bloco de código para resolver uma subinstância menor do problema original.

## Anatomia de uma Função Recursiva

Toda função recursiva precisa obrigatoriamente de duas partes essenciais:

1. Caso Base (Condição de Parada): O estado simples o suficiente em que a resposta é conhecida diretamente sem precisar de novas chamadas recursivas. Sem o caso base, o programa entra em um loop infinito.
2. Passo Recursivo (Redução do Problema): A chamada da própria função, mas passando um parâmetro modificado que aproxime o problema do Caso Base.

```c

// ESTRUTURA DE UMA FUNÇÃO RECURSIVA

  int funcao_recursiva(int n) {
      // 1. CASO BASE (Parada)
      if (n == 0) {
          return valor_conhecido;
      }

      // 2. PASSO RECURSIVO (Aproximação do Caso Base)
      return processar(n) + funcao_recursiva(n - 1);
  }

```

## O que Acontece na Memória RAM?

Clássico exemplo do Fatorial de n (n!), a "pilha de pratos" será montada e desmontada na Stack.

Exemplo: fatorial(3)

```c

int fatorial(int n) {
    // Caso Base
    if (n == 0 || n == 1) {
        return 1;
    }
    // Passo Recursivo
    return n * fatorial(n - 1);
}

```

O Comportamento da Stack na Memória:

```txt

FASE 1: Empilhamento (Indo até o Caso Base)
  ┌─────────────────────────────────────────┐
  │ fatorial(1) ──> Retorna 1 (Caso Base!)  │
  ├─────────────────────────────────────────┤
  │ fatorial(2) ──> Aguarda fatorial(1)     │
  ├─────────────────────────────────────────┤
  │ fatorial(3) ──> Aguarda fatorial(2)     │  <-- Entrada inicial
  └─────────────────────────────────────────┘

  FASE 2: Desempilhamento (Desdobramento do Retorno)
  1. fatorial(1) retorna 1
  2. fatorial(2) calcula: 2 * 1 = 2 e retorna 2
  3. fatorial(3) calcula: 3 * 2 = 6 e retorna 6

```

## Comparativo Prático em C — Iterativo vs. Recursivo

### A diferença entre o loop for e a estrutura recursiva

Exemplo 1: Contagem Regressiva

```c

#include <stdio.h>

// Versão Iterativa (for)
void contagem_iterativa(int n) {
    for (int i = n; i >= 0; i--) {
        printf("%d ", i);
    }
    printf("\n");
}

// Versão Recursiva
void contagem_recursiva(int n) {
    // 1. Caso Base
    if (n < 0) {
        printf("\n");
        return;
    }

    // 2. Ação + Passo Recursivo
    printf("%d ", n);
    contagem_recursiva(n - 1); // Aproxima-se do limite negativo
}

int main(void) {
    printf("Iterativo: ");
    contagem_iterativa(5);

    printf("Recursivo: ");
    contagem_recursiva(5);

    return 0;
}

```

## O Perigo do Stack Overflow & Encarte

As desvantagens da recursividade não controlada:

1. Estouro de Pilha (Stack Overflow): Se o Caso Base for esquecido ou nunca for atingido, a Stack estoura o limite de memória reservado pelo SO (~2MB a 8MB) e gera um Segmentation Fault.
2. Custo de Desempenho: Cada chamada de função adiciona um novo Stack Frame na memória (parâmetros, endereço de retorno e variáveis locais), o que consome mais recursos do que um simples loop iterativo.

Exemplo:

```c

#include <stdio.h>

void contagem_infinita(int n) {
    printf("Chamada com n = %d\n", n);

    // ERRO: Não existe 'if' para verificar se n chegou a 0 (Falta do Caso Base)!
    // A função continuará chamando a si mesma com valores negativos para sempre.
    contagem_infinita(n - 1);
}

int main(void) {
    printf("Iniciando recursão sem parada...\n");
    contagem_infinita(10);
    return 0;
}

```

### O que acontece ao executar este programa?

O programa imprimirá na tela valores decrescentes de n (10, 9, 8, ...) e, em questão de milissegundos, a execução será interrompida abruptamente pelo sistema operacional com a mensagem:

```txt

Iniciando recursão sem parada...
Chamada com n = 10
Chamada com n = 9
...
Chamada com n = -261820
Segmentation fault (core dumped)

```

### A Mecânica da Memória Stack durante o Estouro

Cada chamada de função precisa armazenar na memória Stack os parâmetros passados, o endereço de retorno e as variáveis locais.

```txt

        ESTOURO DA PILHA (STACK OVERFLOW)
  ┌─────────────────────────────────┐
  │ contagem_infinita(n = -261820)  │  <-- Tentativa de novo empilhamento
  ├─────────────────────────────────┤
  │ ...                             │
  ├─────────────────────────────────┤
  │ contagem_infinita(n = 8)        │
  ├─────────────────────────────────┤
  │ contagem_infinita(n = 9)        │
  ├─────────────────────────────────┤
  │ contagem_infinita(n = 10)       │
  └─────────────────────────────────┘
  [ LIMITE DA STACK (ex: 8MB) ATINGIDO ] ──> SEGMENTATION FAULT

```

### Correção do Código

Insira o Caso Base para garantir que a pilha comece a desempilhar ao atingir a condição de parada:

```c

void contagem_correta(int n) {
    // 1. CASO BASE (Condição de Parada)
    if (n < 0) {
        printf("Fim da contagem!\n");
        return; // Interrompe as chamadas e inicia o desempilhamento
    }

    printf("n = %d\n", n);

    // 2. PASSO RECURSIVO
    contagem_correta(n - 1);
}

```
