# Funções em C

## Anatomia e os 3 Pilares de uma Função

'''c
tipo_de_retorno nome_da_funcao(tipo_param1 param1, tipo_param2 param2) {
    // Corpo da função (Declarações e Instruções)
    return valor; // Se o retorno for diferente de void
}
'''

Os 3 Pilares Obrigatórios:

1. Assinatura / Protótipo: Avisa ao compilador que a função existe antes de ser chamada.
2. Chamada: Ponto onde a execução é transferida para a função.
3. Definição: A implementação real do bloco de código.

## Por que usar Protótipos de Função?

C é compilado de cima para baixo. Sem o protótipo no topo, se o main() chamar uma função definida mais abaixo, o compilador emitirá um warning/erro porque ainda não conhece a assinatura e os tipos dos parâmetros daquela função.

## Ciclo de Vida na Memory Stack

1. main() executa e cria seu Stack Frame.
2. main() chama calcular_desconto(100, 15).
3. Um NOVO Stack Frame é empilhado no topo.
4. Os parâmetros 'preco' e 'percentual' recebem CÓPIAS dos valores.
5. A função executa e calcula o retorno.
6. O retorno é enviado de volta para a main().
7. O Stack Frame da função é DESTRUÍDO (memória liberada automaticamente).

Considere este código simples:

'''c
    float calcular_desconto(float preco, float pct) {
        float valor_desconto = preco * (pct / 100.0f);
        return preco - valor_desconto;
    }

    int main(void) {
        float preco_original = 100.0f;
        float final = calcular_desconto(preco_original, 15.0f);
        return 0;
    }
'''

- A main() toma conta da memória (Antes da chamada)

'''txt
ENDEREÇO HEX       ESTADO DA MEMÓRIA STACK               STATUS
┌──────────────┬────────────────────────────────────────┬─────────────┐
│  0x7FFF1004  │  [ final = ??? ]                       │ Reservada   │
│  0x7FFF1000  │  [ preco_original = 100.0 ]            │ Ativa (main)│
└──────────────┴────────────────────────────────────────┴─────────────┘
                               ▲
                       TOPO DA STACK (main)
'''

- O Empilhamento (Push - No momento da chamada)

'''txt
ENDEREÇO HEX       ESTADO DA MEMÓRIA STACK               STATUS
┌──────────────┬────────────────────────────────────────┬─────────────┐
│  0x7FFF0FDC  │  [ valor_desconto = 15.0 ]             │             │
│  0x7FFF0FE0  │  [ pct = 15.0 ]                        │ Ativa       │
│  0x7FFF0FE4  │  [ preco = 100.0 ] (Cópia!)            │ (função)    │
│  0x7FFF0FE8  │  [ Endereço de Retorno para main ]     │             │
├──────────────┼────────────────────────────────────────┼─────────────┤
│  0x7FFF1004  │  [ final = ??? (Aguardando...) ]       │ Pausada     │
│  0x7FFF1000  │  [ preco_original = 100.0 ]            │ (main)      │
└──────────────┴────────────────────────────────────────┴─────────────┘
                               ▲
                      NOVO TOPO DA STACK!
'''

- O Retorno do Valor (Instante final da função)

'''txt
RETORNO: 85.0f
                               │
                               ▼
┌──────────────┬────────────────────────────────────────┬─────────────┐
│  0x7FFF0FDC  │  [ valor_desconto = 15.0 ]             │ Prestes a   │
│  0x7FFF0FE4  │  [ preco = 100.0 ]                    │ ser         │
│  0x7FFF0FE8  │  [ Endereço de Retorno ]               │ destruída!  │
├──────────────┼────────────────────────────────────────┼─────────────┤
│  0x7FFF1004  │  [ final = 85.0 ] <── Recebe o valor!  │ Ativa       │
│  0x7FFF1000  │  [ preco_original = 100.0 ]            │ (main)      │
└──────────────┴────────────────────────────────────────┴─────────────┘
'''

- O Desempilhamento (Pop) e Limpeza (Pós-chamada)

'''txt
ENDEREÇO HEX       ESTADO DA MEMÓRIA STACK               STATUS
┌──────────────┬────────────────────────────────────────┬─────────────┐
│  0x7FFF0FDC  │  [ MEMÓRIA LIBERADA / LIXO ]           │ Inativa     │
│  0x7FFF0FE4  │  [ MEMÓRIA LIBERADA / LIXO ]           │ (Disponível)│
├──────────────┼────────────────────────────────────────┼─────────────┤
│  0x7FFF1004  │  [ final = 85.0 ]                      │ Ativa       │
│  0x7FFF1000  │  [ preco_original = 100.0 ]            │ (main)      │
└──────────────┴────────────────────────────────────────┴─────────────┘
                               ▲
                       TOPO RECUA PARA main()
'''

Main X Função

'''txt

GAVETA DA MAIN()                     GAVETA DA FUNÇÃO
 ┌──────────────────────┐             ┌──────────────────────┐
 │ Endereço: 0x7FFF1000 │             │ Endereço: 0x7FFF0FE4 │
 │ Nome: preco_original │  ──CÓPIA──> │ Nome: preco          │
 │ Valor: 100.0         │             │ Valor: 100.0         │
 └──────────────────────┘             └──────────────────────┘
         ▲                                    ▲
         │                                    │
   Mora na main()                      Mora na função!
   (Sua casa original)                 (Nasce e morre na chamada)

'''

## Exemplo de Função

[Exemplo](temperatura.c)
