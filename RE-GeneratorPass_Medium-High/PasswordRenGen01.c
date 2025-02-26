#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generate_password(const char *input, char *output) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = (input[i] ^ 0x5A) + (i % 5);
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
