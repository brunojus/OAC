//Bruno Justino Garcia Praciano - 13/0006912
#include "funcoes.h"


void loadData(FILE *ponteiroArquivo){
    uint32_t endereco = 2048;

    while(!feof(ponteiroArquivo)){
        fread(&mem[endereco], sizeof(int32_t), 1, ponteiroArquivo);
        endereco++;
    }
}

void loadText(FILE * ponteiroArquivo){
    uint32_t endereco = 0;

    while(!feof(ponteiroArquivo)){
        fread(&mem[endereco], sizeof(int32_t), 1, ponteiroArquivo);
        endereco++;
    }
}

int32_t lw(uint32_t endereco, int16_t deslocamento){

    if(endereco % 4 != 0 || deslocamento % 4 != 0){
        printf("lw: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 4), erro:\n");
        return -2;
    }

    return mem[(endereco + deslocamento)/4];
}

int32_t lh(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;
    int32_t bitMaisSiginificativo[1];
    int32_t bitMaisSiginificativoAnterior;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("lh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2), erro:\n");
        return -2;
    }


    endereco = endereco / 4;


    palavras = deslocamento / 4;


    novoEndereco = endereco + palavras;

    resto = deslocamento % 4;

    bitMaisSiginificativo[0] = mem[novoEndereco] & 0x0000f000;
    bitMaisSiginificativo[1] = mem[novoEndereco] & 0xf0000000;

    anterior = novoEndereco - 1;

    bitMaisSiginificativoAnterior = mem[anterior] & 0xf0000000;

    if(resto == 0){
        if(bitMaisSiginificativo[0] >= 0x00008000){
            return (mem[novoEndereco] | 0xffff0000);
        }
        return (mem[novoEndereco] & 0x0000ffff);
    }

    if(resto == 2){
        if(bitMaisSiginificativo[1] >= 0x80000000){
            return ((mem[novoEndereco] >> 16) | 0xffff0000);
        }
        return ((mem[novoEndereco] >> 16) & 0x0000ffff);
    }
    if(resto == -2){
        if(bitMaisSiginificativoAnterior >= 0x80000000){
            return ((mem[anterior]  >> 16) | 0xffff0000);
        }
        return ((mem[anterior]  >> 16) & 0x0000ffff);
    }
}
int32_t lb(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;
    int32_t bitMaisSiginificativo[3];
    int32_t bitMaisSiginificativoAnterior[2];


    endereco = endereco / 4;

    palavras = deslocamento / 4;

    novoEndereco = endereco + palavras;

    resto = deslocamento % 4;

    bitMaisSiginificativo[0] = mem[novoEndereco] & 0x000000f0;
    bitMaisSiginificativo[1] = mem[novoEndereco] & 0x0000f000;
    bitMaisSiginificativo[2] = mem[novoEndereco] & 0x00f00000;
    bitMaisSiginificativo[3] = mem[novoEndereco] & 0xf0000000;

    anterior = novoEndereco - 1;

    bitMaisSiginificativoAnterior[0] = mem[anterior] & 0xf0000000;
    bitMaisSiginificativoAnterior[1] = mem[anterior] & 0x00f00000;
    bitMaisSiginificativoAnterior[2] = mem[anterior] & 0x0000f000;

    if(resto == 0){

        if(bitMaisSiginificativo[0] >= 0x00000080){
            return (mem[novoEndereco] | 0xffffff00);
        }

        return (mem[novoEndereco] & 0x000000ff);
    }

    if(resto == 1){
        if(bitMaisSiginificativo[1] >= 0x00008000){
            return ((mem[novoEndereco] >> 8) | 0xffffff00);
        }
        return ((mem[novoEndereco] >> 8) & 0x000000ff);
    }
    if(resto == -1){
        if(bitMaisSiginificativoAnterior[0] >= 0x80000000){
            return ((mem[anterior] >> 24) | 0xffffff00);
        }
        return ((mem[anterior] >> 24) & 0x000000ff);
    }
    if(resto == 2){
        if(bitMaisSiginificativo[2] >= 0x00800000){
            return ((mem[novoEndereco] >> 16) | 0xffffff00);
        }
        return ((mem[novoEndereco] >> 16) & 0x000000ff);
    }
    if(resto == -2){
        if(bitMaisSiginificativoAnterior[1] >= 0x00800000){
            return ((mem[anterior] >> 16) | 0xffffff00);
        }
        return ((mem[anterior] >> 16) & 0x000000ff);
    }

    if(resto == 3){
        if(bitMaisSiginificativo[3] >= 0x80000000){
            return ((mem[novoEndereco] >> 24) | 0xffffff00);
        }
        return ((mem[novoEndereco] >> 24) & 0x000000ff);
    }
    if(resto == -3){
        if(bitMaisSiginificativoAnterior[2] >= 0x00008000){
            return ((mem[anterior] >> 8) | 0xffffff00);
        }
        return ((mem[anterior] >> 8) & 0x000000ff);
    }
}

