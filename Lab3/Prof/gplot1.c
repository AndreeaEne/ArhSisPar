#include "gplot1.h"

#define GP_CMD_SIZE     1024

int check_X_display(void)
{
    char    *   display ;
    
    display = getenv("DISPLAY") ;
    if (display == NULL) 
	{
          fprintf(stderr, "variabila DISPLAY este definita?\n") ;
          return 1 ;
        } 
    else return 0 ;
}


gplot_ctrl * gplot_init(void)
{
    gplot_ctrl *  handle ;

    if (check_X_display()) return NULL ;
    
    /* 
     * Initializarea structurii:
     */
    handle = malloc(sizeof(gplot_ctrl)) ;
    gplot_setstyle(handle, "points") ;
     
    handle->gpcmd = popen("gnuplot", "w") ;
    if(handle->gpcmd == NULL)
     {
      fprintf(stderr,"gnuplot este instalat? Verifica $PATH...\n");
      free(handle);
      return NULL;
     }
    else return handle;
}


/*----------------------------------------------------------------------------
 * Functia  :   gplot_close()
 * Intrare  :   handler-ul de control gnuplot
 * Iesire   :   void
 * Rol      :   inchide o sesiune gnuplot deschisa anterior de gplot_init()
 * Nota     :   distruge PID-ul programului dependent.
 *              
 *--------------------------------------------------------------------------*/

void gplot_close(gplot_ctrl * handle)
{
    
    if (check_X_display()) return ;
   
    if (pclose(handle->gpcmd) == -1) {
        fprintf(stderr, "problema cu inchiderea comunicarii cu gnuplot...\n") ;
        return ;
    }
    free(handle) ;
    return ;
}


void gplot_cmd(gplot_ctrl * handle, char * cmd,...)
{
    va_list ap ;
    char    local_cmd[GP_CMD_SIZE];

    va_start(ap, cmd);
    vsprintf(local_cmd, cmd, ap);
    va_end(ap);

    strcat(local_cmd, "\n");

    fputs(local_cmd, handle->gpcmd) ;
    fflush(handle->gpcmd) ;
    return ;

}


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

void gplot_setstyle(gplot_ctrl * h, char * plot_style) 
{
    if (strcmp(plot_style, "lines") &&
        strcmp(plot_style, "points") &&
        strcmp(plot_style, "linespoints") &&
        strcmp(plot_style, "impulses") &&
        strcmp(plot_style, "dots") &&
        strcmp(plot_style, "steps") &&
        strcmp(plot_style, "errorbars") &&
        strcmp(plot_style, "boxes") &&
        strcmp(plot_style, "boxerrorbars")) {
        fprintf(stderr, "warning: unknown requested style: using points\n") ;
        (void)strcpy(h->pstyle, "points") ;
    } else {
        (void)strcpy(h->pstyle, plot_style) ;
    }
    return ;
}




void gplot_set_xlabel(gplot_ctrl * h, char * label)
{
    char    cmd[GP_CMD_SIZE] ;

    (void)sprintf(cmd, "set xlabel \"%s\"", label) ;
    gplot_cmd(h, cmd) ;
    return ;
}


void gplot_set_ylabel(gplot_ctrl * h, char * label)
{
    char    cmd[GP_CMD_SIZE] ;

    (void)sprintf(cmd, "set ylabel \"%s\"", label) ;
    gplot_cmd(h, cmd) ;
    return ;
}


