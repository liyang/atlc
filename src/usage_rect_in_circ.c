#ifdef HAVE_STDLIB_H
#include <stdlib.h>    
#endif

#include "definitions.h"

void usage_rect_in_circ(void)
{
      fprintf(stderr,"Usage: rect_in_circ [-b bmp_size] [-f outfile] [-v] D w h x y Er\n\n");
      fprintf(stderr,"Where \n");
      fprintf(stderr,"  D  is the internal diameter of the outer conductor \n");
      fprintf(stderr,"  w  is the width of the inner conductor\n");
      fprintf(stderr,"  h  is the height of the inner conductor\n");
      fprintf(stderr,"  x  is the horizontal offset between centres of the conductors\n");
      fprintf(stderr,"  y  is the vertical offset between centres of the conductors\n");
      fprintf(stderr,"  Er is the relative permettivity of the dielectric.\n");
      fprintf(stderr,"  D, w, h, x, and y are either all in mm or all in inches (but not a mixture!!)\n\n");   
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMPSIZE);
      fprintf(stderr,"  -f outfile \n     Write output to 'outfile' instead of stdout\n");
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n\n");
      fprintf(stderr,"                                     ***\n");
      fprintf(stderr,"                              *****************\n"); 
      fprintf(stderr,"                          ****                 ****\n");                        
      fprintf(stderr,"                       ****                       ****\n");                     
      fprintf(stderr,"                     ***                             ***\n");                   
      fprintf(stderr,"                   ***    *************  ^             ***\n");                 
      fprintf(stderr,"                 ***      *************  |               ***\n");               
      fprintf(stderr,"                ***       *************  |                ***\n");              
      fprintf(stderr,"               ***      ^ *************  h                 ***\n");             
      fprintf(stderr,"              ***       | *************  |                  ***\n");            
      fprintf(stderr,"             ***        | *************  |                   ***\n");           
      fprintf(stderr,"             **         y *************  v                   **\n");           
      fprintf(stderr,"            ***         | <-----w----->                        ***\n");          
      fprintf(stderr,"            **          |                                      **\n");          
      fprintf(stderr,"            *<----------v-------------D------------------------>*\n");          
      fprintf(stderr,"            **                                                 **\n");          
      fprintf(stderr,"            **                                                 **\n");          
      fprintf(stderr,"            **                   <--x->                        **\n");          
      fprintf(stderr,"            ***                                               ***\n");          
      fprintf(stderr,"             **                                               **\n");           
      fprintf(stderr,"             ***                                             ***\n");           
      fprintf(stderr,"              **                                             **\n");            
      fprintf(stderr,"               **                                           **\n");             
      fprintf(stderr,"                **                                         **\n");              
      fprintf(stderr,"                 ***                                     ***\n");               
      fprintf(stderr,"                  ****                                 ****\n");                
      fprintf(stderr,"                    ****                             ****\n");                  
      fprintf(stderr,"                      *****                       *****\n");                    
      fprintf(stderr,"                         ******               ******\n");                       
      fprintf(stderr,"                             *******************\n");                           
      fprintf(stderr,"                                     ***\n\n");
      fprintf(stderr,"***WARNING*** Since the output from rect_in_circ is binary data (the bitmap) it\n");
      fprintf(stderr,"will screw up your terminal unless you redirect the ouptut to a file.\n");
      fprintf(stderr,"The '-f' option can be used to send the output to 'outfile' \n");
      fprintf(stderr,"or you can use rect_in_circ D d h Er > filename.bmp \n");


      exit(8); /* Exit - program called with wrong number of arguments */
}
