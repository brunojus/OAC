//Bruno Justino Garcia Praciano - 13/0006912
#include "funcoes.c"


int main(){
    FILE *arquivoData;
    FILE *arquivoText;

    uint32_t endereco = 0;
    int indice = 0;

    for(endereco = 0; endereco < MEM_SIZE; endereco++){
        mem[endereco] = 0;
    }

    for(indice = 0; indice < 32; indice++){
        reg[indice] = 0;
    }

    arquivoData = fopen("data.bin", "rb");
    if(arquivoData == NULL){
        perror("Erro ao abrir o arquivo de dados");
        exit(-1);
    }

    arquivoText = fopen("text.bin", "rb");
    if(arquivoText == NULL){
        perror("Erro ao abrir o arquivo de instruções");
        exit(-1);
    }

    loadData(arquivoData);

    loadText(arquivoText);

    menu();

    fclose(arquivoData);
    fclose(arquivoText);

    return 0;
}
