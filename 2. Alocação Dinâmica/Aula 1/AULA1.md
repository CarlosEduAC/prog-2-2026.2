# Alocação Dinâmica

Modelo mental que separa o ciclo de vida das variáveis estáticas da memória dinâmica.

```txt

        ESTRUTURA DA MEMÓRIA RAM DO PROCESSO (C)

  ENDEREÇOS ALTOS
 ┌────────────────────────────────────────────────────────┐
 │ STACK (Pilha)                                          │
 │  • Gerenciada automaticamente pelo sistema             │
 │  • Tamanho fixo e pequeno (~2MB a 8MB)                 │
 │  • Variaveis locais, parâmetros e frames de funções    │
 │  • Desalocada automaticamente no final do escopo       │
 │                     │                                  │
 │                     ▼ (Cresce para baixo)              │
 ├────────────────────────────────────────────────────────┤
 │                     ▲ (Cresce para cima)               │
 │                     │                                  │
 │ HEAP (Monte / Loteamento)                              │
 │  • Gerenciado MANUALMENTE pelo programador             │
 │  • Espaço gigante (Limitado apenas pela RAM física)    │
 │  • Dados persistem até você chamar free()              │
 │  • Acesse EXCLUSIVAMENTE via PONTEIROS                 │
 └────────────────────────────────────────────────────────┘
  ENDEREÇOS BAIXOS

  ````

Principais Diferenças para o Quadro:

```txt

+----------------+------------------------------------+----------------------+
| Característica | Memória Stack (Pilha)              | Memória Heap (Monte) |
+----------------+------------------------------------+----------------------+
| Quem gerencia? | O Compilador / Sistema Operacional | O Programador (Você) |
+----------------+------------------------------------+----------------------+
| Alocação       | Automática (ao declarar variável)  | Manual (via malloc)  |
+----------------+------------------------------------+----------------------+
| Desalocação    | Automática (ao sair da função)     | Manual (via free)    |
+----------------+------------------------------------+----------------------+
| Tamanho        | Rígido e Limitado                  | Flexível e Abundante |
+----------------+------------------------------------+----------------------+
| Acesso         | Nome da variável ou ponteiro       | Apenas via Ponteiros |
+----------------+------------------------------------+----------------------+

```

## As Ferramentas da <stdlib.h>

Funções essenciais da biblioteca padrão:

1. sizeof: O Medidor de Bytes

Antes de pedir memória ao sistema, precisamos saber quantos bytes um tipo ocupa.

```c

size_t tam_int = sizeof(int);       // 4 bytes na maioria dos sistemas
size_t tam_prod = sizeof(Produto); // ~52 bytes (com padding)

```

2. malloc() (Memory Allocation)

Pede ao Sistema Operacional um bloco contíguo de bytes no Heap.

```c

// Solicita espaço no Heap para guardar 1 inteiro (4 bytes)
int *p = (int *) malloc(sizeof(int));

```

- Retorno: Retorna o endereço inicial (void*) do bloco no Heap se houver memória disponível. Retorna NULL se a RAM do computador estiver cheia.

3. free() (Liberação de Memória)

Devolve o bloco de memória do Heap de volta ao Sistema Operacional.

```c

free(p);   // Libera o bloco apontado por p
p = NULL;  // Boa prática: anula o ponteiro pendente

```

## Os 3 Mandamentos da Segurança em Alocação Dinâmica

Erros graves de segurança e estabilidade ao manipular o Heap.

- *Mandamento 1:* "Sempre verificar se o retorno é NULL"

Nunca assuma que a memória foi concedida.

```c

int *p = (int *) malloc(100 * sizeof(int));
if (p == NULL) {
    printf("Erro: Memoria insuficiente na RAM!\n");
    exit(1); // Encerra o programa com segurança
}

```

- *Mandamento 2:* "Para todo malloc(), deve existir um free()"

Se você alocar memória e perder a referência do ponteiro sem chamar free(), ocorre o Vazamento de Memória (Memory Leak).

```c

//[ Memory Leak em Laços ]
for (int i = 0; i < 1000000; i++) {
    int *p = malloc(1000); // 1000 bytes alocados a cada ciclo
    // Sem free(p)! O programa devora a RAM do computador até travar.
}

```

- *Mandamento 3:* "Nunca use memória após o free() (Use-After-Free)"

Após desalocar, atribua NULL ao ponteiro para evitar que ele continue apontando para um endereço inativo (Dangling Pointer).

```c

free(p);
p = NULL; // Zera o ponteiro para evitar acessos indevidos

```

## Resumo da Aula 1 de Alocação Dinâmica:

1. A Stack é rápida e automática, mas rígida e pequena.
2. O Heap é flexível e gigante, mas exige controle manual com malloc e free.
3. Tudo o que alocamos no Heap é acessado exclusivamente por Ponteiros.
