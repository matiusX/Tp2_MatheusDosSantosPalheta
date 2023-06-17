#include "b+tree/b+tree_str.hpp"
#include <string.h>

#define RECORD_BLOCK 2

typedef b_plus_tree_str_t b_plus_tree_s_t;

typedef struct record{
    int id, ano, citacoes;
    char titulo[301], autores[151], atualizacao[20], snippet[1025];
}record_t;

typedef struct block{
    record_t records[RECORD_BLOCK];
    char unused[1070]; 
}block_t;

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Erro: indique um titulo para buscar.\nEx: ./seek2 titulo_completo_entre_aspas\n");
        return 1;
    }
    string titulo = argv[1];
    FILE* arq = fopen("B+TREE_STR.txt", "r");
    fseek(arq,0,SEEK_END);
    int pos = ftell(arq)/BLOCK_SIZE;
    if(pos < 0){
        printf("Erro de Leitura: número de posições no arquivo menor do que zero\n");
        return 1;
    }
    fclose(arq);
    string a = "B+TREE_STR.dump";
    string b = "B+TREE_STR.txt";
    b_plus_tree_s_t* tree = load_b_plus_tree_str(a, b);
    int r = search_key(tree,titulo);
    if(r!=-1){
        printf("Quantidade de blocos no arquivo de dados: %d\n", pos);
        record_t result;
        result.id = -1;
        arq = fopen("records.txt", "r");
        int err = fseek(arq,r*BLOCK_SIZE,SEEK_SET);
        if(err){
            printf("Erro: retorno inválido do fseek.\n");
            return 1;
        }
        block_t bloco;
        err = fread(&bloco, BLOCK_SIZE, 1, arq);
        if(err != 1){
            printf("Erro ao ler o arquivo.\n");
            return 1;
        }
        for(int i = 0; i < RECORD_BLOCK; i++){
            if(string(bloco.records[i].titulo).compare(titulo)>=-1 && string(bloco.records[i].titulo).compare(titulo)<=1) {
                printf("Registro encontrado:\nID: %d\nTitulo: %s\nAno: %d\nAutores: %s\nCitacoes: %d\nAtualizacao: %s\nSnippet: %s\n",
                bloco.records[i].id, bloco.records[i].titulo, bloco.records[i].ano, bloco.records[i].autores, bloco.records[i].citacoes, bloco.records[i].atualizacao, bloco.records[i].snippet);
                return 0;
            }
        }
    }
    else{
    printf("Registro não encontrado.\n");
    }
    return 0;
}
