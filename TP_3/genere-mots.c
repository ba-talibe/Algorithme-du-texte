#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_random_word(int min_word_length, int max_word_length, int alphabet_range) {
    // Détermine une longueur aléatoire pour le mot entre les bornes min et max
    int word_length = rand() % (max_word_length - min_word_length + 1) + min_word_length;

    /*
     * Génération des caractères du mot.
     * Les caractères générés dépendent de la taille de l'alphabet spécifiée.
     */
    for (int i = 0; i < word_length; ++i) {
        char random_char;

        /*
         * Si la taille de l'alphabet est inférieure à 26, 
         * on génère uniquement des lettres minuscules.
         */
        if (alphabet_range < 26) {
            random_char = 'a' + rand() % alphabet_range; // Générer une lettre de l'alphabet
        } else {
            /*
             * Sinon, on inclut des caractères supplémentaires, comme des chiffres ou d'autres symboles,
             * en fonction de la plage spécifiée.
             */
            random_char = '0' + rand() % alphabet_range; 
        }

        // Affiche le caractère généré
        printf("%c", random_char);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    /*
     * Vérifie que le programme a reçu exactement 4 arguments en ligne de commande.
     * Affiche un message d'erreur et arrête le programme si les arguments sont insuffisants.
     */
    if (argc != 5) {
        printf("Utilisation : %s <nombre_de_mots> <longueur_min> <longueur_max> <taille_alphabet>\n", argv[0]);
        return 1; // Retourne une erreur si les arguments sont incorrects
    }

    /*
     * Conversion des arguments passés par la ligne de commande en entiers.
     * Ces paramètres définissent les caractéristiques des mots à générer.
     */
    int num_words = atoi(argv[1]);         // Nombre total de mots à générer
    int min_word_length = atoi(argv[2]);  // Longueur minimale des mots
    int max_word_length = atoi(argv[3]);  // Longueur maximale des mots
    int alphabet_range = atoi(argv[4]);   // Taille de l'alphabet utilisé pour la génération

    /*
     * Initialise le générateur de nombres pseudo-aléatoires avec une graine.
     * La graine est basée sur l'heure actuelle pour garantir des résultats différents à chaque exécution.
     */
    srand(time(NULL));

    // Génère et affiche le nombre de mots demandé par l'utilisateur
    for (int i = 0; i < num_words; ++i) {
        generate_random_word(min_word_length, max_word_length, alphabet_range);
    }

    return 0; 
}
