# Listas Duplamente Encadeadas em C

Na lista simples, nós só conseguimos navegar para a frente. Se estivermos em um nó e precisarmos acessar o elemento anterior, ou se quisermos remover o último nó em O(1), somos obrigados a percorrer a lista inteira desde a cabeça!

## A Limitação da Lista Simples vs. O Duplo Encadeamento

- Lista simplesmente encadeada: Cada nó aponta apenas para o próximo. O último nó não aponta para nenhum outro, indicando o fim da estrutura. Esse modelo é eficiente em uso de memória, porém limitado em navegação, já que o percurso só pode ser feito em um sentido.

- Lista duplamente encadeada: Cada nó possui referência para o próximo e também para o anterior. Isso permite navegação bidirecional. A estrutura exige mais memória, porém oferece maior flexibilidade em operações como inserção e remoção em qualquer posição.

Representação visual:

```txt

1. LISTA SIMPLESMENTE ENCADEADA (Unidirecional)
     head ───> [ Dado: 10 | prox ] ───> [ Dado: 20 | prox ] ───> NULL

2. LISTA DUPLAMENTE ENCADEADA (Bidirecional)
     head                                                         tail
      │                                                            │
      ▼                                                            ▼
     NULL <─── [ ant | 10 | prox ] <───> [ ant | 20 | prox ] <───> [ ant | 30 | prox ] ───> NULL

```

### Vantagens e Desvantagens do Duplo Encadeamento

- Vantagens:

  - Navegação bidirecional (para frente e para trás).
  - Remoção de um nó apontado diretamente em tempo O(1) sem precisar encontrar o nó anterior.
  - Inserção e remoção no fim em O(1) mantendo o ponteiro tail.

- Desvantagens:
  - Maior consumo de memória por nó (um ponteiro extra por elemento: +8 bytes em sistemas 64-bit).
  - Maior complexidade de manipulação: cada inserção/remoção exige ajustar até 4 ponteiros.

## A Anatomia do Nó Duplo e os Ponteiros head e tail

Em uma lista duplamente encadeada, cada nó possui três componentes principais:

1. int dado: Armazena a informação ou carga útil do nó.
2. struct No *anterior: Ponteiro para o nó anterior na lista.
3. struct No *proximo: Ponteiro para o próximo nó na lista.

### O Nó Duplo (struct No)

Cada nó agora possui dois ponteiros auto-referenciados:

```c

typedef struct No {
    int dado;               // Carga útil do nó
    struct No *anterior;    // Ponteiro para o nó antecedente no Heap
    struct No *proximo;     // Ponteiro para o nó conseqüente no Heap
} No;

```

### A Estrutura da Lista com Cabeça e Cauda (struct Lista)

Para simplificar a assinatura das funções e evitar a digitação excessiva de ponteiros triplos, encapsulamos os ponteiros head (cabeça) e tail (cauda) em um tipo Lista:

```c

typedef struct {
    No *head; // Aponta para o primeiro elemento
    No *tail; // Aponta para o último elemento
    int qtd;  // Mantém o tamanho total da lista em O(1)
} Lista;

```

## Operações Bidirecionais em C

Implementação completa de uma Lista Duplamente Encadeada, com todas suas funções fundamentais, pode ser visualizada [aqui](main.c).

## Prática Guiada

Crie a função void inserir_apos(Lista *l, int chave, int novo_valor) que localize o nó que contém chave e insira o novo_valor imediatamente após ele.

Dica: Lembrem-se de ajustar 4 elos de ponteiros: novo->proximo, novo->anterior, atual->proximo e proximo_no->anterior (além de verificar se o nó chave era a própria tail).

## Comparativo Geral de Complexidade e Encarte

| Operação             | Vetor Dinâmico     | Lista Simples       | Lista Dupla (c/ Tail) |
|----------------------|--------------------|---------------------|-----------------------|
| Acesso por Índice    | $O(1)$             | $O(n)$              | $O(n)$                |
| Inserção no Início   | $O(n)$             | $O(1)$              | $O(1)$                |
| Inserção no Fim      | $O(1)$ amortizado  | $O(n)$ sem tail     | $O(1)$                |
| Remoção no Fim       | $O(1)$             | $O(n)$              | $O(1)$                |
| Memória por Elemento | Mínima (sizeof(T)) | $+1$ ponteiro (+8B) | $+2$ ponteiros (+16B) |
