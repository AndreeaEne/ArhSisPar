#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h> /* pentru isspace() */

int main(int argc, char **argv)
{
	char c;
	char *input = argv[1];
	FILE *fisier_intrare;


	//Fisierul de intrare se va citi
	fisier_intrare = fopen("fisier_intrare", "r");

	if (fisier_intrare == 0)
	{
		//fopen returneaza 0 / NULL daca nu se poate deschide fisierul
		perror("Nu se poate deschide fisierul");
		exit(-1);
	}
	else
	{	
		// Cat timp nu am ajuns la finalul fisierului
		while ((c = fgetc(fisier_intrare)) != EOF)
		{	

			if (!isspace(c))
			{
				printf("%c", c);
			}
			
			if (isspace(c))
				{
					putchar('\n');
				}
		}
	}

	printf("\n");
	fclose(fisier_intrare);
	

	return 0;
}