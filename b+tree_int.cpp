#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string>
#include <cstdio>

#include "b+tree_int.hpp"

using namespace std;


static node_t* add_node_in_tree(b_plus_tree_t* tree, node_t* new_node){
	int err = fseek(tree->index_file, tree->next_block*BLOCK_SIZE, SEEK_SET);
	if(err){
    printf("Erro: retorno inválido do fseek 1.\n");
		return NULL;
	}
	size_t error = fwrite(new_node, BLOCK_SIZE, 1, tree->index_file);
	if(error != 1){
    printf("Erro: Erro: Não foi possível escrever no arquivo 1.\n");
		return NULL;
	}
	tree->next_block++;
	return new_node;
}

static node_t* create_node_in_tree(b_plus_tree_t* tree, bool is_leaf){
	node_t* new_node = create_node(is_leaf, tree->next_block);
	return add_node_in_tree(tree, new_node);
}

b_plus_tree_t* create_b_plus_tree(string index_file_name){
	b_plus_tree_t* tree = new b_plus_tree_t;
  tree->index_file_name = index_file_name;
	tree->index_file = fopen(index_file_name.c_str(), "w");
  if(tree->index_file == NULL){
    printf("Erro: Não foi possível abrir arquivo para escrita 1.\n");
    return NULL;
  }
	tree->next_block = 0;
	tree->root = create_node_in_tree(tree, true);
  tree->root_pointer = 0;
  fclose(tree->index_file);
	return tree;
}


typedef struct dump_data{
  int next_block, root_pointer;
}dump_data_t;


bool dump_b_plus_tree(b_plus_tree_t* tree, string dump_file_name){
  FILE* dump_file = fopen(dump_file_name.c_str(), "w");
  if(dump_file == NULL){
    printf("Erro: Não foi possível abrir arquivo para escrita 2.\n");
    return false;
  }
  int err = fseek(tree->index_file, 0, SEEK_SET);
	if(err){
		printf("Erro: retorno inválido do fseek 2.\n");
    fclose(dump_file);
		return false;
	}
  dump_data_t data = {tree->next_block, tree->root_pointer};
  size_t error = fwrite(&data, sizeof(dump_data_t), 1, dump_file);
  if(error != 1){
    printf("Erro: Não foi possível escrever no arquivo 2.\n");
    fclose(dump_file);
    return false;
  }
  fclose(dump_file);
  return true;
}

static b_plus_tree_t* load_b_plus_tree_helper(dump_data_t* data, string index_file_name){
  FILE* index_file = fopen(index_file_name.c_str(), "r");
  if(index_file == NULL){
    printf("Erro: Não foi possível abrir o arquivo para leitura 1.'\n");
    return NULL;
  }
  int err = fseek(index_file, data->root_pointer*BLOCK_SIZE, SEEK_SET);
  if(err){
    printf("Erro: retorno inválido do fseek 3.\n");
    fclose(index_file);
    return NULL;
  }
  node_t* root = new node_t;
  size_t error = fread(root, BLOCK_SIZE, 1, index_file);
  if(error != 1){
    printf("Erro ao ler o arquivo 1.\n");
    fclose(index_file);
    return NULL;
  }
  b_plus_tree_t* tree = new b_plus_tree_t;
  tree->next_block = data->next_block;
  tree->root_pointer = data->root_pointer;
  tree->root = root;
  tree->index_file_name = index_file_name;
  fclose(index_file);
  return tree;
}

b_plus_tree_t* load_b_plus_tree(string dump_file_name, string index_file_name){
  FILE* dump_file = fopen(dump_file_name.c_str(), "r");
  if(dump_file == NULL){
    printf("Erro: Não foi possível abrir o arquivo para leitura 2.\n");
    return NULL;
  }
  int err = fseek(dump_file, 0, SEEK_SET);
  if(err){
    printf("Erro: retorno inválido do fseek 4.");
    fclose(dump_file);
    return NULL;
  }
  dump_data_t* data = new dump_data_t;
  size_t error = fread(data, sizeof(dump_data_t), 1, dump_file);
  if(error != 1){
    fclose(dump_file); 
		printf("Erro ao ler o arquivo 2.\n");
    return NULL;
  }
  b_plus_tree_t* tree = load_b_plus_tree_helper(data, index_file_name);
  fclose(dump_file);
  return tree;
}

