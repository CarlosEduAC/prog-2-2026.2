# Atividades

## Exercício 1: Inversão de String usando Pilha

Implemente a função `void inverter_string(char *str)` que utilize uma Pilha Dinâmica de char para inverter uma string recebida como parâmetro.

Comportamento: A função deve empilhar (push) cada caractere da string original sequencialmente e, em seguida, desempilhar (pop) sobrescrevendo a string original até a pilha esvaziar.

Regra: Não utilize laços de repetição sobre a string na fase de inversão sem usar a pilha. A inversão deve ser feita obrigatoriamente pela propriedade LIFO da pilha.

## Exercício 2: Inverter os $K$ Primeiros Elementos de uma Fila

Crie a função `void inverter_k_primeiros(Fila *f, int k)` que receba uma Fila Dinâmica de inteiros e inverta a ordem apenas dos seus $k$ primeiros elementos, mantendo a ordem relativa dos elementos restantes.

Exemplo: Fila original [10, 20, 30, 40, 50] com k = 3 -> Fila resultante [30, 20, 10, 40, 50].

Dica de Estrutura: Utilize uma Pilha Dinâmica Auxiliar para realizar a inversão do bloco de $k$ elementos, combinando o comportamento FIFO e LIFO.

## Exercício 3: Simulação de Buffer de Atendimento (Fila Dupla de Prioridade)

Escreva uma função `void intercalar_filas(Fila *f_prioritaria, Fila *f_comum, Fila *f_destino)` que receba duas filas dinâmicas de inteiros (uma prioritária e uma comum) e monte uma fila final de atendimento (f_destino).

Regra de Negócio: A fila de destino deve ser montada atendendo a proporção de 2 elementos prioritários para cada 1 elemento comum (2:1).

Se a fila prioritária esvaziar antes, descarregue os elementos restantes da comum na fila de destino (e vice-versa).

As filas originais devem ser esvaziadas (dequeue) à medida que a fila de destino é alimentada (enqueue).
