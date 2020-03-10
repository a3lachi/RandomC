
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head_catg.h"



/* -------------------------------------------------------------------- */
/*                                                                      */
/* Showconstruct          Affiche le contenu d'une structure catg_t     */
/*                                                                      */
/* En entrée: CAT, pointeur sur la structure à afficher                 */
/*                                                                      */
/* -------------------------------------------------------------------- */
void Showstruct(catg_t* catt)
{
	if (catt) // Si la structure existe
	{
		catg_t* ptrcat=catt ;   // Pointeur sur la structure catg_t

		while (ptrcat)   // Parcour de la structure catg_t
		{
			printf("             	Nom du catégorie : %s\n",ptrcat->nom) ;  // Affichage du nom de categorie

			livr_t * livptr=ptrcat->livr_te;   // Pointeur sur la structure livr_t

			while (livptr) // Parcour de la strucutre livr_t
			{
				printf("             	Numéro et titre du titre du livre et indice d'emprunt : %d %s %d \n",livptr->num,livptr->titre,livptr->emprunt);  // Affichage des informations du livre
				
				livptr=livptr->suivant;  // Passage au livre suivant
			}

			ptrcat=ptrcat->suivant; // Passage au catégorie suivante
		}

		printf("\n");  // Style d'affichage 
	}
	else  // La structure n'existe pas
	{
		printf("\n                   La bibliothéque des livres est vide.\n") ;
	}
}




void free_bib(catg_t** cat) 
{
	if (*cat)
	{
		catg_t*          catptr=*cat,
					   * ptrprec=*cat;

		while (catptr) 
		{
			livr_t* livptr=catptr->livr_te , *livprec=catptr->livr_te;

			while(livptr) 
			{
				livptr=livptr->suivant;

				free(livprec);

				livprec=livptr;
			}

			catptr=catptr->suivant;

			free(ptrprec);

			ptrprec=catptr;
		}
		*cat=NULL;
	}
}




/* -------------------------------------------------------------------- */
/*                                                                      */
/* Remplir_livre      	Rempli la toute la cellule livr_t               */
/*                      d'une structure catg_t                          */
/*                                                                      */
/* En entrée: fichier, pointeur sur la source de lecture                */
/*            livrptr, double pointeur sur la structure                 */
/*                     livr_t à modifier                                */
/*            nb_liv, nombre de livre à lire                            */
/*                                                                      */
/* En sortie: La valeur entière retournée est 0 si les chaînes sont     */
/*            égales; négative si s1 < s2 et positive si s1 > s2.       */
/*                                                                      */
/* -------------------------------------------------------------------- */



int Cellule_liv(FILE* fichier, livr_t ** livre) 
{
	*livre=calloc(1,sizeof(livr_t));
	if (*livre) 
	{
		char	       char_liv[256]="hell" ;  
		if(fgets(char_liv,256,fichier)) 
		{
			sscanf(char_liv,"%d %[^\t\n]",&((*livre)->num),(*livre)->titre);
			(*livre)->suivant=NULL;
			return 1;
		}
		else
			return -1;
	}
	else 
		return -1;
}

int Remplir_livre(FILE* fichier, livr_t** livr , int nb_liv) {

	int            i=0;
	(void) Cellule_liv(fichier,livr) ;   // Initialisation
	
	livr_t *livptr=*livr;       

	for (i=0;i<nb_liv-1;i++)    // Lecture des livres 
	{
		if (Cellule_liv(fichier,&(livptr->suivant))>0)     // Si la creation et remplissage d'une cellule se passe bien 
		{
			livptr=livptr->suivant;          // Passage au livre suivant 
		}
		else
			return -1;
		
	}
	return 1;


}










/* -------------------------------------------------------------------- */
/*                                                                      */
/* Remplir_catg     Rempli le nom de la structure catg_t et extracte    */
/*                  le nombre de livre à lire                           */
/*                                                                      */
/* En entrée: fichier, pointeur sur la source de lecture                */
/*            CAT, double pointeur sur la structure à modifier          */
/*                                                                      */
/* En sortie: La valeur entière retournée est le nombre de livre        */
/*            si la lecture du fichier s'est bien passé                 */
/*			  et est -1 sinon                                           */
/*                                                                      */
/* -------------------------------------------------------------------- */

int Remplir_catg(FILE* fichier, catg_t** CAT) 
{
	char	        char_cat[256]="ZZMAX";     // Definition d'une chaine de caractére pour la lecture

	if (fgets(char_cat,256,fichier))    // Lecture du fichier et test sur la lecture
	{
		int	        nb_liv=-1;      // Le nombre de livre 

		sscanf(char_cat,"%s %d",(*CAT)->nom,&nb_liv);    // Extraction du nom de categorie et nombre de livre
		(*CAT)->suivant=NULL;

		return nb_liv;   // La lecture se passe bien
	}
	return -1;  // La lecture ne s'est pas bien passé
	
}


int Remplir_cell_catg(FILE* fichier, catg_t **CAT)
{
	*CAT=calloc(1,sizeof(catg_t));
	if (*CAT)
	{
		 
		int 		nb_liv=Remplir_catg(fichier,CAT);

		if (nb_liv>0)
		{
			if (Remplir_livre(fichier,&((*CAT)->livr_te),nb_liv)>0) 
			{
				return 1;
			}
			else
				return -1;
		}
		else 
			return -1;
	}
	else {

		return -1;
	}
}





/* -------------------------------------------------------------------- */
/*                                                                      */
/* Remplir          Vide le fichier dans la structure catg_t            */
/*                                                                      */
/* En entrée: fichier, pointeur sur la source de lecture                */
/*            CAT, double pointeur sur la structure à modifier          */
/*                                                                      */
/* En sortie: La valeur entière retournée est 1 si le remplissage de    */
/*            la structure s'est bien passé et est -1 sinon             */
/*                                                                      */
/* -------------------------------------------------------------------- */
int Remplir(char* fich, catg_t** CAT)
{
	FILE * fichier=fopen(fich,"r");
	if (fichier) 
	{

		(void) Remplir_cell_catg(fichier,CAT);

		int 			cond=1;
		
		catg_t        * ptrcatg=*CAT;
		
		while (!feof(fichier) && cond>0) 
		{
			cond=Remplir_cell_catg(fichier,&(ptrcatg->suivant));
			
			ptrcatg=ptrcatg->suivant;
		}

		fclose(fichier);
		
		return cond;
	}
	else
	{
		return -1;
	}
	
}










