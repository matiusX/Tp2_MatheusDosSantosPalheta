#include "hash.hpp"
#include "header.hpp"
#include <stdio.h>
#include <stdlib.h>
int num_blocos = 0;
string arquivo_auxiliar = "hash_aux.txt";
string hash_principal = "hash_table.txt";

bucket_t* le_bucket(int ponteiro) {
    if (ponteiro == -1) {
        return NULL;
    }
    FILE* arquivo = fopen(arquivo_auxiliar.c_str(), "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo_auxiliar.c_str());
        return NULL;
    }

    int erro = fseek(arquivo, ponteiro * TAM_BLOCO, SEEK_SET);
    if (erro != 0) {
        printf("erro no fseek.\n");
        fclose(arquivo);
        return NULL;
    }

    bucket_t* bucket_aux = (bucket_t*)malloc(sizeof(bucket_t));
    if (bucket_aux == NULL) {
        printf("nao deu p alocar na memoria.\n");
        fclose(arquivo);
        return NULL;
    }

    erro = fread(bucket_aux, sizeof(bucket_t), 1, arquivo);
    if (erro != 1) {
        printf("nao deu p ler o arquivo\n");
        free(bucket_aux);
        fclose(arquivo);
        return NULL;
    }

    fclose(arquivo);
    return bucket_aux;
}

void adiciona_el_bk(bucket_t* n, int chave_valor, int item_valor){
	if(n->posicao == TAM){
		bucket_t* aux = n;
		int aux_next = n->proximo;
		while(aux_next != -1){
			aux = le_bucket(aux_next);
			if(aux->posicao == TAM) aux_next = aux->proximo;
			else break;
		}

		if(aux->posicao == TAM){
			FILE* arq = fopen(arquivo_auxiliar.c_str(),"r+");
			int err = fseek(arq, 0, SEEK_END);

			if(err){
				printf("A pesquisa nao retornou resultados.\n");
				fclose(arq);
				return; 

			}else{
				err = ftell(arq);

				if(err == -1){return;}
				else{
					int npos = err/TAM_BLOCO;
					aux->proximo = npos;
					bucket_t* novo_bucket = (bucket_t*) malloc(sizeof(bucket_t));
					novo_bucket->posicao = 0;
					novo_bucket->elemento = npos;
					novo_bucket->proximo = -1;					

					for(int i = 0; i < TAM; i++){
						novo_bucket->chave[i] = -1;
						novo_bucket->item[i] = -1;
					}

					adiciona_el_bk(novo_bucket, chave_valor, item_valor);
					int err = fseek(arq, aux->elemento*TAM_BLOCO, SEEK_SET);
					
					if(err){
						printf("Erro: retorno inválido do fseek 3.\n");
						fclose(arq);
						return;
					
					}else{
						int err = fwrite(aux,TAM_BLOCO,1, arq);
						fclose(arq);

						if(err == 0){
							printf("Erro: Não foi possível salvar o arquivo 1.\n");
						}
					}
				}
			}

		}else{
			adiciona_el_bk(aux, chave_valor, item_valor);
		}
	}

	else if(n->posicao < TAM-1){
		n->chave[n->posicao] = chave_valor;
		n->item[n->posicao]= item_valor;
		n->posicao++;
		FILE* arq = fopen("hash_aux.txt","r+");
		int err = fseek(arq, n->elemento*TAM_BLOCO, SEEK_SET);
		if(err){
			printf("Erro: retorno inválido do fseek 4.\n");
			fclose(arq);
			return; 
		}else{
			err = fwrite(n, TAM_BLOCO, 1,arq);
			fclose(arq);
			if(!err){
				printf("Erro: Não foi possível salvar o arquivo 2.\n");
			}
		}	
	}
}

pair<int, int> get_registro(bucket_t* n, int chave_valor){
	bucket_t* aux = n;
	int qnt_blocos_lidos = 0;
	while(aux != NULL){ //procurando em uma lista de buckets
		for(int i = 0; i < aux->posicao; i++){
			if(chave_valor == aux->chave[i]) return pair<int, int> (aux->item[i],qnt_blocos_lidos);
		}
		aux = le_bucket(aux->proximo);
		qnt_blocos_lidos++;
	}
	return pair<int,int> (-1,qnt_blocos_lidos);
}

