#include <stdio.h>
#define LEN_ALPHA 4
#define LEN_ETAT 12



struct _trie {
    int maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite; /* etats terminaux */
};
typedef struct _trie *Trie;
// Table de hachage :
struct _list {
    int startNode, /* etat de depart de la transition */
    targetNode; /* cible de la transition */
    unsigned char letter; /* etiquette de la transition */
    struct _list *next; /* maillon suivant */
};

typedef struct _list *List;
// struct _trie {
// int maxNode; /* Nombre maximal de noeuds du trie */
// int nextNode; /* Indice du prochain noeud disponible */
// List *transition; /* listes d’adjacence */
// char *finite; /* etats terminaux */
// };

// Pour les deux :


Trie createTrie(int maxNode);
void  insertInTrie(Trie tri, char *word);
int isInTrie(Trie tri, char *word);

List createList(int startNode, int targetNode, unsigned char letter);

void insertInList(List *list, int startNode, int targetNode, unsigned char letter);

int isInList(List list, int startNode, unsigned char letter);