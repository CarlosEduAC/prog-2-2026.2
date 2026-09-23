# A Corrente de Nós

## Objetivo

Praticar a criação de estruturas auto-referenciadas (struct No) e o uso de funções recursivas para percorrer elos de memória encadeados.

## Enunciado

Um grupo de sensores industriais está conectado em uma sequência simples, onde cada sensor guarda o seu valor lido e um ponteiro para o próximo sensor da corrente.

1. Defina a estrutura No contendo:

- int valor (a leitura do sensor)
- struct No *proximo (o ponteiro para o próximo nó)

2. Crie a função recursiva int somar_nos(const No *p):

- Caso Base: Se o ponteiro p for NULL, retorne 0.
- Passo Recursivo: Retorne o valor do nó atual somado ao resultado da chamada recursiva para p->proximo.

3. Na função main():

- Aloque dinamicamente 3 nós no Heap (n1, n2 e n3) com os valores 10, 20 e 30.
- Encadeie-os manualmente:
  - n1->proximo = n2;
  - n2->proximo = n3;
  - n3->proximo = NULL; (indica o fim da corrente)
- Chame a função somar_nos(n1) e exiba o resultado no terminal (deve imprimir 60).
- Libere a memória de todos os nós com free().
