/*****************************************************************/
/*    Project: Polynomial library
/*    File: polynomial.c
/*    Version: 1.2
/*    Date: December 23, 2017
/*
/*    (C) Alejandro Santorum Varela
/*        alejandro.santorum@gmail.com
/*        alejandro.santorum@estudiante.uam.es
/*****************************************************************/

#include "polynomial.h"

struct _pol{
  int deg;
  float *coef;
};


pol* pol_create(int deg){
  pol *p=NULL;

  if(deg < 0){ /* Error */
    printf("Fatal Error. Polynomial´s degree is negative.\n");
    exit(1);
  }

  p = (pol *) malloc(sizeof(pol));
  if(p==NULL){ /* Error */
    printf("Fatal Error. Pol-F1-1.\n");
    exit(1);
  }
  p->coef = (float *) malloc((deg+1) * sizeof(float));
  if(p->coef == NULL){ /* Error */
    printf("Fatal Error. Pol-F1-2.\n");
    exit(1);
  }
  p->deg = deg;
  return p;
}


pol* pol_read(){
  pol *p=NULL;
  int i, deg;

  printf("\nINTRODUCE polynomial´s degree: ");
  scanf("%d", &deg);

  p = pol_create(deg);
  if(p==NULL){ /* Error */
    printf("Fatal Error. Pol-F2-1.\n");
    exit(1);
  }

  printf("Introduce coefficient of the independent term: ");
  scanf("%f", &(p->coef[0]));
  for(i=1; i<=p->deg; i++){
    printf("Introduce coefficient of X^%d: ", i);
    scanf("%f", &(p->coef[i]));
  }

  return p;
}


void pol_destroy(pol* p){
  if(p==NULL){ /* Error */
    printf("Fatal Error-F3-1.\n");
    exit(1);
  }
  if(p->coef != NULL) free(p->coef);
  free(p);

  return;
}


void pol_print(pol* p){
  int i;

  if(p == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F4-1.\n");
    exit(1);
  }

  if(p->deg == 0){
    printf("%.2f\n", p->coef[0]);
    return;
  }

  printf("%.2fX^%d", p->coef[p->deg], p->deg);
  for(i=(p->deg-1); i>1; i--){
    if(p->coef[i] != 0.0){
      printf(" + ");
      printf("%.2fX^%d", p->coef[i], i);
    }
  }
  if(p->coef[1] != 0.0){
    printf(" + ");
    printf("%.2fX", p->coef[1]); /* We separate it becuase X^1 doesn't look good */
  }
  if(p->coef[0] != 0.0){  /* We separate it becuase X^0 doesn't look good */
    printf(" + ");
    printf("%.2f", p->coef[0]);
  }
  printf("\n");
  return;
}


pol* pol_copy(pol *p){
  pol *p2=NULL;
  int i;

  if(p == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F5-1.\n");
    exit(1);
  }

  p2 = pol_create(p->deg);
  if(p2==NULL){ /* Error */
    printf("Fatal Error. Pol-F5-2.\n");
    exit(1);
  }

  for(i=0; i<=p->deg; i++){
    p2->coef[i] = p->coef[i];
  }

  return p2;
}


pol* pol_sum(pol *p1, pol *p2){
  pol *sum=NULL;
  pol *max, *min;
  int i;

  if(p1 == NULL || p2 == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F6-1.\n");
    exit(1);
  }

  if(p1->deg >= p2->deg){
    max = p1;
    min = p2;
  }
  else{
    max = p2;
    min = p1;
  }

  sum = pol_create(max->deg);
  if(sum==NULL){ /* Error */
    printf("Fatal Error. Pol-F6-2.\n");
    exit(1);
  }

  for(i = max->deg; i>min->deg; i--){
    sum->coef[i] = max->coef[i];
  }
  for(i = min->deg; i>=0; i--){
    sum->coef[i] = (max->coef[i]) + (min->coef[i]);
  }
  for(i = sum->deg; i>0; i--){
    if(sum->coef[i] == 0.0){
      sum->deg--;
    }
    else if(sum->coef[i] != 0.0) break;
  }

  return sum;
}


pol* pol_opposite(pol *p){
  pol *op=NULL;
  int i;

  if(p==NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F7-1.\n");
    exit(1);
  }

  op = pol_create(p->deg);
  if(op==NULL){ /* Error */
    printf("Fatal Error. Pol-F7-2.\n");
    exit(1);
  }

  for(i=0; i<=p->deg; i++){
    op->coef[i] = (p->coef[i] * -1);
  }

  return op;
}


