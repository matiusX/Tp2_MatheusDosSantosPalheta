#include "hash.hpp"
#include "header.hpp"


int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Erro: indique um id para buscar.\nEx: ./findrec 1\n");
        return 1;
    }
    int id = atoi(argv[1]);
    FILE* arq = fopen("reg.txt", "r");
    fseek(arq,0,SEEK_END);
    int pos = ftell(arq)/TAM_BLOCO;
    if(pos < 0){
        printf("Erro de Leitura: número de posições no arquivo menor do que zero\n");
        return 1;
    }
    fclose(arq);

    pair<int,int> r = get_bucket(id);
    registro_t result;
    result.id = -1;
    printf("Quantidade de blocos lidos: %d\nQuantidade de blocos no arquivo de dados: %d\n", r.second+1,pos);
    arq = fopen("reg.txt", "r");
    int err = fseek(arq,r.first*TAM_BLOCO,SEEK_SET);
    if(err){
        printf("Erro: retorno inválido do fseek.\n");
        return 1;
    }
    bloco_t bloco;
    err = fread(&bloco, TAM_BLOCO, 1, arq);
    if(err != 1){
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }
    for(int i = 0; i < QNT_REGISTROS_POR_BLOCO; i++) if(bloco.regs[i].id == id){
        printf("Registro encontrado:\nID: %d\nTitulo: %s\nAno: %d\nAutores: %s\nCitacoes: %d\nAtualizacao: %s\nSnippet: %s\n",
        bloco.regs[i].id, bloco.regs[i].titulo, bloco.regs[i].ano, bloco.regs[i].autores, bloco.regs[i].citacoes, bloco.regs[i].atualizacao, bloco.regs[i].snippet);
        return 0;
    }

    
}