/*
main.c
*/
#define LEN_ALPHA 4
#define LEN_ETAT 12
#include <stdio.h>



const char alphabet[LEN_ALPHA] = {'a', 'c', 't', 'g'};
struct _trie {
    int maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite; /* etats terminaux */
} TrieStruct;
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
typedef struct _trie *Trie;

Trie createTrie(int maxNode){
    Trie tri = (Trie)malloc(sizeof(TrieStruct));
    tri->maxNode = maxNode;
    tri-> nextNode = 1;
    int finite[LEN_ETAT] = (int *)malloc(LEN_ETAT * sizeof(int));
    for (int i = 0; i < LEN_ETAT; i++) {
            finite[i] = 0;
    }
    tri->finite = finite;

    int **table = (int **)malloc(LEN_ETAT * sizeof(int *));
    for (int i = 0; i < LEN_ETAT; i++) {
        table[i] = (int *)malloc(LEN_ALPHA * sizeof(int));
    }

    int value = 1;
    for (int i = 0; i < LEN_ETAT; i++) {
        for (int j = 0; j < LEN_ALPHA; j++) {
            table[i][j] = 0;
        }
    }
    tri->transition = table;
    return tri;
}

void  insertInTrie(Trie tri, char *word){
    int i = 0;
    int etat = 0;
    while (word[i] != '\0') {
        int j = 0;
        while (j < LEN_ALPHA && word[i] != alphabet[j]) {
            j++;
        }
        if (j < LEN_ALPHA) {
            if (tri->transition[etat][j] == 0) {
                tri->transition[etat][j] = tri->nextNode;
                tri->nextNode++;
            }
            etat = tri->transition[etat][j];
            i++;
        } else {
            i++;
        }
    }
    tri->finite[etat] = 1;
}

int isInTrie(Trie tri, char *word){
    int i = 0;
    int etat = 0;
    while (word[i] != '\0') {
        int j = 0;
        while (j < LEN_ALPHA && word[i] != alphabet[j]) {
            j++;
        }
        if (j < LEN_ALPHA) {
            if (tri->transition[etat][j] == 0) {
                return 0;
            }
            etat = tri->transition[etat][j];
            i++;
        } else {
            i++;
        }
    }
    return tri->finite[etat];
}

int main(void)
{
    // creer l'alphabet
    
    // creer le lamguage
     
    char table[3][20] = {"acagt", "acgt", "cagt"};
    // creer la table de transition
    Trie tri = createTrie(20);
    for (int i = 0; i < 3; i++) {
        insertInTrie(tri, table[i]);
    }
    printf("%d\n", isInTrie(tri, "acagt"));
    return 0;
}
