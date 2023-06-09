#ifndef HEADER_HPP
#define HEADER_HPP

#define QNT_REGISTROS_POR_BLOCO 2

typedef struct registro_t{
    int id, ano, citacoes;
    char titulo[301], autores[151], atualizacao[20], snippet[1025];
}registro_t;

typedef struct bloco_t{
    registro_t regs[QNT_REGISTROS_POR_BLOCO];
    char unused[1070];           
}bloco_t;

typedef struct mem_sec_t{
  int proximo, ponteiro;
}mem_sec_t;
#endif