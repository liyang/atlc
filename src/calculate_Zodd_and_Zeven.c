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

void calculate_Zodd_and_Zeven(double *Zodd, double *Zeven, double *Zo, double w, double H, double s, double er)
{
#ifdef HAVE_LIBGSL
  double ke, ko, ko_dash, ke_dash;
  ke=(tanh((M_PI/2)*(w/H)))*tanh((M_PI/2)*(w+s)/H);
  ko=(tanh((M_PI/2)*(w/H)))/tanh((M_PI/2)*(w+s)/H);

  ke_dash=sqrt(1-ke*ke);
  ko_dash=sqrt(1-ko*ko);

  *Zeven=30.0*M_PI*gsl_sf_ellint_Kcomp(ke_dash, GSL_PREC_DOUBLE)/(gsl_sf_ellint_Kcomp(ke,GSL_PREC_DOUBLE)*sqrt(er));
  *Zodd= 30.0*M_PI*gsl_sf_ellint_Kcomp(ko_dash, GSL_PREC_DOUBLE)/(gsl_sf_ellint_Kcomp(ko,GSL_PREC_DOUBLE)*sqrt(er));
  *Zo=sqrt( (*Zodd)*(*Zeven));

#else
  printf("This was not linked against the GNU scientific library, gsl.\n");
  printf("Obtain gsl from http://sources.redhat.com/gsl then run 'configure' again.\n");
  printf("and rebuild from the sources again.\n");
  exit(1);
#endif
}
