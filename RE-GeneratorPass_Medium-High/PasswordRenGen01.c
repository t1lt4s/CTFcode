/*
Descrição:
O binário executável pede que o jogador insira uma flag correta. Caso contrário, ele responde com "Flag incorreta!". O desafio é reverter a lógica e descobrir qual flag será aceita.

Detalhes Técnicos:

- O código pode ter verificações como hash de senha (`SHA256`, `MD5`) ou operações bitwise sobre a entrada.
- Pode ser um binário ELF (Linux) ou PE (Windows).
- Algumas partes podem estar ofuscadas para dificultar a análise.

Abordagem esperada do jogador:

- Extrair a lógica de verificação via `strings`, `objdump`, `radare2` ou `Ghidra`.
- Escrever um script em Python para gerar um input válido.
- 
Objetivo do desafio:

O jogador recebe um binário e precisa descobrir qual flag ele aceita como entrada válida.

Detalhes técnicos:

- O binário pede que o usuário insira uma string e a compara com a flag correta.
- Pode usar um hash (MD5/SHA256) para verificar a entrada ou um algoritmo customizado.
- Pode conter técnicas de ofuscação para dificultar a análise.
- Opcional: incluir anti-debugging (`ptrace`, `IsDebuggerPresent`).

Passos para desenvolvimento:

1. Criar um programa em C que recebe uma string como entrada.
2. Implementar a verificação da flag via hash ou transformação matemática.
3. Ofuscar partes do código (exemplo: espalhar a verificação da flag pelo código).
4. Gerar o binário e remover símbolos de depuração (`strip` no Linux).
5. Testar reversão com ferramentas como `strings`, `objdump`, `Ghidra`.
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Função para verificar a flag
int check_flag(const char *input) {
    char correct_flag[] = {0x43, 0x54, 0x46, 0x7B, 0x52, 0x65, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6E, 0x67, 0x5F, 0x43, 0x68, 0x61, 0x6C, 0x6C, 0x65, 0x6E, 0x67, 0x65, 0x7D, 0x00};
    int len = strlen(correct_flag);
    uint32_t hash = 0;
    
    for (int i = 0; i < len; i++) {
        hash += input[i] ^ (i * 13);
    }
    
    return hash == 0x5F5D3A2B; // Valor pré-calculado para a flag correta
}

int main() {
    char flag[64];
    
    printf("Digite a flag: ");
    scanf("%63s", flag);
    
    if (check_flag(flag)) {
        printf("Flag correta! Parabéns!\n");
    } else {
        printf("Flag incorreta! Tente novamente.\n");
    }
    
    return 0;
}




/*
Desafio:

- Solicita uma flag ao usuário.
- Calcula um hash simples baseado nos caracteres da flag.
- Compara o hash com um valor pré-calculado correspondente à flag correta.

Para dificultar a engenharia reversa, podemos adicionar:

- Ofuscação do valor da flag.
- Proteções anti-debugging.
- Obfuscação matemática do cálculo do hash.

flag está ofuscada como uma sequência de valores hexadecimais no código, dificultando sua 
extração com ferramentas como `strings`.


*/