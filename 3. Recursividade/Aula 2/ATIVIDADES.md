# Atividades

## Exercício 1: Contagem de Elementos Pares

Crie uma função recursiva int contar_pares(const int *v, int tam) que receba um vetor de inteiros e o seu tamanho tam, retornando a quantidade total de números pares presentes no vetor.

- Exemplo: Para o vetor {3, 8, 12, 5, 10}, a função deve retornar 3.
- Regra: Não utilize laços de repetição (for, while ou do-while).

## Exercício 2: Verificação de Vetor Ordenado

Escreva uma função recursiva bool esta_ordenado(const int *v, int tam) que verifique se um vetor de inteiros está classificado em ordem crescente (não decrescente).

- Retorno: Deve retornar true se o vetor estiver ordenado ou false caso contrário.- Exemplo: {2, 5, 8, 12} => true | {2, 10, 5, 12} => false.
- Dica: O caso base ocorre quando o tamanho do subvetor for menor ou igual a 1 (um vetor de 0 ou 1 elemento é trivialmente ordenado).

## Exercício 3: Palíndromo Numérico em Vetor

Um vetor é um palíndromo se a sequência de seus elementos for idêntica quando lida da esquerda para a direita ou da direita para a esquerda. Crie uma função recursiva:

```c

bool eh_palindromo_vetor(const int *v, int inicio, int fim);

```

- Retorno: Retorna true se o vetor for um palíndromo e false caso contrário.
- Exemplo: {1, 4, 9, 4, 1} => true | {1, 4, 9, 8, 1} => false.
- Regra: A função deve operar ajustando os índices de extremidade (inicio e fim).
