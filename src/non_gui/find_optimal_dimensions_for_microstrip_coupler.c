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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"

int main(int argc, char **argv)
{
  double s, w, g, Zcomm, Zdiff, Zodd, Zeven;  
  double Er_odd, Er_even, Zo;
  double error_min=1e100, error, best_s, best_w, best_g; 
  double ideal_Zcomm=30; 
  double ideal_Zdiff=90;
  int x;
  char *text, *null;
  FILE *fp, *fp_best;
  text = (char *) malloc(4000);
  null = (char *) malloc(4000);

  //for(s=0.1; s<5; s+=0.5)
  s=0.5;
    for(w=0.1; w<=5; w+=0.5)
      for(g=0.1; g<=5; g+=0.5)
      {
	//printf("s=%f w=%f g=%f >>iterate.txt");
	sprintf(text,"generate_bmp_for_coupled_microstrip %f %f %f 1.593 0.035 1 3.7 iterate.bmp\n",w, s, g);
	system(text);
	//printf(text);
	//printf(text);
	sprintf(text,"atlc iterate.bmp >> foo.txt\n");
	//printf(text);
	system(text);
	fp=fopen("foo.txt","r");
	if(fp==NULL)
	{
	  fprintf(stderr,"can't open file\n");
	  exit(2);
        }
	fscanf(fp,"%s %d %s %lf %s %lf %s %lf %s %lf %s %lf %s %lf %s %lf",null,&x,null,&Er_odd,null,&Er_even, null, &Zodd,null,&Zeven,null,&Zo, null, &Zdiff,null,&Zcomm);
	fclose(fp);
	printf("x=%d Er_odd=%f Er_even=%f Zodd=%lf Zeven=%lf Zo=%lf Zdiff=%lf Zcomm=%lf\n",x, Er_odd,Er_even,Zodd, Zeven,Zo, Zdiff, Zcomm);
	error=fabs(Zdiff-ideal_Zdiff)/ideal_Zdiff+fabs(Zcomm-ideal_Zcomm)/ideal_Zcomm;
	if(error< error_min)
	{
	  best_s=s;
	  best_w=w; 
	  best_g=g;
	  error_min=error;
	  printf("best so far = s=%f w=%f g=%f Zodd=%f Zeven=%f Zdiff=%f Zcomm=%f\n",s,w,g, Zodd, Zeven,Zdiff, Zcomm);
	  fp_best=fopen("test_results.txt","a");
	  if(fp_best == NULL)
	  {
	    fprintf(stderr,"Can't open file  test_results.txt for update\n");
	    exit(1);
          }
	  fprintf(fp_best,"best so far = s=%f w=%f g=%f Zodd=%f Zeven=%f Zdiff=%f Zcomm=%f\n",s,w,g, Zdiff, Zcomm,Zodd, Zeven);
	  fclose(fp_best);
        }
      }
      exit(0);
}
	
    
