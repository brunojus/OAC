#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define MEM_SIZE 4096

#define ENDERECO_TEXT 0x00000000        //DEFINE O ENDEREÇO ONDE OS DADOS DO SEGMENTO .TEXT DO MIPS ESTARÃO
#define ENDERECO_DATA 0x00002000        //DEFINE O ENDEREÇO ONDE OS DADOS DO SEGMENTO .DATA DO MIPS ESTARÃO

//Memoria
int32_t MEM[MEM_SIZE];

uint32_t *mem = new uint32_t[MEM_SIZE];

uint32_t *pc=0x00000000;

uint32_t i;



uint32_t *POSICAO_NA_MEMORIA_TEXT, *POSICAO_NA_MEMORIA_DATA;        //PONTEIRO PARA OS SEGMENTOS DE TEXTO E DADOS DO PROGRAMA NA MEMÓRIA



// lê um inteiro alinhado - endereços multiplos de 4
int32_t lw(uint32_t address, int16_t kte){
    uint32_t pos = (address + kte)/4;
    return mem[pos];
}

//lê um byte - retorna inteiro com sinal
int32_t lb(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = mem[pos];

    word = word>>8*res;
    int32_t pattern = 0x000000ff;
    int32_t wordanded = (word&pattern);

    return wordanded;
}


// lê um byte - retorna inteiro sem sinal

int32_t lbu(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = mem[pos];

    word = word>>8*res;
    int32_t pattern = 0x000000ff;
    int32_t wordanded = (word&pattern);

    return wordanded;
}


// lê meia palavra, 16 bits-retorna inteiro com sinal
int32_t lh(uint32_t *address, int16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = mem[pos];
    if (res>1){
        word = word>>16;
    }
    int32_t pattern = 0x0000ffff;
    int32_t wordanded = (word & pattern);

    return wordanded;
}


// lê meia palavra, 16 bits- retorna inteiro sem sinal
int32_t lhu(uint32_t *address, uint16_t kte){
    uint32_t pos = (*address + kte)/4;
    uint32_t res = (*address + kte)%4;
    int32_t word = mem[pos];
    if (res>1){
        word = word>>16;
    }
    int32_t pattern = 0x0000ffff;
    int32_t wordanded = (word & pattern);

    return wordanded;
}



// escreve um inteiro alinhado na memória - endereços múltiplos de 4
void sw(uint32_t address, int16_t kte, int32_t dado){
    int pos = (address + kte)/4;
    mem[pos] = dado;
}

// escreve um byte na memória
void sb(uint32_t *address, int16_t kte, int32_t dado){
    int pos = (*address + kte)/4;
    int res = (*address + kte)%4;

    if (res==1){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<8;
        mem[pos] = mem[pos]&0xffff00ff;
        mem[pos] = mem[pos]|dado32bits;

    }else if(res == 2){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<16;
        mem[pos] = mem[pos]&0xff00ffff;
        mem[pos] = mem[pos]|dado32bits;
    }else if(res == 3){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<24;
        mem[pos] = mem[pos]&0x00ffffff;
        mem[pos] = mem[pos]|dado32bits;
    }else{
        mem[pos] = mem[pos]&0xffffff00;
        mem[pos] = mem[pos]|dado;
    }
}

//  escreve meia palavra, 16 bits - endereços múltiplos de 2
void sh(uint32_t *address, int16_t kte, int32_t dado){
    int pos = (*address + kte)/4;
    int res = (*address + kte)%4;
    if (res>1){
        int32_t dado32bits = dado;
        dado32bits = dado32bits<<16;
        mem[pos] = mem[pos]&0x0000ffff;
        mem[pos] = mem[pos]|dado32bits;

    }else{
        mem[pos] = mem[pos]&0xffff0000;
        mem[pos] = mem[pos]|dado;
    }
}

int main(int argc, char const *argv[])
{
	int32_t dado;

    for(i = 0; i < MEM_SIZE; i++)
        mem[i] = 0;

    FILE * _TEXT, * _DATA;     //DECLARAÇÃO DE PONTEIROS PARA VARIÁVEIS DO TIPO FILE

    _TEXT = fopen(argv[1],"rb");        //ABRE O ARQUIVO text.bin PARA LEITURA BINÁRIA E USA UM APONTADOR _TEXT PARA MANIPULAR O ARQUIVO
    _DATA = fopen(argv[2],"rb");        //ABRE O ARQUIVO data.bin PARA LEITURA BINÁRIA E USA UM APONTADOR _DATA PARA MANIPULAR O ARQUIVO

    POSICAO_NA_MEMORIA_TEXT = &mem[ENDERECO_TEXT];      //APONTA O APONTADOR DE SEGMENTO DE TEXTO DO PROGRAMA PARA A REGIÃO TEXT DA MEMÓRIA
    POSICAO_NA_MEMORIA_DATA = &mem[ENDERECO_DATA/32];      //APONTA O APONTADOR DE SEGMENTO DE DADOS DO PROGRAMA PARA A REGIÃO DATA DA MEMÓRIA

    i=0;
    while(!feof(_TEXT))     //CONDICÃO DE PARADA DA LEITURA DO ARQUIVO >> ENQUANTO O ARQUIVO NÃO CHEGAR AO FIM
    {
        fread(&dado,sizeof(int32_t),1,_TEXT);

        sw(ENDERECO_TEXT+(4*i),0,dado);
        i++;
        POSICAO_NA_MEMORIA_TEXT++;
    }

    i=0;
    while(!feof(_DATA))     //CONDICÃO DE PARADA DA LEITURA DO ARQUIVO >> ENQUANTO O ARQUIVO NÃO CHEGAR AO FIM
    {
        fread(&dado,sizeof(uint32_t),1,_DATA);

        sw((i*4),(4*(ENDERECO_DATA/32)),dado);
        i++;
        POSICAO_NA_MEMORIA_DATA++;
    }

    pc = &mem[ENDERECO_TEXT];

    int fim_text = POSICAO_NA_MEMORIA_TEXT - &mem[ENDERECO_TEXT];
    int fim_data = POSICAO_NA_MEMORIA_DATA - &mem[ENDERECO_DATA/32];

    cout << "Segmento TEXT" << endl;
    cout << "Endereço  --  Code" << endl;
    cout.fill('0');
    for(i=0;i<fim_text;i++)
    {
    	cout << "Ox" << setw(8) << hex << ENDERECO_TEXT+(4*i) << " - ";
    	cout << "0x" << setw(8) << hex << lw(0,ENDERECO_TEXT+(4*i)) << endl;
    }

    cout << dec << endl;

    cout << "Fim segmento TEXT" << endl;

    cout << "Segmento DATA" << endl;
    cout << "Endereço  --  Value(0+) -- Value(+4) -- Value(+8) -- Value(+c) -- Value(+10)--Value(+14)-- Value(+18)-- Value(+1c)" << endl;
    int k;
    for(i=ENDERECO_DATA/32, k=0;i<fim_data;i = i+8, k = k+8)
    {
    	cout << "0x" << setw(8) << hex << (ENDERECO_DATA+(0x20*((i-ENDERECO_DATA/32)/8)));
    	for(int j=0;j<8;j++)
    		cout << " - " << "0x" << setw(8) << hex << lw((4*j)+(k*4),(4*(ENDERECO_DATA/32)));

    	cout << endl;
    }

    cout << "Fim do segmento DATA" << endl;
    fclose(_TEXT);          //FECHA O ARQUIVO BINARIO text.bin
    fclose(_DATA);          //FECHA O ARQUIVO BINARIO data.bin
    return 0;

}
