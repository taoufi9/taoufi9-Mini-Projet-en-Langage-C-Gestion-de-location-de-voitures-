#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date
{
    int jj;
    int mm;
    int aa;
}date;
typedef struct voiture
{
 int idVoiture;
 char marque[15];
 char nomVoiture[15];
 char couleur[7];
 int nbplaces;
 int prixJour;
 char EnLocation[4];
} voiture;


typedef struct contratLocation
{
 float numContrat;
 int idVoiture;
 int idClient;
 date debut;
 date fin;
 int cout;
} contrat;

typedef struct Client
{
 int idClient;
 char nom[20];
 char prenom[20];
 int cin;
 char adresse[15];
 int telephone;
}client;

/*----------------------- Visualiser Contrat -----------------------------------*/
void visualiser_contrat(FILE* pf) {
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else
    {
	contrat C ;
	int K=0;
	float N;
	pf=fopen("Contrat.txt","rb+");
	printf("\t\t\tDonnez le num du contrat : ");
	scanf("%f",&N);
	fseek(pf, 0, SEEK_SET);
	while (fread(&C, sizeof(contrat), 1,pf) != 0 && K==0)
    {

	    if (C.numContrat == N)
        {
			K = 1 ;
			break ;
		}

	}
	if (K == 0)
    {
		 printf("\t\t\tERROR Aucun contart aven ce num!\n");
	}
	else
    {
		 fseek(pf,-(sizeof (contrat)),SEEK_CUR) ;
		 printf("\t\t\tLes entrees anciennes : \n");
		 printf("\t\t\tNum de contrat        : %.2f\n",C.numContrat);
		 printf("\t\t\tVoiture ID            : %d\n",C.idVoiture  );
		 printf("\t\t\tClient ID             : %d\n",C.idClient  );
		 printf("\t\t\tDebu(jour mois annee) : %d %d %d\n",C.debut.jj , C.debut.mm , C.debut.aa  );
		 printf("\t\t\tFin(jour mois annee)  : %d %d %d\n",C.fin.jj , C.fin.mm , C.fin.aa  );
		 printf("\t\t\tCOUT : %d\n",C.cout  );
	}

 	fseek(pf, 0, SEEK_SET);
 	fclose(pf);
    }
}

/*----------------------- louer voiture-----------------------------------------*/