int32_t lhu(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("lh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2), erro:\n");
        return -2;
    }
    endereco = endereco / 4;
    palavras = deslocamento / 4;
    novoEndereco = endereco + palavras;
    resto = deslocamento % 4;
    if(resto == 0){
        return (mem[novoEndereco] & 0x0000ffff);
    }
    if(resto == 2){
        return ((mem[novoEndereco] >> 16) & 0x0000ffff);
    }
    if(resto == -2){
        return ((mem[novoEndereco-1] >> 16) & 0x0000ffff);
    }
}
int32_t lbu(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;


    endereco = endereco / 4;

    palavras = deslocamento / 4;

    novoEndereco = endereco + palavras;

    resto = deslocamento % 4;

    if(resto == 0){
        return (mem[novoEndereco] & 0x000000ff);
    }

    if(resto == 1){
        return ((mem[novoEndereco] >> 8) & 0x000000ff);
    }
    if(resto == -1){
        return ((mem[novoEndereco-1] >> 24) & 0x000000ff);
    }

    if(resto == 2){
        return ((mem[novoEndereco] >> 16) & 0x000000ff);
    }

    if(resto == -2){
        return ((mem[novoEndereco-1] >> 16) & 0x000000ff);
    }

    if(resto == 3){
        return ((mem[novoEndereco] >> 24) & 0x000000ff);
    }
    if(resto == -3){
        return ((mem[novoEndereco-1] >> 8) & 0x000000ff);
    }
}

void sw(uint32_t endereco, int16_t deslocamento, int32_t dado){

    if(endereco % 4 != 0 || deslocamento % 4 != 0){
        printf("sw: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 4)\n");
        return;
    }

    endereco = endereco / 4;

    mem[endereco + (deslocamento/4)] = dado;
}
void sh(uint32_t endereco, int16_t deslocamento, int16_t dado){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("sh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2)\n");
        return;
    }
    endereco = endereco / 4;

    palavras = deslocamento / 4;
    novoEndereco = endereco + palavras;
    resto = deslocamento % 4;
    anterior = novoEndereco - 1;
    if(resto == 0){
        mem[novoEndereco] = (dado & 0x0000ffff) | (mem[novoEndereco] & 0xffff0000);
    }

    if(resto == 2){
        mem[novoEndereco] = ((dado & 0x0000ffff) << 16) | (mem[novoEndereco] & 0x0000ffff);
    }


    if(resto == -2){
        mem[anterior] = ((dado & 0x0000ffff) << 16) | (mem[anterior] & 0x0000ffff);
    }
}


void sb(uint32_t endereco, int16_t deslocamento, int8_t dado){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;

    endereco = endereco / 4;

    palavras = deslocamento / 4;

    novoEndereco = endereco + palavras;

    resto = deslocamento % 4;

    anterior = novoEndereco - 1;

    if(resto == 0){
        mem[novoEndereco] = (dado & 0x000000ff) | (mem[novoEndereco] & 0xffffff00);
    }


    if(resto == 1){
        mem[novoEndereco] = ((dado & 0x000000ff) << 8) | (mem[novoEndereco] & 0xffff00ff);
    }


    if(resto == -1){
        mem[anterior] = ((dado & 0x000000ff) << 24) | (mem[anterior] & 0x00ffffff);
    }


    if(resto == 2){
        mem[novoEndereco] = ((dado & 0x000000ff) << 16) | (mem[novoEndereco] & 0xff00ffff);
    }


    if(resto == -2){
        mem[anterior] = ((dado & 0x000000ff) << 16) | (mem[anterior] & 0xff00ffff);
    }


    if(resto == 3){
        mem[novoEndereco] = ((dado & 0x000000ff) << 24) | (mem[novoEndereco] & 0x00ffffff);
    }


    if(resto == -3){
        mem[anterior] = ((dado & 0x000000ff) << 8) | (mem[anterior] & 0xffff00ff);
    }
}


