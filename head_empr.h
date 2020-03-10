
/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                   Structures utilisateur             */
/*                                                                      */
/* -------------------------------------------------------------------- */
typedef struct empru {
	int               nmb;
	int               datret;
	struct empru    * suivant;
} empru ;



/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                   Fonctions utilisées                */
/*                                                                      */
/* -------------------------------------------------------------------- */
void Showemprunt(empru* emp) ;
int book_found(catg_t* cat, int num , int nb_emp );
empru** cherche_emp(empru** emp, int date) ;
int insert(catg_t* cat, char* fich , empru ** emp) ;
int cel_emp(empru ** precemp, int num, int date);
void print_dat(empru* emp, int dat) ;
void save_emp(empru* emp) ;
void free_emp(empru** emp);



void SupValeur(catg_t* CAT,empru** emp, char* fich);
void Supression(empru** prec);
empru ** recherche(empru** emp, int num);


