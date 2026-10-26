#include "math_game.h"
#include <math.h>

// Função auxiliar estática privada (não exposta no .h nem ao Linker)
static float calcular_distancia_quadrada(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return (dx * dx) + (dy * dy);
}

float math_clamp(float valor, float min, float max) {
    if (valor < min) return min;
    if (valor > max) return max;
    return valor;
}

bool math_colisao_circulos(float x1, float y1, float r1, float x2, float y2, float r2) {
    float dist_sq = calcular_distancia_quadrada(x1, y1, x2, y2);
    float raio_soma = r1 + r2;
    return dist_sq <= (raio_soma * raio_soma);
}