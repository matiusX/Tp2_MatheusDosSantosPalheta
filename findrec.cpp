#include "hash.hpp"
#include "header.hpp"
int main(int argc, char* argv[]){
    int id = atoi(argv[1]);
    FILE* arquivo = fopen("reg.txt", "r");
    fseek(arquivo,0,SEEK_END);
    int pos = ftell(arquivo)/TAM_BLOCO;
    if(pos < 0){return 1;}
    fclose(arquivo);
    pair<int,int> par = get_bucket(id);
    arquivo = fopen("reg.txt", "r");
    int err = fseek(arquivo,par.first*TAM_BLOCO,SEEK_SET);
    if(err){return 1;}
    bloco_t bloco;
    err = fread(&bloco, TAM_BLOCO, 1, arquivo);
    if(err != 1){return 1;}
    for(int i = 0; i < QNT_REGISTROS_POR_BLOCO; i++){
        if(bloco.regs[i].id == id){
        std::cout << "Registro encontrado:" << std::endl;
        std::cout << "ID: " << bloco.regs[i].id << std::endl;
        std::cout << "Titulo: " << bloco.regs[i].titulo << std::endl;
        std::cout << "Ano: " << bloco.regs[i].ano << std::endl;
        std::cout << "Autores: " << bloco.regs[i].autores << std::endl;
        std::cout << "Citacoes: " << bloco.regs[i].citacoes << std::endl;
        std::cout << "Atualizacao: " << bloco.regs[i].atualizacao << std::endl;
        std::cout << "Snippet: " << bloco.regs[i].snippet << std::endl;
    }}
    
}