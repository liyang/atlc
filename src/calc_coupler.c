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
#ifdef HAVE_LIBGSL
  double H, w, s, er, Zodd, Zeven, Zo;
  double ke, ko, ko_dash, ke_dash;
  if(argc!=5)
  {
    usage_calc_coupler();
    exit(1);
  }
  H=atof(argv[1]);
  w=atof(argv[2]);
  s=atof(argv[3]);
  er=atof(argv[4]);

  ke=(tanh((M_PI/2)*(w/H)))*tanh((M_PI/2)*(w+s)/H);
  ko=(tanh((M_PI/2)*(w/H)))/tanh((M_PI/2)*(w+s)/H);
  //ko=tanh((M_PI/2)*(w/H)))*tanh((M_PI/2)*(w+s)/H);

  ke_dash=sqrt(1-ke*ke);
  ko_dash=sqrt(1-ko*ko);

  Zeven=30.0*M_PI*gsl_sf_ellint_Kcomp(ke_dash, GSL_PREC_DOUBLE)/(gsl_sf_ellint_Kcomp(ke,GSL_PREC_DOUBLE)*sqrt(er));
  Zodd= 30.0*M_PI*gsl_sf_ellint_Kcomp(ko_dash, GSL_PREC_DOUBLE)/(gsl_sf_ellint_Kcomp(ko,GSL_PREC_DOUBLE)*sqrt(er));

  printf("Zodd=%f Zeven=%f\n", Zodd, Zeven);

#else
  printf("calc_coupler was not linked against the GNU scientific library, gsl.\n");
  printf("Obtain gsl from http://sources.redhat.com/gsl then run 'configure' again.\n");
  printf("and rebuild calc_coupler from the sources again.\n");
  exit(1);
#endif

  //exit(0);
}
