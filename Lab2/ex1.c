/* Programul calculeaza valorile functiei J0(x) pe un grid de NMAX puncte uniform pe intervalul (0,20).
 * 
 * Valorile calculate sunt scrise in 2 fisiere: text si binar. 
 * Numele fisierului trebuie dat ca parametru in linia de comanda.
 * Ulterior programul reciteste a 20-a pereche (x, J0(x)) din fisierul binar.
 1-> erori cu fisiere
 2-> erori de memorie*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//pentru operatii cu string
#include <gsl/gsl_math.h> 

//pentru functiile speciale bessel
#include <gsl/gsl_sf_bessel.h>


/* main() trebuie chemat cu parametrii pentru a cere numele de fisier in linia de comanda */
int main (int argc, void **argv)
{
  if (argc != 2)
  {
    printf("Utilizare: %s nume_fisier. \n nume_fisier este numele fisierului de date care va fi creat \n\n", argv[0]);
    exit(1);
  }
  
  int crs;
  const int NMAX = 400;
  double delta = ((double) 20) / ((double)NMAX);
  
  double *pdata, *pBdata;
  /*
   * pdata  -> stocheaza valorile pe grid
   * Bpdata -> stocheaza valorile functiile bessel J0 pe grid */
  
  /* Pot aloca spatiul RAM necesar? */
  if ((pdata = (double*) malloc(NMAX *sizeof(double))) == NULL)
  {
    printf("Nu pot aloca spatiu pe grid. Ies...\n\n");
    exit(2);
  }
  
  if ((pBdata = (double*) malloc(NMAX *sizeof(double))) == NULL)
  {
    printf("Nu pot aloca spatiu pt J0. Ies...\n\n");
    exit(2);
  }
  
  /* Initializez spatiul alocat cu val corespunzatoare */
  for (crs = 0; crs < NMAX; crs++)
  {
    *(pdata + crs)  = ((double)crs)*delta;
    *(pBdata + crs) = gsl_sf_bessel_J0(*(pdata + crs));
  }
  
  
  FILE *fp;
  
  /* Definesc numele complet al fisierului text */
  char nume_fis[80];
  strcpy (nume_fis, argv[1]);
  strcat (nume_fis, ".txt");
  
  /* Pot crea fisierul text? */
  if ((fp = fopen(nume_fis, "a")) == NULL)
  {
    printf("Nu pot crea fisierul text. Disc plin! Ies..\n\n");
    exit(1);
  }
    else
    {
      for (crs = 0; crs <= NMAX; crs++)
      {
	fprintf(fp, "%.7lf \t %.7lf \n", *(pdata + crs), *(pBdata + crs));
      }
    }
    
   /* Inchid stream-ul actual */
   fclose(fp);
   fp = NULL;
    
   /* Definesc numele complet al fisierului binar */
   strcpy (nume_fis, argv[1]);
   strcat (nume_fis, ".bin");
  
  /* Pot crea fisierul binar? */
  if ((fp = fopen(nume_fis, "ab")) == NULL)
  {
    printf("Nu pot crea fisierul binar. Disc plin! Ies..\n\n");
    exit(1);
  }
    else
    {
      for (crs = 0; crs <= NMAX; crs++)
      {
	fwrite((pdata + crs),  sizeof(double), 1, fp);
	fwrite((pBdata + crs), sizeof(double), 1, fp);
      }
    }
    
   /* Inchid stream-ul actual */
   fclose(fp);
   fp = NULL;
   
   if ((fp = fopen(nume_fis, "rb")) == NULL)
   {
     printf("Nu pot deschide fisierul binar. Disc plin! Ies..\n\n");
     exit(1);
   }
   
   /* Aloc spatiu pentru 2 valori double */
   double *buf;
   if ((buf = (double *) malloc(2 * sizeof(double))) == NULL)
   {
     printf("Memorie plina! Ies...\n\n");
     exit(2);
   }
   
   if(fseek(fp, 20 * sizeof(double), SEEK_SET))
   {
     printf("Eroare la pozitionare in fisierul binar! Ies...\n\n");
   }
   if (!fread(buf, 2 * sizeof(double), 1, fp))
   {
     printf("Eroare de accesare in fisierul binar!\n\n");
     exit(1);
   }
   printf("Perechea de date citita: \n x = %.7lf \t J0(x) = %.7lf\n\n", *buf, *(buf+1));
   
   /* Si iesim gratios */
  return 0;
}