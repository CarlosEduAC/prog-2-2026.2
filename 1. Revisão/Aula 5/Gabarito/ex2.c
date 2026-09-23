#include <stdio.h>

void converter_tempo(int total_segundos, int *horas, int *minutos, int *segundos);

int main(void) {
    int total_seg = 7385; // Equivalente a 2h 3m 5s
    int h, m, s;

    // Passagem dos endereços das variáveis da main
    converter_tempo(total_seg, &h, &m, &s);

    printf("Total em segundos: %d s\n", total_seg);
    printf("Formatado: %02dh %02dm %02ds\n", h, m, s);

    return 0;
}

void converter_tempo(int total_segundos, int *horas, int *minutos, int *segundos) {
    // 1 Hora = 3600 segundos
    *horas = total_segundos / 3600;

    // Resto dos segundos após extrair as horas
    int resto = total_segundos % 3600;

    // 1 Minuto = 60 segundos
    *minutos = resto / 60;

    // Segundos restantes
    *segundos = resto % 60;
}