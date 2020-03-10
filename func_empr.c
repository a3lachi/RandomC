#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head_catg.h"
#include "head_empr.h"



void Showemprunt(empru* emp) 
{
	if (emp) 
	{
		empru* ptremp=emp;
		while (ptremp)
		{
			printf("             	Le livre numero %d â retourner le %d/%d/%d  \n",ptremp->nmb,(ptremp->datret)/10000,((ptremp->datret)/100)%100,(ptremp->datret)%100);
			ptremp=ptremp->suivant;
		}
		printf("\n\n");
	}
	else
		printf("\n                   La structure des emprunts est vide.\n") ;
}

int book_found(catg_t* cat, int num , int nb_emp )
{
	catg_t* catptr=cat;

	int bol=-1;

	while (catptr && bol<0) 
	{
		livr_t* livptr=catptr->livr_te;

		while (livptr && bol<0) 
		{
			if (livptr->num==num) 
			{
				bol=1;
				livptr->emprunt=nb_emp;
			}
			livptr=livptr->suivant;
		}
		catptr=catptr->suivant;
	}
	
	return bol;
}

int cel_emp(empru ** precemp, int num, int date)
{
	empru *nouv=calloc(1,sizeof(empru)) ;

	if (nouv)
	{
		nouv->nmb=num;
		nouv->datret=date;
		nouv->suivant=(*precemp)->suivant;
		*precemp=nouv;
		return 1;
	}
	
	return -1;
}

empru** cherche_emp(empru** emp, int date) 
{
	empru ** prec=emp;
	empru  *cour=*emp;
	while (cour && (*cour).datret>date)
	{
		*prec=cour->suivant;
		cour=cour->suivant;
	}
	return prec;
}


int insert(catg_t* cat,  char* fich , empru ** emp) 
{	
	FILE* fichier=fopen(fich,"r");
	
	if (fichier)
	{

		if (cat)
		{
			int   num=0 , date=0;
			char    lin[20]="zzmax";
			empru     **prec;

			while(fgets(lin,256,fichier))   // Lecture de fichier 
			{
				sscanf(lin,"%d %d",&num,&date);  

				if (book_found(cat,num,1)>0)    // Livre trouvé
				{
					prec=cherche_emp(emp,date);  // Si l'insertion ne se passe pas bien on quitte 
					if (cel_emp(prec,num,date)<0)
						return 1;
				}
				
			}
			fclose(fichier);
			return 1;
		}
		else 
		{
			printf("             La bibliothéque des livres est vide.\n");
			return -1;
		}

	}
	else 
	{
		printf("             Veuillez indiquer bien le nom du fichier.");
		return -1;
	}
}





void SupValeur(catg_t* CAT, empru** emp, char* fich)
{
	FILE* fichier=fopen(fich,"r");
	if (fichier)
	{
		char      buf[20]="zzmax";
		int        num=0;
		empru ** prec;
		while (fgets(buf,20,fichier))
		{
			printf("adresse *emp :%d\n",(int)*emp);
			sscanf(buf,"%d",&num);

			if (book_found(CAT,num,0)>0)
			{
				prec=recherche(emp,num);
				if (*prec && (*prec)->nmb==num)
				{
					Supression(prec);
				}
			}
		}
	}

}


void Supression(empru** prec)
{
	empru    *cour=*prec;
	*prec=cour->suivant;
	//free(*cour);
}


empru ** recherche(empru** emp, int num)
{
	empru ** prec=emp;
	empru  *cour=*emp;
	while (cour && (*cour).nmb!=num)
	{
		*prec=cour->suivant;
		cour=cour->suivant;
	}
	return prec;
	
}








void print_dat(empru* emp, int dat) 
{
	empru               * ptremp=emp;
	printf("livr_te numero de date inferieir : ");

	while(ptremp) 
	{
		if (ptremp->datret < dat)
			printf("%d ",ptremp->nmb);

		ptremp=ptremp->suivant;
	}
}



void save_emp(empru* emp) 
{
	if (emp)
	{
		FILE* fichier=fopen("emprunt_copy.txt","w");
		if (fichier)
		{
			empru* ptremp=emp;
		
			while (ptremp) 
			{
				fprintf(fichier,"%d %d\n",ptremp->nmb,ptremp->datret);
				ptremp=ptremp->suivant;
			}

			fclose(fichier);
			printf("             La liste des emprunts a bien été sauvegardé\n.");
		}
	}
	else
		printf("             La liste des emprunts est vides. Aucune sauvegarde n'a été faite.\n");
}



void free_emp(empru** emp) 
{
	if (*emp)
	{
		empru              * ptremp=*emp, 
					   * ptrprec=*emp;

		while (ptremp) 
		{
			ptremp=ptremp->suivant;
			free(ptrprec);
			ptrprec=ptremp;
		}

		*emp=NULL;  //Debug
	}     
}


