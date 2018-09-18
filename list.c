#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "site.h"
#define ERROR 505
#define DEBUG 0

//lista de sites, contem um site no inicio e um no final e o tamanho
struct list{
	
	SITE* start; //primeiro
	SITE* end; //ultimo
	int size; //tamanho da lista
	
};

//funcao que cria uma lista e retorna essa
LIST* create_list(void){
	LIST* L; //declarado um ponteiro para lista
	L = (LIST*) malloc(sizeof(LIST)); //alocando a lista na heap
	
	//se alocou, entra
	if(L != NULL){
		L->start = NULL; //nenhum item no comeco da lista
		L->end = NULL; //nenhum item no final da lista
		L->size = 0; //portanto, lista vazia
	}
	
	return(L);//retorna a lista vazia
	
}

//escaneando o arquivo, essa funcao recebe o ponteiro para o arquivo a ser escaneado e o numero
LIST* scan_file(FILE* fp, int n_lines){
	
	LIST* l; //ponteiro para lista
	SITE* s; //ponteiro para site

	l = create_list(); //lista l recebe a lista criada

	int i = 0; //variaveis i, j sao auxiliares
	int j = 0;

	s = create_site(); //s recebe o site criado
	l->start = s; //o comeco da lista recebe o primeiro site
	while(l->size < n_lines){ //enquanto o contador (que conta quantas linhas ja foram lidas) for menor que o numero de linhas, segue

		prepare_site(fp, s, i, j);
		l->end = s; //o fim recebe o ultimo site que foi criado
		l->size++; //aumenta o tamanho da lista
		next_site(s, l->size, n_lines);
		printf("\n");

	}

	return l; //retorna a lista
}