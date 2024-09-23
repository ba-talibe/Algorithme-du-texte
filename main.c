/*
main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"


int main(void){
    // creer l'alphabet
    
    // creer le lamguage
     
    char table[3][20] = {"acagt", "acgt", "cagt"};
    // creer la table de transition
    Trie tri = createTrie(12);
    for (int i = 0; i < 3; i++) {
        insertInTrie(tri, table[i]);
    }
    printf("%d\n", isInTrie(tri, "acagt"));
    return 0;
}
