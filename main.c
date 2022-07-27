#include "biblio.h"

void menu() {
	printf("Menu:\n");
	printf("0-Sortie\n");
	printf("1-Affichage\n");
	printf("2-Recherche morceaux uniques\n");
	printf("3-Recherche morceau par titre\n");
	printf("Votre choix : ");
}

int main(int argc, const char *argv[])
{

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}
	
	const char *nomfic = argv[1];
	int nlignes = atoi(argv[2]);
	char titre[249];
	char artiste[249];
	printf("Lecture :\n");
	Biblio *biblio = charge_n_entrees(nomfic, nlignes);
	int duree;
	clock_t start, difference;
	
	int ch;
	do {
		menu();
		int lus = scanf("%d", &ch);
		if (lus == 0)
			ch = 0;
		
		switch(ch) {
			case 1 :
				printf("Affichage\n");
				affiche(biblio);
				break;
			case 2:
				{
					Biblio *Bunique = uniques(biblio);
					affiche(Bunique);
					libere_biblio(Bunique);
					break;
				}
			case 3 :
				{
					printf("Saisir le titre du morceau :\n");
					scanf(" %248[^\n]", titre);
					start = clock();
					CellMorceau * r = rechercheParTitre(biblio, titre);
					difference = clock() - start;
					duree = (difference * 1000000 / CLOCKS_PER_SEC);
					printf("On a prit : %d microseconds.\n", duree);
					if (r == NULL) printf("Aucun morceau de titre : %s!!!\n", titre);
					else afficheMorceau(r);
					break;
				}
			case 4 :
				{
					printf("Saisir l'artiste :\n");
					scanf(" %248[^\n]", artiste);
					start = clock();
					Biblio * r = extraireMorceauxDe(biblio, titre);
					difference = clock() - start;
					duree = (difference * 1000000 / CLOCKS_PER_SEC);
					printf("On a prit :  %d microseconds.\n", duree);
					if (r == NULL) printf("Aucun morceau de cette artiste : %s!!!\n", artiste);
					else affiche(r);
					break;
				}	
			default :
				ch = 0;
				break;
		
		}
		
	} while (ch != 0);
	
	libere_biblio(biblio);
	printf("Au revoir\n");
	
	return 0;
}
