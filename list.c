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
//escaneando o arquivo, essa funcao recebe o ponteiro para o arquivo a ser escaneado e o numero
LIST* scan_file(FILE* fp, int n_lines){
	
	LIST* l; //ponteiro para lista
	SITE* s; //ponteiro para site
	SITE* auxiliar;

	l = create_list(); //lista l recebe a lista criada

	int i = 0; //variaveis i, j sao auxiliares
	int j = 0;

	s = create_site(); //s recebe o site criado
	prepare_site(fp, s, i, j, l->size);
	l->start = s; //o comeco da lista recebe o primeiro site
	l->end = s;
	l->size++;

	while(l->size < n_lines){ //enquanto o contador (que conta quantas linhas ja foram lidas) for menor que o numero de linhas, segue
		auxiliar = create_site(); //usando um auxiliar para poder conectar os no's da lista
		next_site(s, auxiliar); //conectando s ao auxiliar
		prepare_site(fp, auxiliar, i, j, l->size); //recebendo os dados no site
		l->end = auxiliar; //o ultimo item da lista e' o auxiliar recem-criado
		l->size++; //aumenta o tamanho da lista
		if(l->size == n_lines) break; //se ainda nao chegou no final do arquivo, continua conectando
		s = create_site(); //a mesma logica das 6 linhas acima, cria um site, aponta o anterior pra ele, prepara, e coloca o fim nele
		next_site(auxiliar, s);
		prepare_site(fp, s, i, j, l->size);	
		l->end = s;
		l->size++; //aumenta o tamanho da lista
	}

	if(l->start == NULL) printf("inicio null\n");
	if(l->end == NULL) printf("fim null\n");

	return l; //retorna a lista
}


//funcao que printa os sites de uma determinada lista, recebe essa lista como parametro
void print_list(LIST* list){

	int i = -1;

	SITE* site; //site auxiliar

	site = list->start; //esse site recebe o inicio da lista

	print_site(site, &i); //executa a funcao recursiva

}
