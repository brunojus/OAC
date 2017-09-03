/* Trabalho 1 - SIMULADOR MIPS
Organização e Arquitetura de Computadores - 2/2017
Professor: Ricardo Pezzuol Jacobi
Turma: C

Bruno Justino Garcia Praciano
Matrícula: 13/0006912
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];
int32_t reg[32];

/* Lê um inteiro alinhado, só aceitando endereços múltiplos de 4 {$X = MEMORY[$Y+IMM]}
OPCODE -> 100011 */
int32_t lw(uint32_t address, int16_t kte);

/* Lê meia palavra - 16 bits, retorna inteiro com sinal e só aceita endereços múltiplos de 2
OPCODE-> 100001 */
int32_t lh(uint32_t address, int16_t kte);

/* Lê um byte, retorna inteiro com sinal
OPCODE -> 100000 */
int32_t lb(uint32_t address, int16_t kte);

/* Escreve um inteiro alinhado na memória, só aceitando endereços múltiplos de 4 {MEMORY[$Y+IMM] = $X}
OPCODE -> 101011 */
void sw(uint32_t address, int16_t kte, int32_t dado);

/* Escreve meia palavra - 16 bits, só aceitando endereços múltiplos de 2
OPCODE -> 101001 */
void sh(uint32_t address, int16_t kte, int16_t dado);

/* Escreve um byte na memória
OPCODE -> 101000 */
void sb(uint32_t address, int16_t kte, int8_t dado);

/* Função para inicializar os vetores de memória e registradores */
void init();

/* Função que lê o arquivo passado como parâmetro e coloca na memória a partir da posição indicada */
int leitura(FILE *p, int pos);

/* Executa as instruções fornecidas pelo binário ao associar o binário com a função correspondente */
void instrExec(int num_instr);

/* Imprime na tela e gera um arquivo binário com o resultado do data ao final da simulação. Além disso, imprime o estado final dos registradores */
void gerarData();