void louer_voiture(FILE *pfv , FILE *pfclt , FILE *cont,FILE *templ){
    if(pfv == 0 || pfclt == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
	client C ;
	voiture test ;
	voiture V ;
	contrat CON ;
	int K = 0;
	int L = 0 ;
	int id;

    printf("\t\t\t Saisir votre ID  :");
    scanf("%d",&id);
    fseek(pfclt, 0, SEEK_SET);

    while (fread(&C, sizeof(client), 1, pfclt) != 0 && K == 0)
    {
        if ( C.idClient == id )
	    {
	      	printf("\t\t\tEntrez les information de la voiture voulu: \n");
	      	printf ("\t\t\tmarque  : ");
			scanf ("%s", &test.marque);
			printf ("\t\t\tnom voiture : ");
			scanf ("%s", &test.nomVoiture);
			printf("\t\t\tcouleur : ");
			scanf("%s",&test.couleur);
			printf("\t\t\tnombre des places :");
			scanf("%d",&test.nbplaces);

	        while (fread(&V, sizeof(voiture), 1, pfv) != 0 && L == 0)
			{
				/* comparaison des specifications inserer avec les voitures disponibles*/
	            if(strcmp(V.marque,test.marque)==0  &&  strcmp(V.nomVoiture,test.nomVoiture)==0  &&  strcmp(V.couleur,test.couleur)==0   &&    V.nbplaces==test.nbplaces    )
	            {
								/* changement de la valeur de ---enlocation-- et insersion des info de contrat */
                                if(strcmp(V.EnLocation, "Non") == 0 || strcmp(V.EnLocation, "non") == 0 || strcmp(V.EnLocation, "NON") == 0)
                                {
									strcpy(V.EnLocation , "Oui");
	                                printf("\t\t\tCette voiture est disponible!\n");
	                                printf("\t\t\tchoisir le numero de votre contrat : ");
	                                scanf("%f",&CON.numContrat);
	                                CON.idVoiture = V.idVoiture ;
	                                CON.idClient = id ;
	                                printf("\t\t\tDate du debu ?(jour mois annee):");
	                                scanf("%d %d %d" , &CON.debut.jj,&CON.debut.mm,&CON.debut.aa);
	                                printf("\t\t\tDate dy fin ?(jour mois annee):");
	                                scanf("%d %d %d" , &CON.fin.jj, &CON.fin.mm , &CON.fin.aa);
	                                CON.cout = ( CON.fin.jj - CON.debut.jj ) * V.prixJour ;
	                                fseek(cont, 0, SEEK_END);
	                                fwrite (&CON, sizeof(contrat), 1, cont);
	                                L = 1 ;
	                                system("cls");
                                }else
                                    {
                                        printf("\t\t\tCette voiture est deja en location!\n");
                                        L = 1 ;
                                    }
	            }
	            fwrite(&V,sizeof(voiture),1,templ);
	        }

			if(L == 0)
            {
                printf("\t\t\t cette voiture n'est pas disponible ! \n");
			}
	        K =1;
		}
	}
	if (K == 0) {
	printf("\t\t\t on a aucun voiture avec ce nom,veuillez enregister vos info dans le menu /gestion de clients/\n");
	}
	fseek(pfclt, 0, SEEK_SET);
	fseek(cont, 0, SEEK_SET);
	fclose(pfclt);
	fclose(cont);
	fclose(pfv);
    remove("voiture.txt");
    fclose(templ);
    rename("testlouer.txt","voiture.txt");
    }
}

/*----------------------- supprimer contrat ------------------------------------*/

void supprimer_contrat(FILE *pfv ,FILE *cont,FILE *tempct){
    if(pfv == 0 || cont == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
	contrat CON ;
	voiture V ;
	float N;
	int K = 0;
	int L = 0;
	int CTidV = 0;
	char test;

	printf("\t\t\t Contrat Num : ");
	scanf("%f",&N);


	fseek(cont , 0, SEEK_SET);

	/* verification de num de contrat */
	while (fread(&CON, sizeof(contrat), 1, cont) != 0 && K == 0)
    {
		if(CON.numContrat == N )
		{
					K = 1;
					CTidV = CON.idVoiture;
					break;
		}
	}
	if (K == 0)
	{
		system("cls");
		printf("\t\t\tAucun Contrat avec ce nom!\n");
	}

	else {
		fseek(pfv, 0, SEEK_SET);
		while (fread(&V, sizeof(voiture), 1, pfv) != 0 && L == 0)
			{
				/* verification si la voiture est louee ou non*/
				if(V.idVoiture == CTidV && strcmp(V.EnLocation, "Non" ) == 0)
                {
						fseek(cont, 0, SEEK_SET);
						while(fread(&CON, sizeof(contrat), 1, cont))
						{
							if(CON.numContrat == N)
							{
								continue;
							}
							else
							{
							fwrite(&CON,sizeof(contrat),1,tempct);
							}
						}
						L = 1;
					}else
					{
						printf("\t\t\ttu ne peut pas supprimer une contrat avant car cette voiture est deja louee\n");
					}
				}
			}

	if(L != 0){
		fclose(cont);
		remove("contrat.txt");
		fclose(tempct);
		rename("testct.txt" , "contrat.txt");
	}

	fclose(pfv);
    }
}

