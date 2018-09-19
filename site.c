#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#define DEBUG 0

//definindo a estrutura de um so site
struct site{
	
	int code; //codigo
	char name[51]; //nome
	int relevance; //relevancia
	char link[101]; //link
	char keywords[10][51]; //palavras-chave
	int n_keywords[10];
	SITE* next; //proximo site
	
};

//criando um site
SITE* create_site(void){
	
	SITE* create;//ponteiro opaco para um site
	
	create = (SITE*) malloc(sizeof(SITE)); //alocando na heap o site

	//se alocou, entra
	if (create != NULL){
		create->code = 0; //zerando o codigo
		create->relevance = 0; //zerando a relevancia
		create->next = NULL;
	}
	
	//retornando o site criado
	return(create);
}

void prepare_site(FILE* fp, SITE* s, int i, int j, int position){

	char aux; //esse auxiliar servira' para escanear char por char do que nao for numeros
	char c; //char c que so' tem a funcao de armazenar as virgulas para descarte
	fscanf(fp, "%d%c", &s->code, &c); //escaneando o codigo do site e a virgula que vem logo depois

	if (DEBUG) printf("%d ", s->code); //printando o codigo para debug

	fscanf(fp, "%c", &aux); // pegando o primeiro caractere do nome

	//resetando o j
	j = 0;

	while(aux != ','){ //enquanto nao for virgula, segue escaneando o nome
		s->name[j] = aux; //armazenando o nome
		if (DEBUG) printf("%c", s->name[j]); //armazenando o nome
		j++;			
		fscanf(fp, "%c", &aux); //escaneando o proximo pra testar ate' ser virgula
	}

	//resentando o j
	j = 0;

	if (DEBUG) printf(" "); //printando espaco para debug

	fscanf(fp, "%d%c", &s->relevance, &c); //pegando a relevancia e a virgula que vem depois

	if (DEBUG) printf("%d ", s->relevance); //printando a relevancia para debug

	fscanf(fp, "%c", &aux); //escaneando o primeiro caractere do link

	while(aux != ','){ //enquanto nao for virgula
		s->link[j] = aux; //armazenando o link na posicao link da struct site
		if (DEBUG) printf("%c", s->link[j]); //printando para debug
		j++; 
		fscanf(fp, "%c", &aux); //escaneando novamente para reavaliacao	
	}

	if (DEBUG) printf(" "); //printando espaco para debug

	//resetando o j
	j = 0;
	//resetando o i
	i = 0;

	fscanf(fp, "%c", &aux); //escaneando o primeiro caractere das palavras-chave

	while(aux != '\n'){ //enquanto nao chegar no final da linha, vai escaneando as palavras-chave
		if(aux != ','){ //se nao for virgula, entra para salvar nas palavras
			s->keywords[i][j] = aux; //armazena na variavel de palavras-chave
			if (DEBUG) printf("%c", s->keywords[i][j]); //printando para debug
			j++; //vai para a proxima letra
		}
		else{
			if (DEBUG) printf(" "); //se for virgula, printa um espaco para debug
			j = 0; //resentando o j para uma nova palavra chave
			i++; //indo para a proxima palavra-chave
		}
		s->n_keywords[position] = i;
		fscanf(fp, "%c", &aux); //escaneando char por char das palavras-chave para avaliar se nao e' \n
	}
}

//funcao que conecta os sites (encadeia), recebe dois sites
//o site a recebe, em next, o site aux
void next_site(SITE* a, SITE* aux){

	a->next = aux;

}

//recursao que printa os sites, recebe o site e um contador
void print_site(SITE* site, int* h){

	*h = *h + 1;
	int j = 0;

	printf("%d, ", site->code);
	printf("%s, ", site->name);
	printf("%d, ", site->relevance);
	printf("%s, ", site->link);

	//while para printar as n palavras chave de cada site
	while(j <= site->n_keywords[*h]){
		printf("%s ", site->keywords[j]);
		j++;
	}
	printf("\n");
	site = site->next; //indo para o proximo site

	if (site != NULL) print_site(site, h);//enquanto o site nao for null, printa os sites

}
