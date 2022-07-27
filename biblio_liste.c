#include "biblio_liste.h"


Biblio * nouvelle_biblio(void)
{
    Biblio* new =malloc(sizeof(*new));
	new->L=NULL;
	new->nE=0;
	return new;
}

void insere(Biblio *B, int num, char *titre, char *artiste)
{
    CellMorceau* c=(CellMorceau *)malloc(sizeof(CellMorceau));
	c->num=num;
	c->titre=titre;
	c->artiste=artiste;
	c->suiv=B->L;
	B->L=c;
	B->nE++;
}

void libere_biblio(Biblio *B)
{
    CellMorceau * c;
    c=B->L;
    while (c){
    	CellMorceau * tmp = c;
    	c=c->suiv;
    	free(tmp->titre);
    	free(tmp->artiste);
    	free(tmp);
    }
    free(B);
}

void afficheMorceau(CellMorceau *cell)
{
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
    CellMorceau* c;
    c=B->L;
    while(c){
        afficheMorceau(c);
        c=c->suiv;
    }
}


Biblio *uniques (Biblio *B)
{
    Biblio * A = nouvelle_biblio();
    CellMorceau* c;
    CellMorceau* d;
    c=B->L;
    

    while(c){
        d=B->L;
        while(d){
            if(strcmp(c->titre,d->titre)==0 && strcmp(c->artiste,d->artiste)==0 && c != d){
                break;
            }
            d=d->suiv;
        }
        if(d == NULL){
            insere(A,c->num,c->titre,c->artiste);
        }
        c=c->suiv;
    }
    return A;
}

CellMorceau * rechercheParNum(Biblio *B, int numero)
{
	CellMorceau *c=B->L;
	while(c){
		if(c->num == numero){
			return c;
		}
		c=c->suiv;
	}
	return NULL;
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	CellMorceau *c=B->L;
	while(c){
		if(strcmp(c->titre,titre)==0){
			return c;
		}
		c=c->suiv;
	}
	return NULL;
	
}

Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	Biblio* res=uniques(B);
	CellMorceau *c=B->L;
	while(c){
		if(strcmp(c->artiste,artiste)==0){
			insere(res,c->num,c->titre,c->artiste);
		}
		c=c->suiv;
	}
	return uniques(res);
}


void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B,B->nE,titre,artiste);
}

int supprimeMorceau(Biblio *B, int num)
{
	uniques(B);
	CellMorceau* c=B->L;
	CellMorceau* tmp=c->suiv;

	if(c->num==num ){
			free(c->artiste);
			free(c->titre);
			free(c);
			B->L=tmp;
			B->nE--;
			return 1;
	}
	while(c->suiv){
		if(c->suiv->num==num ){
			tmp=c->suiv;
			c->suiv=tmp->suiv;
			free(tmp->suiv->artiste);
			free(tmp->suiv->titre);
			free(tmp->suiv);
			B->nE--;
			return 1;
		}
		c=c->suiv;

	}
	return 0;
}



