/*----------------------- modifier Contrat -------------------------------------*/
void modifier_contrat(FILE* pf){
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
	contrat CON ;
	int K = 0;
	int N;
	char test;

	printf("\t\t\tSaisir le num du contrat : ");
	scanf("%d",&N);

	fseek(pf, 0, SEEK_SET);

	/* verification de num de contrat */
	while (fread(&CON, sizeof(contrat), 1, pf) != 0 && K == 0)
    {
        if (CON.numContrat == N)
            {
                K= 1 ;
                break ;
            }
	}

	if (K == 0)
	{
	    printf("\t\t\tCette contrat n'existe pas!\n");
	}
    else
    {
	    fseek(pf,-(sizeof(contrat)),SEEK_CUR) ;
		printf("\t\t\tInformation du contrat : \n");
	    printf("\t\t\tdate debut (jour mois annee): %d %d %d\n",CON.debut.jj , CON.debut.mm , CON.debut.aa  );
	    printf("\t\t\tdate fin (jour mois annee): %d %d %d\n",CON.fin.jj , CON.fin.mm , CON.fin.aa );

	    printf("\t\t\t qu'est ce que tu veux changer ? \n");

	    CON.numContrat = N ;

	    /* modifier la date de debut */

	    printf("debut ? (o/n): ") ;
		scanf("%s",&test) ;
		if(test == 'o')
        {
			    scanf("%d %d %d",&CON.debut.jj,&CON.debut.mm,&CON.debut.aa) ;
        }
		else
        {
			CON.debut = CON.debut  ;
        }
		printf("\n");

		/* modifier la date de fin */

	    printf("fin ? (o/n): ") ;
		scanf("%s",&test) ;
		if(test == 'o')
        {
            scanf("%d %d %d",&CON.fin.jj,&CON.fin.mm,&CON.fin.aa) ;
        }
		else
        {
            CON.fin = CON.fin ;
        }
		printf("\n");

		CON.cout = CON.cout ;

		CON.idClient = CON.idClient ;

		CON.idVoiture = CON.idVoiture ;

		/* sauvegarder les modification */
		fwrite(&CON,sizeof(contrat),1,pf);
    }

    fseek(pf, 0, SEEK_SET);
    fclose(pf);
    }
}

/*----------------------- retourner  voiture -----------------------------------*/

 void retourner_voiture(FILE *cont ,FILE *pfv,FILE *tempr){
     if(cont == 0 || pfv == 0)
     {
         printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
     }
     else{
	voiture V ;
	contrat CON ;
	int K=0;
	float N;

    printf("\t\t\tNUM de contrat : ");
	scanf("%f",&N);

	fseek(cont , 0, SEEK_SET);

	/* verification de num de contrat */
	while (fread(&CON, sizeof(contrat), 1, cont) != 0 && K == 0)
    {
		if(CON.numContrat == N )
		{
					K = 1;
					break;
		}
	}

	if(K == 0)
    {
		printf("\t\t\tcette Contrat n'est pas valable\n");
	}
	else{
		fseek(cont , 0, SEEK_SET);
		while (fread(&CON, sizeof(contrat), 1, cont) != 0)
            {
			if(CON.numContrat == N ){
					fseek(pfv , 0, SEEK_SET);
					while (fread(&V, sizeof(voiture), 1, pfv) != 0) {

						/* changement de la valeur de --enlocation-- */
						if(V.idVoiture == V.idVoiture){
							strcpy(V.EnLocation , "Non");
						}
						/* sauvegarde des modifications dans un fichier temporaire */
						fwrite(&V,sizeof(voiture),1,tempr);
					}
					fclose(pfv);
					remove("voiture.txt");
					fclose(tempr);
					rename("testr.txt","voiture.txt");
					printf("\t\t\tVotre contrat a etait supprimee!\n");
				}
			}
		}
	fseek(cont, 0, SEEK_SET);
	fclose(cont);
     }
}

