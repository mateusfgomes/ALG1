#ifndef SITE_H
#define SITE_H

typedef struct site SITE; //struct de um site

SITE* create_site(void); //funcao que cria o site

void prepare_site(FILE* fp, SITE* s, int i, int j); //funcao que prepara um site para ser acrescentado na lista

void next_site(SITE* s, int first, int last); //funcao que cria um novo site para encadear a lista

#endif
