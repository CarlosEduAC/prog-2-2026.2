O mecanismo de rollback é essencial quando uma função/construtor realiza duas ou mais alocações dinâmicas interdependentes. Se a $N$-ésima alocação falhar (retornar NULL por falta de memória RAM), o programa deve desalocar em ordem inversa todas as alocações anteriores $1 \dots N-1$ antes de retornar NULL. Sem o rollback, as alocações anteriores ficariam órfãs no Heap, gerando memory leaks irreversíveis.

Construtor Seguro do TAD FilaInimigos:

```c

FilaInimigos* fila_inimigos_criar(void) {
    FilaInimigos *f = (FilaInimigos *) malloc(sizeof(FilaInimigos));

    // Tratamento defensivo de falha de alocação no Heap
    if (f == NULL) {
        return NULL; // Falha segura
    }

    // Inicialização que garante a invariante de fila vazia
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;

    return f;
}

```
