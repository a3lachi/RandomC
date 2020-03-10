


/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                   Structures utilisateur             */
/*                                                                      */
/* -------------------------------------------------------------------- */
typedef struct livr_t {
	int                  num;
	char                 titre[20];
	int                  emprunt;
	struct livr_t      * suivant;
} livr_t ;


typedef struct catg_t {
	char                 nom[3];
	livr_t             * livr_te;
	struct catg_t      * suivant;
} catg_t ;







/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                   Fonctions utilisées                */
/*                                                                      */
/* -------------------------------------------------------------------- */
void Showstruct(catg_t* catt);

void free_bib(catg_t** cat);

int Remplir_livre(FILE* fichier, livr_t** livrptr , int nb_liv);

int Remplir_catg(FILE* fichier, catg_t** CAT);

int Remplir(char* fich, catg_t** CAT);

int Cellule_liv(FILE* fichier, livr_t ** livr) ;

int Remplir_cell_catg(FILE* fichier, catg_t **CAT);
