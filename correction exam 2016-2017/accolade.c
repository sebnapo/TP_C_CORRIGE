#include "accolade.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int format(const char *file)
{
	char *buf;
	FILE *fpR,*fpW;
	int ret=0;

	size_t nb=strlen(file); 
	buf=(char*)malloc(sizeof(char)*(nb+4+1));
	strcpy(buf,file);
	strcpy(&buf[nb],".tmp");

	if ((fpW=fopen(buf,"wt"))!=NULL)
	{
		if ((fpR=fopen(file,"rt"))!=NULL)
		{
			char c;
			unsigned int nb=0;
			int skip=1;

			ret=1;
			while ((ret==1) && ((c=fgetc(fpR))!=EOF))
			{
				int val=nb;
				if (c=='{') nb++;
				else if (c=='}')
				{
					if (nb==0) ret=0;
					else nb--;
					val=nb;
				}

				if (skip && c!=' ' && c!='\t')
				{
					for (unsigned int i=0;i<val;++i) fputc('\t',fpW);
					skip=0;
				}
				if (!skip) fputc(c,fpW);
				if (c=='\n')
				{
					skip=1;
				}
			}
			if (nb!=0) ret=0;
			fclose(fpR);
		}
		fclose(fpW);
	}

	if (ret==0) unlink(buf);
	else
	{
		unlink(file);
		rename(buf,file);
	}
	return(ret);
}
