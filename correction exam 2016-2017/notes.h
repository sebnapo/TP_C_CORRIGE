#pragma once

#define _GNU_SOURCE
#include <stdio.h>

typedef struct
{
	char nom[50];
	double note;
} SEleve;

int ChargementMemoire(FILE *fp, SEleve tab[], unsigned int size);
void AffichageSupMoyenne(SEleve tab[], unsigned int size, double moyenneMin);
double AffichageMoyenne(SEleve tab[], unsigned int size, const char *nom);
