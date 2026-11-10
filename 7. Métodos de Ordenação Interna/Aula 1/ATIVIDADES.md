# Atividades

## Exercício 1: Rastreamento e Contagem de Operações

Considere o vetor de 5 elementos inteiros:

$$V = [\, 4, \; 1, \; 3, \; 2, \; 5 \,]$$

Suponha a execução de duas abordagens de ordenação em ordem crescente:

- Abordagem A: Bubble Sort com flag de parada antecipada (early exit).
- Abordagem B: Selection Sort padrão (que busca o índice do menor elemento e troca no final de cada iteração externa).

Sua Tarefa:

1. Determine o número exato de comparações de chaves e o número exato de trocas efetivas de elementos (onde $v[i] \neq v[j]$) realizadas pelo Bubble Sort. Mostre o estado do vetor ao final de cada passagem do laço externo.
2. Determine o número exato de comparações de chaves e o número de trocas efetivas realizadas pelo Selection Sort. Mostre o estado do vetor ao final de cada iteração externa.
3. Compare os dois resultados: qual algoritmo executou menos comparações neste caso específico? E qual executou menos trocas?

## Exercício 2: Prova Concreta de Instabilidade

Um algoritmo de ordenação é classificado como instável quando não garante a manutenção da ordem relativa original entre registros que possuem chaves de ordenação idênticas.

Considere a lista de registros de alunos com chaves de notas ($0$ a $10$) e índices originais de identificação:

$$L = [\, (8, \text{aluno}_A), \; (5, \text{aluno}_B), \; (8, \text{aluno}_C), \; (3, \text{aluno}_D) \,]$$

A ordenação deve ser feita de forma crescente pela Nota.

Sua Tarefa:

1. Execute o passo a passo do Selection Sort sobre essa lista, mostrando em qual iteração a ordem relativa entre $\text{aluno}_A$ e $\text{aluno}_C$ é violada.
2. Explique formalmente por que a troca por salto a longa distância do Selection Sort gera instabilidade, enquanto a troca estritamente adjacente do Bubble Sort (com operador >) preserva a estabilidade original.

## Exercício 3: Instrumentação e Diagnóstico de Eficiência

Em análise de algoritmos, instrumentar um código significa adicionar medidores para contabilizar operações em tempo de execução sem alterar a complexidade do algoritmo.

Sua Tarefa:

Implemente um programa em C contendo:

1. A função void selection_sort_instrumentado(int *v, int n, unsigned long *comp_out, unsigned long *trocas_out).
2. A função void bubble_sort_instrumentado(int *v, int n, unsigned long *comp_out, unsigned long *trocas_out).
3. Uma função main() que execute ambos os algoritmos sobre o pior caso de ordenação (um vetor em ordem estritamente decrescente de $n = 100$ elementos: 100, 99, 98, ..., 1) e imprima a tabela comparativa de comparações e trocas.