pol* pol_subtraction(pol *p1, pol *p2){
  pol *op_p2=NULL, *sub=NULL;

  if(p1 == NULL || p2 == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F8-1.\n");
    exit(1);
  }

  op_p2 = pol_opposite(p2); /* We change the sign of each coefficient */
  if(op_p2 == NULL){ /* Error */
    printf("Fatal Error. Pol-F8-2.\n");
    exit(1);
  }

  sub = pol_sum(p1, op_p2); /* We sum p1 to the opposite of p2 */
  if(sub == NULL){ /* Error */
    printf("Fatal Error. Pol-F8-3.\n");
    exit(1);
  }

  pol_destroy(op_p2); /* Freeing the auxiliary memory */

  return sub;
}


float pol_eval(pol *p, float x){
  int i;
  float res = 0;

  if(p == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F9-1.\n");
    exit(1);
  }

  res = p->coef[0];
  for(i=1; i<=p->deg; i++){
    res += (p->coef[i] * pow(x, i));
  }
  return res;
}


pol* pol_derivate(pol *p){
  pol *der=NULL;
  int i;

  if(p == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F10-1.\n");
    exit(1);
  }

  der = pol_create(p->deg - 1);
  if(der==NULL){ /* Error */
    printf("Fatal Error. Pol-F10-2.\n");
    exit(1);
  }

  der->coef[0] = p->coef[1];
  for(i=1; i<=der->deg; i++){
    der->coef[i] = p->coef[i+1] * (i+1);
  }

  return der;
}


pol* pol_mult(pol *p1, pol *p2){
  pol *mult=NULL;
  int i, j;

  if(p1 == NULL || p2 == NULL){ /* Checking input arguments */
    printf("Fatal Error. Pol-F11-1.\n");
    exit(1);
  }

  mult = pol_create(p1->deg + p2->deg);
  if(mult==NULL){ /* Error */
    printf("Fatal Error. Pol-F11-2.\n");
    exit(1);
  }

  for(i = 0; i<=mult->deg; i++){ /* Initializing mult´s vector to zero */
    mult->coef[i] = 0;
  }

  for(i = 0; i<=p1->deg; i++){
    for(j = 0; j<=p2->deg; j++){
      mult->coef[i+j] = (mult->coef[i+j] + (p1->coef[i] * p2->coef[j])); /* Parenthesis are not required */
    }
  }
  for(i = mult->deg; i>0; i--){
    if(mult->coef[i] == 0.0){
      mult->deg--;
    }
    else if(mult->coef[i] != 0.0) break;
  }

  return mult;
}


pol* pol_div(pol *dend, pol *der){
  pol *q=NULL;
  pol *aux1=NULL, *aux2=NULL, *s1=NULL, *m1=NULL, *op=NULL;
  int i;

   /* -----------Checking input arguments---------- */
  if(dend == NULL || der == NULL){
    printf("Fatal Error. Pol-F12-1.\n");
    exit(1);
  }
  if(der->deg == 0 && der->coef[0] == 0){
    printf("It is not allowed to divide by the zero polynomial.\n");
    exit(1);
  }
  /* -------------------------------------------------*/

  /* Case in that the degree of the divider polynomial is greater than the dividend polynomial */
  if(dend->deg < der->deg){
    q = pol_create(0);
    if(q==NULL){ /* Error */
      printf("Fatal Error. Pol-F12-2.\n");
      exit(1);
    }

    *(q->coef) = 0.0;
    return q;
  }

  /* Allocating memory for the quotient */
  q = pol_create(dend->deg - der->deg);
  if(q==NULL){ /* Error */
    printf("Fatal Error. Pol-F12-3.\n");
    exit(1);
  }

  for(i = 0; i<=q->deg; i++){ /* Initializing q´s vector to zero */
    q->coef[i] = 0;
  }
  /* ----------------------------------- */

  /* Case in that the degree of the divider polynomial is zero */
  if(der->deg == 0){
    for(i=0; i<=q->deg; i++){
      q->coef[i] = dend->coef[i] / der->coef[0]; /* It is already checked it is not equal to zero */
    }
    return q;
  }

  /* Now, the rest of the cases... */
  aux1 = pol_copy(dend);
  if(aux1 == NULL){ /* Error */
    printf("Fatal Error. Pol-F12-4.\n");
    exit(1);
  }

  while(aux1->deg >= der->deg){
    aux2 = pol_create(aux1->deg - der->deg);
    if(aux2==NULL){ /* Error */
      printf("Fatal Error. Pol-F12-5.\n");
      exit(1);
    }

    for(i = 0; i<=aux2->deg; i++){ /* Initializing q´s vector to zero */
      aux2->coef[i] = 0;
    }

    aux2->coef[aux2->deg] = aux1->coef[aux1->deg] / der->coef[der->deg];

    q->coef[aux1->deg - der->deg] = aux1->coef[aux1->deg] / der->coef[der->deg];

    m1 = pol_mult(aux2, der);
    op = pol_opposite(m1);
    s1 = pol_sum(aux1, op);

    pol_destroy(aux1);
    aux1 = s1;
    pol_destroy(m1);
    pol_destroy(op);
    pol_destroy(aux2);
  }
  pol_destroy(aux1);
  return q;
}


