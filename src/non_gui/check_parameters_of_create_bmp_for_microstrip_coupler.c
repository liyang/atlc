

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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"

#ifdef ENABLE_MP

#ifdef HAVE_THREAD_H
#include <thread.h>
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#endif

#include "exit_codes.h"

void check_parameters_of_create_bmp_for_microstrip_coupler(struct transmission_line_properties pcb) 
{
      if ( pcb.ww <= 0)
	error_and_exit("w <= 0",ARGUMENT_w_OUT_OF_RANGE);
      if ( pcb.ss <= 0)
	error_and_exit("s <= 0",ARGUMENT_s_OUT_OF_RANGE);
      if ( pcb.gg <= 0)
	error_and_exit("g <= 0",ARGUMENT_g_OUT_OF_RANGE);
      if ( pcb.hh <= 0)
	error_and_exit("h <= 0",ARGUMENT_h_OUT_OF_RANGE);
      if ( pcb.tt <= 0)
	error_and_exit("0 <= 0",ARGUMENT_t_OUT_OF_RANGE);
      if ( pcb.Er1 < 1)
	error_and_exit("0 <= 0",ARGUMENT_Er1_OUT_OF_RANGE);
      if ( pcb.Er2 < 1)
	error_and_exit("0 <= 0",ARGUMENT_Er2_OUT_OF_RANGE);
}