/*--------------------------------- Menu de location voiture -------------------*/
void Location_Voiture(){
int choix;
    system("cls");
    FILE* cont,*templ,*pfv,*pfclt,*tempr,*tempct;
    pfv = fopen("voiture.txt","rb+");
    pfclt = fopen("client.txt","rb+");
    cont = fopen("contrat.txt","rb+");
    printf("\t\t\t|-----LOCATION VOITURE---------|\n");
    printf("\t\t\t|    Visualisez contrat.......1|\n");
    printf("\t\t\t|    Louer voitures...........2|\n");
    printf("\t\t\t|    Retourner voiture........3|\n");
    printf("\t\t\t|    Modifier contrat.........4|\n");
    printf("\t\t\t|    Supprimer Contrat........5|\n");
    printf("\t\t\t|    Retour...................6|\n");
    printf("\t\t\t Votre choix :");
    scanf("%d",&choix);
    switch(choix)
    {
        case 1:
             visualiser_contrat(cont);
            break;
        case 2:
            templ = fopen("testlouer.txt","wb+");
            louer_voiture(pfv,pfclt,cont,templ);
            break;
        case 3:
            tempr = fopen("testretourner.txt","wb+");
            retourner_voiture(cont,pfv,tempr);
            break;
        case 4:
            modifier_contrat(cont);
            break;
        case 5:
            tempct = fopen("testsupp.txt","wb+");
            supprimer_contrat(pfv,cont,tempct);
            break;
        case 6:
            Menu_principal(cont);
            break;
    }
}




/* -------------------------Liste les voitures --------------------------------*/
void liste_voitures(FILE* pf) {
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    voiture V;
    fseek(pf,0,SEEK_SET);
   while(fread(&V,sizeof(voiture),1,pf) != 0){
     printf("\t\t\tVoiture ID        : %d \n",V.idVoiture);
     printf("\t\t\tLa marque         : %s \n",V.marque);
     printf("\t\t\tnom du voiture    : %s \n",V.nomVoiture);
     printf("\t\t\tCouleur           : %s \n",V.couleur);
     printf("\t\t\tnombre des places :  %d \n",V.nbplaces);
     printf("\t\t\tPrix par Jour     : %d \n",V.prixJour);
     printf("\t\t\tEn Location ?     : %s\n",V.EnLocation);
     printf("\t\t\t------------------------------\n");
   }
    fseek(pf, 0, SEEK_SET);
	fclose(pf);
    }
}
/*--------------------------ajouter  voiture ----------------------------------*/

void ajouter_voiture(FILE* pf) {
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
      voiture V;
      printf("\t\t\tVoiture ID   :");
      scanf("%d",&V.idVoiture);
      printf ("\t\t\tMarque      :");
      scanf ("%s", &V.marque);
      printf ("\t\t\tNOM         :");
      scanf ("%s", &V.nomVoiture);
      printf("\t\t\tCouleur      :");
      scanf("%s",&V.couleur);
      printf("\t\t\tNbr de place :");
      scanf("%d",&V.nbplaces);
      printf("\t\t\tPrix/J       :");
      scanf("%d",&V.prixJour);
      printf("\t\t\tEn location ?:");
      scanf("%s",&V.EnLocation);
      fseek(pf, 0, SEEK_END);
      fwrite(&V, sizeof(voiture),1,pf);
      fseek(pf, 0, SEEK_SET);
      fclose(pf);
      printf("\t\t\tCette Voiture est bien ajoutee!\n");
    }
}

