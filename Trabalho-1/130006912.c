/* Trabalho 1 - SIMULADOR MIPS
Organização e Arquitetura de Computadores - 2/2017
Professor: Ricardo Pezzuol Jacobi
Turma: C

Bruno Justino Garcia Praciano
Matrícula: 13/0006912
*/

#include "mips.h"

int32_t lw(uint32_t address, int16_t kte){
	int32_t aux;

	if((address+kte)%4 != 0){
		printf("\nError. Para 'lw' endereços devem ser múltiplos de 4.\n");
		exit(EXIT_FAILURE);
	}

	aux = (int32_t) mem[(address + kte)/4];

	return aux;
}

int32_t lh(uint32_t address, int16_t kte){
	int32_t aux;

	if((address+kte)%2 != 0){
		printf("\nError. Para 'lh' endereços devem ser múltiplos de 2.\n");
		exit(EXIT_FAILURE);
	}

	if((address+kte)%4 == 0){
		aux = (int32_t) (mem[(address + kte)/4] & 0x0000ffff);
		if(aux >= 0x00008000)
			aux = (int32_t) aux | 0xffff0000;
	}
	else{
		aux = (int32_t) (mem[(address + kte-2)/4] & 0xffff0000);
		if(aux >= 0x80000000)
			aux = (int32_t) aux | 0x0000ffff;
		aux = aux >> 16;
	}

	return aux;
}

int32_t lb(uint32_t address, int16_t kte){
	int32_t aux;

	if((address+kte)%1 != 0){
		printf("\nError. Para 'lb' endereços devem ser múltiplos de 1.\n");
		exit(EXIT_FAILURE);
	}

	if((address+kte)%4 == 0){
		aux = (int32_t) (mem[(address + kte)/4] & 						0x000000ff);
		if(aux >= 0x00000080)
			aux = (int32_t) aux | 0xffffff00;
	}
	else if((address+kte)%4 == 3){
		aux = (int32_t) (mem[(address + kte-3)/4] & 						0xff000000);
		if(aux >= 0x80000000)
			aux = (int32_t) aux | 0x00ffffff;
		aux = aux >> 24;
	}
	else if((address+kte)%2 == 0){
		aux = (int32_t) (mem[(address + kte-2)/4] & 						0x00ff0000);
		if(aux >= 0x00800000)
			aux = (int32_t) aux | 0xff00ffff;
		aux = aux >> 16;
	}
	else{
		aux = (int32_t) (mem[(address + kte-1)/4] & 						0x0000ff00);
		if(aux >= 0x00008000)
			aux = (int32_t) aux | 0xffff00ff;
		aux = aux >> 8;
	}

	return aux;
}

void sw(uint32_t address, int16_t kte, int32_t dado){
	if((address+kte)%4 != 0){
		printf("\nError. Para 'sw' endereços devem ser múltiplos de 4.\n");
		exit(EXIT_FAILURE);
	}

	mem[(address + kte)/4] = (int32_t) dado;
}

void sh(uint32_t address, int16_t kte, int16_t dado){
	int32_t aux1, aux2;

	if((address+kte)%2 != 0){
		printf("\nError. Para 'sh' endereços devem ser múltiplos de 2.\n");
		exit(EXIT_FAILURE);
	}

	if((address+kte)%4 == 0){
		aux1 = (int32_t) mem[(address + kte)/4] & 0xffff0000;
		aux2 = (int32_t) dado & 0x0000ffff;
		mem[(address + kte)/4] = (int32_t) aux1 + aux2;
	}
	else{
		aux1 = (int32_t) mem[(address + kte-2)/4] & 0x0000ffff;
		aux2 = (int32_t) dado & 0x0000ffff;
		aux2 = aux2 << 16;
		mem[(address + kte-2)/4] = (int32_t) aux1 + aux2;
	}
}

void sb(uint32_t address, int16_t kte, int8_t dado){
	int32_t aux1, aux2;

	if((address+kte)%1 != 0){
		printf("\nError. Para 'sb' endereços devem ser múltiplos de 1.\n");
		exit(EXIT_FAILURE);
	}

	if((address+kte)%4 == 0){
		aux1 = (int32_t) mem[(address + kte)/4] & 0xffffff00;
		aux2 = (int32_t) dado & 0x000000ff;
		mem[(address + kte)/4] =
		(int32_t) aux1 + aux2;
	}
	else if((address+kte)%4 == 3){
		aux1 = (int32_t) mem[(address + kte-3)/4] & 0x00ffffff;
		aux2 = (int32_t) dado & 0x000000ff;
		aux2 = aux2 << 24;
		mem[(address + kte-3)/4] =
			(int32_t) aux1 + aux2;
	}
	else if((address+kte)%2 == 0){
		aux1 = (int32_t) mem[(address + kte-2)/4] & 0xff00ffff;
		aux2 = (int32_t) dado & 0x000000ff;
		aux2 = aux2 << 16;
		mem[(address + kte-2)/4] =
			(int32_t) aux1 + aux2;
	}
	else{
		aux1 = (int32_t) mem[(address + kte-1)/4] & 0xffff00ff;
		aux2 = (int32_t) dado & 0x000000ff;
		aux2 = aux2 << 8;
		mem[(address + kte-1)/4] =
			(int32_t) aux1 + aux2;
	}
}

void init(){
	int i;

	for(i = 0; i < 32; i++)
		reg[i] = 0;

	for(i = 0; i < 4096; i++)
		mem[i] = 0;

}

