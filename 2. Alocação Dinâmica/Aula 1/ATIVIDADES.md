# Atividade

## Exercício 1: Alocação Dinâmica de Registro Simples no Heap

Você foi contratado para criar um módulo de cadastro individual de veículos para uma oficina. Como a memória do computador da oficina é limitada, o cadastro não deve usar a Stack para o registro.

1. Crie uma struct chamada Veiculo contendo:
    - placa (string / vetor de char de tamanho 8)
    - ano (int)
    - preco (float)
2. Na função main(), declare apenas um ponteiro do tipo Veiculo *v = NULL;.
3. Aloque espaço no Heap dinamicamente para 1 veículo usando malloc(sizeof(Veiculo)).
4. Faça a verificação de segurança contra NULL.
5. Leia os dados do teclado (placa, ano e preco) e preencha a estrutura alocada utilizando o operador seta (->).
6. Exiba os dados cadastrados na tela de forma formatada.
7. Libere a memória alocada com free(v); e anule o ponteiro com v = NULL;.
