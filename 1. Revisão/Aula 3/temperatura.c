#include <stdio.h>
#include <stdbool.h>

// Protótipos
void exibir_menu();
float converter_celsius_para_fahrenheit(float c);
bool eh_temperatura_critica(float c);

int main(void) {
    float temp_celsius = 37.5f;

    exibir_menu();

    float temp_f = converter_celsius_para_fahrenheit(temp_celsius);
    printf("Temperatura em Fahrenheit: %.2f F\n", temp_f);

    if (eh_temperatura_critica(temp_celsius)) {
        printf("[ ALERTA ] Temperatura em nivel critico!\n");
    } else {
        printf("[ OK ] Temperatura dentro do limite normal.\n");
    }

    return 0;
}

// Implementações
void exibir_menu() {
    printf("=========================================\n");
    printf("   SISTEMA DE MONITORAMENTO DE TEMPERATURA\n");
    printf("=========================================\n\n");
}

float converter_celsius_para_fahrenheit(float c) {
    return (c * 9.0f / 5.0f) + 32.0f;
}

bool eh_temperatura_critica(float c) {
    return (c >= 38.0f || c <= 35.0f);
}