int cria_bucket(){
    FILE* arq = fopen("hash_aux.txt","r+");
    int err = fseek(arq, 0, SEEK_END);
    int prox_bloco = ftell(arq)/TAM_BLOCO;
	bucket_t* bucket_aux = (bucket_t*) malloc(sizeof(bucket_t));
	bucket_aux->posicao = 0;
	bucket_aux->elemento = prox_bloco;
	bucket_aux->proximo = -1;					
	for(int i = 0; i < TAM; i++){
		bucket_aux->chave[i] = -1;
		bucket_aux->item[i] = -1;
	}
    err = fwrite(bucket_aux,TAM_BLOCO,1,arq);
    fclose(arq);
    free(bucket_aux);
    return prox_bloco;
}

int funcao_hash(int key) {
    const double A = 0.6180339887;  // Constante recomendada para hashing por multiplicação
    double hash_value = key * A;
    hash_value -= static_cast<int>(hash_value);  // Obtém a parte fracionária do resultado
    int hash_index = static_cast<int>(hash_value * (num_blocos * MAX));
    return hash_index;
}

void new_table(){   
    FILE* arq = fopen("hash_table.txt","r+");
    int err = fseek(arq,0,SEEK_END);
    hash_bloco_t n;
    for(int i = 0; i < MAX;i++){
        n.elementos[i] = -1;
    }
    n.flag = 0;
    err = fwrite(&n, TAM_BLOCO, 1,arq);
    fclose(arq);
    if(err != 1){
        printf("Erro: Não foi possível salvar o arquivo 1.\n");
        return;
    }
}

hash_bloco_t* read_table(int pos){
    FILE* arq = fopen("hash_table.txt","r");
    int err = fseek(arq, pos*TAM_BLOCO, SEEK_SET);
    if(err){
        printf("Erro: retorno inválido do fseek.\n");
        return NULL;
    }
    hash_bloco_t* t = (hash_bloco_t*) malloc(sizeof(hash_bloco_t));
    err = fread(t,TAM_BLOCO,1,arq);
    fclose(arq);
    if(err != 1) printf("Erro ao ler o arquivo.\n");
    return t;
}

void adiciona_chave_hash(int key, int value){
    if(num_blocos == 0){
        FILE* arq = fopen(hash_principal.c_str(),"r");
		int err = fseek(arq,0,SEEK_END);
		num_blocos = ftell(arq)/TAM_BLOCO;
		fclose(arq);
        if(num_blocos == 0){
            new_table();
			FILE* arq = fopen(hash_principal.c_str(),"r");
			int err = fseek(arq,0,SEEK_END);
			num_blocos = ftell(arq)/TAM_BLOCO;
        } 
    }
    int pos = funcao_hash(key);
    int bpos = pos%MAX;
    pos-=bpos;
    int tpos = pos/MAX;
    hash_bloco_t* t = read_table(tpos);
    int node_pos = t->elementos[bpos];
    if(node_pos == -1){
        node_pos = cria_bucket();
        t->elementos[bpos] = node_pos;
        t->flag++;
		FILE* arq = fopen(hash_principal.c_str(),"r+");
		int err = fseek(arq, tpos*TAM_BLOCO, SEEK_SET);
		err = fwrite(t, TAM_BLOCO, 1,arq);
		fclose(arq);
    }
    bucket_t* b = le_bucket(node_pos);
    adiciona_el_bk(b, key, value);
}

pair<int,int> get_bucket(int key){
    if(num_blocos == 0){
        FILE* arq = fopen(hash_principal.c_str(),"r");
		int err = fseek(arq,0,SEEK_END);
		num_blocos = ftell(arq)/TAM_BLOCO;
        if(num_blocos == 0){
            printf("Erro: tabela está vazia.\n");
            return pair<int,int> (-1,-1);
        } 
    }
    int read_blocks = 0;
    int pos = funcao_hash(key);
    int bpos = pos%MAX;
    pos-=bpos;
    int tpos = pos/MAX;
    
    hash_bloco_t* t = read_table(tpos);
    read_blocks++;
    int node_pos = t->elementos[bpos];
    if(node_pos == -1) return pair<int,int> (-1, read_blocks);
    bucket_t* b = le_bucket(node_pos);
    read_blocks++;
    pair<int,int> result = get_registro(b,key);
    return pair<int,int> (result.first, result.second + read_blocks);
}

void inicia_hash(int tam){
    FILE* arq = fopen(hash_principal.c_str(),"w");
    fclose(arq);
    num_blocos = ((int) tam/MAX +1) * MAX;
    for(int i = 0; i < num_blocos; i++) {
        new_table();
    }
	
	FILE* file = fopen(arquivo_auxiliar.c_str(),"w");
    fclose(file);
}