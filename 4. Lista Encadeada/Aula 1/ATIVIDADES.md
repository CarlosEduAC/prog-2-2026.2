# Atividades

## Exercício 1: Inserção Ordenada

Implemente a função void inserir_ordenado(No **head, int valor) para inserir elementos mantendo a lista sempre em ordem crescente.

- Comportamento: A função deve localizar a posição correta na sequência e ajustar os elos sem a necessidade de reordenar a lista posteriormente.
- Casos de Borda: Inserção em lista vazia, inserção no início (novo menor elemento) e inserção no fim (novo maior elemento).

## Exercício 2: Inversão da Lista In-Place

Crie a função void inverter_lista(No **head) que inverta a orientação de todos os elos da lista encadeada sem criar novos nós no Heap e sem alocar memória adicional (O(1) de espaço).

- Exemplo: Head -> [10] -> [20] -> [30] -> NULL vira Head -> [30] -> [20] -> [10] -> NULL.
- Dica: Utilize três ponteiros auxiliares (anterior, atual e proximo) para realizar as trocas de apontamento durante o percurso.

## Exercício 3: Fusão de Duas Listas Ordenadas

Escreva a função No *fundir_listas(No* l1, No *l2) que receba duas listas simplesmente encadeadas previamente ordenadas e retorne uma nova lista unificada, mantendo todos os elementos em ordem crescente.

- Regra: Não crie novos nós no Heap; apenas reaproveite e reencadeie os nós existentes das listas originais l1 e l2.
- Retorno: Retorna o ponteiro para a cabeça da nova lista intercalada.
