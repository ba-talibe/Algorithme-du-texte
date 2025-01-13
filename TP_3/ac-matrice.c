#include "trie.h"
#include "queue.h"

#define MAX_WORD_LENGTH 60
#define MAX_WORDS 100
#define MAX_TEXT_LENGTH 5000000

/* Utilisation de la structure de matrice de transitions */
typedef struct _trieMatrice *Trie;

/*****************************************************************************/
/* Chercher noeud qui contient notre lettre                                  */
/*****************************************************************************/
int chercher_noeud(List list, unsigned char l) {
    List temp = list;
    while (temp != NULL) {
        if (temp->letter == l) {
            return temp->targetNode;
        }
        temp = temp->next;
    }
    return -1; // Lettre non trouvée
}

/*****************************************************************************/
/* Insertion d'un nouveau noeud                                              */
/*****************************************************************************/
void nouveau_noeud(List *llist, unsigned char c, int noeud) {
    List temp = (List)malloc(sizeof(struct _list));
    temp->letter = c;
    temp->targetNode = noeud;
    temp->next = *llist; // Insertion au début
    *llist = temp;
}

/*****************************************************************************/
/* Utilisation d'une file (pour les états de suppléance)                     */
/*****************************************************************************/
Queue createQueue() {
    Queue queue = (Queue)malloc(sizeof(struct _queue)); // Allocation de mémoire
    queue->debut = NULL;
    queue->fin = NULL;
    queue->taille = 0;
    return queue;
}

/*****************************************************************************/
/* Insertion dans une file                                                   */
/*****************************************************************************/
void insertQueue(Queue queue, int valeur) {
    if (queue->taille == 0) { // Queue vide
        queue->fin = (Element)malloc(sizeof(struct _element));
        queue->fin->valeur = valeur;
        queue->fin->prochain = NULL;
        queue->debut = queue->fin;
    } else { // Queue non vide
        queue->fin->prochain = (Element)malloc(sizeof(struct _element));
        queue->fin->prochain->valeur = valeur;
        queue->fin->prochain->prochain = NULL;
        queue->fin = queue->fin->prochain;
    }
    queue->taille = queue->taille + 1;
}

/*****************************************************************************/
/* Récupération de valeur d'une file                                         */
/*****************************************************************************/
int recupQueue(Queue queue) {
    if (queue->taille == 0) return -1; // Queue vide
    int valeur = queue->debut->valeur;
    queue->debut = queue->debut->prochain;
    queue->taille = queue->taille - 1; // Décrémenter la taille de la file
    return valeur;
}

/*****************************************************************************/
/* Création du trie                                                          */
/*****************************************************************************/
Trie createTrie(int maxNode) {
    int i, j;
    Trie trie = (Trie)malloc(sizeof(struct _trieMatrice)); // Allocations nécessaires
    trie->transition = (int **)malloc(maxNode * sizeof(int *));
    trie->finite = (char *)malloc(maxNode * sizeof(char));
    trie->mon_suppl = (int *)malloc(maxNode * sizeof(int));
    trie->maxNode = maxNode;
    trie->nextNode = 1;
    for (i = 0; i < maxNode; i++) { // Initialisations
        trie->mon_suppl[i] = -1; // Initialiser les états de suppléance
        trie->transition[i] = (int *)malloc(256 * sizeof(int));
        for (j = 0; j < 256; j++) {
            trie->transition[i][j] = -1; // Initialiser la matrice à -1
        }
        trie->finite[i] = 0; // Tous les états sont non terminaux
    }
    return trie; // Retourner le trie
}

/*****************************************************************************/
/* Insertion dans le trie                                                    */
/*****************************************************************************/
void insertTrie(Trie mon_trie, unsigned char *w) {
    int j = 0, i = 0, noeud_courant = 0;
    while (w[j] != '\0') j++; // Récupération de la taille du mot
    int taille_mot = j;

    while (w[i] != '\0') { // Début insertion
        if (mon_trie->transition[noeud_courant][w[i]] == -1) { // Vérifier possibilité d'insertion
            if (taille_mot - i > mon_trie->maxNode - mon_trie->nextNode) return; // Quitter
            mon_trie->transition[noeud_courant][w[i]] = mon_trie->nextNode;
            noeud_courant = mon_trie->nextNode;
            mon_trie->nextNode = mon_trie->nextNode + 1;
        } else {
            noeud_courant = mon_trie->transition[noeud_courant][w[i]];
        }
        i++;
    }
    mon_trie->finite[noeud_courant] = 1; // Dernier nœud comme terminal
}

/*****************************************************************************/
/* Compléter la racine (les transitions vers la racine)                      */
/*****************************************************************************/
void completer_trie(Trie trie) {
    for (int i = 0; i < 256; i++) { // 256 : caractères non signés
        if (trie->transition[0][i] == -1) trie->transition[0][i] = 0;
    }
}

/*****************************************************************************/
/* Rechercher et retourner les transitions                                   */
/*****************************************************************************/
Trans avoirTrans(Trie trie, int ISRoot, int origine) {
    int isRoot = ISRoot ? -1 : 0;
    Trans transitions = NULL, temp;
    for (int i = 0; i < 256; i++) {
        if (trie->transition[origine][i] > isRoot) { // Ajouter la transition à la liste
            temp = (Trans)malloc(sizeof(struct _transition));
            temp->origine = origine;
            temp->letter = i;
            temp->vers = trie->transition[origine][i];
            temp->prochain = transitions;
            transitions = temp;
        }
    }
    return transitions;
}

/*****************************************************************************/
/* Chercher et retourner le 'vers' d'une transition                          */
/*****************************************************************************/
int chercher_vers(Trie trie, int src, unsigned char c) {
    return trie->transition[src][c]; // Retourner la destination
}
.
