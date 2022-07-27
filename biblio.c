#include "biblio.h"

Biblio *charge_n_entrees(const char *nom_fichier, int n)
{
    Biblio *B= nouvelle_biblio();
    FILE *f= fopen(nom_fichier,"r");
    if(f==NULL){
        printf("error");
        exit(1);
    }
    int i=0;
    while( !end_of_file(f) && i < n){
        int num;
        char *titre = NULL;
        char *artiste = NULL;
        int ntitre, nartiste;
        if(!(parse_int(f, &num)
            && parse_char(f,'\t')
            && parse_string(f, &titre, &ntitre, '\t')
            && parse_char(f, '\t')
            && parse_string(f, &artiste, &nartiste, '\n')
            && parse_char(f, '\n') )){
                    printf("error");
                    exit(2);
        }
        insere(B,num,titre,artiste);
        i++;
    }
    fclose(f);
    return B;
}



