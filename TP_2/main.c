/*
main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "tp2.h"


int main(void){

    char *texte = "abracadabra";
    char *motif = "abra";
    int occ = algo_naif_boucle_rapide_sans_santinelle(texte, motif);
    printf("algo_naif_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ);
    printf("algo_naif_boucle_rapide_avec_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ);
    return 0;
}
