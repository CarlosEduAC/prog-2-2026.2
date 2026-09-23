# Atividades da Aula 5

## Exercício 1: Min-Max (Retornando Dois Valores sem return)

Escreva uma função com a seguinte assinatura:

'''c
    void encontrar_min_max(int a, int b, int c, int *menor, int* maior);
'''

A função deve receber três números inteiros (a, b, c) por valor e, utilizando os ponteiros menor e maior, alterar o valor das variáveis da main para armazenar o menor e o maior número entre os três lidos.

## Exercício 2: Conversor de Tempo (Divisão e Resto via Ponteiros)

Crie um programa com a função:

'''c
    void converter_tempo(int total_segundos, int *horas, int* minutos, int *segundos);
'''

A função deve receber um tempo total em segundos (inteiro) e decompô-lo em horas, minutos e segundos restantes, atualizando diretamente os valores das variáveis declaradas na main.

## Exercício 3: Reajuste Salarial de Funcionário (struct + Ponteiros)

Defina a estrutura Funcionario:

'''c
    typedef struct {
        int id;
        float salario;
        char cargo[30];
    } Funcionario;
'''

Implemente a função:

'''c
    bool reajustar_salario(Funcionario *f, float percentual_aumento);
'''

- A função deve aplicar o aumento percentual ao salário do funcionário apontado por f usando o operador seta (->).
- Se o percentual_aumento for menor ou igual a zero, a função deve retornar false e não alterar o salário. Caso contrário, aplica o reajuste e retorna true.
