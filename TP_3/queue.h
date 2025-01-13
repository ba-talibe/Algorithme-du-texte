

struct _transition {
  int origine;
  int vers;
  unsigned char letter;
  struct _transition *prochain;
};

typedef struct _transition *Trans;
/* Les elements de la queue */

struct _element {
	int valeur;
	struct _element *prochain;
};

typedef struct _element *Element;
struct _queue {
	int taille;
	Element debut;
	Element fin;
};
typedef struct _queue *Queue;

struct _list {
    int start_node, /* etat de depart de la transition */
    target_node; /* cible de la transition */
    unsigned char letter; /* etiquette de la transition */
    struct _list *next; /* maillon suivant */
};

typedef struct _list *List;