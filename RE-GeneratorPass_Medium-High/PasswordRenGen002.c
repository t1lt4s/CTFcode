#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void generate_password(const char *input, char *output) {
    int len = strlen(input);
    uint32_t seed = 0;
    
    // Criando um seed baseado na soma dos caracteres do nome
    for (int i = 0; i < len; i++) {
        seed += input[i];
    }
    seed ^= 0xA5A5A5A5;  // Aplicando um XOR com uma constante
    
    // Gerando a senha baseada no seed e no nome
    for (int i = 0; i < len; i++) {
        output[i] = ((input[i] ^ (seed & 0xFF)) + (i % 7)) ^ ((seed >> 8) & 0xFF);
    }
    output[len] = '\0';
}

int main() {
    char name[32];
    char password[32];
    
    printf("Digite seu nome: ");
    scanf("%31s", name);
    
    generate_password(name, password);
    
    printf("Senha gerada: %s\n", password);
    
    return 0;
}
