/*****************************************************************/
/*    Project: Polynomial library
/*    File: pol_test.c
/*    Version: 1.2
/*    Date: December 23, 2017
/*
/*    (C) Alejandro Santorum Varela
/*        alejandro.santorum@gmail.com
/*        alejandro.santorum@estudiante.uam.es
/*****************************************************************/
/*    File information: It is just a little program which tries
/*          to check every function available at polynomial.h
/*****************************************************************/

#include "polynomial.h"

int main(){
  pol *p1=NULL;

  p1 = pol_read();
  if(p1 == NULL) return EXIT_FAILURE;

  if(pol_plot(p1, 31, 31) == -1) return EXIT_FAILURE;

  if(pol_filePlot(p1, "output.txt", -100, 100) == -1) return EXIT_FAILURE;

  pol_destroy(p1);

  return EXIT_SUCCESS;
}
