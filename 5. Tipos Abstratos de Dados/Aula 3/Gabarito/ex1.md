- struct Pública (.h): Expõe todos os seus membros internos para qualquer arquivo que inclua o cabeçalho. O código cliente tem permissão de leitura e escrita direta nos campos (objeto.campo ou ponteiro->campo), podendo atribuir valores inválidos, violar invariantes e criar dependência acoplada com os nomes das variáveis internas.

- TAD com Ponteiro Opaco: Expõe apenas o nome do tipo (typedef struct MeuTAD MeuTAD;) no .h, enquanto a definição concreta dos campos fica oculta exclusivamente no .c.

- Vantagens Principais:

1. Integridade de Dados: O cliente só consegue alterar o estado chamando funções validadas do TAD.

2.Desacoplamento e Mantenabilidade: A implementação interna no .c pode ser alterada (ex: mudar um campo de int para float ou trocar um vetor por uma lista encadeada) sem que nenhuma linha do main.c precise ser reescrita ou modificada.
