/*
Descrição:

Um binário gera uma senha baseada em certos parâmetros ocultos. O jogador precisa analisar a lógica do gerador e produzir uma senha válida.

Detalhes Técnicos:

- O código pode usar valores fixos em XOR ou uma sequência pseudoaleatória previsível.
- Pode ter ofuscação para dificultar a engenharia reversa.

Ferramentas úteis:

- `Ghidra` para desmontar e analisar a lógica.
- `angr` para simulação simbólica do código.
- `Python` para criar um script que gera a senha correta.


Objetivo do desafio:

O jogador recebe um binário que gera uma senha aparentemente aleatória. A missão é entender a lógica e gerar uma senha válida sem executar o programa.


Detalhes técnicos:

- O gerador pode depender de dados previsíveis (timestamp, nome do usuário).
- Pode usar operações como XOR, rotação de bits ou hashing parcial.
- O código pode ter verificações adicionais, como checksum.

Passos para desenvolvimento:

1. Criar um gerador de senha em C baseado em um algoritmo previsível.
2. Introduzir operações matemáticas para transformar a entrada.
3. Opcional: adicionar um fator externo (exemplo: número de segundos desde o boot).
4. Compilar e remover símbolos (`strip`).
5. Testar análise reversa com `Ghidra` e `radare2`.

*/

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
