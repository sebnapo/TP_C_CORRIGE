#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//-----------------------------------------------------------------------
//- Exercice 1

void Q1()
{
	char *tab;

	tab=(char*)malloc(50*sizeof(char));
	strcpy(tab,"Bonjour");

	for (char *p=tab;*p!='\0';p++)
		putc(*p,stdout);
	putc('\n',stdout);

	free(tab);
}

void conv(int nb)
{
	int total=(int)ceil(log(nb+1)/log(2));

	printf("%d=",nb);
	if (total==0) putc('0',stdout);
	else
	{
		while (total>0)
		{
			if (nb&(1<<(total-1))) putc('1',stdout);
			else putc('0',stdout);
			total--;
		}
	}
	putc('\n',stdout);
}

void Q3(const char *src)
{
	FILE *fp;
	int nb=0;
	char c;

	if (fp=fopen(src,"rt"))
	{
		while ((c=fgetc(fp))!=EOF)
		{
			if (c=='{') nb++;
			else if (c=='}') nb--;
		}
		printf("Le fichier '%s' ",src);
		if (nb==0) printf("est correctement formé.\n");
		else printf("n'est pas correctement formé.\n");
		fclose(fp);
	}
}

//-----------------------------------------------------------------------
//- Exercice 2

int VerifieValeurs(int grille[9][9])
{
	int error=0;

	for (int i=0;i<9 && !error;i++)
		for (int j=0;j<9 && !error;j++)
			if ((grille[i][j]<1) || (grille[i][j]>9)) error=1;

	return(error!=0);
}

int ControleLigne(int grille[9][9],int ligne)
{
	int tab=0;

	for (int i=0;i<9;i++)
	{
		if (tab & (1<<(grille[ligne][i]-1))) return(0);
		tab|=1<<(grille[ligne][i]-1);
	}

	return(1);
}

int ControleColonne(int grille[9][9],int col)
{
	int tab=0;

	for (int i=0;i<9;i++)
	{
		if (tab & (1<<(grille[i][col]-1))) return(0);
		tab|=1<<(grille[i][col]-1);
	}

	return(1);
}

int ControleCarre(int grille[9][9],int g)
{
	int tab=0;

	for (int c=0;c<3;c++)
	{
		for (int l=0;l<3;l++)
		{
			if (tab & (1<<(grille[l+(g/3)*3][c+(g%3)*3]-1))) return(0);
			tab|=1<<(grille[l+(g/3)*3][c+(g%3)*3]-1);
		}
	}
	return(1);
}

void Sudoku()
{
	int grille[9][9]={	{8,3,5,4,1,6,9,2,7},
						{2,9,6,8,5,7,4,3,1},
						{4,1,7,2,9,3,6,5,8},
						{5,6,9,1,3,4,7,8,2},
						{1,2,3,6,7,8,5,4,9},
						{7,4,8,5,2,9,1,6,3},
						{6,5,2,7,8,1,3,9,4},
						{9,8,1,3,4,5,2,7,6},
						{3,7,4,9,6,2,8,1,5}};

	printf("Veuillez saisir une grille de sudoku :\n");
	for (int i=0;i<9;i++)
	{
		for (int j=0;j<9;j++)
		{
			printf("l%d c%d : ",i+1,j+1);
			scanf("%d",&grille[i][j]);
		}
	}

	if (VerifieValeurs(grille)) printf("Grille incorrecte.\n");
	else
	{
		for (int i=0;i<9;i++)
		{
			if (!ControleLigne(grille,i))
			{
				printf("La ligne %d est incorrecte\n",i+1);
				return;
			}
			if (!ControleColonne(grille,i))
			{
				printf("La colonne %d est incorrecte\n",i+1);
				return;
			}
			if (!ControleCarre(grille,i))
			{
				printf("La sous-grille %d est incorrecte\n",i+1);
				return;
			}
		}
		printf("La grille est correcte.\n");
	}
}

//-----------------------------------------------------------------------
//- Exercice 3

