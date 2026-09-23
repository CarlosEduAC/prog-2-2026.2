# Aula 2

## O Mapa da Memória RAM

A memória é dividida em 4 regiões principais (segmentos), cada uma com uma responsabilidade bem definida.
                MEMÓRIA RAM DO PROGRAMA
            ENDEREÇOS ALTOS (Ex: 0x7FFF...)
  ┌─────────────────────────────────────────────────────────┐
  │                        STACK                            │
  │  • Variáveis locais, parâmetros e retornos de função    │
  │  • Cresce de CIMA para BAIXO (endereços menores)        │
  │                          │                              │
  │                          ▼                              │
  ├─────────────────────────────────────────────────────────┤
  │                       ( ESPAÇO LIVRE )                  │
  ├─────────────────────────────────────────────────────────┤
  │                          ▲                              │
  │                          │                              │
  │  • Cresce de BAIXO para CIMA (endereços maiores)        │
  │                        HEAP                             │
  │  • Alocação dinâmica manual (malloc / free)             │
  ├─────────────────────────────────────────────────────────┤
  │                     DATA / BSS                          │
  │  • Variáveis globais e estáticas                        │
  ├─────────────────────────────────────────────────────────┤
  │                     TEXT / CODE                         │
  │  • Instruções do processador em código de máquina       │
  └─────────────────────────────────────────────────────────┘
            ENDEREÇOS BAIXOS (Ex: 0x0000...)

### Segmento TEXT / CODE (Código)

É a região onde ficam armazenadas as instruções em linguagem de máquina (assembly/binário) resultantes da compilação do seu código C.

- O que guarda: O código das funções (main, printf, funções próprias) e constantes literais de texto.
- Permissão: Somente Leitura (Read-Only) e Executável.
- Por que é protegido? Para impedir que o programa altere suas próprias instruções durante a execução ou que ataques maliciosos injetem código executável nessa área.

### Segmento DATA e BSS (Dados Globais e Estáticos)

Esta região guarda as variáveis que precisam existir durante toda a vida útil do programa (variáveis globais e variáveis static), antes mesmo da main() começar. Ela é dividida em duas partes:

A. Segmento DATA (Initialized Data)

- O que guarda: Variáveis globais e estáticas que foram inicializadas com um valor explícito pelo programador.
- Exemplo: int g_contador = 10; ou static float TAXA = 0.05f;.

B. Segmento BSS (Block Started by Symbol / Uninitialized Data)

- O que guarda: Variáveis globais e estáticas que não foram inicializadas explicitamente no código.
- Característica: O sistema operacional zera automaticamente toda essa área antes do programa iniciar (0, NULL ou 0.0).
- Exemplo: int g_vetor[1000]; (não ocupa espaço no arquivo executável do disco, apenas na RAM).

### Segmento HEAP (Memória Dinâmica)

O Heap é um "balde de memória livre" gerenciado manualmente pelo programador em tempo de execução.

- O que guarda: Dados alocados dinamicamente através de funções como malloc(), calloc() e realloc().
- Crescimento: Cresce dos endereços baixos em direção aos endereços altos (de baixo para cima).
- Ciclo de vida: A memória permanece reservada até ser explicitamente liberada com a função free().
- Risco: Se você alocar com malloc() e esquecer de dar free(), ocorre o Vazamento de Memória (Memory Leak).

### Segmento STACK (Pilha de Execução)

A Stack é uma estrutura LIFO (Last In, First Out) controlada automaticamente pelo compilador e pelo processador para gerenciar chamadas de funções e variáveis locais.

- O que guarda:

1. Variáveis locais declaradas dentro de funções.
2. Parâmetros passados para funções.
3. Endereço de retorno (para onde o programa deve voltar após a função terminar).

- Crescimento: Cresce dos endereços altos em direção aos endereços baixos (de cima para baixo).
- Ciclo de vida: Automático. Quando a função é chamada, seu bloco (Stack Frame) é empilhado. Quando a função encerra, o bloco é desempilhado e a memória é liberada instantaneamente.
- Risco: Se você fizer recursão infinita ou declarar vetores locais gigantescos, a Stack invade o espaço do Heap, provocando o erro Stack Overflow.

[Mapeamento Prático em Código C](main.c)

Exemplo:

'''c
    // Declarando uma variável inteira
    int idade = 25;
'''

    NOME DA VARIÁVEL: "idade"

    ENDEREÇO DA GAVETA      CONTEÚDO (1 BYTE CADA)
   ┌──────────────────┐   ┌────────────────────────┐
   │    0x7ffd5e40    │   │  0 0 0 0 0 0 0 0       │ ─┐
   ├──────────────────┤   ├────────────────────────┤  │
   │    0x7ffd5e41    │   │  0 0 0 0 0 0 0 0       │  │── O conjunto de 4 bytes
   ├──────────────────┤   ├────────────────────────┤  │   guarda o valor 25!
   │    0x7ffd5e42    │   │  0 0 0 0 0 0 0 0       │  │
   ├──────────────────┤   ├────────────────────────┤  │
   │    0x7ffd5e43    │   │  0 0 0 1 1 0 0 1       │ ─┘
   └──────────────────┘   └────────────────────────┘
            ▲                         ▲
            │                         │
     O que o '&' pega          O valor que o C lê