void menu (){
    int escolha = 0;
    uint32_t endereco = 0;
    uint32_t inicio, fim;
    char formato;

    do{
        printf("\n\n/**************SIMULADOR ASSEMBLER MIPS**************/\n\n");
        printf("(1) - Dump Memory\n");
        printf("(2) - Dump All Memory\n");
        printf("(3) - Step by Step\n");
        printf("(4) - Dump Registers\n");
        printf("(5) - Run\n");
        printf("(0) - Exit\n");
        printf("------------------------------------------------------\n");

        printf("Digite um valor correspondente a um opcao no menu: ");
        scanf("%d", &escolha);

        /* Dump Memory */
        if(escolha == 1){
            printf("\n");

            printf("\nDigite o endereco inicial em hexadecimal: ex:(00000000)");
            scanf("%" SCNd32, &inicio);

            printf("\nDigite o endereco final em hexadecimal: ex: (00000001)");
            scanf("%" SCNd32, &fim);

            getchar();
            printf("\nDigite o formato da exibicao: d-para decimal e h para hexadecimal ");
            scanf("%c", &formato);

            dump_mem((inicio/4), (fim/4), formato);
        }

        /* Dump All Memory */
        else if(escolha == 2){
            printf("\n");

            for(endereco = 0; endereco < MEM_SIZE; endereco++){
                if(mem[endereco] != 0){
                    printf("Address [0x%.8x] = 0x%.8x\n", endereco*4, mem[endereco]);
                }
            }
        }

        /* Step by Step */
        else if(escolha == 3){
            printf("\nDump Step:");

            printf("\nSaida no terminal = ");
            step();

            printf("\nInstrução atual = 0x%.8x\n", ri);
            printf("opcode = 0x%.8x\n", opcode);
            printf("rs = 0x%.8x\n", rs);
            printf("rt = 0x%.8x\n", rt);
            printf("rd = 0x%.8x\n", rd);
            printf("shamt = 0x%.8x\n", shamt);
            printf("funct = 0x%.8x\n", funct);
            printf("k16 = 0x%.8x\n", k16);
            printf("k26 = 0x%.8x\n", k26);

            dump_reg('x');
        }


        else if(escolha == 4){
            getchar();
            printf("\nDigite o formato da exibicao: ");
            scanf("%c", &formato);

            dump_reg(formato);
        }


        else if(escolha == 5){
            pc = 0;
            run();
        }

    }while(escolha != 0);

}

void fetch(uint32_t endereco){

    ri = mem[endereco];

    pc = endereco + 1;
}


void decode(){

    opcode = ri >> 26;

    rs = ri << 6;

    rs = rs >> 27;

    rt = ri << 11;

    rt = rt >> 27;

    rd = ri << 16;

    rd = rd >> 27;



    shamt = ri << 21;

    shamt = shamt >> 27;

    funct = ri << 26;

    funct = funct >> 26;

    k16 = ri << 16;

    k16 = k16 >> 16;

    k26 = ri << 6;

    k26 = k26 >> 6;


}

