#include "biblio_hachage.h"

Biblio *nouvelle_biblio_taille(int taille)
{
	Biblio* B= (Biblio*)malloc(sizeof(Biblio));
	B->nE = 0;
	B->m = taille;
	B->T = (CellMorceau**)malloc(taille*sizeof(CellMorceau*));
	int i;
	/*for (i = 0; i < taille; i++) {
		B->T[i] = NULL;//adresse cell morceau dans T
	}*/
	return B;
}

Biblio *nouvelle_biblio(){
    return nouvelle_biblio_taille(TAILLE_TABLE);
}

void libere_biblio(Biblio *B)
{
    int i;
    for (i = 0; i < B->m; i++) {
		CellMorceau* M = B->T[i];
        if (M == NULL) return;
        CellMorceau* tmp;
        while (M) {
            tmp = M->suiv;
            free(M->titre);
            free(M->artiste);
            free(M);
            M = tmp;
        }
	}
	free(B->T);
	free(B);
}

unsigned int fonction_cle(const char *artiste)
{
	unsigned int som = 0;
	const char *c = artiste;
	while (*c != '\0') {
		som+=*c;
		c++;
	}
	return som;
}

unsigned int fonction_hachage(unsigned int cle, int m)
{
	return (unsigned int)(m * (cle * A - (int)(cle * A)));
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{
    unsigned int cle = fonction_cle(artiste);
	cle = fonction_hachage(cle, B->m);
	CellMorceau *M = (CellMorceau *)malloc(sizeof(CellMorceau));
	M->cle = cle;
	M->num = num;
	M->titre = titre;
	M->artiste = artiste;
	M->suiv = *(B->T);
	*(B->T+cle) = M;//M cell morceau d indice cle dans T
	B->nE++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
    for (CellMorceau **M = B->T; M < B->T+B->m; M++) {
		CellMorceau* tmp = *M;
        while (tmp) {
            afficheMorceau(tmp);
            tmp = tmp->suiv;
        }
	}
}

int inListCell(CellMorceau* list,int num, char* titre, char* artiste)
{
	CellMorceau* M = list;
	while (M) {
		if (M->num == num && (strcmp(M->titre, titre) == 0) && (strcmp(M->artiste, artiste) == 0)) {
            return 1;
        }
		M = M->suiv;
	}
	return 0;
}

int in(Biblio* B,int num, char* titre, char* artiste)
{
	unsigned int cle = fonction_cle(artiste);
	cle = fonction_hachage(cle, B->m);
	return inListCell(*(B->T+cle), num, titre, artiste);
}

Biblio *uniques (Biblio *B)
{
    Biblio* New= nouvelle_biblio_taille(B->m);
	CellMorceau *M;
	int i;
	for (i = 0; i < B->m; i++) {
		M = B->T[i];
		while (M) {
			if (in(New,M->num, M->titre, M->artiste) == 0) {
				insere(New, M->num, strdup(M->titre), strdup(M->artiste));
			}
			M = M->suiv;
		}
	}
	return New;
}

CellMorceau * rechercheParNum(Biblio *B, int num)
{
    CellMorceau* M;
    int i;
	for (i = 0; i < B->m; i++) {
		M = B->T[i];
		while (M) {
			if (M->num == num) {
				return M;
			}
			M = M->suiv;
		}
	}
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
    CellMorceau* M;
    int i;
	for (i = 0; i < B->m; i++) {
		M = B->T[i];
		while (M) {
			if (strcmp(M->titre, titre)==0) {
				return M;
			}
			M = M->suiv;
		}
	}
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
    Biblio* New = uniques(B);
    int i;
    for (i = 0; i < B->m; i++) {
        CellMorceau* M = B->T[i];
        while (M) {
            if (strcmp(M->artiste, artiste)==0) {
                insere(New,M->num, strdup(M->titre), strdup(M->artiste));
		    }
             M = M->suiv;
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
    uniques(B);
	CellMorceau *M;
	int i;
	for (i = 0; i < B->m; i++) {
		M = B->T[i];
		CellMorceau* tmp=M->suiv;
		if (M->num == num) {
            free(M->titre);
            free(M->artiste);
            *(B->T+i)=tmp;
            B->nE--;
            return 1;
        }
		while (M->suiv) {
            if (M->suiv->num == num) {
                tmp=M->suiv;
                M->suiv=tmp->suiv;
                free(tmp->titre);
                free(tmp->artiste);
                B->nE--;
                return 1;
            }
            M = M->suiv;
        }
    }
	return 0;
}





