int pol_plot(pol *p, int Xlen, int Ylen){
  char **M=NULL;
  int i, j;
  int OX, OY;
  int res, y;

  /*Input error checking */
  if(p==NULL){
    printf("Fatal Error. Pol-F13-1.\n");
    exit(1);
  }
  if(Xlen > MaxXlen || Xlen <= 2){
    printf("Error. X-axis lenght is incorrect.\n");
    return -1;
  }
  if(Ylen > MaxYlen || Ylen <= 2){
    printf("Error. Y-axis lenght is incorrect.\n");
    return -1;
  }
  /* --------------------------------- */
  OY = (Xlen-1)/2;
  OX = Ylen/2;
  M = (char **) malloc(Ylen * sizeof(char *));
  if(M==NULL){ /* Error */
    printf("Fatal Error. Pol-F13-2.\n");
    exit(1);
  }

  for(i=0; i<Ylen; i++){
    M[i] = (char *) malloc((Xlen+1) * sizeof(char)); /* +1 because we need the /0 of end of string */
    if(M[i]==NULL){ /* Error + freeing everything already allocated */
      printf("Fatal Error. Pol-F13-3.\n");
      for(j=0; j<i; j++){
        free(M[j]);
      }
      free(M);
      exit(1);
    }
  }

  for(i=0; i<Ylen; i++){ /* Writing the /0 of end of string */
    M[i][Xlen] = 0;
  }

  for(i=0; i<Ylen; i++){
    for(j=0; j<Xlen; j++){
      M[j][i] = ' ';
    }
  }
  for(i=0; i<Xlen; i++){ /* Writing X-axis */
    M[OX][i] = '-';
  }
  for(i=0; i<Ylen; i++){ /* Writing Y-axis */
    M[i][OY] = '|';
  }
  M[OX][OY] = '+'; /* Writing origin */

  for(i=0, j=((Xlen-1)/-2); i<Xlen; i++, j++){ /* Ploting */
    res = (int) pol_eval(p, j);
    if(res <= (Ylen/2) && res >= ((Ylen-1)/-2)){
      y = (-1)*(res - (Ylen/2));
      M[y][i] = 'o';
    }
  }

  printf("POLYNOMIAL PLOT OF:\n");
  pol_print(p);
  for(i=0; i<Ylen; i++){ /*Printing*/
    printf("%s\n", M[i]);
  }

  for(i=0; i<Ylen; i++){
    free(M[i]);
  }
  free(M);

  return 0;
}


int pol_filePlot(pol *p, char *filename, int a, int b){
  FILE *f=NULL;
  int i;
  float res;

  if(p==NULL || filename==NULL){
    printf("Fatal Error. Pol-F14-1.\n");
    exit(1);
  }
  if(a>=b){
    printf("Error. Plotting interval is wrong.\n");
    return -1;
  }

  f = (FILE *) fopen(filename, "w");
  if(f==NULL){
    printf("Fatal Error. Pol-F14-2.\n");
    exit(1);
  }

  fprintf(f, "X     f(X)\n");
  for(i=a; i<=b; i++){
    res = pol_eval(p, i);
    fprintf(f, "%d   %.2f\n", i, res);
  }

  fclose(f);
  return 0;
}
