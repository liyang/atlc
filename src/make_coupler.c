/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */

#include "definitions.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_GSL_GSL_SF_ELLINT_H
#include <gsl/gsl_sf_ellint.h>
#endif

#ifdef HAVE_GSL_GSL_COMPLEX_H
#include <gsl/gsl_complex.h>
#endif

#ifdef HAVE_GSL_GSL_COMPLEX_MATH_H
#include <gsl/gsl_complex_math.h>
#endif

int main(int argc, char **argv)
{
  double H, w, s, er, Zodd, Zeven, Zo;
  if(argc!=5)
  {
    usage_make_coupler();
    exit(1);
  }
  H=atof(argv[1]);
  w=atof(argv[2]);
  s=atof(argv[3]);
  er=atof(argv[4]);
  calculate_Zodd_and_Zeven(&Zodd,&Zeven,&Zo,w,H,s,er);
  printf("Zodd=%f Zeven=%f Zo=%f\n", Zodd, Zeven,Zo);
  exit(0);
}
