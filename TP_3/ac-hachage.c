#include "trie.h"
#include "queue.h"

#define MAX_WORD_SIZE 60
#define MAX_WORDS 100
#define MAX_TEXT_SIZE 5000000

// Utilisation de la structure de hachage
typedef struct _trie_hachage *Trie;


void ajout_noeud(List *list, unsigned char caractere, int noeud) {
    /*
        Ajoute un noeud à la liste
    */
    List copie = (List)malloc(sizeof(struct _list));
    copie->letter = caractere;	
    copie->target_node = noeud;

    copie->next = *list;
    *list = copie;
}

int rechercher_noeud(List list, unsigned char l) {
    /*
        Recherche un noeud dans la liste
    */
    List copie = list;
    while (copie != NULL) {
        if (copie->letter == l) {
            return copie->target_node;
        }
        copie = copie->next;
    }
    // aucune lettre trouvé
    return -1; 
}


Queue create_queue() {
    /* 
        Création de la file
    */
    Queue queue = (Queue)malloc(sizeof(struct _queue));
    queue->debut = NULL;
    queue->fin = NULL;
    queue->taille = 0;
    return queue;
}

void ajout_valeur(Queue queue, int valeur) {
    /*
        Ajoute une valeur à la file
    */
    if (queue->taille == 0) {
        queue->fin = (Element)malloc(sizeof(struct _element));
        queue->fin->valeur = valeur;
        queue->fin->prochain = NULL;
        queue->debut = queue->fin;
    } 
    else {
        queue->fin->prochain = (Element)malloc(sizeof(struct _element));
        queue->fin->prochain->valeur = valeur;
        queue->fin->prochain->prochain = NULL;
        queue->fin = queue->fin->prochain;
    }
    queue->taille =queue->taille + 1;
}

int recuperer_valeur(Queue queue) {
    /*
        recupere la valeur de la file
    */
    if (queue->taille == 0) {
        return -1;
    }
    int valeur = queue->debut->valeur;
    queue->debut = queue->debut->prochain;

    queue->taille = queue->taille - 1;
    return valeur;
}


Trie create_trie(int max_node) {
    /*
        Cree une trie
    */
    int i;
    Trie trie = (Trie)malloc(sizeof(struct _trie_hachage));
    trie->transition = (List *)malloc(max_node * sizeof(struct _list));
    trie->suppleant = (int *)malloc(max_node * sizeof(int));
    trie->finite = (char *)malloc(max_node * sizeof(char));
    // Initialisations 
    trie->max_node = max_node;
    trie->next_node = 1;
    for (i = 0; i < max_node; i++) {
        trie->suppleant[i] = -1;
        trie->finite[i] = 0; 
    }
    /* retourner le trie*/
    return trie;
}

void insert_trie(Trie trie, unsigned char *w) {
    /*
        Insert un mot dans le trie
    */
    int i=0;
    int noeud_courant = 0;
    int copie;

    int j;
    for (j = 0; w[j] != '\0'; j++) {}


    int taille_mot = j;

    // tentative d'insertion
    while (w[i] != '\0') {
        copie = rechercher_noeud(trie->transition[noeud_courant], w[i]);
        if (copie == -1) {

        // verifier si le trie est plein
            if (taille_mot - i > trie->max_node - trie->next_node) 
                return;
            // insertion du mot
            while (w[i] != '\0') {
                List copie1 = (List)malloc(sizeof(struct _list));
                copie1->target_node = trie->next_node;
                copie1->letter = w[i];
                copie1->next = trie->transition[noeud_courant];
                trie->transition[noeud_courant] = copie1;
                noeud_courant = trie->next_node;
                trie->next_node = trie->next_node + 1;
                i=i+1;
            }
        } else {
            noeud_courant = copie;
        }
        i++;
    }	
    // etat final
    trie->finite[noeud_courant] = 1;
}


void completer_trie(Trie trie) {
    /*
        Ajouter les transition qui vont vers la racine
    */
    List list = trie->transition[0];
    for (int i = 0; i < 256; i++) {
        if (rechercher_noeud(list, i) == -1) {
            ajout_noeud(&list, i, 0);
        }
    }
}



Trans recuperer_transition(Trie trie,  int est_racine, int origine) {
    /*
        Recupere les transitions d'un noeud
    */
    int dest_est_racine = est_racine ? -1 : 0;

    //  Initialisation de la liste des transitions 
    Trans transitions = NULL;
    List list = trie->transition[origine];
    // Récuperation et ajout des transition de la liste 
    while (list != NULL) {
        if (list->target_node > dest_est_racine) {
            Trans copie = (Trans)malloc(sizeof(struct _transition));
            copie->vers = list->target_node;
            copie->origine = origine;
            copie->prochain = transitions;
            copie->letter = list->letter;
            transitions = copie;
            list = list->next;
        }
    }
    return transitions;
}

