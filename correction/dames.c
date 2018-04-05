#include <stdio.h>
#include <stdlib.h>

void initialisation(char damier[10][10]);
void affichage(char damier[10][10]);
void joue_coup(char damier[10][10],int i1,int j1,int i2,int j2);
int gagne(char damier[10][10],char joueur);
int depart_valide(char damier[10][10],int i1,int j1,char joueur);
int coup_valide(char damier[10][10],int i1,int j1,int i2,int j2,char joueur);
void joue(char damier[10][10],char joueur);

int main()
{
	char damier[10][10];
	char joueur;

	initialisation(damier);
	affichage(damier);

	joueur='o';
	do
	{
		if (joueur=='o') joueur='x';
		else joueur='o';

		printf("Joueur %c :\n",joueur);
		joue(damier,joueur);
		affichage(damier);
	} while (!gagne(damier,joueur));

	printf("Le joueur %c a gagné\n",joueur);
	return(0);
}

void initialisation(char damier[10][10])
{
	int i,j;

	for (j=0;j<10;j++)
	{
		for (i=0;i<10;i++)
		{
			char c;

			if (i>3 && i<6) c=' ';
			else
			{
				if (((i%2==0) && (j%2==0)) || ((i%2==1) && (j%2==1))) c=' ';
				else c=i<5 ? 'x' : 'o';
			}

			damier[i][j]=c;
		}
	}
}

void affichage(char damier[10][10])
{
	int i,j;

	printf(" ");
	for (i=0;i<10;i++) printf(" %d",i);
	printf("\n");

	for (j=0;j<10;j++)
	{
		printf(" ");
		for (i=0;i<10;i++) printf("+-");
		printf("+\n%d",j);
		for (i=0;i<10;i++) printf("|%c",damier[j][i]);
		printf("|\n");
	}
	printf(" ");
	for (i=0;i<10;i++) printf("+-");
	printf("+\n");
}

void joue_coup(char damier[10][10],int i1,int j1,int i2,int j2)
{
	if (abs(i1-i2)>1) damier[(i2+i1)/2][(j2+j1)/2]=' ';
	damier[i2][j2]=damier[i1][j1];
	damier[i1][j1]=' ';
}

int gagne(char damier[10][10],char joueur)
{
	int i,j;

	if (joueur=='o') joueur='x';
	else joueur='o';

	for (j=0;j<10;j++)
	{
		for (i=0;i<10;i++)
			if (damier[j][i]==joueur) return(0);
	}
	return(1);
}

int depart_valide(char damier[10][10],int i1,int j1,char joueur)
{
	return(damier[i1][j1]==joueur);
}

int coup_valide(char damier[10][10],int i1,int j1,int i2,int j2,char joueur)
{
	char anti_joueur;
	int di=abs(i1-i2);
	int dj=abs(j1-j2);

	if (joueur=='o') anti_joueur='x';
	else anti_joueur='o';

	if ((di!=dj) || (di<1) || (di>2) || (damier[i2][j2]!=' ')) return(0);
	if ((di==2) && (damier[(i2+i1)/2][(j2+j1)/2]!=anti_joueur)) return(0);
	return(1);
}

void joue(char damier[10][10],char joueur)
{
	int i1,j1,i2,j2;
	int correct;

	do
	{
		do
		{
			printf("-> entrez la ligne de départ :\n");
			scanf("%d",&i1);
			printf("-> entrez la colonne de départ :\n");
			scanf("%d",&j1);
			correct=depart_valide(damier,i1,j1,joueur);
		} while (!correct);

		printf("-> entrez la ligne d'arrivée :\n");
		scanf("%d",&i2);
		printf("-> entrez la colonne d'arrivée :\n");
		scanf("%d",&j2);
		correct=coup_valide(damier,i1,j1,i2,j2,joueur);
	} while (!correct);

	joue_coup(damier,i1,j1,i2,j2);
}
