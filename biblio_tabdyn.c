#include "biblio_tabdyn.h"

Biblio *nouvelle_biblio(void)
{
    Biblio* B = (Biblio*)malloc(sizeof(Biblio));
	B->capacite=100;
	B->nE=0;
	B->T =(CellMorceau *)(malloc(100*sizeof(CellMorceau)));
	
	return B;
}

void libere_biblio(Biblio *B)
{
    int i;
    for( i=0;i<B->nE;i++){
        CellMorceau* M=B->T+i;
        free(M->titre);
        free(M->artiste);
      
        
    }
    free(B->T);
    free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{
    if (B->nE == B->capacite) {
		B->T = (CellMorceau*)realloc(B->T,(B->capacite)*2*sizeof(CellMorceau));
		B->capacite *= 2;
	}
	(B->T+B->nE)->titre = titre;
	(B->T+B->nE)->artiste = artiste;
	(B->T+B->nE)->num = num;
	B->nE++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("*T* %8d * %-32.32s * %-32.32s *T*\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
    int i;
	for (i = 0; i < B->nE; i++) {
		afficheMorceau(B->T+i);
	}
}

int in(Biblio* B,int num, char* titre, char* artiste)
{
    int i;
	for (i = 0; i < B->nE; i++) {
		if ( (B->T+i)->num == num && strcmp((B->T+i)->titre, titre) == 0 && strcmp((B->T+i)->artiste, artiste) == 0) {
			return 1;
		}
	}
	return 0;
}


Biblio *uniques (Biblio *B)
{
    Biblio* New = nouvelle_biblio();
    int i;
	for (i = 0; i < B->nE; i++) {
		if (in(New,(B->T+i)->num,(B->T+i)->titre,(B->T+i)->artiste) == 0) {
			insere(New,(B->T+i)->num, strdup((B->T+i)->titre), strdup((B->T+i)->artiste));
		}
	}
	return New;
}


CellMorceau * rechercheParNum(Biblio *B, int num)
{
    int i;
    for (i = 0; i < B->nE; i++) {
		if ((B->T+i)->num == num) {
			return (B->T+i);
		}
	}
	return 	NULL;
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
    int i;
    for (i = 0; i < B->nE; i++) {
		if (strcmp((B->T+i)->titre, titre)==0) {
			return (B->T+i);
		}
	}
	return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
    Biblio* New = uniques(B);
    int i;
    for (i = 0; i < B->nE; i++) {
		if (strcmp((B->T+i)->artiste, artiste)==0) {
			insere(New,(B->T+i)->num, strdup((B->T+i)->titre), strdup((B->T+i)->artiste));
		}
	}
	return New;
}

void insereSansNum(Biblio *B, char *titre, char *artiste)
{
    insere(B,B->nE, strdup(titre), strdup(artiste));
}


int supprimeMorceau(Biblio *B, int num)
{
    int i;
    uniques(B);
    if(B->T->num == num ) {
        CellMorceau* tmp=B->T+1;
        free(B->T->titre);
        free(B->T->artiste);
        free(B->T);
        B->T=tmp;
        B->nE--;
        return 1;
    }
	for (i = 0; i < B->nE; i++) {
        if ( (B->T+i)->num == num ) {
			free((B->T+i)->titre);
			free((B->T+i)->artiste);
			free(B->T+i);
			B->nE--;
			return 1;
		}
	}
	return 0;
}




































