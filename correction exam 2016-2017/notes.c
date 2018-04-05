#include "notes.h"
#include <stdlib.h>
#include <string.h>

enum EState
{
	ESbegin,
	ESname,
	ESprenote,
	ESnote,
	ESend
};

int ChargementMemoire(FILE *fp, SEleve tab[], unsigned int size)
{
	int nb=0;
	
	if (fp!=NULL)
	{
		char *line=NULL;
		size_t len=0;
		ssize_t read;
		unsigned int nbCar;
		char buf[20];

		while ((nb<size) && ((read=getline(&line,&len,fp))!=-1))
		{
			enum EState state=ESbegin;

			unsigned int i=0;
			while (i<read && state!=ESend)
			{
				switch(state)
				{
				case ESbegin:
					state=ESname;
					nbCar=0;
				case ESname:
					if (line[i]==' ' || line[i]=='\t') 
					{
						tab[nb].nom[nbCar]='\0';
						state=ESprenote;
					}
					else tab[nb].nom[nbCar++]=line[i];
					break;

				case ESprenote:
					if (line[i]==' ' || line[i]=='\t') break;
					else
					{
						nbCar=0;
						state=ESnote;
					}
				case ESnote:
					if (line[i]==' ' || line[i]=='\t' || line[i]=='\0' || line[i]=='\r' || line[i]=='\n' || nbCar>=20)
					{
						buf[nbCar]='\0';
						tab[nb].note=atof(buf);
						nb++;
						state=ESend;
					}
					else buf[nbCar++]=line[i];
				}
				i++;
			}
		}

		if (line) free(line);
	}
	return(nb);
}

void AffichageSupMoyenne(SEleve tab[], unsigned int size, double moyenneMin)
{
	for (unsigned int i=0;i<size;++i)
	{
		if (tab[i].note>=moyenneMin)
			printf("- %s : %f\n",tab[i].nom,tab[i].note);
	}
}

double AffichageMoyenne(SEleve tab[], unsigned int size, const char *nom)
{
	for (unsigned int i=0;i<size;++i)
	{
		if (strcmp(tab[i].nom,nom)==0) return(tab[i].note);
	}
	return(-1);
}
