#include <stdio.h>
#include <stdlib.h>

// 1. DATA Segment (Global inicializada)
int g_valor_inicializado = 100;

// 2. BSS Segment (Global NÃO inicializada -> garantida como 0)
int g_valor_zerado;

// 1. TEXT Segment (Código compilado da função)
void minha_funcao(int parametro) {
    // 4. STACK Segment (Variável local da função)
    int var_local_funcao = 20;
}

int main(void) {
    // 4. STACK Segment (Variável local da main)
    int a = 5;

    // 3. HEAP Segment (Alocação dinâmica)
    int *ptr_heap = (int*) malloc(sizeof(int));
    *ptr_heap = 50;

    minha_funcao(a);

    // Liberando a memória do Heap
    free(ptr_heap);

    return 0;
}