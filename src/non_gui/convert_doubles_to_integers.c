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

#include "definitions.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "exit_codes.h"

/* This fuction will convert numbers in a structure such that the 'm'
'best-fit' integers are calculated to best represent a vector of 'm'
floating point numbers. A different weigth can be applied to 
any specific element, by using the vector 'weight' (Set all m elements
of equal weight if all numbers are equally important). The parameter
'error' in the structure gets set to the maximum percentrage error and
the parameters 'good' and 'acceptable' put limits on what is considered
a good fit and what is just acceptable. 

The largest integer that will be fitted is the parameter 'n_max' and the
smallest 'n_min'

The function returns 0 if the maximum percentage error is less than
'good', it returns 'REASONABLE_FITTING_OF_INTEGERS_TO_DOUBLES' if the
maximum error is between 'good and acceptable' and to 
UNACCEPTABLE_FITTING_OF_INTEGERS_TO_DOUBLES  */


int convert_doubles_to_integers(struct fit_doubles_to_integers *x)
{
  return(0);
}