static void set_tree_root(b_plus_tree_t* tree, node_t* node){
  tree->root_pointer = node->my_pointer;
	tree->root = node;
}


static node_t* read_node(b_plus_tree_t tree, int pointer){
  int err = fseek(tree.index_file, pointer*BLOCK_SIZE, SEEK_SET);
  if(err){
    printf("Erro: retorno inválido do fseek 5.\n");
    return NULL;
  }
  node_t* new_node = new node_t;
  size_t error = fread(new_node, BLOCK_SIZE, 1, tree.index_file);
  if(error != 1){
    printf("Erro ao ler o arquivo 3.\n");
    return NULL;
  }
  return new_node;
}


static void update_node_in_tree(b_plus_tree_t* tree, node_t* node){
	int pointer = node->my_pointer;
	int err = fseek(tree->index_file, pointer*BLOCK_SIZE, SEEK_SET);
	if(err){
		printf("Erro: retorno inválido do fseek 6.\n");
		return ;
	}
  if(sizeof(*node) > BLOCK_SIZE)
    printf("Erro: tamanho do nó maior que o tamanho do bloco.\n");
	size_t error = fwrite(node, BLOCK_SIZE, 1, tree->index_file);
	if(error != 1){
		printf("Erro: Não foi possível escrever no arquivo 3.\n");
	}
}

static int binary_search(int* array, int n, int key){
	int e = -1, d = n;
   	while (e < d-1) { 
      int m = (e + d)/2;
      if (array[m] < key) e = m;
      else {
      	if(array[m] == key) return m;
      	d = m;
      }
   }
   return d - 1;
}

static void insert_in_node(node_t* node, entry_t entry){
	int i = node->n;
	while(i > 0 && node->keys[i - 1] > entry.key){
		node->keys[i] = node->keys[i - 1];
		node->pointers[i + 1] = node->pointers[i];
		node->pointers[i] = node->pointers[i-1];
		i--;
	}
	node->keys[i] = entry.key;
  if(node->is_leaf)
	  node->pointers[i] = entry.pointer;
  else
    node->pointers[i+1] = entry.pointer;
    
	node->n++;
}
static entry_t split_leaf(b_plus_tree_t* tree, node_t* left, entry_t entry){
	node_t* right = create_node_in_tree(tree, true);
	for(int i = 0; i < M; i++){
		right->keys[i] = left->keys[i + M];
		right->pointers[i] = left->pointers[i + M];
	}
	right->n = M;
	left->n = M;
	if(entry.key < left->keys[left->n - 1]){
		insert_in_node(left, entry);
	}else{
		insert_in_node(right, entry);
	}
  left->pointers[left->n] = tree->next_block - 1;
	entry_t middle = {right->keys[0], tree->next_block - 1};
	update_node_in_tree(tree, left);
	update_node_in_tree(tree, right);
	return middle;
}

static entry_t split_non_leaf(b_plus_tree_t* tree, node_t* node, entry_t new_child_entry){
	entry_t middle = {0,0};
	node_t* new_node = create_node_in_tree(tree, false);
	int lower_bound;
	bool is_to_insert_new_child_in_new_node = false;
	bool is_to_insert_new_child_in_node = false;
	if(node->keys[M-1] <= new_child_entry.key && new_child_entry.key < node->keys[M]){
		middle.key = new_child_entry.key;
		lower_bound = M;
	}else if(new_child_entry.key >= node->keys[M]){
		middle.key = node->keys[M];
		lower_bound = M + 1;
		is_to_insert_new_child_in_new_node = true;
	}else{
		middle.key = node->keys[M - 1];
		lower_bound = M;
		is_to_insert_new_child_in_node = true;
	}
  int i;
	for(i = lower_bound; i < (2*M); i++){
		new_node->keys[i - lower_bound] = node->keys[i];
		new_node->pointers[i - lower_bound] = node->pointers[i];
		new_node->n++;
		node->n--;
	}
  new_node->pointers[i - lower_bound] = node->pointers[i];
	if(is_to_insert_new_child_in_new_node){
    node->n--;
		insert_in_node(new_node, new_child_entry);
	}else if(is_to_insert_new_child_in_node){
    node->n--;
		insert_in_node(node, new_child_entry);
	}
	middle.pointer = tree->next_block - 1;
	update_node_in_tree(tree, node);
	update_node_in_tree(tree, new_node);
	return middle;
}

