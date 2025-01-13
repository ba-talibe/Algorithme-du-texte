#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Includes de la structure list  */
struct _list {
  int target_node;	/* cible de la transition     */
  unsigned char letter; /* etiquette de la transition */
  struct _list *next;	/* maillon suivant            */
};

typedef struct _list *List;

/* Includes de la structure listes  */
struct _trie_hachage {
	
  int max_node;	         	/* Nombre maximal de noeuds du trie    */
  int next_node;	        	/* Indice du prochain noeud disponible */
  List *transition; 		/* listes d’adjacence                  */
  char *finite;	    		/* etats terminaux                     */
  int *suppleant;		/* état de suppléance                  */
  
};

/* Structure matrice  */

struct _trie_matrice {
  int max_node;	   		/* Nombre maximal de noeuds du trie	*/
  int next_node;	    		/* Indice du prochain noeud disponible 	*/
  int **transition; 		/* matrice de transition 		*/
  char *finite;	   		/* etats terminaux 			*/
  int *suppleant;		/* état de suppléance                  	*/
};