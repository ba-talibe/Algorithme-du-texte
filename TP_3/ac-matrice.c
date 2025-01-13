#include "trie.h"
#include "queue.h"

#define MAX_WORD_LENGTH 60
#define MAX_WORDS 100
#define MAX_TEXT_SIZE 5000000

// Utilisation de la structure de matrice de transitions 
typedef struct _trie_matrice *Trie;


void ajout_noeud(List *llist, unsigned char c, int noeud) {
    List copie = (List)malloc(sizeof(struct _list));
    copie->letter = c;
    copie->target_node = noeud;
    copie->next = *llist; // Insertion au début
    *llist = copie;
}

int rechercher_noeud(List list, unsigned char l) {
    List copie = list;
    while (copie != NULL) {
        if (copie->letter == l) {
            return copie->target_node;
        }
        copie = copie->next;
    }
    // Aucune lettre trouvée
    return -1; 
}

Queue create_queue() {
    // Allocation de mémoire
    Queue queue = (Queue)malloc(sizeof(struct _queue)); 
    queue->debut = NULL;
    queue->fin = NULL;
    queue->taille = 0;
    return queue;
}


void insert_queue(Queue queue, int valeur) {
    /*
        Insert une valeur dans la file
    */
    if (queue->taille == 0) { 
        // la file est vide
        queue->fin = (Element)malloc(sizeof(struct _element));
        queue->fin->valeur = valeur;
        queue->fin->prochain = NULL;
        queue->debut = queue->fin;
    } else { 
        // la file n'est pas vide
        queue->fin->prochain = (Element)malloc(sizeof(struct _element));
        queue->fin->prochain->valeur = valeur;
        queue->fin->prochain->prochain = NULL;
        queue->fin = queue->fin->prochain;
    }
    queue->taille = queue->taille + 1;
}
int recuperer_valeur(Queue queue) {
    /*
        recupere la valeur de la file
    */
    if (queue->taille == 0) return -1; // Queue vide
    int valeur = queue->debut->valeur;
    queue->debut = queue->debut->prochain;
    queue->taille = queue->taille - 1; // Décrémenter la taille de la file
    return valeur;
}

Trie create_trie(int max_node) {
    /*
        Cree une trie
    */
    int i, j;
    Trie trie = (Trie)malloc(sizeof(struct _trie_matrice)); // Allocations nécessaires
    trie->transition = (int **)malloc(max_node * sizeof(int *));
    trie->finite = (char *)malloc(max_node * sizeof(char));
    trie->suppleant = (int *)malloc(max_node * sizeof(int));
    trie->max_node = max_node;
    trie->next_node = 1;
    for (i = 0; i < max_node; i++) { // Initialisations
        trie->suppleant[i] = -1; // Initialiser les états de suppléance
        trie->transition[i] = (int *)malloc(256 * sizeof(int));
        for (j = 0; j < 256; j++) {
            trie->transition[i][j] = -1; // Initialiser la matrice à -1
        }
        trie->finite[i] = 0; // Tous les états sont non terminaux
    }
    return trie; // Retourner le trie
}


void insert_trie(Trie mon_trie, unsigned char *w) {
    /*
        Insert un mot dans le trie
    */
    int j = 0, i = 0, noeud_courant = 0;
    while (w[j] != '\0') j++; // Récupération de la taille du mot
    int taille_mot = j;

    while (w[i] != '\0') { // Début insertion
        if (mon_trie->transition[noeud_courant][w[i]] == -1) { // Vérifier possibilité d'insertion
            if (taille_mot - i > mon_trie->max_node - mon_trie->next_node) 
                return;
            mon_trie->transition[noeud_courant][w[i]] = mon_trie->next_node;
            noeud_courant = mon_trie->next_node;
            mon_trie->next_node = mon_trie->next_node + 1;
        } else {
            noeud_courant = mon_trie->transition[noeud_courant][w[i]];
        }
        i++;
    }
    mon_trie->finite[noeud_courant] = 1; // Dernier nœud comme terminal
}


