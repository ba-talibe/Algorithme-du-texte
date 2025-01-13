#include "algo_rapide.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define ALPHABET_SIZE 256



int calcul_bord(const char* mot)
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

// int calcul_bord(const char* mot)
// {
//     int taille=strlen(mot);
//     int taille_bord = 0;
//     for (int i = 1; i < taille; i++) {
//         char x[i + 1]; 
//         strncpy(x, mot, i); 
//         x[i] = '\0';  
//         if (strcmp(x, &mot[taille - i]) == 0) {
//             taille_bord = i;
//         }
//     }
//     return taille_bord;
// }

int bon_prefix(char* mot,int index){
    if(index==0){
        return -1;
    }
    else{
          char *tmp = (char*)malloc(index+1 * sizeof(char)); 
          for(int i=0;i<index;i++){
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

int plus_long_bord(const char *mot){
    int m = strlen(mot);
    int long_bord = 0;
    for (int i = 1; i < m; i++) {
        char x[i + 1]; 
        strncpy(x, mot, i); 
        x[i] = '\0';  
        if (strcmp(x, &mot[m - i]) == 0) {
            long_bord = i;
        }
    }
    return long_bord;
}

void calcul_meil_pref(const char *mot, int *tab){
    size_t m = strlen(mot);
    tab[0] = -1;  
    
    int long_bord = 0;
    
    for (int i = 1; i <= m; i++) {
        
        char x[i + 1]; 
        strncpy(x, mot, i); 
        x[i] = '\0';  
       
        long_bord = plus_long_bord(x);

       
        if (x[i]!=x[long_bord])
            tab[i] = long_bord;  
        else
            tab[i]=tab[long_bord];
    }
}


int algo_knut_morris_pratt(char *texte, char *motif){
    int size_texte = strlen(texte);
    int size_motif = strlen(motif);

    int tab_bon_prefix[size_motif + 1];

    calcul_meil_pref(motif, tab_bon_prefix);

    int i=0;
    int j=0;
    int occ=0;
    while (i < size_texte) {
        while (j >= 0 && texte[i] != motif[j]) {
            j = tab_bon_prefix[j];  
        }

        i++;
        j++;

        if (j == size_motif) {
            occ+=1;
            j = tab_bon_prefix[j];  
        }
    }
    return occ;
}


void calcul_table_bon_suffix(const char *mot, int *tab_suff, int *tab_bon_suff){
    int m = strlen(mot);

    int i = m;
    int j = m + 1;
    tab_bon_suff[i] = j;

    // Initialisation du tableau des suffixes
    for (int k = 0; k < m + 1; k++) {
        tab_suff[k] = 0;
    }

    // CASE 1 : Construction de tab_bon_suff
    while (i > 0) {
        while (j <= m && mot[i - 1] != mot[j - 1]) {
            if (tab_suff[j] == 0)
                tab_suff[j] = j - i;
            j = tab_bon_suff[j];
        }
        i--;
        j--;
        tab_bon_suff[i] = j;
    }

    // CASE 2 : Remplissage des cases non définies de tab_suff
    j = tab_bon_suff[0]; 
    for (i = 0; i <= m; i++) {
        if (tab_suff[i] == 0)
            tab_suff[i] = j;
        if (i == j)
            j = tab_bon_suff[j];
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int algo_Boyer_Moore(char *texte, char *motif){
    int n = strlen(texte);
    int m = strlen(motif);
    int occ = 0;

    int *tab_suff = (int *)malloc((m + 1) * sizeof(int));  // Allouer la mémoire pour tab_suff
    int *tab_bon_suff = (int *)malloc((m + 1) * sizeof(int));  // Allouer la mémoire pour tab_bon_suff

    if (tab_suff == NULL || tab_bon_suff == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    calcul_table_bon_suffix(motif, tab_suff, tab_bon_suff);

    int j = m - 1;
    int s = 0; // Décalage du motif par rapport au texte

    while (s <= n - m) {
        j = m - 1;

        while (j >= 0 && texte[s + j] == motif[j]) {
            j--;
        }

        if (j < 0) {
            occ++;
            s += tab_bon_suff[0];
        } else {
            s += max(tab_suff[j + 1], j - tab_bon_suff[j]);
        }
    }

    free(tab_suff);
    free(tab_bon_suff);

    return occ;
}

void calcul_dern_occ(const char *mot, int m, int *tab){
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        tab[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        tab[(int)mot[i]] = i;
    }
}

void calcul_table_bon_suffix2(const char *mot, int *tabSuff, int *tabBonSuff){
    int m = strlen(mot);

    int *dern_occ = (int *)malloc(ALPHABET_SIZE * sizeof(int));  // Allouer la mémoire pour dern_occ

    if (dern_occ == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    calcul_dern_occ(mot, m, dern_occ);

    int i = m;
    int j = m + 1;
    tabBonSuff[i] = j;

    for (int k = 0; k < m + 1; k++) {
        tabSuff[k] = 0;
    }

    while (i > 0) {
        while (j <= m && mot[i - 1] != mot[j - 1]) {
            if (tabSuff[j] == 0) {
                tabSuff[j] = j - i;
            }
            j = tabBonSuff[j];
        }
        i--;
        j--;
        tabBonSuff[i] = j;
    }

    j = tabBonSuff[0];
    for (i = 0; i <= m; i++) {
        if (tabSuff[i] == 0) {
            tabSuff[i] = j;
        }
        if (i == j) {
            j = tabBonSuff[j];
        }
    }

    free(dern_occ);
}

int algo_Horspool(char *texte, char *motif){
    int n = strlen(texte);
    int m = strlen(motif);
    int occ = 0;

    int *tabSuff = (int *)malloc((m + 1) * sizeof(int));  // Allouer la mémoire pour tabSuff
    int *tabBonSuff = (int *)malloc((m + 1) * sizeof(int));  // Allouer la mémoire pour tabBonSuff

    if (tabSuff == NULL || tabBonSuff == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    calcul_table_bon_suffix2(motif, tabSuff, tabBonSuff);

    int *dern_occ = (int *)malloc(ALPHABET_SIZE * sizeof(int));  // Allouer la mémoire pour dern_occ

    if (dern_occ == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    calcul_dern_occ(motif, m, dern_occ);

    int i = m - 1;
    int s = 0;

    while (s <= n - m) {
        i = m - 1;

        while (i >= 0 && texte[s + i] == motif[i]) {
            i--;
        }

        if (i < 0) {
            occ++;
            s += tabBonSuff[0];
        } else {
            s += max(tabSuff[i], i - dern_occ[(int)texte[s + i]]);
        }
    }

    free(tabSuff);
    free(tabBonSuff);
    free(dern_occ);

    return occ;
}


void calcul_dern_occ2(const char *mot, int m, int *tab){
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        tab[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        tab[(int)mot[i]] = i;
    }
}

int algo_quick_search(char *texte, char *motif){
    int n = strlen(texte);
    int m = strlen(motif);
    int occ = 0;

    int *tabDernOcc = (int *)malloc(ALPHABET_SIZE * sizeof(int));  // Allouer la mémoire pour tabDernOcc

    if (tabDernOcc == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    calcul_dern_occ2(motif, m, tabDernOcc);

    int j = 0;

    j = 0;
    while (j <= n - m) {
        if (memcmp(motif, texte + j, m) == 0)  // Comparer le motif avec la sous-chaîne du texte
            occ++;

        j += tabDernOcc[(unsigned char)texte[j + m]];  // Décalage basé sur le prochain caractère
    }

    free(tabDernOcc);  // Libérer la mémoire

    return occ;
}