int destination_transition(Trie trie, int origine, unsigned char caractere) {
    if (origine == -1)
        return 0;
    List list = trie->transition[origine]; // Récupération de la liste des transitions
    return rechercher_noeud(list, caractere);    // Recherche de la destination
}


void complete(Trie trie) {
    /*
        Completion des liens de suppléance
    */
    unsigned char caractere;
    int origine=0, vers=0, s=0;
   
    // recuperation des transitions de la racine
    Trans transitions = recuperer_transition(trie, 0, 0);
    
     // Création de la file
    Queue queue = create_queue();

    // Fonction de suppleancre
    while (transitions != NULL) {
        vers = transitions->vers;
        transitions = transitions->prochain;
        // insertion dans la file
        ajout_valeur(queue, vers);
        // retour à la racine
        trie->suppleant[vers] = 0;
    }
    // execution de la fonction de supppleance sur elements de la file
    while (queue->taille != 0) {
        origine = recuperer_valeur(queue);
        transitions = recuperer_transition(trie, 1, origine);
        while (transitions != NULL) {
            origine = transitions->origine;
            caractere = transitions->letter;
            vers = transitions->vers;
            transitions = transitions->prochain;
            ajout_valeur(queue, vers);

            s = trie->suppleant[origine];
            //  Transition non définie 
            while (destination_transition(trie, s, caractere) == -1) {
                s = trie->suppleant[s];
            }
            trie->suppleant[vers] = destination_transition(trie, s, caractere);
            // Fonction de sortie 
            if (trie->finite[trie->suppleant[vers]]) {
                trie->finite[vers] = 1;
            }
        }
    }
}


Trie Iniatil_AHO(unsigned char **mots, int nb_max) {
    /*
        Création du trie et complétion des transitions
    */
    Trie trie = create_trie(nb_max * 60);

    int i;
   // Insetion des mots dans le trie
    for (i = 0; i < nb_max; i++) {
        insert_trie(trie, mots[i]);
    }
    // Completion la racine 
    completer_trie(trie);
    // Completion des lien de suppseances
    complete(trie);
    return trie;
}


void aho_corasick(unsigned char **mots, int nb_max, unsigned char *texte) {
    /*
        point d'entrée de l'algorithme d'Aho-Corasick
    */
    int origine = 0, occurrence = 0;
    // Création du trie
    Trie trie = Iniatil_AHO(mots, nb_max);
    // teste si le trie est vide
    if (trie == NULL) 
        return;
    //recherche des mots dans le texte
    for (int i = 0; texte[i] != '\0'; i++) {
        // recherche de suppleant s'il n'y a pas de destination 
        while (destination_transition(trie, origine, texte[i]) == -1) {
            origine = trie->suppleant[origine];
        }
        origine = destination_transition(trie, origine, texte[i]);
        // Incrementation du nombre d'occurence si l'etat est final
        if (trie->finite[origine]) {
            occurrence = occurrence + 1;
        }
    }
    printf("\nLe nombre de mots retrouvés dans le texte est de %d\n occurence", occurrence);
}



int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier des mots> < fichier de text>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    unsigned char * text = (unsigned char *)malloc(MAX_TEXT_SIZE * sizeof(unsigned char));
    unsigned char *words[MAX_WORDS];


    // Lecture des mots depuis le fichier
    FILE* words_file = fopen(argv[1], "r");
        if (!words_file) {
            perror("Erreur lors de la lecture du fichier de mots");
            return EXIT_FAILURE;
        }

        int words_count = 0;
        char tampon[MAX_WORD_SIZE];
        while (fgets(tampon, sizeof(tampon), words_file) != NULL && words_count < MAX_WORDS) {
            tampon[strcspn(tampon, "\n")] = '\0'; // Supprimer le saut de ligne
            words[words_count] = (unsigned char *)strdup(tampon);
            // printf("%s\n", words[words_count]);
            words_count++;
        }

    fclose(words_file);

    // Lire le texte depuis le fichier
    FILE* text_file = fopen(argv[2], "r");
        if (!text_file) {
            perror("Erreur lors de la lecture du fichier de texte");
            return EXIT_FAILURE;
        }

        fseek(text_file, 0, SEEK_END);
        long fileSize = ftell(text_file);
        fseek(text_file, 0, SEEK_SET);


        fread(text, 1, fileSize, text_file);
    fclose(text_file);


    printf("Nombre d'occurences \n");
    clock_t debut = clock();
    
    // execution de aho_corasick
    aho_corasick(words, words_count, text);
    clock_t fin = clock();
    printf("Durée d'exécution de la recherche est de : %f seconde(s)\n", (double) (fin - debut) / CLOCKS_PER_SEC);

    return 0;
}
