/*****************************************************************/
/*    Project: Polynomial library
/*    File: polynomial.h
/*    Version: 1.2
/*    Date: December 23, 2017
/*
/*    (C) Alejandro Santorum Varela
/*        alejandro.santorum@gmail.com
/*        alejandro.santorum@estudiante.uam.es
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxXlen 151 /* Maximum X-axis length for pol_plot function */
#define MaxYlen 201 /* Maximum Y-axis length for pol_plot function */

typedef struct _pol pol;

/* Function that allocates all the necessary memory for a polynomial of degree "deg" */
/* Input: integer that expecifies the degree */
/* Returns: pointer to a pol type structure already allocated in memory that has to be freed later */
pol* pol_create(int deg);

/* Function that asks the user for a polynomial´s degree and then for the polynomials' coefficients */
/* Input: none */
/* Returns: pointer to a pol type structure already allocated in memory that has to be freed later */
pol* pol_read();

/* Function that frees all the memory allocated for a polynomial */
/* Input: pointer of the polynomial to be freed */
/* Returns anything */
void pol_destroy(pol* p);

/* Function that prints on the screen a polynomial */
/* Input: pointer of the polynomial to be printed */
/* Returns anything */
void pol_print(pol* p);

/* Function that copies all the information of a polynomial(its degree and coefficients) into another polynomial, which is allocated in memory */
/* Input: pointer of the polynomial to be copied */
/* Returns: pointer of the new polynomial which is a copy of the previous one */
/* Note: both polynomials have its own data, both have to be freed later */
pol* pol_copy(pol *p);

/* Function that sums two polynomials */
/* Input: pointers of the polynomials to be added, order is not important */
/* Returns: pointer of the result, it has to be freed later because it has its own allocated memory */
pol* pol_sum(pol *p1, pol *p2);

/* Function that returns the opposite polynomial of a given one */
/* Input: pointer of a polynomial */
/* Returns: pointer to a polynomial whose coefficients have been multiplied by -1 */
/* Note: both polynomials have its own data, both have to be freed later */
pol* pol_opposite(pol *p);

/* Function that substracts two polynomials */
/* Input: first, pointer of the  minuend (p1), then, pointer of the subtrahend (p2) */
/* Returns: pointer of the result, it has to be freed later because it has its own allocated memory */
pol* pol_subtraction(pol *p1, pol *p2);

/* Function that evaluates one polynomial in a given point */
/* Input: first, pointer of the polynomial to be evaluated, then, point where the polynomial has to be evaluated */
/* Returns: float of the result */
float pol_eval(pol *p, float x);

/* Function that calculates the derivative of a given polynomial, which is another polynomial */
/* Input: pointer of the polynomial to be derivated */
/* Returns: pointer of the derivative, it has to be freed later because it has its own allocated memory */
pol* pol_derivate(pol *p);

/* Function that multiplies two polynomials */
/* Input: pointers of the polynomials to be multiplied, order is not important */
/* Returns: pointer of the result, it has to be freed later because it has its own allocated memory */
pol* pol_mult(pol *p1, pol *p2);

/* Function that divides two polynomials */
/* Input: first, pointer of the  dividend (dend), then, pointer of the divider (der) */
/* Returns: pointer of the result, it has to be freed later because it has its own allocated memory */
pol* pol_div(pol *dend, pol *der);

/* Function that sketches a given polynomial */
/* Input: first, the polynomial to be plotted, then the lenght of X-axis, and last the lenght of Y-axis */
/* Output: It returns -1 if something went wrong with the parameters(Xlen and/or Ylen), or 0 if everything went OK */
int pol_plot(pol *p, int Xlen, int Ylen);

/* Function that writes in a file the points (x, f(x)) of a given polynomial in a specific interval */
/* Input: first, the polynomial to be plotted, second the name of the file (it is opened using "w" so if the file already exists it gets deleted), and last the interval [a,b] where the polynomial is going to be evaluated */
/* Output: It returns -1 if something went wrong with the parameters(a and/or b), or 0 if everything went OK */
int pol_filePlot(pol *p, char *filename, int a, int b);
