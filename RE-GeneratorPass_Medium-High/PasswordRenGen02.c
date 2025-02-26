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

**CÓDIGO01**

**Características do desafio:**

- O programa solicita um nome como entrada.
- Gera uma senha baseada nesse nome, aplicando operações matemáticas e bitwise.
- O objetivo do jogador é reverter a lógica e criar um gerador de senhas válido sem executar o programa.

Vou gerar o código em C para que possamos trabalhar nele.


*/
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

/*
Este código gera uma senha baseada no nome do usuário, aplicando uma operação XOR (`^ 0x5A`) e uma adição condicional.

***Como o jogador pode resolver o desafio?***

1. **Analisando o binário:** Usando `Ghidra` ou `IDA Pro`, ele pode observar a função `generate_password`.
2. **Revertendo a lógica:** Ele perceberá que a senha é derivada do nome com operações previsíveis.
3. **Criando um script inverso:** O jogador pode recriar o algoritmo para gerar senhas sem rodar o programa original.



**CÓDIGO02**

Aumento de complexidade no gerador de senhas:

- Criar uma seed baseada na soma dos caracteres do nome.
- Aplicar um XOR com uma constante (`0xA5A5A5A5`).
- Usar deslocamento de bits e modularidade para dificultar a reversão.



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
    
*/