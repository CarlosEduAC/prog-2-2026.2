# Atividades

## Exercício 1: Soma dos Primeiros N Números Naturais

Implemente uma função recursiva int somatorio(int n) que receba um número inteiro positivo $n$ e retorne a soma de todos os números inteiros de 1 até n.

- Exemplo: somatorio(5) => 5 + 4 + 3 + 2 + 1 = 15.
- Regra: Não utilize laços de repetição (for, while ou do-while).

## Exercício 2: Impressão Inversa de String

Crie uma função recursiva void imprimir_reverso(const char *str) que receba uma string (ponteiro para char) e a imprima de trás para frente no terminal.

- Exemplo: imprimir_reverso("ALGORITMO") => Imprime OMTIROGLA.
- Dica: O Caso Base deve identificar o caractere nulo de terminação ('\0'). O caractere atual só deve ser impresso após o retorno da chamada recursiva do próximo caractere.

## Exercício 3: Busca Binária Recursiva em Vetor

Implemente a versão recursiva do algoritmo de Busca Binária com a seguinte assinatura:

```c

int busca_binaria_recursiva(const int *vetor, int inicio, int fim, int chave);

```

A função deve buscar a chave dentro de um vetor previamente ordenado.

- Se a chave for encontrada, retorne o índice onde ela está no vetor.
- Se não for encontrada, retorne -1.
- Lógica: Calcule o elemento do meio. Se chave == vetor[meio], retorna o meio (Caso Base de sucesso). Se inicio > fim, o elemento não existe (Caso Base de falha). Caso contrário, faça a chamada recursiva restringindo a busca apenas para a metade esquerda ou direita.