void execute(){
    if(opcode == LW){
        reg[rt] = lw(reg[rs], k16);
    }

    if(opcode == LB){
        reg[rt] = lb(reg[rs], k16);
    }

    if(opcode == LBU){
        reg[rt] = lbu(reg[rs], k16);
    }

    if(opcode == LH){

        reg[rt] = lh(reg[rs], k16);
    }

    if(opcode == LHU){

        reg[rt] = lhu(reg[rs], k16);
    }

    if(opcode ==  LUI){

        reg[rt] = k16 << 16;
    }

    if(opcode == SW){

        sw(reg[rs],k16,reg[rt]);
    }

    if(opcode == SB){

        sb(reg[rs],k16,reg[rt]);
    }

    if(opcode == SH){

        sh(reg[rs],k16,reg[rt]);
    }

    if(opcode == BEQ){

        if(reg[rs] == reg[rt]){
            pc = pc + k16;
        }
    }

    if(opcode == BNE){

        if(reg[rs] != reg[rt]){
            pc = pc + k16;
        }
    }

    if(opcode == BLEZ){

        if(reg[rs] <= 0){
            pc = pc + k16;
        }
    }

    if(opcode == BGTZ){

        if(reg[rs] > 0){
            pc = pc + k16;
        }
    }

    if(opcode == ADDI){

        reg[rt] = reg[rs] + k16;
    }

    if(opcode == SLTI){

        reg[rt] = (reg[rs] < k16) ? 1 : 0;
    }

    if(opcode == SLTIU){

        reg[rt] = (reg[rs] < (uint32_t)k16) ? 1 : 0;
    }

    if(opcode == ANDI){

        reg[rd] = reg[rs] & k16;
    }

    if(opcode == ORI){

        reg[rt] = reg[rs] | k16;
    }

    if(opcode == XORI){

        reg[rt] = reg[rs] ^ k16;
    }

    if(opcode == ADDIU){
        reg[rt] = reg[rs] + k16;
    }


    if(opcode == J){
        pc = k26;
    }

    if(opcode == JAL){
        reg[31] = pc;
        pc = k26;
    }

    if(opcode == EXT){

        if(funct == ADD){
            reg[rd] = reg[rs] + reg[rt];
        }

        if(funct == SUB){
            reg[rd] = reg[rs] - reg[rt];
        }

        if(funct == MULT){
            int64_t temporario;

            temporario = reg[rs] * reg[rt];

            hi = (temporario & 0x1111111100000000) >> 32;
            lo = temporario & 0x0000000011111111;
        }

        if(funct == DIV){
            /* Div */
            lo = reg[rs] / reg[rt];
            hi = reg[rs] % reg[rt];
        }

        if(funct == AND){
            reg[rd] = reg[rs] & reg[rt];
        }

        if(funct == OR){
            reg[rd] = reg[rs] | reg[rt];
        }

        if(funct == XOR){
            reg[rd] = reg[rs] ^ reg[rt];
        }

        if(funct == NOR){
            reg[rd] = ~(reg[rs] | reg[rt]);
        }

        if (funct == SLT){
            reg[rd] = (reg[rs] < reg[rt]) ? 1 : 0;
        }

        if(funct == JR){
            pc = reg[rs];
        }

        if(funct == SLL){
            reg[rd] = reg[rt] << shamt;
        }

        if(funct == SRL){
            reg[rd] = (uint32_t)reg[rt] >> shamt;
        }

        if(funct == SRA){
            reg[rd] = reg[rt] >> shamt;
        }

        if(funct == SYSCALL){
            if(reg[2] == 1){
                printf("%d", reg[4]);
            }

            if(reg[2] == 4){
                uint32_t endereco = reg[4]/4;

                char *caracter;

                caracter = (char *)&(mem[endereco]);

                caracter += reg[4] % 4;
                do{
                    printf("%c", *caracter);
                    caracter++;
                }while(*caracter != '\0');
            }

            if(reg[2] == 10){
                printf("\n-- program is finished running --\n");

                dump_reg('x');

                exit(EXIT_SUCCESS);
            }

        }

        if(funct == MFHI){
            reg[rd] = hi;
        }

        if(funct == MFLO){
            reg[rd] = lo;
        }

    }
}

void step(){

    fetch(pc);
    decode();
    execute();

}

void run(){
    uint32_t indice = 0;

    while(indice < MEM_SIZE){
        reg[0] = 0;

        step();
        indice++;
    }
}
void dump_mem(uint32_t start, uint32_t end, char format){
    uint32_t indice;

    printf("\nDump Memory:\n");
    for(indice = start; indice <= end; indice++){
        if(format == 'd'){
            printf("Address [0x%.8x] = %d\n", indice*4, mem[indice]);
        }

        else{
            printf("Address [0x%.8x] = 0x%.8x\n", indice*4, mem[indice]);
        }
    }
}

void dump_reg(char format){
      uint32_t indice;

    if(format == 'd'){
        printf("\nDump Registers:\n");

        for(indice = 0; indice < 32; indice++){
            if(indice == 31){
                printf("reg[%d] = %d\n", indice, reg[indice]*4);
            }
            else{
                printf("reg[%d] = %d\n", indice, reg[indice]);
            }
        }

        printf("pc = %d\n", pc*4);
        printf("hi = %d\n", hi);
        printf("lo = %d\n", lo);
    }

    else{
        printf("\nDump Registers:\n");

        for(indice = 0; indice < 32; indice++){
            if(indice == 31){
                printf("reg[%d] = 0x%.8x\n", indice, reg[indice]*4);
            }
            else{
                printf("reg[%d] = 0x%.8x\n", indice, reg[indice]);
            }
        }

        printf("pc = 0x%.8x\n", pc*4);
        printf("hi = 0x%.8x\n", hi);
        printf("lo = 0x%.8x\n", lo);
    }
}
