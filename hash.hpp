#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#define TAM_BLOCO 4096
#define TAM 510
using namespace std; 
#define MAX 1023 //serve p 20k

typedef struct bucket_t{
	int chave[TAM];
	int item[TAM];
	int elemento;
	int proximo;
    int espaco;
	int posicao;
}bucket_t;

int cria_bucket();
bucket_t* le_bucket(int pointer);
void adiciona_el_bk(bucket_t* n, int aKey, int aValue);
pair<int, int> get_registro(bucket_t* n, int aKey);
void limpa_arquivo();


typedef struct hash_bloco_t{
    int elementos[MAX];
    int flag;
}hash_bloco_t;

void inicia_hash(int tam);
void adiciona_chave_hash(int key, int value);
pair<int,int> get_bucket(int key);

#endif