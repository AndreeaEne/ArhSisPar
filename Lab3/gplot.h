/*
 * Prototipurile si variabilele necesare unei librarii minimale pentru deschiderea unei sesiuni GNUplot
 */

#ifndef _GPLOT_H_  /* if not def */
#define _GPLOT_H_  /* -> pentru a evita declararea multipla */

/* Includeri standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_bessel.h>

/* Numarul maxim de caractere in linia de comanda catre programul GNUplot din sesiunea activa */
const unsigned int GP_CMD_SIZE = 1024; /* Clauza de atribuire */
//#define GP_CMD_SIZE 1024

/* Structura contine campurile esentiale pentru deschiderea sesiunii grafice */

int chk_X_Display();
/* 
 * Rol: Verifica daca variabila de mediu Display este definita
 * Intrare: -
 * Iesire: 0, succes
 * 	   1, eroare
*/

typedef struct _GPLOT_CTRL_ 
{
  FILE *gpcmd;  	/* Stream-ul catre programul de grafica externa */
  char pstyle[32];	/* Tipul de reprezentare grafica */
  
} gplot_ctrl;		/* Alias pentru structura */


gplot_ctrl *gplot_Init();
/*
 * Rol: Initializarea sesiunii grafice
 * Intrare: -
 * Iesire: Adresa spatiului de memorie alocat pentru sesiunea grafica
*/

void setpstyle(gplot_ctrl *h, const char *style);
/*
 * Rol: Definirea stilului reprezentarii grafice
 * Intrare: un handler pe o sesiune grafica activa
 * 	    un stil reprezentand stilul grafic
 * Iesire: -
*/

void gplot_Close(gplot_ctrl *handle);
/*
 * Rol: Inchiderea sesiunii grafice active
 * Intrare: un handler pe o sesiune grafica activa
 * Iesire: -
*/

void gplot_Cmd(gplot_ctrl *h, const char *cmd, ...);
/*
 * Rol: Transmite o comanda catre programul gplot in sesiunea activa
 * Intrare: un handler pe o sesiune grafica activa
 *          o lista variabila continand comenzile de transmisie
 * Iesire: -
*/

void gplot_setxlabel(gplot_ctrl *h, const char *label);
/*
 * Rol: Defineste numele axei X la reprezentarea grafica curenta
 * Intrare: un handler pe o sesiune grafica activa
 *          o constana string reprezentand numele abscisei
 * Iesire: -
*/

void gplot_setylabel(gplot_ctrl *h, const char *label);
/*
 * Rol: Defineste numele axei Y la reprezentarea grafica curenta
 * Intrare: un handler pe o sesiune grafica activa
 *          o constana string reprezentand numele ordonatei
 * Iesire: -
*/


#endif