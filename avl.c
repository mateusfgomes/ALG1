#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "site.h"
#define ERROR -404

/*ESTRUTURA DE DADOS USADA: Lista Encadeada Ordenada*/
struct node{
	SITE* site;
	NODE* left;
	NODE* right;
	int height;
};

struct avl{
	NODE* root;
	int depth;
};

AVL *avl_create(void){
	AVL *tree = (AVL *) malloc(sizeof (AVL));
	if(tree != NULL){
		tree->root = NULL;
		tree->depth = -1;
	}
	return tree;
}

AVL* scan_file(FILE* fp, int n_lines){
	AVL* aux = avl_create(); 
	SITE* S;
	int count = 0;
	while(count < n_lines){
		S = read_file_sites(fp);
		if(avl_insert(aux, S)) printf("NOVO SITE INSERIDO COM SUCESSO...\n");
		count++;
	}
	return aux; 
}

void delete_node(NODE* a){
	if(a != NULL){
		free(a->site);
		a = NULL;
	}
}

void delete_avl_aux(NODE *root){
	if(root != NULL){
		delete_avl_aux(root->left);
		delete_avl_aux(root->right);
		delete_node(root);
		free(root);
	}
}

void avl_delete(AVL **tree){
	delete_avl_aux((*tree)->root);
	free(*tree);
	*tree = NULL;
}

int avl_height_node(NODE* root){
	if(root == NULL){
		return -1;
	}else{
		return root->height;
	}
}

NODE *avl_create_node(SITE *site){
	NODE *node = (NODE *) malloc(sizeof (NODE));
	if(node != NULL){
		node->height = 0;
		node->right = NULL;
		node->left = NULL;
		node->site = site;
	}
	return node;
}

NODE *rotate_right(NODE *a){
	NODE *b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(avl_height_node(a->left),avl_height_node(a->right)) + 1;
	b->height = max(avl_height_node(b->left),	a->height) + 1;
	return b;
}

NODE *rotate_left(NODE *a){
	NODE *b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(avl_height_node(a->left),avl_height_node(a->right)) + 1;
	b->height = max(avl_height_node(b->right),	a->height) + 1;
	return b;
}

NODE *rotate_left_right(NODE *a){
	a->left = rotate_left(a->left);
	return rotate_right(a);
}

NODE *rotate_right_left(NODE *a){
	a->right = rotate_right(a->right);
	return rotate_left(a);
}

NODE *avl_insert_node(NODE *root, SITE *site){
	
	if(root == NULL){
		root = avl_create_node(site);
	}
	
	else if(site_code(site) > site_code(root->site)){
		root->right = avl_insert_node(root->right, site);
		if(avl_height_node(root->left) - avl_height_node(root->right) == -2){
			if(site_code(site) > site_code(root->right->site)){
				root = rotate_left(root);
			}else{
				root = rotate_right_left(root);
			}
		}
	}

	else if(site_code(site) < site_code(root->site)){
		root->left = avl_insert_node(root->left, site);
		if(avl_height_node(root->left) - avl_height_node(root->right) == 2){
			if(site_code(site) < site_code(root->left->site)){
				root = rotate_right(root);
			}else{
				root = rotate_left_right(root);
			}
		}
	}
	root->height = max(avl_height_node(root->left),avl_height_node(root->right)) + 1;
	return root;
}

NODE* avl_search_code(NODE* root, int code){
	if(root == NULL) return NULL;
	if(code == site_code(root->site)) return root;
	else if(code < site_code(root->site)) return avl_search_code(root->left, code);
	else return avl_search_code(root->right, code);
}

NODE* avl_root(AVL* T){
	if(T == NULL) return NULL;
	return T->root;
}

SITE* avl_search(NODE* root, int code){
	if(root == NULL) return NULL;
	NODE* aux = avl_search_code(root, code);
	if(aux == NULL) return NULL;
	return aux->site;
}

int avl_insert(AVL *tree, SITE *site){
	return ((tree->root = avl_insert_node(tree->root, site)) != NULL);
}

int code_found(AVL* L, int code){
	if(L == NULL) return 0;
	return (avl_search_code(L->root, code) != NULL);
}

int avl_remove(AVL* A, int code){
	return 1;
}

void print_tree(NODE* root){

	if(root == NULL) return;
	print_tree(root->left);
	print_site(root->site, 0);
	print_tree(root->right);

}

void avl_print(AVL* A){
	print_tree(A->root);

}

void tree_search(NODE* root, char search[51], int* flag){

	if(root == NULL) return;
	SITE* aux = keyword_found(root->site, search);
	if(aux != NULL){
		print_site(aux, 1);
		*flag = 1;
	}
	tree_search(root->left, search, flag);
	tree_search(root->right, search, flag);

}

int avl_search_keyword(AVL* A, char search[51]){

	int flag = 0;
	tree_search(A->root, search, &flag);
	if(!flag) printf("Não foram encontrados sites com essa palavra-chave\n");

}