int leitura(FILE *p, int pos){
	int32_t n;
	int i = pos, cont;

	fread(&n,sizeof(int32_t),1,p);
	while(!feof(p)){
		mem[i] = n;
		if(n == 0) {
			cont = 0;
			fread(&n,sizeof(int32_t),1,p);
			while(n == 0 && !feof(p)){
				cont++; i++;
				mem[i] = n;
				fread(&n,sizeof(int32_t),1,p);
			}

			if(cont == 1) printf("0x%08x 0x%08x\n ",
							mem[i-1],mem[i]);
			else{
				if(n == 0)
					printf("{%d repetições de 0x%08x}\n ",
						cont,mem[i]);
				else
					printf("{%d repetições de 0x%08x} 0x%08x\n ", cont,mem[i-1],mem[i]);
			}
		}
		else printf("0x%08x \n",mem[i]);

		i++;
		fread(&n,sizeof(int32_t),1,p);
	}
	printf("\n");

	return (i-pos);
}

void instrExec(int num_instr){
	int i, op, rs, rt, imm, ender;

	printf("\nExecução das instruções:\n");
	for(i = 0; i < num_instr; i++){
		op = mem[i] >> 26 & 0x3f;
		rs = mem[i] >> 21 & 0x1f;
		rt = mem[i] >> 16 & 0x1f;
		imm = mem[i] & 0xffff;

		switch(op){
			case 0:
				printf("Essa é a função Syscall, mas para esse primeiro trabalho não foi implementada\n");
				break;
			case 2:
					printf("Essa é a função J, mas para esse primeiro trabalho não foi implementada\n");
					break;
			case 4:
				printf("Essa é a função BEQ, mas para esse primeiro trabalho não foi implementada\n");
				break;
			case 8:
				printf("Essa é a função ADDI, mas para esse primeiro trabalho não foi implementada\n");
				break;

			case 9:
				printf("Essa é a função ADDIU, mas para esse primeiro trabalho não foi implementada\n");
				break;




			case 32:
				printf("lb $%d,%d($%d)\n",rt,imm,rs);
				reg[rt] = lb(reg[rs],imm);
				printf(">> $%d = 0x%08x\n",rt,reg[rt]);
				break;

			case 33:
				printf("lh $%d,%d($%d)\n",rt,imm,rs);
				reg[rt] = lh(reg[rs],imm);
				printf(">> $%d = 0x%08x\n",rt,reg[rt]);
				break;

			case 35:
				printf("lw $%d,%d($%d)\n",rt,imm,rs);
				reg[rt] = lw(reg[rs],imm);
				printf(">> $%d = 0x%08x\n",rt,reg[rt]);
				break;

			case 41:
				printf("sh $%d,%d($%d)\n",rt,imm,rs);
				sh(reg[rs],imm,reg[rt]);
				ender = (reg[rs] + imm)/4;
				printf(">> mem[$%d+%d] = 0x%08x\n", rs,imm,mem[ender]);
				break;

			case 40:
				printf("sb $%d,%d($%d)\n",rt,imm,rs);
				sb(reg[rs],imm,reg[rt]);
				ender = (reg[rs] + imm)/4;
				printf(">> mem[$%d+%d] = 0x%08x\n", rs,imm,mem[ender]);
				break;

			case 43:
				printf("sw $%d,%d($%d)\n",rt,imm,rs);
				sw(reg[rs],imm,reg[rt]);
				ender = (reg[rs] + imm)/4;
				printf(">> mem[$%d+%d] = 0x%08x\n", rs,imm,mem[ender]);
				break;
		}
		getchar();
	}
	printf("Fim das instruções.\n");
}

void gerarData(){
	int i, cont;
	FILE *dataS;

	dataS = fopen("dataSim.bin", "wb");

	printf("\nData obtida pela simulação:\n");
	for(i = 2048; i < 4096; i++){
		if(mem[i] == 0) {
			cont = 0;
			while(mem[i] == 0 && i < 4096){
				fwrite(&mem[i],sizeof(int32_t),1,dataS);
				cont++; i++;
			}

			if(cont == 1) printf("0x%08x 0x%08x ",
							mem[i-1],mem[i]);
			else{
				if(mem[i] == 0)
					printf("{%d repetições de 0x%08x} ",
						cont,mem[i]);
				else
					printf("{%d repetições de 0x%08x} 0x%08x ", cont,mem[i-1],mem[i]);
			}
		}
		else printf("0x%08x ",mem[i]);

		fwrite(&mem[i],sizeof(int32_t),1,dataS);
	}
	printf("\n");

	fclose(dataS);

	printf("\nRegistradores após a simulação:\n");
	for(i = 0; i < 32; i++){
		if(i < 31) printf("$%d = 0x%08x || ", i, reg[i]);
		else printf("$%d = 0x%08x\n", i, reg[i]);
	}
}

int main(){
	FILE *data, *text;
	int aux;

	init();

	printf("\n\n ---SIMULADOR MIPS--- \n\nAperte 'Enter' para executar cada etapa do programa.\n");
	getchar();

	data = fopen("data.bin", "rb");
	if(!data){
		printf("\nNão foi possível abrir o arquivo data.bin\n");
		return -1;
	}
	printf("Data: \n");
	leitura(data, 2048);
	fclose(data);
	getchar();

	text = fopen("text.bin", "rb");
	if(!text){
		printf("\nNão foi possível abrir o arquivo text.bin\n");
		return -1;
	}
	printf("Text: \n");
	aux = leitura(text, 0);
	fclose(text);
	getchar();

	instrExec(aux);
	getchar();

	gerarData();

	return 0;
}
