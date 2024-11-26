/*
main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "tp2.h"


int main(void){

    // char *texte = "abracadabra";
    // char *motif = "abra";
    // int occ_1 = algo_naif_boucle_rapide_sans_santinelle(texte, motif);
    // int occ_2 = algo_naif_boucle_rapide_avec_santinelle(texte, motif);
    // int occ_3 = algo_naif_sans_boucle_rapide_sans_santinelle(texte, motif);
    // int occ_4 = algo_naif_strncomp_sans_boucle_rapide_sans_santinelle(texte, motif);
    // int occ_5 = algo_naif_strncomp_avec_boucle_rapide_sans_santinelle(texte, motif);
    // int occ_6 = algo_naif_strncomp_avec_boucle_rapide_sans_santinelle(texte, motif);
    // printf("algo_naif_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_1);
    // printf("algo_naif_boucle_rapide_avec_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_2);
    // printf("algo_naif_sans_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_3);
    // printf("algo_naif_sans_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_3);
    // printf("algo_naif_strncomp_sans_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_4);
    // printf("algo_naif_strncomp_avec_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_5);
    // printf("algo_naif_strncomp_avec_boucle_rapide_avec_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_6);

    // char *texte = "abracadabra";
    char *motif = "aabraa";
    printf("prefix : %d\n", fonction_prefix(motif, 2));


    return 0;
}