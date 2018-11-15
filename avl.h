#ifndef AVL_H
#define AVL_H
#include "site.h"

#define max(a, b) ((a > b) ? a : b)

typedef struct avl AVL;
typedef struct node NODE;

AVL* scan_file(FILE* fp, int n_lines);
AVL *avl_create(void);
void delete_avl_aux(NODE *root);
void avl_delete(AVL **tree);
int avl_height_node(NODE* root);
NODE *avl_create_node(SITE *site);
NODE *rotate_right(NODE *a);
NODE *rotate_left(NODE *a);
NODE *rotate_left_right(NODE *a);
NODE *rotate_right_left(NODE *a);
NODE *avl_insert_node(NODE *root, SITE *site);
int avl_insert(AVL *tree, SITE *site);
int avl_remove(AVL* A, int code);
int code_found(AVL* L, int code);
NODE* avl_search_code(NODE* root, int code);
SITE* avl_search(NODE* root, int code);
NODE* avl_root(AVL* T);
void avl_print(AVL* A);
int avl_search_keyword(AVL* A, char search[51]);
void tree_search(NODE* root, char search[51], int* flag);

#endif