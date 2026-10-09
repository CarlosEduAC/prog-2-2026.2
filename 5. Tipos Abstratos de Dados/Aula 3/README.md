# Integrando TADs e Encapsulamento ao Space Defender

## A Arquitetura Limpa do Game Loop

A camada de apresentação/interface (Raylib) e a camada de regra de negócio (TADs).

Se mudarmos a biblioteca gráfica da Raylib para SDL2 ou Ncurses no futuro, o código dos TADs Defensor e Inimigo não deve sofrer alteração de uma única linha. O main.c atua apenas como um orquestrador que lê entradas do usuário, chama os métodos do TAD e manda desenhar o estado retornado.

```txt

CAMADA DE APRESENTAÇÃO                      CAMADA DE REGRA DE NEGÓCIO
              (main.c)                                (TADs no Heap)

   ┌──────────────────────────┐                    ┌──────────────────────────┐
   │ Input (Teclado/Mouse)    │ ─── Chamadas ───>  │  TAD Defensor (Pilha)    │
   ├──────────────────────────┤     de Métodos     ├──────────────────────────┤
   │ Renderização (Raylib)    │ <── Retorno de ─── │  TAD Inimigo (Fila/List) │
   └──────────────────────────┘      Valores       └──────────────────────────┘

```
