#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"

const char alphabet[LEN_ALPHA] = {'a', 'c', 't', 'g'};


Trie createTrie(int maxNode){
    Trie tri = (Trie) malloc(sizeof(Trie));
    tri->maxNode = maxNode;
    tri-> nextNode = 1;
    tri->finite = (char *)malloc(LEN_ETAT * sizeof(char));
    for (int i = 0; i < LEN_ETAT; i++) {
            tri->finite[i] = 0;
    }

    int **table = (int **)malloc(LEN_ETAT * sizeof(int *));
    for (int i = 0; i < LEN_ETAT; i++) {
        table[i] = (int *)malloc(LEN_ALPHA * sizeof(int));
    }

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


List createList(int startNode, int targetNode, unsigned char letter){
    List list = (List)malloc(sizeof(List));
    list->startNode = startNode;
    list->targetNode = targetNode;
    list->letter = letter;
    list->next = NULL;
    return list;
}