#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ----------------------------------------------------------------------------
// ESTRUTURAS DE SUPORTE
// ----------------------------------------------------------------------------

// Nó Genérico de Inteiros
typedef struct No {
    int dado;
    struct No *proximo;
} No;

// Pilha Dinâmica de Inteiros
typedef struct {
    No *topo;
    int qtd;
} Pilha;

Pilha* criar_pilha(void) {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    if (p == NULL) exit(1);
    p->topo = NULL;
    p->qtd = 0;
    return p;
}

void push(Pilha *p, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->dado = valor;
    novo->proximo = p->topo;
    p->topo = novo;
    p->qtd++;
}

bool pop(Pilha *p, int *valor_out) {
    if (p->topo == NULL) return false;
    No *temp = p->topo;
    *valor_out = temp->dado;
    p->topo = p->topo->proximo;
    free(temp);
    p->qtd--;
    return true;
}

void liberar_pilha(Pilha *p) {
    int dummy;
    while (pop(p, &dummy));
    free(p);
}

// Fila Dinâmica de Inteiros
typedef struct {
    No *inicio;
    No *fim;
    int qtd;
} Fila;

Fila* criar_fila(void) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    if (f == NULL) exit(1);
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;
    return f;
}

void enqueue(Fila *f, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->dado = valor;
    novo->proximo = NULL;
    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->qtd++;
}

bool dequeue(Fila *f, int *valor_out) {
    if (f->inicio == NULL) return false;
    No *temp = f->inicio;
    *valor_out = temp->dado;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(temp);
    f->qtd--;
    return true;
}

void imprimir_fila(const Fila *f) {
    const No *atual = f->inicio;
    printf("Inicio -> ");
    while (atual != NULL) {
        printf("[%d] ", atual->dado);
        atual = atual->proximo;
    }
    printf("<- Fim\n");
}

void liberar_fila(Fila *f) {
    int dummy;
    while (dequeue(f, &dummy));
    free(f);
}

// Exercicio 1: Inversão de String com Pilha

void inverter_string(char *str) {
    if (str == NULL) return;

    int tam = strlen(str);
    Pilha *p = criar_pilha();

    // 1. Passo LIFO: Empilha todos os caracteres da string
    for (int i = 0; i < tam; i++) {
        push(p, (int)str[i]);
    }

    // 2. Desempilha os caracteres sobrescrevendo a string original
    for (int i = 0; i < tam; i++) {
        int char_code;
        pop(p, &char_code);
        str[i] = (char)char_code;
    }

    liberar_pilha(p);
}

// Exercicio 2: Inverter $K$ Primeiros Elementos da Fila

void inverter_k_primeiros(Fila *f, int k) {
    // Validação de segurança dos limites de k e da fila
    if (f == NULL || k <= 0 || k > f->qtd) return;

    Pilha *p_aux = criar_pilha();

    // 1. Retira os k primeiros da fila e empilha na pilha auxiliar
    for (int i = 0; i < k; i++) {
        int val;
        dequeue(f, &val);
        push(p_aux, val);
    }

    // 2. Desempilha da pilha auxiliar e recoloca de volta na fila
    // (a propriedade LIFO da pilha garante que o bloco virá invertido)
    while (p_aux->qtd > 0) {
        int val;
        pop(p_aux, &val);
        enqueue(f, val);
    }

    // 3. Move os (tamanho - k) elementos restantes do início para o fim da fila
    // garantindo que fiquem após os k elementos recém-invertidos
    int restantes = f->qtd - k;
    for (int i = 0; i < restantes; i++) {
        int val;
        dequeue(f, &val);
        enqueue(f, val);
    }

    liberar_pilha(p_aux);
}

// Exercicio 3: Intercalar Filas com Prioridade ($2:1$)

void intercalar_filas(Fila *f_prioritaria, Fila *f_comum, Fila *f_destino) {
    if (f_prioritaria == NULL || f_comum == NULL || f_destino == NULL) return;

    int val;

    // Enquanto houver elementos em pelo menos uma das filas
    while (f_prioritaria->qtd > 0 || f_comum->qtd > 0) {

        // Atende até 2 elementos prioritários
        for (int i = 0; i < 2; i++) {
            if (dequeue(f_prioritaria, &val)) {
                enqueue(f_destino, val);
            }
        }

        // Atende 1 elemento comum
        if (dequeue(f_comum, &val)) {
            enqueue(f_destino, val);
        }
    }
}

int main(void) {
    // Teste Ex 1: Inversão de String
    printf("=== TESTE EX 1: INVERSÃO DE STRING ===\n");
    char texto[] = "ESTRUTURAS DE DADOS";
    printf("Original : %s\n", texto);
    inverter_string(texto);
    printf("Invertida: %s\n\n", texto);

    // Teste Ex 2: Inverter K primeiros elementos da Fila
    printf("=== TESTE EX 2: INVERTER K PRIMEIRA POSIÇÕES ===\n");
    Fila *f1 = criar_fila();
    enqueue(f1, 10); enqueue(f1, 20); enqueue(f1, 30);
    enqueue(f1, 40); enqueue(f1, 50);

    printf("Fila Original: ");
    imprimir_fila(f1); // 10 20 30 40 50

    printf("Invertendo os K=3 primeiros:\n");
    inverter_k_primeiros(f1, 3);
    printf("Fila Resultante: ");
    imprimir_fila(f1); // Esperado: 30 20 10 40 50
    printf("\n");

    // Teste Ex 3: Intercala Prioritária e Comum (Proporção 2:1)
    printf("=== TESTE EX 3: INTERCALAR FILAS (2:1) ===\n");
    Fila *prio = criar_fila();
    Fila *comum = criar_fila();
    Fila *atendimento = criar_fila();

    // Prioritários: 101, 102, 103, 104
    enqueue(prio, 101); enqueue(prio, 102); enqueue(prio, 103); enqueue(prio, 104);
    // Comuns: 1, 2
    enqueue(comum, 1); enqueue(comum, 2);

    intercalar_filas(prio, comum, atendimento);

    printf("Fila Final Atendimento: ");
    imprimir_fila(atendimento);
    // Esperado: 101 102 1 (2 prio, 1 comum) -> 103 104 2 (2 prio, 1 comum)

    liberar_fila(f1);
    liberar_fila(prio);
    liberar_fila(comum);
    liberar_fila(atendimento);

    return 0;
}