/* -------------------------modifier Voiture ----------------------------------*/
void modifier_voiture(FILE* pf){
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    voiture V ;
    int K = 0;
    int id;
    char test;
    printf("\t\t\tSaisir ID : ");
    scanf("%d",&id);
    fseek(pf, 0, SEEK_SET);
     /* verification de id*/
    while (fread(&V, sizeof(voiture), 1, pf) != 0 && K == 0)
    {
        if (V.idVoiture == id)
        {
            K = 1 ;
            break ;
        }
    }

    if(K == 0)
    {
          printf("Cette voiture  n'existe pas\n");
    }else{

            fseek(pf,-(sizeof(voiture)),SEEK_CUR) ;
            printf("\t\t\tInformation du voiture \n");
            printf("\t\t\tmarque     : %s\n",V.marque  );
            printf("\t\t\tnom        : %s\n",V.nomVoiture  );
            printf("\t\t\tcouleur    : %s\n",V.couleur  );
            printf("\t\t\tnbplaces   : %d\n",V.nbplaces  );
            printf("\t\t\tprix/jour  : %d\n",V.prixJour  );
            printf("\t\t\tqu'est ce que tu veux changer ?\n ");

            V.idVoiture = id;
            /* modifier la marque */
            printf("\t\t\tmarque ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNew Marque : ");
                scanf("%s",&V.marque);
            }else
            {
                strcpy(V.marque , V.marque);
            }
            printf("\n");

            /* modifier le nom */
            printf("\t\t\tnom2 ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW nom : ");
                scanf("%s",&V.nomVoiture) ;
            }else
            {
                strcpy(V.nomVoiture,V.nomVoiture);
            }
             printf("\n");

            /* modifier la couleur */
            printf("\t\t\tcouleur ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW couleur : ");
                scanf("%s",&V.couleur) ;
            }else
            {
                strcpy(V.couleur,V.couleur) ;
            }
            printf("\n");

             /* modifier nb places*/
            printf("\t\t\tnb palces ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW nb de places : ");
                scanf("%d",&V.nbplaces) ;
            }else
            {
                V.nbplaces = V.nbplaces ;
            }
            printf("\n");

            /* modifier prix/j*/
            printf("\t\t\tprix/j ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW prix/j ? : ");
                scanf("%d",&V.prixJour);
            }else
            {
                V.prixJour = V.prixJour ;
            }
            printf("\n");

            fwrite(&V,sizeof(voiture),1,pf);
        }

        fseek(pf, 0, SEEK_SET);
        fclose(pf);
        printf("\t\t\tCette Voiture est bien modifiee!\n");
    }
}

/*--------------------------supprimer voiture----------------------------------*/
void supprimer_voiture(FILE* pf,FILE* pft){
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    voiture V ;
    int K = 0;
    int id;

    printf("\t\t\t ID a supprimee : ");
    scanf("%d",&id);

    fseek(pf, 0, SEEK_SET);

    // verification de id
    while (fread(&V, sizeof(voiture), 1, pf) != 0 && K == 0)
    {
        if (V.idVoiture == id)
        {
            K = 1 ;
            break ;
        }
    }

    if (K == 0)
    {
        printf("\t\t\tCette voiture n'existe pas!\n");
        system("pause");
    }

    fseek(pf, 0, SEEK_SET);

    /* copier les voitures qui n'est pas supprimer dans le fichier "testv" */
    while(!feof(pf) && fread(&V, sizeof(voiture), 1, pf))
	{
		if(V.idVoiture==id)
		{
            continue;
		}
		else
		{
			fwrite(&V,sizeof(voiture),1,pft);
		}
	}
	fclose(pf);
    remove("voiture.txt");
    fclose(pft);
    rename("suppvoiture.txt","Voiture.txt");
    printf("\t\t\tCette voiture est bien supprimee!\n\n");
    }
}

/*--------------------------Menu de gestion voitures---------------------------*/
void Gestion_Voiture(){
FILE* pfv,*tempv;
pfv = fopen("voiture.txt", "rb+");
tempv = fopen("suppvoiture.txt","wb+");
int choix;
int n;
    system("cls");
    printf("\t\t\t|-----GESTION DES VOITURES-----|\n");
    printf("\t\t\t|    Liste des voitures.......1|\n");
    printf("\t\t\t|    Ajouter voiture..........2|\n");
    printf("\t\t\t|    Modifier voitures........3|\n");
    printf("\t\t\t|    Supprimer voiture........4|\n");
    printf("\t\t\t|    Retour...................5|\n");
    do{
        printf("\t\t\t  Votre choix :");
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                liste_voitures(pfv);
                break;
            case 2:
                ajouter_voiture(pfv);
                break;
            case 3:
                modifier_voiture(pfv);
                break;
            case 4:
                tempv = fopen("suppvoiture.txt","wb+");
                supprimer_voiture(pfv,tempv);
                rename("suppvoiture.txt","Voiture.txt");
                break;
            case 5:
                Menu_principal();
                break;
        }
    }while(choix<1 || choix>5);
}





