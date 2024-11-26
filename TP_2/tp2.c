#include "tp2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 



int algo_naif_boucle_rapide_sans_santinelle(char *texte, char *motif){
    int i = 0;

    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);
    int count = 0;
    char c = motif[0];  
    while(i < taille_texte){

        if (texte[i] == c){
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
    char c = motif[0];
    while(1){

        if (texte_santinelle[i] == c){
            int j = 1;
            while(j < taille_motif && texte_santinelle[i+j] == motif[j]){
                j++;
            }
            if (j == taille_motif){
                if( i == taille_texte){
                    return count;
                }
                count ++;
            }
        } 
        i++;
    }
    return -1;
}


int algo_naif_sans_boucle_rapide_sans_santinelle(char *texte, char *motif){
    int i = 0;
    int count = 0;
    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);

    while(i < taille_texte - taille_motif + 1){
        int j = 0;
        while(j < taille_motif && texte[i+j] == motif[j]){
            j++;
        }
        if (j == taille_motif){
            count ++;
        }
        i++;
    }
    return count;
}


int algo_naif_strncomp_sans_boucle_rapide_sans_santinelle(char *texte, char *motif){
    int i = 0;
    int count = 0;
    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);

    while(i < taille_texte - taille_motif + 1){
        if (strncmp(texte + i, motif, taille_motif) == 0){
            count ++;
        }
        i++;
    }
    return count;
}

int algo_naif_strncomp_avec_boucle_rapide_sans_santinelle(char *texte, char *motif){
    int i = 0;
    int count = 0;
    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);
    char c = motif[0];
    while(i < taille_texte - taille_motif + 1){

         if (texte[i] == c){
            if (strncmp(texte + i , motif, taille_motif) == 0){
                count ++;
            }
        } 
        i++;
    }
    return count;
}

int algo_naif_strncomp_avec_boucle_rapide_avec_santinelle(char *texte, char *motif){
    int i = 0;
    int count = 0;
    int taille_texte = strlen(texte);
    int taille_motif = strlen(motif);
    char *texte_santinelle = (char *) malloc(taille_texte + taille_motif + 1);
    strcpy(texte_santinelle, texte);
    strcat(texte_santinelle, motif);
    char c = motif[0];
    while(1){
        if (texte_santinelle[i] == c){
            if (strncmp(texte_santinelle + i , motif, taille_motif) == 0){
                if( i == taille_texte){
                    return count;
                }
                count ++;
            }
        }
        i++;
    }
    return -1;
}


int fonction_prefix(char *motif, int i){
    int j = 0;
    int periode = 0;
    while(j < i){
        if (motif[i] == motif[j]){
            return j + 1;
        }
    }
    return j;
}

int algo_morris_pratt(char *texte, char *motif){
    int table_prefix [strlen(motif)];
}
