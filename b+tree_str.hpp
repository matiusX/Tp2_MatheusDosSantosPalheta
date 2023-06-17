#ifndef B_PLUS_TREE_STR_HPP
#define B_PLUS_TREE_STR_HPP
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

#define BLOCK_SIZE 4096
#define M_STR 6

typedef struct alfa_300{
  char str[301];
}alfa_300_t;

typedef struct node_str{
	int n;
	bool is_leaf;
	alfa_300_t keys[2*M_STR];
	int pointers[2*M_STR+1];
  int my_pointer;
}node_str_t;

typedef struct b_plus_tree_str{
	int next_block;
  int root_pointer;
  string index_file_name;
	FILE* index_file;
	node_str_t* root;
}b_plus_tree_str_t;

typedef struct entry_str{
	std::string key; 
	int pointer;
}entry_str_t;

node_str_t* create_node_str(bool is_leaf, int my_pointer);
b_plus_tree_str_t* create_b_plus_tree_str(string index_file);
bool dump_b_plus_tree_str(b_plus_tree_str_t* tree, string dump_file_name);
b_plus_tree_str_t* load_b_plus_tree_str(string dump_file_name, string index_file_name);
void insert_entry(b_plus_tree_str_t* tree, entry_str_t entry);
int search_key(b_plus_tree_str_t* tree, string key);
void show_summary_of_tree_in_order(b_plus_tree_str_t* tree);
bool is_entry_null(entry_str_t entry);

#endif