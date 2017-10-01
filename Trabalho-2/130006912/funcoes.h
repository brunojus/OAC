//Bruno Justino Garcia Praciano - 13/0006912
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MEM_SIZE 4096


uint32_t pc;
uint32_t ri;
int32_t hi;
int32_t lo;


int32_t reg[32];


uint32_t opcode;
uint32_t rs;
uint32_t rt;
uint32_t rd;
uint32_t shamt;
uint32_t funct;
int32_t k16;
uint32_t k26;

enum OPCODES {
  EXT=0x00,     LW=0x23,      LB=0x20,      LBU=0x24,       ADDIU=0x09,
  LH=0x21,      LHU=0x25,     LUI=0x0F,     SW=0x2B,
  SB=0x28,      SH=0x29,      BEQ=0x04,     BNE=0x05,
  BLEZ=0x06,    BGTZ=0x07,    ADDI=0x08,    SLTI=0x0A,
  SLTIU=0x0B,   ANDI=0x0C,    ORI=0x0D,     XORI=0x0E,
  J=0x02,       JAL=0x03
};

enum FUNCT {
  ADD=0x20,     SUB=0x22,     MULT=0x18,    DIV=0x1A,         AND=0x24,
  OR=0x25,      XOR=0x26,     NOR=0x27,     SLT=0x2A,         JR=0x08,
  SLL=0x00,     SRL=0x02,     SRA=0x03,     SYSCALL=0x0c,     MFHI=0x10,  MFLO=0x12
};

int32_t mem[MEM_SIZE];


void loadData(FILE *ponteiroArquivo);


void loadText(FILE *ponteiroArquivo);

int32_t lw(uint32_t endereco, int16_t deslocamento);


int32_t lh(uint32_t endereco, int16_t deslocamento);


int32_t lb(uint32_t endereco, int16_t deslocamento);


int32_t lhu(uint32_t endereco, int16_t deslocamento);


int32_t lbu(uint32_t endereco, int16_t deslocamento);

void sw(uint32_t endereco, int16_t deslocamento, int32_t dado);


void sh(uint32_t endereco, int16_t deslocamento, int16_t dado);


void sb(uint32_t endereco, int16_t deslocamento, int8_t dado);

void menu ();

void fetch(uint32_t instrucao);


void decode();


void execute();

void step();

void run();

void dump_mem(uint32_t start, uint32_t end, char format);

void dump_reg(char format);
