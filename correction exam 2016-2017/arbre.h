#pragma once

typedef union
{
	int iNombre;
	char cSigne;
} UValeur;

typedef struct Sommet
{
	UValeur valeur;
	struct Sommet *filsG ,*filsD;
} Sommet;

typedef Sommet* Arbre;

Arbre ConstruireFeuille(int iEntier);
void DetruireArbre(Arbre tree);
Arbre ConstruireNoeud(char cOperateur, Arbre gauche, Arbre droit);
void Infixe(Arbre tree);
void Prefixe(Arbre tree);
void Postfixe(Arbre tree);
int Eval(Arbre tree);
