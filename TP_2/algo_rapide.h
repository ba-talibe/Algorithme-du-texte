


int bon_prefix(char* mot,int indexe);
int calcul_bord(const char* mot);
int algo_morris_pratt(char *texte, char *motif);

void calcul_meil_pref(const char *mot, int *tab);
int plus_long_bord(const char *mot);
int algo_knut_morris_pratt(char *texte, char *motif);

void calcul_table_bon_suffix(const char *mot, int *tab_suff, int *tab_bon_suff);
int algo_Boyer_Moore(char *texte, char *motif);

void calcul_dern_occ(const char *mot, int m, int *tab);
void calcul_table_bon_suffix2(const char *mot, int *tabSuff, int *tabBonSuff);
int algo_Horspool(char *texte, char *motif);

void calcul_dern_occ2(const char *mot, int m, int *tab);
int algo_quick_search(char *texte, char *motif);
