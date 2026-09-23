# Atividades

## Exercício 1: Troca do Primeiro com o Último Nó

Crie a função void trocar_primeiro_ultimo(Lista *l) que troque as posições do primeiro nó (head) e do último nó (tail) de uma lista duplamente encadeada.

Regra: Não altere/copie o campo dado dos nós; faça a troca reajustando exclusivamente os ponteiros (proximo e anterior) e atualizando os ponteiros head e tail da estrutura Lista.

Tratamento de Bordas: A função deve funcionar perfeitamente para listas vazias, com 1 elemento, com 2 elementos ou com $N$ elementos.

## Exercício 2: Busca Bidirecional (Otimização)

Implemente a função No* buscar_otimizado(const Lista *l, int valor, int posicao_estimada) que busque um valor na lista de forma otimizada.

Comportamento: Se a posicao_estimada for menor que a metade do tamanho da lista (l->qtd / 2), a busca deve iniciar no head caminhando para a direita (proximo). Caso contrário, deve iniciar no tail caminhando para a esquerda (anterior).

Retorno: Retorna o ponteiro para o No encontrado ou NULL se não existir.

## Exercício 3: Filtrar e Remover Todos os Pares

Escreva a função int remover_pares(Lista *l) que percorra a lista duplamente encadeada e remova todos os nós que contêm números pares, liberando a memória do Heap corretamente.

Retorno: Retorna a quantidade total de nós que foram removidos.

Cuidado: Garanta que a conexão entre os nós vizinhos (anterior e próximo ao nó removido) seja preservada e que os ponteiros head, tail e a qtd da lista permaneçam consistentes.
