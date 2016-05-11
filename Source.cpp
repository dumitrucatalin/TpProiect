#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct radix
{
	char caracter;
	radix**next;
	unsigned int nr_fii;

};
radix*rad;
void inserare(radix*&p,char caracter)
{
	radix*q = (radix*)malloc(sizeof(radix));
	q->caracter = caracter;
	q->nr_fii = 0;
	if (p == NULL)
	{
		q->next = NULL;
		p = q;
	}
	else
	{
		p->nr_fii++;
		p->next = (radix**)realloc(p->next, p->nr_fii*sizeof(radix*));
		q->next = NULL;
		(p->next)[p->nr_fii - 1] = q;
	}
}
void parcurgere(radix*rad)
{
	int i;
	if (rad != NULL)
	{
		printf("%c", rad->caracter);
		for (i = 0; i < rad->nr_fii; i++)
		{
			parcurgere((rad->next)[i]);
		}
	}
}
void constructie(radix*rad, char*cuv,int index)
{
	int i;
	for (i = index; i < strlen(cuv); i++)
	{
		inserare(rad, cuv[i]);
		rad = (rad->next)[rad->nr_fii-1];
	}
}
radix*gasire_pointer(radix*rad, char car,int&ok)
{
	for (int i = 0; i < rad->nr_fii; i++)
	{
		if (rad->next[i]->caracter == car)
		{
			return rad->next[i];
		}
	}
	ok = 1;
	return rad;  ///
}
void functie(char*cuv, radix*rad)
{
	int ok = 0;
	int i = 0;
	radix*fin = NULL, *aux = NULL;
	fin = gasire_pointer(rad, cuv[i],ok);
	aux = fin;
	while (ok!=1)
	{	
		i++;
		aux = fin;
		fin = gasire_pointer(fin, cuv[i],ok);
	}
	constructie(aux, cuv,i);
}
void main()
{
	/*char buffer[20];
	int i=0;
	int nr_cuvinte;
	FILE*fis;
	fis = fopen("fis.txt", "rt");
	while (!feof(fis))
	{
		fscanf(fis, "%s", &buffer);
		while (1)
		{
			if (isalpha(buffer[i])==0)
			{
				break;
			}
			inserare(rad,buffer[i]);
			i++;
		}
	}
	inserare(p, 'b');
	inserare(p, 'c');
	//constructie(p->next[1], cuv,0);
	inserare(p, 'd');
	inserare((p->next)[1], 'x');
//	printf("%c", ((p->next)[1]->next)[0]->caracter);
	x = gasire_pointer(p, 'c');
	constructie(x, cuv, 1);
	parcurgere(p);
*/
	radix*p = NULL;
	radix*x = NULL;
	inserare(p, char(0));
	char*cuv = "episcopie";
	char*cuv2 = "epifiza";
	char*cuv3 = "episcule";
	char*cuv4 = "episcular";
	char*cuv5 = "episcopiment";
	char*cuv6 = "vaca";
	functie(cuv, p);
	functie(cuv2, p);
	functie(cuv3, p);
	functie(cuv4, p);
	functie(cuv5, p);
	functie(cuv6, p);
	parcurgere(p);
}