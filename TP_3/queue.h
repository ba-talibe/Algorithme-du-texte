

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