static entry_t insert_inner(b_plus_tree_t* tree, node_t* root, entry_t entry){
	if(root->is_leaf){
		if(root->n < 2*M){
			insert_in_node(root, entry);
			update_node_in_tree(tree, root);
			return {-1, -1};
		}else{
			entry_t middle = split_leaf(tree, root, entry);
			return middle;
		}
	}else{
		int i;
		if(entry.key < root->keys[0]){
			i = 0;
		}else{
			for(i = 1; i < root->n; i++)
				if(root->keys[i-1] <= entry.key && entry.key < root->keys[i])
					break;
		}
		node_t* child = read_node(*tree, root->pointers[i]);
		entry_t new_child_entry = insert_inner(tree, child, entry);

		if(is_entry_null(new_child_entry))
			return {-1, -1};
		if(root->n < 2*M){
			insert_in_node(root, new_child_entry);
			update_node_in_tree(tree, root);
			return {-1, -1};
		}else{
			entry_t middle = split_non_leaf(tree, root, new_child_entry);
			if(tree->root == root){
				node_t* new_tree_root = create_node_in_tree(tree, false);
				insert_in_node(new_tree_root, middle);
        new_tree_root->pointers[0] = root->my_pointer;
				set_tree_root(tree, new_tree_root);
        update_node_in_tree(tree, new_tree_root);
				return {-1, -1};
			}
			return middle;
		}
	}
}

void insert_entry(b_plus_tree_t* tree, entry_t entry){
  tree->index_file = fopen(tree->index_file_name.c_str(), "r+");
  if(tree->index_file == NULL){
    printf("Erro: Não foi possível abrir o arquivo para leitura 4.'\n");
    return ;
  }
	entry_t middle = insert_inner(tree, tree->root, entry);
  if(!is_entry_null(middle)){
    node_t* new_root = create_node_in_tree(tree, false);
    insert_in_node(new_root, middle);
    new_root->pointers[0] = tree->root->my_pointer;
    set_tree_root(tree, new_root);
    update_node_in_tree(tree, new_root);
  }
  fclose(tree->index_file);
}

int search_key(b_plus_tree_t* tree, int key){
  tree->index_file = fopen(tree->index_file_name.c_str(), "r");
  if(tree->index_file == NULL){
    printf("Erro: Não foi possível abrir o arquivo para leitura 5.'\n");
    return -1;
  }
	node_t* aux = tree->root;
	int i = -1;
  int count_blocks_read = 1; 
	while(aux->is_leaf == false){
		i = binary_search(aux->keys, aux->n, key);
		if(key < aux->keys[i]){
			aux = read_node(*tree,aux->pointers[i]);
		}else{
			aux = read_node(*tree,aux->pointers[i+1]);
		}
    count_blocks_read++;
	}
  i = binary_search(aux->keys, aux->n, key);
  fclose(tree->index_file);
	if(key == aux->keys[i]){
    printf("Quantidade de blocos lidos: %d\n", count_blocks_read);
    return aux->pointers[i];
  }else{
    return -1;
  } 
}

bool is_entry_null(entry_t entry){
	return entry.key == -1 && entry.pointer == -1;
}

node_t* create_node(bool is_leaf, int my_pointer){
	node_t* new_node = new node_t;
	new_node->is_leaf = is_leaf;
	new_node->n = 0;
  new_node->my_pointer = my_pointer;
	return new_node;
}
