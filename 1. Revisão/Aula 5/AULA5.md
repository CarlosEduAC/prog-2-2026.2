# Aula 5

## Problema de múltiplo retorno

"Crie uma única função em C para calcular o dobro e o triplo de um número e devolver AMBOS os resultados para a main() se o return só aceita um valor?"

'''c
    // Como resolver isso sem usar variáveis globais?
    void calcular_dobro_e_triplo(int numero, int *dobro, int *triplo) {
        *dobro = 2 * numero;
        *triplo = 3 * numero;
    }
'''

## A Anatomia do Ponteiro e os Operadores & e *

Um ponteiro é uma variável cujo valor é o endereço de memória de outra variável.

- & (Endereço de): "Onde esta variável mora na RAM?"

- '*' (Conteúdo de / Desreferenciação): "Vá até o endereço guardado e pegue/modifique o valor lá dentro."

VARIÁVEL COMUM (int x = 10;)                PONTEIRO (int *p = &x;)
 ┌──────────────────────────────┐       ┌──────────────────────────────┐
 │ Endereço: 0x7FFF1000         │       │ Endereço: 0x7FFF1004         │
 │ Nome    : x                  │       │ Nome    : p                  │
 │ Valor   : 10                 │       │ Valor   : 0x7FFF1000         │
 └──────────────────────────────┘       └──────────────┬───────────────┘
                 ▲                                     │
                 └─────────────────────────────────────┘
                             (p aponta para x)

- p é um ponteiro para inteiro (int *p), ou seja, ele guarda o endereço de memória de uma variável do tipo inteiro.
- *p é o conteúdo do endereço guardado em p, ou seja, o valor da variável x.
- *p = 20; vai até o endereço 0x7FFF1000 e altera o valor da variável x para 20, pois p aponta para x.
- Se declararmos um ponteiro sem inicializá-lo, ele vai apontar para um endereço aleatório na memória (lixo de memória). Por isso, é importante sempre inicializar um ponteiro com o endereço de uma variável válida ou com NULL.

## A Troca de Valores

### Passagem por Valor ❌

'''c
    void troca_por_valor(int a, int b) {
        int temp = a;
        a = b;
        b = temp;
    } // 'a' e 'b' morrem aqui sem alterar a main()

    int main () {
        int num1 = 10, num2 = 20;

        troca_por_valor(num1, num2);
    }
'''

### Passagem por Referência ✅

[Exemplo](main.c)

## Struct + Ponteiros

Quando temos um ponteiro para uma struct:

'''c
    Aluno a1 = {101, "Carlos", 8.5f};
    Aluno *ptr = &a1; // ptr guarda o endereço de a1
'''

Se quisermos acessar o campo nota usando o ponteiro ptr, a primeira ideia seria fazer:

'''c
    *ptr.nota = 9.0f; //  ERRO DE COMPILAÇÃO!
'''

Por que isso dá erro?

Na linguagem C, o operador ponto (.) tem maior prioridade (precedência) do que o operador de desreferenciação (*). Então o compilador entende que você está tentando acessar ptr.nota antes de buscar o conteúdo do ponteiro, o que não faz sentido porque ptr é um endereço, não a struct.

Para corrigir a prioridade, precisaríamos usar parênteses obrigatoriamente:

'''c
    (*ptr).nota = 9.0f; // CORRETO!
'''

Essa linha diz: "Primeiro vá até o endereço guardado em ptr (*ptr), e só depois acesse o campo nota (.nota)".

### O Operador Seta (->)

Como a sintaxe (*ptr).campo é poluída e propensa a esquecimento de parênteses, os criadores do C criaram o operador seta (->) como um atalho direto e elegante.

O operador -> faz as duas coisas ao mesmo tempo: desreferencia o ponteiro (*) e acessa o membro da struct (.).

'''c
    ptr->nota = 9.0f; // CORRETO E MAIS LIMPO!
'''

Resumo da Regra de Ouro (Ponto vs Seta)

| Tipo de Variável | Operador Utilizado | Exemplo de Uso | O que significa na prática? |
|------------------|--------------------|----------------|-----------------------------|
| **Variável Direta** (a `struct` em si) | **Ponto (`.`)** | `a1.nota` | Acessa o campo diretamente da variável física. |
| **Ponteiro** (Endereço da `struct`) | **Seta (`->`)** | `ptr->nota` | Vai até o endereço armazenado no ponteiro e acessa o campo lá dentro (`(*ptr).nota`). |