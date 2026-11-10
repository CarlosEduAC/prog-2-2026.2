# Fundamentos da Ordenação Interna e Métodos Quadráticos ($O(n^2)$)

## Fundamentos da Ordenação em Memória

A ordenação em memória (ou ordenação interna) é o processo de organizar um conjunto de dados diretamente na memória principal (RAM) do computador, em ordem crescente ou decrescente, para agilizar buscas e manipulações.

### 1. Definição Formal do Problema

Dada uma sequência de $n$ registros:

$$S = \langle r_1, r_2, r_3, \dots, r_n \rangle$$

onde cada registro possui uma chave de comparação $k_i \in K$ dotada de uma relação de ordem total ($\le$), o objetivo é produzir uma permutação $S' = \langle r'_1, r'_2, \dots, r'_n \rangle$ tal que:

$$k'_1 \le k'_2 \le \dots \le k'_n$$

### 2. Ordenação Interna vs. Ordenação Externa

• Interna: Ocorre inteiramente na memória RAM, sendo muito mais rápida porque todos os dados cabem nela.
• Externa: Utilizada quando o volume de dados é maior que a memória disponível, exigindo o uso de armazenamento secundário (como SSDs ou HDs) em blocos.

### 3. Outros

Estabilidade: Um algoritmo é estável se ele mantém a ordem relativa original de elementos que possuem chaves iguais (por exemplo, Insertion Sort e Mergesort).

Complexidade: Mede a eficiência do algoritmo em relação ao tempo de execução e ao uso de memória conforme o tamanho da entrada (n) aumenta.

## Principais Algoritmos em Memória

### 1. Métodos Simples (O(n²))

Ideais para pequenos volumes de dados ou implementação básica:

• Bubble Sort: Compara elementos adjacentes e os troca de lugar repetidamente até que a lista esteja ordenada.
• Selection Sort: Seleciona o menor (ou maior) elemento e o coloca na primeira posição, repetindo para o restante.
• Insertion Sort: Percorre a lista inserindo cada elemento na sua posição correta em relação aos já ordenados.

### 2. Métodos Eficientes (\(O(n \log n)\))

Ideais para grandes volumes de dados:

• Quick Sort: Utiliza a técnica de "divisão e conquista" escolhendo um pivô para particionar a lista.
• Mergesort: Divide recursivamente a lista pela metade até restar elementos unitários e depois os mescla de forma ordenada.
• Heapsort: Utiliza uma estrutura de dados do tipo Heap (árvore binária) para extrair os maiores ou menores elementos.

## Métricas de Avaliação e Estabilidade

Os algoritmos de ordenação são classificados e avaliados antes de codificar.

### 1. Complexidade de Tempo e Espaço

Avalia-se o algoritmo sob três cenários:

- Melhor Caso: A entrada já está idealmente ordenada.
- Caso Médio: Permutação aleatória de chaves.
- Pior Caso: A entrada está na ordem inversa ou desfavorável ao particionamento.
- Espaço Auxiliar: Algoritmos In-Place (no próprio vetor) usam $O(1)$ de memória extra além do vetor de entrada.

### 2. A Propriedade de Estabilidade (Stability)

Um algoritmo de ordenação é dito estável se ele preserva a ordem relativa original de registros que possuem chaves idênticas.

```txt

Entrada original (ordenada por nome):
[1] (Nota: 8.5, Nome: "Ana")
[2] (Nota: 8.5, Nome: "Bruno")

Após ordenar por Nota decrescente:
- Algoritmo ESTÁVEL:   "Ana" continua antes de "Bruno".
- Algoritmo INSTÁVEL:  "Bruno" pode ultrapassar "Ana" sem critério.

```

Por que isso importa na prática? Se você ordenar uma tabela de tarefas por "Data" e depois por "Prioridade", um algoritmo estável garante que as tarefas de mesma prioridade continuem ordenadas por data.

## Bubble Sort (Ordenação por Flutuação)

O princípio do Bubble Sort é fazer elementos maiores "flutuarem" para o fim do vetor através de trocas de pares vizinhos adjacentes.

```txt

Vetor inicial: [ 5,  1,  4,  2 ]
Passo 1:      (5 > 1) -> Troca -> [ 1,  5,  4,  2 ]
Passo 2:      (5 > 4) -> Troca -> [ 1,  4,  5,  2 ]
Passo 3:      (5 > 2) -> Troca -> [ 1,  4,  2, (5) ] -> O maior (5) está na posição correta!

```

