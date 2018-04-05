#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

Arbre ConstruireFeuille(int iEntier)
{
	Arbre tree=(Arbre)malloc(sizeof(Sommet));
	tree->valeur.iNombre=iEntier;
	tree->filsG=tree->filsD=NULL;

	return(tree);
}

Arbre ConstruireNoeud(char cOperateur, Arbre gauche, Arbre droit)
{
	Arbre tree=(Arbre)malloc(sizeof(Sommet));
	tree->valeur.cSigne=cOperateur;
	tree->filsG=gauche;
	tree->filsD=droit;

	return(tree);
}

void DetruireArbre(Arbre tree)
{
	if (tree)
	{
		DetruireArbre(tree->filsG);
		DetruireArbre(tree->filsD);
		free(tree);
	}
}

void Infixe(Arbre tree)
{
	if (tree->filsG==NULL || tree->filsD==NULL) printf("%d",tree->valeur.iNombre);
	else
	{
		printf("(");
		Infixe(tree->filsG);
		printf("%c",tree->valeur.cSigne);
		Infixe(tree->filsD);
		printf(")");
	}
}

void Prefixe(Arbre tree)
{
	if (tree->filsG==NULL || tree->filsD==NULL) printf("%d ",tree->valeur.iNombre);
	else
	{
		printf("%c ",tree->valeur.cSigne);
		Prefixe(tree->filsG);
		Prefixe(tree->filsD);
	}
}

void Postfixe(Arbre tree)
{
	if (tree->filsG==NULL || tree->filsD==NULL) printf("%d ",tree->valeur.iNombre);
	else
	{
		Postfixe(tree->filsG);
		Postfixe(tree->filsD);
		printf("%c ",tree->valeur.cSigne);
	}
}

int Eval(Arbre tree)
{
	if (tree->filsG==NULL || tree->filsD==NULL) return(tree->valeur.iNombre);
	else
	{
		int val1=Eval(tree->filsG);
		int val2=Eval(tree->filsD);
		int total;

		switch(tree->valeur.cSigne)
		{
		case'+':total=val1+val2;break;
		case'-':total=val1-val2;break;
		case'*':total=val1*val2;break;
		default:total=0;
		}
		return(total);
	}
	return(0);
}
