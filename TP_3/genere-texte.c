#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define ALPHABET_SIZE 90

// Fonction pour générer un caractère aléatoire
char generer_caractere(int taille_alphabet) {
    /*
        Génère un caractère pseudo-aléatoire en fonction de la taille de l'alphabet
    */
    char generated_char;
    if(taille_alphabet < 26){
            generated_char = 'a' + rand() % taille_alphabet;
    }else
        {
            generated_char = '0' + rand() % taille_alphabet;
    }
    return generated_char;
}


void generer_texte(int longueur_texte, int taille_alphabet) {
    /*
        Génère un texte pseudo-aléatoire de longueur donnée
    */
    for (int i = 0; i < longueur_texte; ++i) {
        char caractere = generer_caractere(taille_alphabet);

        printf("%c", caractere);
    }
}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <longueur du texte> <taille de alphabet>\n", argv[0]);
        return -1;
    }

    int longueur_texte = atoi(argv[1]);
    int taille_alphabet = atoi(argv[2]);

  
    if (taille_alphabet > ALPHABET_SIZE) {
        printf("Erreur: La taille de l'alphabet doit etre inferieur à %d\n", ALPHABET_SIZE);
        return -1;
    }


    // Génération du texte pseudo-aléatoire
    generer_texte(longueur_texte, taille_alphabet);

    return 0;
}
