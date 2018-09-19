#ifndef LIST_H
#define LIST_H
#include <stdio.h> //tive que colocar a stdio aqui por causa do parametro "FILE*"
#include "site.h"

typedef struct list LIST; //struct da lista de sites

LIST* create_list(void); //funcao que cria a lista para armazenar os sites

LIST* scan_file(FILE* fp, int n_lines); //funcao que escaneia o arquivo, recebe o arquivo e o numero de linhas dele

void print_list(LIST* l); //funcao que printa a lista de sites

#endif
