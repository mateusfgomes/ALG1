#include <stdlib.h>
#include <string.h>
#include "list.h"

//funcao para contar o numero de linhas do arquivo (conta as quebras de linha '\n's)
int count_lines(FILE* file){
	
	int count = 0;
	char h;

  	//enquanto nao chega no final
    while((fscanf(file, "%c", &h)) != EOF){
		if(h == '\n') //se for uma quebra de linha
			count++; //conta
	}	
	
	return count; //retorna o numero de linha
}

int main(void){
	
	FILE* fp; //ponteiro para arquivo
	int n_lines; //variavel que armazena o numero de linhas
	LIST* l = NULL;
	
	fp = fopen("googlebot.txt", "r"); //abre o arquivo googlebot.txt em modo leitura
	n_lines = count_lines(fp); //conta as linhas
	rewind(fp); //volta ao inicio do arquivo

	l = scan_file(fp, n_lines); //le o arquivo
	
	return 0;
}