void Comptage()
{
	char tab[]="aeiouy";
	char texte[1024]="je me figure ce zouave qui joue du xylophone en buvant du whisky";
	int taille=sizeof(tab)/sizeof(char)-1;
	int *cpt=calloc(taille,sizeof(int));

	printf("Donnez un texte de votre choix :\n");
	scanf("%s",texte);

	char *txt=texte;
	while (*txt)
	{
		for (int i=0;i<taille;i++)
		{
			if (tab[i]==*txt) cpt[i]++;
		}
		txt++;
	}

	printf("Votre texte comporte :\n");
	for (int i=0;i<taille;i++)
	{
		printf("%d fois la lettre %c\n",cpt[i],tab[i]);
	}
	free(cpt);
}

//-----------------------------------------------------------------------
//- Exercice 4

enum EState
{
	ESstart,
	ESnumber,
	ESbuzz
};

int ReadFile(const char *file,char *tab[100])
{
	FILE *fp;
	char c;
	enum EState state=ESstart;
	char buzz[]="Buzz";
	char tmp[10];
	int i;
	int sizeTab=0;

	if (fp=fopen(file,"rt"))
	{
		while ((c=fgetc(fp))!=EOF)
		{
			if (c==' ')
			{
				switch (state)
				{
				case ESstart:break;

				case ESbuzz:
					if (sizeTab>99) return(0);
					tab[sizeTab++]=strdup(buzz);
					break;

				case ESnumber:
					if (sizeTab>99) return(0);
					tmp[i]='\0';
					tab[sizeTab++]=strdup(tmp);
					break;
				}
				state=ESstart;
			}
			else
			{
				switch (state)
				{
				case ESstart:
					if ((c>='0') && (c<='9'))
					{
						state=ESnumber;
						tmp[0]=c;
						i=1;
					}
					else if (c==buzz[0])
					{
						state=ESbuzz;
						i=1;
					}
					else return(0);
					break;

				case ESnumber:
					if ((c>='0') || (c<='9')) tmp[i++]=c;
					else return(0);
					break;

				case ESbuzz:
					if (buzz[i]=='\0') return(0);
					if (c!=buzz[i++]) return(0);
					break;
				}
			}
		}
	}

	return(1);
}

void FizzBuzz(const char *file)
{
	char *tab[100];
	char nb[100];
	int i;

	for (i=0;i<100;i++)
	{
		tab[i]=NULL;
		nb[i]=0;
	}

	if (!ReadFile(file,tab))
	{
		printf("Erreur dans la lecture du fichier.\n");
		return;
	}

	if (tab[99]==NULL)
	{
		printf("Le fichier contient moins de 100 éléments.\n");
		return;
	}
	for (i=0;i<100;i++)
	{
		if ((tab[i][0]>='0') && (tab[i][0]<='9'))
		{
			int tmp=atoi(tab[i]);
			if ((tmp<1 || tmp>100))
			{
				printf("Nombre non compris dans l'intervalle 1-100 détecté.\n");
				return;
			}
			if (nb[tmp-1])
			{
				printf("Le nombre %d est dupliqué dans la liste.\n",tmp);
				return;
			}
			nb[tmp-1]=1;
		}
	}

	for (i=0;i<100;i++) free(tab[i]);

	// Les nombres masqués par Buzz sont ceux qui ont une valeur de 0 dans le tableau nb (indicé -1)

	int n,p;
	int found;

	for (i=0,found=0;i<100 && found!=2;i++)
	{
		if (nb[i]==0)
		{
			if (found==0)
			{
				n=i+1;
				found++;
			}
			else
			{
				if (n%(i+1)!=0)
				{
					p=i+1;
					found++;
				}
			}
		}
	}
	printf("Les nombres recherchés sont :\nn=%d\np=%d\n",n,p);
}

//-----------------------------------------------------------------------
//- main

int main()
{
	printf("############################################\n# Exercice 1\n\n");
	printf("--------------------\n- Q1.1\n\n");
	Q1();

	printf("\n--------------------\n- Q1.2\n\n");
	for (int i=0;i<16;i++) conv(i);

	printf("\n--------------------\n- Q1.3\n\n");
	Q3("main.c");

	printf("\n\n############################################\n# Exercice 2\n\n");
	Sudoku();

	printf("\n\n############################################\n# Exercice 3\n\n");
	Comptage();

	printf("\n\n############################################\n# Exercice 4\n\n");
	FizzBuzz("buzz.txt");

	return(0);
}
