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
  double H, w, s, er, ke_dash, ko_dash,ke, ko, Zodd, Zeven, Zo;
  gsl_complex z;
  GSL_SET_COMPLEX(&z, 3, 4);
  if(argc!=4)
  {
    usage_calc_coupler();
    exit(1);
  }
  H=atof(argv[1]);
  w=atof(argv[2]);
  s=atof(argv[3]);
  er=atof(argv[4]);

  ke_dash=sqrt(1-(ke*ke));
  ko_dash=sqrt(1-(ko*ko));

  ke=(tanh((M_PI/2)*(w/H)))*tanh((M_PI/2)*(w+s)/H);
  //z=(M_PI/2)*(w+s)/H;
  //ko=(tanh((M_PI/2)*(w/H)))*coth((M_PI/2)*(w+s)/H);
}