- Nome: o identificador idade que você usa no código.
- Valor: o número 25 guardado lá dentro em binário.
- Endereço: o número da gaveta na memória, ex: 0x7ffd5e40.

## O Tamanho das Variáveis (sizeof) e os Bytes

Diferentes tipos ocupam quantidades diferentes de gavetas (bytes).

'''c
    printf("char        : %lu byte  (8 bits)\n", sizeof(char));
    printf("bool        : %lu byte  (8 bits)\n", sizeof(bool));
    printf("int         : %lu bytes (32 bits)\n", sizeof(int));
    printf("float       : %lu bytes (32 bits)\n", sizeof(float));
    printf("double      : %lu bytes (64 bits)\n", sizeof(double));
    printf("long long   : %lu bytes (64 bits)\n", sizeof(long long));
'''

[Ver código fonte](tamanhos.c)

Pergunta:

Se um int ocupa 4 bytes, o que acontece se declararmos 5 variáveis int em sequência?

'''c
    int a, b, c, d, e;
'''

## Endereço de Memória — O Operador &

'''c
    int x = 10, y =20;
    printf("O endereço de memória da variável x é: %p\n", &x);
    printf("O endereço de memória da variável y é: %p\n", &y);
'''

[Ver código fonte](enderecos.c)

Vamos calcular y - x para ver a diferença entre os endereços de memória das duas variáveis.

Será exatamente 4 bytes de diferença, pois cada variável int ocupa 4 bytes na memória.

A memória costuma ser organizada de forma previsível e sequencial.

## O "Problema da Escala"

### Problema 1: A Limitação das Variáveis Isoladas

Cenário: O professor quer calcular a média de 5 notas e depois dizer quais notas ficaram acima da média.

'''c
    int nota1, nota2, nota3, nota4, nota5;
    float media;
    media = (nota1 + nota2 + nota3 + nota4 + nota5) / 5.0;
'''

O Dilema: Sem usar vetor, precisamos criar nota1, nota2, nota3, nota4, nota5. Se fossem 100 alunos, o código seria inviável de escrever.

A Pergunta: "Como fazemos para o computador guardar 100 valores sob um único nome sequencial na memória?"

➤ (A resposta será: Vetores).

'''c
    int notas[5]; // Vetor de 5 elementos do tipo inteiro
    float media;
    media = (notas[0] + notas[1] + notas[2] + notas[3] + notas[4]) / 5.0;
'''

*notas = notas[0]
*notas + 1 = notas[1]
*notas + 2 = notas[2]

### Problema 2: A Limitação dos Tipos Primitivos Separados

Cenário: Precisamos armazenar o cadastro de um produto: id (int), nome (texto), preco (float) e em_estoque (bool).

'''c
    int id;
    char nome[50];
    float preco;
    bool em_estoque;
'''
O Dilema: As variáveis ficam soltas. Não há nada no código que "amarre" o preco ao id daquele produto específico.

A Pergunta: "Como criamos um novo tipo de dado personalizado que agrupe essas 4 informações em um único bloco de memória?"

➤ (A resposta será: Structs).

'''c
    struct Produto {
        int id;
        char nome[50];
        float preco;
        bool em_estoque;
    };

    struct Produto p1; // Declarando uma variável do tipo Produto
'''

### Problema 3: A Limitação do Escopo de Funções (Cópia por Valor)

Cenário: Queremos criar uma função zerar(int x) que mude o valor de uma variável da main para 0.

'''c
    #include <stdio.h>

    void zerar(int n) {
        n = 0; // Altera apenas a CÓPIA local de 'n' na Stack da função zerar()
    }

    int main(void) {
        int numero = 50;
        zerar(numero);
        printf("Numero = %d\n", numero); // Continua sendo 50!
        return 0;
    }
'''

O Dilema: A função zerar recebe apenas uma cópia do valor. Ela não sabe em qual gaveta da memória a variável numero original mora.

A Pergunta: "O que precisamos passar para a função para que ela consiga alterar a variável original da main?"

➤ (A resposta será: O Endereço da memória / Ponteiros).

'''c
    #include <stdio.h>

    void zerar(int *n) {
        *n = 0; // Altera o valor da variável original na Stack da main()
    }

    int main(void) {
        int numero = 50;
        zerar(&numero); // Passando o endereço de memória da variável numero
        printf("Numero = %d\n", numero); // Agora é 0!
        return 0;
    }
'''
