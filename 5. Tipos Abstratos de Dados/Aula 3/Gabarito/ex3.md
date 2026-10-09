Uma Invariante de Estado é uma propriedade lógica que obrigatoriamente se mantém verdadeira durante toda a existência do objeto no Heap.

Implementação Defensiva da Função:

```c

void defensor_causar_dano(Defensor *d, int dano) {
    // 1. Defesa contra ponteiro nulo (evita crash/segfault)
    if (d == NULL) return;

    // 2. Defesa contra dano inválido ou negativo
    if (dano <= 0) return;

    // 3. Aplicação do dano mantendo a invariante [0 <= vida <= 100]
    d->vida -= dano;
    if (d->vida < 0) {
        d->vida = 0; // Impede que a vida fique negativa no HUD
    }
}

```