/*--------------------------- lister les clients -------------------------*/

void lister_clients(FILE* pf) {
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    client C;

    fseek(pf,0,SEEK_SET);

    while (fread(&C,sizeof(client),1,pf) != 0)
    {
        printf("\t\t\tClient ID    : %d\n",C.idClient  );
        printf("\t\t\tNOM          : %s\n",C.nom  );
        printf("\t\t\tPrenom       : %s\n",C.prenom  );
        printf("\t\t\tCIN          : %d\n",C.cin  );
        printf("\t\t\tAdresse      : %s\n",C.adresse  );
        printf("\t\t\tN° Telephone : %d\n",C.telephone  );
        printf("\t\t\t---------------------------- \n");
   }
   fseek(pf, 0, SEEK_SET);
   fclose(pf);
    }
}

/*--------------------------- ajouter un client --------------------------*/

void ajouter_client (FILE* pf) {
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    client C;
    printf("\t\t\tID         :");
    scanf("%d",&C.idClient);

    printf ("\t\t\tNOM        :");
    scanf ("%s", &C.nom);

    printf ("\t\t\tPrenom     :");
    scanf ("%s", &C.prenom);

    printf("\t\t\tCIN         :");
    scanf("%d",&C.cin);

    printf("\t\t\tAdresse     :");
    scanf("%s",&C.adresse);

    printf("\t\t\tN° Telephone:");
    scanf("%d",&C.telephone);

    fseek(pf, 0, SEEK_END);
    fwrite (&C, sizeof(client), 1, pf);
    fseek(pf, 0, SEEK_SET);
    fclose(pf);
    printf("\t\t\tCe Client est bien ajoutee!\n");
    }
}

/*--------------------------- modifier client ----------------------------*/

void modifier_client(FILE* pf){
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    client  C ;
    int K = 0;
    int id;
    char test;
    printf("\t\t\tSaisir ID : ");
    scanf("%d",&id);
    fseek(pf, 0, SEEK_SET);

     /* verification de id*/
    while (fread(&C, sizeof(client), 1, pf) != 0 && K == 0)
    {
        if (C.idClient == id)
         {
            K = 1 ;
            break ;
        }
    }

    if(K == 0){
          printf("Ce client  n'existe pas\n");
    }else{

            fseek(pf,-sizeof(client),SEEK_CUR) ;
            printf("\t\t\tInformation de Client: \n");
            printf("\t\t\tNOM          : %s\n",C.nom  );
            printf("\t\t\tPrenom       : %s\n",C.prenom );
            printf("\t\t\tCIN          : %d\n",C.cin  );
            printf("\t\t\tAdresse      : %s\n",C.adresse  );
            printf("\t\t\tN° Telephone : %d\n",C.telephone  );
            printf("\t\t\tqu'est ce que tu veux changer ?\n ");

            C.idClient = id;
            /* modifier le nom */
            printf("\t\t\tnom ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNew nom : ");
                scanf("%s",&C.nom);
            }else
                {
                    strcpy(C.nom , C.nom);
                }
            printf("\n");

             /* modifier le prenom */
            printf("\t\t\tprenom ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW prenom : ");
                scanf("%s",&C.prenom) ;
            }else
                {
                    strcpy(C.prenom,C.prenom);
                }
            printf("\n");

            /* modifier le CIN */
            printf("\t\t\tCIN ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW CIN : ");
                scanf("%d",&C.cin) ;
            }else
                {
                    C.cin = C.cin ;
                }
            printf("\n");

            /* modifier l'adresse */
            printf("\t\t\tAdresse ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW adresse : ");
                scanf("%s",&C.adresse) ;
            }else
                {
                    strcpy(C.adresse,C.adresse);
                }
            printf("\n");

            /* modifier le telephone */
            printf("\t\t\tN° Telephone ? (o/n): ") ;
            scanf("%s",&test) ;
            if(test == 'o')
            {
                printf("\t\t\tNEW N° Telephone : ");
                scanf("%d",&C.telephone);
            }else
                {
                    C.telephone = C.telephone ;
                }
            printf("\n");

            /* sauvegarder les modification*/
            fwrite(&C,sizeof(client),1,pf);
        }
        fseek(pf, 0, SEEK_SET);
        fclose(pf);
        printf("\t\t\tCe Client est bien modifier!\n");
    }
}

