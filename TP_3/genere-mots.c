#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_random_word(int min_word_length, int max_word_length, int alphabet_range) {
    /*
        Génère un mot pseudo-aléatoire de longueur donnée
    */
   
    // Détermine une longueur aléatoire 
    int word_length = rand() % (max_word_length - min_word_length + 1) + min_word_length;

    // generation du mot caractere par caractere
    for (int i = 0; i < word_length; ++i) {
        char random_char;

        // ne generer que des lettres minuscules si l'alphabet est de taille 26
        random_char = (alphabet_range < 26) ? 'a' + rand() % alphabet_range : '0' + rand() % alphabet_range;
        

        // Affiche le caractère généré
        printf("%c", random_char);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
   // verification des argument du programme
    if (argc != 5) {
        printf("Utilisation : %s <nombre_de_mots> <longueur_min> <longueur_max> <taille_alphabet>\n", argv[0]);
        return 1; // Retourne une erreur si les arguments sont incorrects
    }

    // conversion des arguments en entiers
    int num_words = atoi(argv[1]);         // Nombre total de mots à générer
    int min_word_length = atoi(argv[2]);  // Longueur minimale des mots
    int max_word_length = atoi(argv[3]);  // Longueur maximale des mots
    int alphabet_range = atoi(argv[4]);   // Taille de l'alphabet utilisé pour la génération

    // Initialisation de la graine pour la génération de nombres aléatoires
    srand(time(NULL));

    // Génère et affiche le nombre de mots demandé par l'utilisateur
    for (int i = 0; i < num_words; ++i) {
        generate_random_word(min_word_length, max_word_length, alphabet_range);
    }

    return 0; 
}
