//evitam referinte multiple
#ifndef _GPLOT_H_
#define _GPLOT_H_

/*----------------------------------------------------------------------------
 *                              includeri standard
 *--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>



#define GP_CMD_SIZE     1024

/*
 * Aceasta structura mentine toate informatia necesara pentru a schimba date cu 
 * gnuplot, intr-o sesiune deschisa.
 */
typedef struct _GPLOT_CTRL_ {
    /* handler pentru fisierul executabil */
    FILE    * gpcmd ;
    
    /* optiuni grafice */
    char      pstyle[32] ;  /* Stilul curent */
    
} gplot_ctrl ;



/*----------------------------------------------------------------------------
 *                     Prototipurile functiilor
 *--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
   Functia  :   check_X_display()
   Intrare  :   void
   Iesire   :   int 0 daca display Ok, 1 altfel
   Rol      :   verifica existenta variabilei de mediu DISPLAY, necesara pentru 		rularea in bune conditii a gnuplot.
   Nota     :   
 ---------------------------------------------------------------------------*/

int check_X_display(void) ;


/*----------------------------------------------------------------------------
 * Functia  :   gplot_init()
 * Intrare  :   void
 * Iesire   :   pointer pe o sesiune deschisa gnuplot
 * Rol      :   lanseaza o sesiune gnuplot, in vederea schimbului de date.
 * Nota   :
 *--------------------------------------------------------------------------*/

gplot_ctrl * gplot_init(void) ;


/*----------------------------------------------------------------------------
 * Functia  :   gplot_close()
 * Intrare  :   handler-ul de control al sesiunii gnuplot
 * Iesire   :   void
 * Rol      :   inchide sesiunea gnuplot activa, initializata de gplot_init()
 * Nota     :   distruge PID-ul asociat programului gnuplot dependent (procesul
 *              copil).
 *--------------------------------------------------------------------------*/

void gplot_close(gplot_ctrl *handle) ;


/*----------------------------------------------------------------------------
 * Functia  :   gplot_cmd()
 * Intrare  :   handler-ul de control gnuplot, stringul de comanda
 * Iesire   :   void
 * Rol      :   trimite un string de control catre gnuplot, asa cum ar fi el 
 *              utilizat intr-o sesiune interactiva.
 * Nota     :   nu se testeaza integritatea comenzii, d.p.d.v. sintactic.
 *--------------------------------------------------------------------------*/

void gplot_cmd(gplot_ctrl *handle, char *cmd, ...) ;

/*----------------------------------------------------------------------------
 * Function  :   gplot_setstyle()
 * Intrare   :   stil de reprezentare grafica: un string din setul de valori permise
 *              urmator:
 *              "lines"
 *              "points"
 *              "linespoints"
 *              "impulses"
 *              "dots"
 *              "steps"
 *              "errorbars"
 *              "boxes"
 *              "boxeserrorbars"
 * Iesire    :   void
 * Rol       :   defineste stilul de reprezentare grafica pentru o sesiune gnuplot
 *               activa
 * Nota      :
 *--------------------------------------------------------------------------*/

void gplot_setstyle(gplot_ctrl * h, char * plot_style) ;



/*----------------------------------------------------------------------------
 * Functia  :   gplot_set_xlabel()
 * Intrare  :   handler pe gplot_ctrl, eticheta axei x
 * Iesire   :   void
 * Rol      :   defineste eticheta axei x a reprezentarii grafice curente
 * Nota     :
 *--------------------------------------------------------------------------*/
void gplot_set_xlabel(gplot_ctrl * h, char * label) ;


/*----------------------------------------------------------------------------
 * Functia  :   gplot_set_ylabel()
 * Intrare  :   handler pe gplot_ctrl, eticheta axei y
 * Iesire   :   void
 * Rol      :   defineste eticheta axei y a reprezentarii grafice curente
 * Nota     :
 *--------------------------------------------------------------------------*/
void gplot_set_ylabel(gplot_ctrl * h, char * label) ;



#endif
/*----------------------------- end of file --------------------------------*/

