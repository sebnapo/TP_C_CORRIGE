#include <stdio.h>
#include "notes.h"
#include "arbre.h"
#include "accolade.h"

void AfficherEleves(SEleve tab[], unsigned int size)
{
	printf("%d eleves chargés\n",size);
	for (unsigned int i=0;i<size;++i) printf("- %s : %f\n",tab[i].nom,tab[i].note);
}

int main(int argc,char *argv[])
{
	printf("\n===============================\nListe élèves\n\n");
	
	SEleve tabEleves[50];
	FILE *fp;

	if ((fp=fopen("liste_eleves.txt","rt"))!=NULL)
	{
		int nb=ChargementMemoire(fp,tabEleves,50);
		AfficherEleves(tabEleves,nb);

		printf("\nMoyenne > 12 :\n");
		AffichageSupMoyenne(tabEleves,50,12);

		char nom[]="Millet";
		printf("\nMoyenne de %s : ",nom);
		double note=AffichageMoyenne(tabEleves,50,nom);
		if (note==-1) printf("aucune");
		else printf("%f",note);
		printf("\n");

		fclose(fp);
	}

	printf("\n===============================\nArbres binaires\n\n");
	Arbre arbre=ConstruireNoeud('*',ConstruireNoeud('+',ConstruireFeuille(12),ConstruireFeuille(15)),ConstruireNoeud('-',ConstruireNoeud('*',ConstruireFeuille(7),ConstruireFeuille(10)),ConstruireFeuille(3)));
	printf("Infixe : ");
	Infixe(arbre);
	printf("\nPrefixe : ");
	Prefixe(arbre);
	printf("\nPostfixe : ");
	Postfixe(arbre);
	printf("\nValeur : %d\n",Eval(arbre));
	DetruireArbre(arbre);

	printf("\n===============================\nAccolades et indentation\n\n");
	for (unsigned int i=1;i<argc;++i)
	{
		printf("Fichier '%s' :",argv[i]);
		int val=format(argv[i]);
		if (val!=0) printf("succes");
		else printf("fail");
		printf("\n");
	}

	return(0);
}
