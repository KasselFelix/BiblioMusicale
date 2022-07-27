#include "biblio_arbrelex.h"

Biblio *nouvelle_biblio(void)
{
   Biblio * new = (Biblio *)malloc(sizeof(Biblio));
   new->nE=0;
   new->A= NULL;
   return new;
}


void libere_Noeud(Noeud* N)
{
    if(N){
    	CellMorceau* a=N->liste_morceaux;
	    while(a){
	    	CellMorceau* tmp=a;
	    	a=a->suiv;
	    	free(tmp->artiste);
	    	free(tmp->titre);
	 		free(tmp);
	    }
	    libere_Noeud(N->liste_car);
    	libere_Noeud(N->car_suiv);
	}
	return;
}

void libere_biblio(Biblio *B){
	libere_Noeud(B->A);
	free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{
 int i = 0; // Indice lisant nom

	if (B->A == NULL) {
		Noeud *n = (Noeud *)malloc(sizeof(Noeud));
		n->car = artiste[0];
		n->car_suiv = NULL;
		n->liste_car = NULL;
		n->liste_morceaux = NULL;
		B->A = n;
	}

	Noeud *cour = B->A; // Pointeur courant
	Noeud *prec = cour; // Pointeur sur la valeur precedant cour

	while ((cour != NULL) && (artiste[i] != '\0')) {
		prec = cour;

		if (cour->car == artiste[i]) { // On a lu le bon caractere
			cour = cour->car_suiv;
			i++;
		}
		else { // On tente un caractere alternatif
			cour = cour->liste_car;
		}
	}

	if (artiste[i] == '\0') {
		CellMorceau *M = (CellMorceau *)malloc(sizeof(CellMorceau));
		M->num = num;
		M->titre = strdup(titre);
		M->artiste = strdup(artiste);
		M->suiv = NULL;
		
		CellMorceau *liste = prec->liste_morceaux;
		if (liste) {
			while (liste->suiv ) {
				liste = liste->suiv;
			}
			liste->suiv = M;
		}
		else {
			prec->liste_morceaux = M;
		}

		B->nE++;
	}

	else {
		Noeud *n = (Noeud *)malloc(sizeof(Noeud));
		n->car = artiste[i];
		n->car_suiv = NULL;
		n->liste_car = NULL;
		n->liste_morceaux = NULL;

		if (artiste[i-1] == prec->car) {
			prec->car_suiv = n;
			insere(B, num, titre, artiste);
		}
		else {
			prec->liste_car = n;
			insere(B, num, titre, artiste);
		}
	}

	return;

}

void afficheMorceau(CellMorceau *cell)
{
	printf("|A| %8d | %-32.32s | %-32.32s |A|\n", cell->num, cell->titre, cell->artiste);
}

void affiche_cell(Noeud *N){
    if(N){
        CellMorceau* c=N->liste_morceaux;
        while(c){
            afficheMorceau(c);
            c=c->suiv;
        }
        affiche_cell(N->liste_car);
        affiche_cell(N->car_suiv);
    }
}

void affiche(Biblio *B)
{
    affiche_cell(B->A);
}

void noeud_uniques(Biblio *B, Noeud *N){
	if(N == NULL) return;
	CellMorceau *c1 = N->liste_morceaux;
	while(c1){
		CellMorceau *c2=N->liste_morceaux;
		while(c2){
			if(strcmp(c1->titre,c2->titre)==0 && c1 != c2 ) {
				break;
			}
			c2=c2->suiv;
		}
		if(c2 == NULL){
			insere(B,c1->num,strdup(c1->titre),strdup(c1->artiste));
		}
		c1=c1->suiv;
	}
	noeud_uniques(B,N->car_suiv);
	noeud_uniques(B,N->liste_car);
}

Biblio *uniques (Biblio *B)
{
	Biblio * new = nouvelle_biblio();
	noeud_uniques(new,B->A);
	return new;

}

CellMorceau* rechercheNoeudNum(Noeud* N,int num){
	if(N){
		CellMorceau* M=N->liste_morceaux;
		while(M){
			if(M->num==num){
				return M;
			}
			M=M->suiv;
		}
		M=rechercheNoeudNum(N->liste_car,num);
		if(M){ return M;}
		return rechercheNoeudNum(N->car_suiv,num);	
	}
	return NULL;
}


CellMorceau * rechercheParNum(Biblio *B, int num)
{
	return rechercheNoeudNum(B->A,num);

}

CellMorceau* rechercheNoeudTitre(Noeud* N,char * titre){
	if(N){
		if(N){
		CellMorceau* M=N->liste_morceaux;
		while(M){
			if(strcmp(M->titre,titre)==0){
				return M;
			}
			M=M->suiv;
		}
		M=rechercheNoeudTitre(N->liste_car,titre);
		if(M){ return M;}
		return rechercheNoeudTitre(N->car_suiv,titre);	
		}
		return NULL;
	}
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	
	return rechercheNoeudTitre(B->A,titre);
}

void rechercheNoeudArtiste(Biblio* new,Noeud* N,char * Artiste){
	if(N){
		CellMorceau* M=N->liste_morceaux;
		while(M){
			if(strcmp(M->artiste,Artiste)==0){
				insere(new,M->num,strdup(M->titre),strdup(M->artiste));
			}
			M=M->suiv;
		}
		rechercheNoeudArtiste(new,N->liste_car,Artiste);
		rechercheNoeudArtiste(new,N->car_suiv,Artiste);
	}
}

Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	Biblio* B2=uniques(B);
	Biblio* new=nouvelle_biblio();
	rechercheNoeudArtiste(new,B2->A ,artiste);
	return new;
}


void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B,B->nE,strdup(titre),strdup(artiste));

}

int supprimerMorceauNoeud(Noeud* N,int num){
	if(N){
		CellMorceau* M=N->liste_morceaux;
		CellMorceau* tmp=M->suiv;
		if(M->num==num ){
			free(M->artiste);
			free(M->titre);
			free(M);
			N->liste_morceaux=tmp;
			return 1;
		}
		while(M->suiv){
			if(M->suiv->num==num ){
				tmp=M->suiv;
				M->suiv=tmp->suiv;
				free(tmp->artiste);
				free(tmp->titre);
				free(tmp);
				return 1;
			}
			M=M->suiv;
		}
		supprimerMorceauNoeud(N->liste_car,num);
		supprimerMorceauNoeud(N->car_suiv,num);
	}
}

int supprimeMorceau(Biblio *B, int num)
{
	uniques(B);
	if(supprimerMorceauNoeud(B->A,num)==1){
        B->nE--;
        return 1;
	}
	return 0;
}
























