/* atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either package_version 2
of the License, or (at your option) any later package_version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
USA.

Dr. David Kirkby, e-mail drkirkby@ntlworld.com 

*/

/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */

#include "definitions.h"

#ifdef HAVE_GSL_GSL_SF_ELLINT_H 
#include <gsl/gsl_sf_ellint.h>
#endif

#ifdef HAVE_GSL_GSL_COMPLEX_H
#include <gsl/gsl_complex.h>
#endif

#ifdef HAVE_GSL_GSL_COMPLEX_MATH_H
#include <gsl/gsl_complex_math.h>
#endif

#ifdef HAVE_GSL_GSL_BESSEL_MATH_H
#include <gsl/gsl_bessel_math.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "exit_codes.h"

void calculate_Zodd_and_Zeven(double *Zodd, double *Zeven, double *Zo, double w, double H, double s, double er)
{
/*
#if defined(AS_SPARC64_FLAG) || (defined(IN_LIBGCC2) && (defined(__arch64__) || defined(__sparcv9)))
*/

#if defined(HAVE_LIBGSL) && defined(HAVE_GSL_GSL_SF_ELLINT_H) 

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
  exit_with_msg_and_exit_code("",NOT_LINKED_WITH_GSL_LIBRARY);
#endif
}
