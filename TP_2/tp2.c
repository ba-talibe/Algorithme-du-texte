#include "tp2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 



int algo_naif_boucle_rapide_sans_santinelle(char *texte, char *motif){
    int i = 0;

    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);
    int count = 0;
    while(i < taille_texte){

        if (texte[i] == motif[0]){
            int j = 1;
            while(j < taille_motif && texte[i+j] == motif[j]){
                j++;
            }
            if (j == taille_motif){
                count ++;
            }
        } 
        i++;
    }
    return count;
}

int algo_naif_boucle_rapide_avec_santinelle(char *texte, char *motif){
    int i = 0;
    int count = 0;
    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);
    char *texte_santinelle = (char *) malloc(taille_texte + taille_motif + 1);
    strcpy(texte_santinelle, texte);
    strcat(texte_santinelle, motif);
    while(1){

        if (texte_santinelle[i] == motif[0]){
            int j = 1;
            while(j < taille_motif && texte[i+j] == motif[j]){
                j++;
            }
            if (j == taille_motif){
                if( i + taille_motif == taille_texte){
                    return count;
                }
                count ++;
            }
        } 
        i++;
    }
    return -1;
}
