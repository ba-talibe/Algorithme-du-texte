/*
main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "algo_naif.h"
#include "algo_rapide.h"


int main(void){

    char *texte = "abracadabra";
    char *motif = "abra";
    int occ_1 = algo_naif_boucle_rapide_sans_santinelle(texte, motif);
    int occ_2 = algo_naif_boucle_rapide_avec_santinelle(texte, motif);
    int occ_3 = algo_naif_sans_boucle_rapide_sans_santinelle(texte, motif);
    int occ_4 = algo_naif_strncomp_sans_boucle_rapide_sans_santinelle(texte, motif);
    int occ_5 = algo_naif_strncomp_avec_boucle_rapide_sans_santinelle(texte, motif);
    int occ_6 = algo_naif_strncomp_avec_boucle_rapide_avec_santinelle(texte, motif);

    int occ_7 = algo_morris_pratt(texte, motif);
    int occ_8 = algo_knut_morris_pratt(texte, motif);
    int occ_9 = algo_Boyer_Moore(texte, motif);
    int occ_10 = algo_Horspool(texte, motif);
    int occ_11 = algo_quick_search(texte, motif);
    printf("Algorithme Naif\n");    
    printf("\talgo_naif_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_1);
    printf("\talgo_naif_boucle_rapide_avec_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_2);
    printf("\talgo_naif_sans_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_3);
    printf("\talgo_naif_sans_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_3);
    printf("\talgo_naif_strncomp_sans_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_4);
    printf("\talgo_naif_strncomp_avec_boucle_rapide_sans_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_5);
    printf("\talgo_naif_strncomp_avec_boucle_rapide_avec_santinelle : occ  de %s dans %s : %d\n", motif, texte, occ_6);
    printf("\n\n");
    printf("Algorithme Naif\n");
    printf("\talgo_morris_pratt : occ  de %s dans %s : %d\n", motif, texte, occ_7);
    printf("\talgo_knut_morris_pratt : occ  de %s dans %s : %d\n", motif, texte, occ_8);
    printf("\talgo_Boyer_Moore : occ  de %s dans %s : %d\n", motif, texte, occ_9);
    printf("\talgo_Horspool : occ  de %s dans %s : %d\n", motif, texte, occ_10);
    printf("\talgo_quick_search : occ  de %s dans %s : %d\n", motif, texte, occ_11);
    return 0;
}