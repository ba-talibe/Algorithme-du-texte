#include "algo_naif.h"
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


int calcul_bord(char* mot)
{
    int taille=strlen(mot);
    int bord[taille];
    bord[0]=0;
    int i=1,j=0;
    while(i<taille){
        if(mot[i]==mot[j]){
            j++;
            bord[i]=j;
            i++;
        }
        else{
            if(j!=0){
                j=bord[j-1];
            }
            else{
                bord[i]=0;
                i++;
            }
           
        }
    }
    return bord[taille-1];
}

int bon_prefix(char* mot,int indexe){
    if(indexe==0){
        return -1;
    }
    else{
          char *tmp = (char*)malloc(indexe+1 * sizeof(char)); 
          for(int i=0;i<indexe;i++){
            tmp[i]=mot[i];
          }
          return calcul_bord(tmp);
    }
    
}

int algo_morris_pratt(char *texte, char *motif){
    int i=0;
    int nb_occurence=0;
    int taille=strlen(texte);
    int bonpref[strlen(motif)];
    for (int j=0;j<strlen(motif);j++)
    { 
        bonpref[j]=bon_prefix(motif,j);
    }
    for (int j=0;j<taille;j++)
    {
        while(i>=0 && motif[i]!=texte[j]){
            i=bonpref[i];
        }
        i++;
        if(i==strlen(motif)){
             nb_occurence++;
             i=bonpref[i];
        }
    }
    return nb_occurence;
}