### Otimização Vital: A Flag de Parada Antecipada

Se o vetor for percorrido por inteiro sem que ocorra nenhuma troca, isso prova formalmente que todos os elementos adjacentes satisfazem $v[j] \le v[j+1]$. Portanto, o vetor já está ordenado e o laço pode ser abortado imediatamente (early exit).

Implementação em C:

```c

#include <stdbool.h>

void bubble_sort(int *vetor, int n) {
    if (vetor == NULL || n <= 1) return;

    for (int i = 0; i < n - 1; i++) {
        bool houve_troca = false;

        // A cada passo 'i', os últimos 'i' elementos já estão no lugar definitivo
        for (int j = 0; j < n - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // Troca adjacente
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                houve_troca = true;
            }
        }

        // Se nenhuma troca ocorreu nesta passagem, o vetor já está ordenado
        if (!houve_troca) {
            break;
        }
    }
}

```

Análise Assintótica do Bubble Sort:

Comparações:

- Pior caso: $\sum_{i=1}^{n-1} (n - i) = \frac{n(n - 1)}{2} \implies O(n^2)$
- Melhor caso (com flag): $n - 1 \implies O(n)$

Trocas:

- Pior caso: $O(n^2)$
- Melhor caso: $0$ trocas $\implies O(1)$

Estabilidade: Estável (usa >, logo não troca elementos com chaves iguais).

Espaço: $O(1)$ (In-place).

## Selection Sort (Ordenação por Seleção)

O Selection Sort divide conceitualmente o vetor em duas partes: o subvetor já ordenado (à esquerda) e o subvetor desordenado (à direita). A cada iteração, ele encontra o menor elemento da porção desordenada e o coloca na primeira posição livre.

```txt

Vetor: [ 29,  10,  14,  37,  13 ]
Iteração 0: Menor valor entre índices 0..4 é 10 (índice 1). Troca com índice 0:
            [(10),  29,  14,  37,  13 ]
Iteração 1: Menor valor entre índices 1..4 é 13 (índice 4). Troca com índice 1:
            [(10,  13),  14,  37,  29 ]
Iteração 2: Menor valor entre índices 2..4 é 14 (índice 2). Troca consigo mesmo:
            [(10,  13,  14),  37,  29 ]
Iteração 3: Menor valor entre índices 3..4 é 29 (índice 4). Troca com índice 3:
            [(10,  13,  14,  29),  37 ]

```

Implementação em C:

```c

void selection_sort(int *vetor, int n) {
    if (vetor == NULL || n <= 1) return;

    for (int i = 0; i < n - 1; i++) {
        int indice_menor = i;

        // Procura o índice do menor elemento restante
        for (int j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[indice_menor]) {
                indice_menor = j;
            }
        }

        // Executa a troca apenas se o menor não for o próprio elemento atual
        if (indice_menor != i) {
            int temp = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = temp;
        }
    }
}

```

Análise Assintótica do Selection Sort:

- Comparações: Sempre $\frac{n(n - 1)}{2} \implies \Theta(n^2)$ em todos os casos (melhor, médio e pior), pois ele não consegue inferir se o vetor já estava ordenado sem varrer todo o restante.
- Trocas: No máximo $n - 1$ trocas no total $\implies \mathbf{O(n)}$!
- Estabilidade: Instável por padrão (trocas a longa distância podem alterar a ordem relativa de elementos iguais; ex: em [2a, 2b, 1], o 2a troca com 1 e vai para depois do 2b).
- Espaço: $O(1)$ (In-place).

## Comparativo Prático

Quadro sinóptico de comparação e uma conexão direta com o uso prático:

| Característica       | Bubble Sort (Otimizado)                         | Selection Sort                                                                                       |
|----------------------|-------------------------------------------------|------------------------------------------------------------------------------------------------------|
| Melhor Caso (Tempo)  | $\mathbf{O(n)}$ (Vetor já ordenado)             | $O(n^2)$                                                                                             |
| Pior Caso (Tempo)    | $O(n^2)$                                        | $O(n^2)$                                                                                             |
| Número de Trocas     | Alto: até $O(n^2)$                              | Mínimo: no máximo $n - 1$ trocas ($O(n)$)                                                            |
| Estabilidade         | Estável                                         | Instável                                                                                             |
| Vantagem de Uso Real | Detecta que o vetor já está ordenado em $O(n)$. | Ideal quando a escrita na memória/disco é uma operação fisicamente cara (ex: memórias Flash/EEPROM). |