/*--------------------------- supprimer client ---------------------------*/

void supprimer_client(FILE* pf,FILE* tempc){
    if(pf == 0)
    {
        printf("\t\t\tERREUR: Impossible d'ouvrir le fichier!\n");
    }
    else{
    client C ;
    int K = 0;
    int id;

    printf("Donnez le id a supprimer : ");
    scanf("%d",&id);

    fseek(pf, 0, SEEK_SET);

    // verification de id
    while (fread(&C, sizeof(client), 1, pf) != 0 && K == 0)
    {
        if (C.idClient == id)
        {
            K = 1 ;
            break ;
        }
    }

    if (K == 0)
    {
        printf("\t\t\tCette voiture n'existe pas!\n");
        system("pause");
    }

    fseek(pf, 0, SEEK_SET);

    /* copier les voitures qui n'est pas supprimer dans le fichier "suppclient" */
    while( fread(&C, sizeof(client), 1, pf))
	{
		if(C.idClient == id)
		{
            continue;
		}
		else
		{
			fwrite(&C,sizeof(client),1,tempc);
		}
	}
	fclose(pf);
    remove("client.txt");
    fclose(tempc);
    rename("suppclient.txt","client.txt");
    printf("Ce client est bien supprimee!\n");
    }
}
/*--------------------------- Menu de gestion  clients -------------------*/
void Gestion_Clients(){
int choix;
FILE *pfclt,*tempc;
pfclt = fopen("client.txt","rb+");
/*tempc = fopen("suppclient.txt","wb+");*/
    do{
            system("cls");
            printf("\t\t\t|-----GESTION DES CLIENTS------|\n");
            printf("\t\t\t|    Liste des clients........1|\n");
            printf("\t\t\t|    Ajouter client...........2|\n");
            printf("\t\t\t|    Modifier client..........3|\n");
            printf("\t\t\t|    Supprimer client.........4|\n");
            printf("\t\t\t|    Retour...................5|\n");
            printf("\t\t\t Votre choix :");
            scanf("%d",&choix);
            switch(choix)
                {
                    case 1:
                        lister_clients(pfclt);
                        break;
                    case 2:
                        ajouter_client(pfclt);
                        break;
                    case 3:
                        modifier_client(pfclt);
                        break;
                    case 4:
                        tempc = fopen("suppclient.txt","wb+");
                        supprimer_client(pfclt,tempc);
                        break;
                    case 5:
                        Menu_principal();
                        break;
                }
        }while(choix<0 || choix>5);
}

/*--------------------------- Menu principal -----------------------------*/
void Menu_principal(){
int choix;
    do{
        printf("\t\t\t|--------MENU PRINCIPAL--------|\n");
        printf("\t\t\t|    Location.................1|\n");
        printf("\t\t\t|    Gestion voitures.........2|\n");
        printf("\t\t\t|    Gestion clients..........3|\n");
        printf("\t\t\t|    Quitter..................4|\n");
        printf("\t\t\t Votre choix :");
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                Location_Voiture();
                break;
            case 2:
                Gestion_Voiture();
                break;
            case 3:
                Gestion_Clients();
                break;
            case 4:
                printf("\n\t\t\t FIN DU PROGRAMME!\n");
                exit(0);
                break;
        }
    }while(choix>1 || choix<4);
}

 main ()
{
    Menu_principal();
    return 0;
}
