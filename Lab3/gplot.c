#include "gplot.h"

int chk_X_Display()
{
  char *display;
  if ((display = getenv("DISPLAY")) == NULL)  /* Verifica daca variabial DISPLAY este definita */
  {
    fprintf(stderr, "Variabila de mediu DISPLAY nu este definita.\n");
    return 1; /* Codul de eroare in cazul in care nu este definita */
  }
  return 0;
}


gplot_ctrl *gplot_Init()
{
  if (chk_X_Display())
  {
    fprintf(stderr, "server X functional? \n");
    return NULL;
  }
  
  gplot_ctrl *handle; /* Adresa spatiului alocat pentru initializarea sesiunii grafice */
  if ((handle = (gplot_ctrl *)malloc(sizeof(gplot_ctrl))) == NULL)
  {
    fprintf(stderr, "Nu pot aloca RAM pentru sesiunea grafica.\n");
    return NULL;
  }
  else
  {
    if ((handle -> gpcmd = popen("gnuplot", "w")) == NULL)
    {
      fprintf(stderr, "Este GNUplot instalat? Este in path / calea std? \n");
      free(handle); /* Eliberam spatiul de memorie alocat */
      return NULL;
    }
    
    setpstyle(handle, "lines");
    return handle;
  }
}


void setpstyle(gplot_ctrl *h, const char *style)
{
  if (strcmp(style, "lines") &&
      strcmp(style, "points") &&
      strcmp(style, "linespoints") &&
      strcmp(style, "impulses") &&
      strcmp(style, "dots") &&
      strcmp(style, "steps") &&
      strcmp(style, "errorbars") &&
      strcmp(style, "boxes") &&
      strcmp(style, "boxerrorbars"))
  {
    fprintf(stderr, "Atentie: Stil de reprezentare grafica necunoscut; Folosim lines. \n");
    strcpy(h -> pstyle, "lines");
  }
  else
  {
    strcpy(h -> pstyle, style);
  }
  return;
}


void gplot_Close(gplot_ctrl *handle)
{
  if (chk_X_Display()) return; /* Nimic de facut, nu exista sesiune activa */
  if (pclose(handle -> gpcmd) == -1)
  {
    fprintf(stderr, "Problema de comunicare cu gnuplot in sesiunea activa! \n");
    return;
  }
  free(handle);              /* Elibereaza spatiul RAM alocat de program */
  return;     
}

void gplot_Cmd(gplot_ctrl *h, const char *cmd, ...)
{
  va_list ap;
  char local_cmd[GP_CMD_SIZE];
  
  va_start(ap, cmd);
  vsprintf(local_cmd, cmd, ap);
  va_end(ap);
  
  strcat(local_cmd, "/n"); 	/* Enter-ul de la final */
  fputs(local_cmd, h -> gpcmd);	/* Transmiterea catre stream */
  
  fflush(h -> gpcmd);
  return;
}

void gplot_setxlabel(gplot_ctrl *h, const char *label)
{
  char local_cmd[GP_CMD_SIZE];
  sprintf(local_cmd, "set xlabel \"%s\"", label);
  gplot_Cmd(h, local_cmd);
  return;
}

void gplot_setylabel(gplot_ctrl *h, const char *label)
{
  char local_cmd[GP_CMD_SIZE];
  sprintf(local_cmd, "set ylabel \"%s\"", label);
  gplot_Cmd(h, local_cmd);
  return;
}









