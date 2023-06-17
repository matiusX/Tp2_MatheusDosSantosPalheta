#ifndef B_PLUS_TREE_INT_HPP
#define B_PLUS_TREE_INT_HPP

#include <string>
#include <stdio.h>

using namespace std;

#define BLOCK_SIZE 4096
#define M 255

typedef struct node{
	int n;
	bool is_leaf;
	int keys[2*M];
	int pointers[2*M+1];
  int my_pointer;
}node_t;

typedef struct b_plus_tree{
	int next_block;
  int root_pointer;
  string index_file_name;
	FILE* index_file;
	node_t* root;
}b_plus_tree_t;

typedef struct entry{
	int key; // chave a ser inserida
	int pointer; // apontador do bloco que contém 'key' no arquivo de dados
}entry_t;

node_t* create_node(bool is_leaf, int my_pointer);
b_plus_tree_t* create_b_plus_tree(string index_file);
bool dump_b_plus_tree(b_plus_tree_t* tree, string dump_file_name);
b_plus_tree_t* load_b_plus_tree(string dump_file_name, string index_file_name);
void insert_entry(b_plus_tree_t* tree, entry_t entry);
int search_key(b_plus_tree_t* tree, int key);
void show_summary_of_tree_in_order(b_plus_tree_t* tree);
bool is_entry_null(entry_t entry);

#endif