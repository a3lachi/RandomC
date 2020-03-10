
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head_catg.h"
#include "head_empr.h"


// alias xx='./prog fich.txt emp_ajout.txt emp_del.txt'


// est-ce que notre programme doit créer une bibliothéque ?
// est ce que desallouer la memoire le moment des suppressions demprunts ?
// test avec int ou tout void ?

// prckon fesai pa l'absence les seances d'avant


catg_t* z_catg_t=NULL;

empru* z_empr=NULL;





void style_bib(void)
{
	printf("\n");
	printf("             ----------------------------------------------------------\n");
	printf("             ------|  1. Creer une nouvelle bibiliothéque  ------------\n");
	printf("             ------|  2. Afficher la bibliothéque des livres  ---------\n");
	printf("             ------|  3. Creer une nouvelle liste d'emprunts  ---------\n");
	printf("             ------|  4. Supprimer des emprunts  ----------------------\n");
	printf("             ------|  5. Afficher la liste des emprunts  --------------\n");
	printf("             ------|  6. Sauvegarder et quitter  ----------------------\n");
	printf("             ----------------------------------------------------------\n");
}

void start_prog(char* fich_bib ,char* fich_ajout_emp , char* fich_del_emp)
{
	printf("\n\n\n");
	system("read -n 1 -s -r -p '                   Cliquez sur une touche pour continuer' && clear");
	style_bib();
	char   lin[5]="5";
	int    cas=0;
	printf("\n                   Selectionner une tâche : ");
	if(fgets(lin,4,stdin))
	{
		printf("\n");
		sscanf(lin,"%d",&cas);
		if (0<cas && cas<6)
		{
			switch(cas) 
			{
				
				case 1 :
					free_bib(&z_catg_t);
					if (Remplir(fich_bib,&z_catg_t)>0) 
					{
						printf("             La structure des livres est rempli avec succés.\n");
					}
					else
						printf("             Une erreur est survenue lors du remplissage de la structure des livres.\n");
					break;
				
				case 2 :
					Showstruct(z_catg_t);
					break;
				
				case 3 :
					free_emp(&z_empr);
					if (insert(z_catg_t, fich_ajout_emp, &z_empr)>0)
					{
						printf("             La liste des emprunts est crée avec succés.\n");
					}
					else
						printf("             Une erreur est survenue lors de la création du liste des emprunts.\n");
					break;
				
				case 4 :
					SupValeur(z_catg_t,&z_empr,fich_del_emp);
					// if (delt(z_catg_t, fich_del_emp, &z_empr)>0)
					// 	printf("             La supression des anciens emprunts a bien été effectué.\n");
					// else
					// 	printf("             Une erreur est survenue lors de la supresision des listes des emprunts.\n");
					break;
				
				case 5 :
					Showemprunt(z_empr);
					break;

			}
			start_prog(fich_bib,fich_ajout_emp,fich_del_emp);
		}

		else if (cas==6) 
		{
			save_emp(z_empr);
		}
	}
	free_bib(&z_catg_t);
	free_emp(&z_empr);
}






int main(int argc, char* argv[]) 
{
	(void)argc;

	
	start_prog(argv[1],argv[2],argv[3]);

	return 0;
}
