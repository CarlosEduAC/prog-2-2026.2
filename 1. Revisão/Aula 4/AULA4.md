# Aula 4

## Variáveis Soltas

Para cadastrar um aluno, podemos criar variáveis separadas:

'''c
    // Como fazíamos em Prog 1:
    int matricula1 = 101;
    float nota1 = 8.5f;
    char status1 = 'A';

    int matricula2 = 102;
    float nota2 = 4.0f;
    char status2 = 'R';
'''

* Problemas nessa abordagem:
  1. Código Grande e Repetitivo.
  2. Se precisarmos cadastrar 100 alunos, teremos que criar 100 conjuntos de variáveis.
  3. Não há uma forma de agrupar as informações de cada aluno.
  4. Falta de Vínculo Lógico: Nada no código garante que nota1 pertence a matricula1. São gavetas soltas na Stack.
  5. Inviabilidade para Passagem de Parâmetros: Se uma função precisar processar os dados do aluno, precisará receber 3, 4 ou 5 parâmetros separados.
  6. Impossibilidade de Ordenação Simples: Se quisermos trocar a ordem dos alunos, teremos que trocar individualmente cada uma das variáveis soltas.

## Structs: Agrupando Variáveis em Objetos

Struct é uma abreviação para Structure, que significa estrutura em português. Na linguagem de programação C (e em muitas outras) é uma estrutura de dados composto que define fisicamente uma lista de variáveis agrupadas sob um nome em um bloco de memória, logo, todas as variáveis conseguem ser acessadas por meio de um único ponteiro ou pelo que é declarado na estrutura que retorna o mesmo endereço.

### Sintaxe Base de Struct

Exemplo de declaração de uma struct para armazenar informações de um aluno:

'''c
    struct Aluno {
        int matricula;      // 4 bytes
        char nome[50];      // 50 bytes
        float media;        // 4 bytes
        char situacao;      // 1 byte
    };
'''

                    REPRESENTAÇÃO DA STRUCT NA STACK
  ┌─────────────────┬───────────────────────────────┬─────────┬──────────┐
  │ matricula (int) │         nome (char[50])       │ media   │ situacao │
  │    4 bytes      │            50 bytes           │ 4 bytes │  1 byte  │
  └─────────────────┴───────────────────────────────┴─────────┴──────────┘
  ◄─────────────────────────── Total: ~59 bytes ────────────────────────►

### Acesso aos Campos da Struct

O operador ponto (.) é a ferramenta para selecionar o campo interno da estrutura:

'''c
    struct Aluno a1; // Declaração da variável do tipo struct Aluno

    a1.matricula = 202601;
    a1.media = 8.5f;
    a1.situacao = 'A';
    strcpy(a1.nome, "Carlos Eduardo"); // Para strings em C, usamos strcpy da <string.h>
'''

                O BLOCO DA STRUCT 'a1' NA MEMÓRIA RAM (STACK)

  ENDEREÇO HEX     MEMBRO INTERNO         TAMANHO       O QUE ESTÁ GUARDADO
 ┌──────────────┬──────────────────────┬─────────────┬─────────────────────────┐
 │  0x7FFF1000  │  a1.matricula        │  4 bytes    │ [ 00 03 15 89 ] (202201)│
 ├──────────────┼──────────────────────┼─────────────┼─────────────────────────┤
 │  0x7FFF1004  │  a1.nome[0..49]      │  50 bytes   │ "Maria Silva\0..."      │
 ├──────────────┼──────────────────────┼─────────────┼─────────────────────────┤
 │  0x7FFF1036  │  (Padding / Preench) │  2 bytes*.  │ [ lixo de memória ]     │
 ├──────────────┼──────────────────────┼─────────────┼─────────────────────────┤
 │  0x7FFF1038  │  a1.media            │  4 bytes    │ [ 9.50 ]                │
 ├──────────────┼──────────────────────┼─────────────┼─────────────────────────┤
 │  0x7FFF103C  │  a1.situacao         │  1 byte     │ [ 'A' ]                 │
 ├──────────────┼──────────────────────┼─────────────┼─────────────────────────┤
 │  0x7FFF103D  │  (Padding Final)     │  3 bytes*   │ [ lixo de memória ]     │
 └──────────────┴──────────────────────┴─────────────┴─────────────────────────┘
 ◄──────────────────────── Total Físico: 64 bytes ────────────────────────►

### O poder do typedef

Para não precisar escrever `struct` toda vez que declaramos uma variável do tipo struct, podemos usar o `typedef`:

'''c
    // O typedef cria um apelido/alias para o tipo
    typedef struct {
        int codigo;
        char descricao[50];
        float preco;
        int quantidade;
    } Produto;

    // Agora declaramos diretamente como se fosse um tipo nativo (int, float):
    int main() {
        ...

        Produto p1;

        ...
    }
'''

### Vetores de Structs

Podemos criar vetores de structs para armazenar múltiplos produtos em um estoque:

'''c
    #define TAM_ESTOQUE 50

    // Um vetor onde CADA posição é uma struct Produto inteira!
    Produto estoque[TAM_ESTOQUE];

    // Acessando e modificando o preço do terceiro produto do estoque:
    estoque[2].preco = 49.90f;
'''

 ┌─────────────────────────────────────────────────────────────────────────────┐
 │                          VETOR produto[3] (192 bytes)                       │
 ├──────────────────────────┬──────────────────────────┬───────────────────────┤
 │        produto[0]        │        produto[1]        │      produto[2]       │
 │        (64 bytes)        │        (64 bytes)        │      (64 bytes)       │
 ├────────┬──--────┬───┬────┼────────┬─────--─┬───┬────┼────────┬─────--─┬───┬─┤
 │ código │ descri │pre│qtd.│ código │ descri │pre│qtd.│ código │ descri │pre│q│
 └────────┴──--────┴───┴────┴────────┴─────--─┴───┴────┴────────┴────--──┴───┴─┘
  0x7FFF1000                 0x7FFF1040                 0x7FFF1080