void completer_trie(Trie trie) {
    /*
        Complerte de trie en ajoutant les transitions manquantes
    */
    for (int i = 0; i < 256; i++) { // 256 : caractères non signés
        if (trie->transition[0][i] == -1) trie->transition[0][i] = 0;
    }
}


Trans recuperer_transition(Trie trie, int est_racine, int origine) {
    int est_racine = est_racine ? -1 : 0;
    Trans transitions = NULL, copie;
    for (int i = 0; i < 256; i++) {
        if (trie->transition[origine][i] > est_racine) { // Ajouter la transition à la liste
            copie = (Trans)malloc(sizeof(struct _transition));
            copie->origine = origine;
            copie->letter = i;
            copie->vers = trie->transition[origine][i];
            copie->prochain = transitions;
            transitions = copie;
        }
    }
    return transitions;
}

int destination_transition(Trie trie, int src, unsigned char c) {
    return trie->transition[src][c]; // Retourner la destination
}



void complete(Trie trie) {
    unsigned char c;
    int origine=0, vers=0, s=0;
        
    /* Création de la file */
    Queue queue = createQueue();
    /* Avoir les transition de la racine */
    Trans transitions = avoirTrans(trie, 0, 0);
    /* Fonction de supp pour les fils de la racine 'sons of the root '*/
    while (transitions != NULL) {
        vers = transitions->vers;
        transitions = transitions->prochain;
        /* inserer dans la file */
        insert_queue(queue, vers);
        /* Destination = racine*/
        trie->suppleant[vers] = 0;
    }
    /* Récupérer les element a partir de la file, et exectuer la fonction de supp */
    while (queue->taille != 0) {
        origine = recupQueue(queue);
        transitions = avoirTrans(trie, 1, origine);
        while (transitions != NULL) {
        origine = transitions->origine;
        c = transitions->letter;
        vers = transitions->vers;
        transitions = transitions->prochain;
        insert_queue(queue, vers);

        s = trie->suppleant[origine];
        /* Transition no définie */
        while (destination_transition(trie, s, c) == -1) {
            s = trie->suppleant[s];
        }
        trie->suppleant[vers] = destination_transition(trie, s, c);
        // Fonction de sortie
        if (trie->finite[trie->suppleant[vers]]) {
            trie->finite[vers] = 1;}
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
    int origine = 0, occurrence = 0, i=0;
    // Création du trie
    Trie trie = Iniatil_AHO(mots, nb_max);
    // teste si le trie est vide
    if (trie == NULL) {return; /* Quitter */}
    //recherche des mots dans le texte
    for (i = 0; texte[i] != '\0'; i++) {
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
        return -1;
    }
    
    unsigned char * text = (unsigned char *)malloc(MAX_TEXT_SIZE * sizeof(unsigned char));
    unsigned char *words[MAX_WORDS];


    // Lecture des mots depuis le fichier
    FILE* words_file = fopen(argv[1], "r");
        if (!words_file) {
            perror("Erreur lors de la lecture du fichier de mots");
            return -1;
        }

        int words_count = 0;
        char tampon[MAX_WORD_LENGTH];
        while (fgets(tampon, sizeof(tampon), words_file) != NULL && words_count < MAX_WORDS) {
            tampon[strcspn(tampon, "\n")] = '\0'; // Supprimer le saut de ligne
            words[words_count] = (unsigned char *)strdup(tampon);
            words_count++;
        }

    fclose(words_file);

    // Lire le texte depuis le fichier
    FILE* text_file = fopen(argv[2], "r");
    if (!text_file) {
        perror("Erreur lors de la lecture du fichier de texte");
        return -1;
    }

    fseek(text_file, 0, SEEK_END);
    long file_size = ftell(text_file);
    fseek(text_file, 0, SEEK_SET);
    fread(text, 1, file_size, text_file);
    fclose(text_file);


    printf("Nombre d'occurences \n");
    clock_t debut = clock();
    
    // execution de aho_corasick
    aho_corasick(words, words_count, text);
    clock_t fin = clock();
    printf("Durée d'exécution de la recherche est de : %f seconde(s)\n", (double) (fin - debut) / CLOCKS_PER_SEC);

    return 0;
}
