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

#ifdef HAVE_PTHREADS_H
#include <pthreads.h>
#endif

#endif


#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif
struct pixels Er_on_command_line[MAX_DIFFERENT_PERMITTIVITIES];
struct pixels Er_in_bitmap[MAX_DIFFERENT_PERMITTIVITIES];

double **Vij;
double **Er;
int **cell_type; 
unsigned char *image_data;
int width, height;
extern int errno;
double found_this_dielectric=1000000.0;
int avoid_use_of_fast_convergence_method=FALSE;
size_t size;
int max_threads=MAX_THREADS, non_vacuum_found=FALSE;
int append_flag=FALSE;
int verbose=0;
int dielectrics_to_consider_just_now;
int coupler=FALSE;
double r=1.95;

extern int main(int argc, char **argv) /* Read parameters from command line */
{
  FILE *where_to_print_fp=stdout, *image_data_fp;
  char *outputfile_name, *inputfile_name, *appendfile_name;
  long i;
  int offset;
  int q;
  char *end;
  struct transmission_line_properties data;

  set_data_to_sensible_starting_values(&data);
  inputfile_name=string(0,1000);
  outputfile_name=string(0,1000);
  appendfile_name=string(0,1000);
  /* only use this if we have both a multi-threaded application and that 
  with have the function */
  while((q=get_options(argc,argv,"Cr:vsSc:d:F:i:t:")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright( (char *) "1996-2002");
      exit(1);
    break;
    case 'b':
      data.should_binary_data_be_written_tooQ=TRUE;
    case 'd':
      /* Read a colour from the command line */
      Er_on_command_line[data.dielectrics_on_command_line].other_colour=\
      strtol(my_optarg, &end, 16);
      /* Sepparte it into the Red, Green and Blue components */
      Er_on_command_line[data.dielectrics_on_command_line].blue=\
      Er_on_command_line[data.dielectrics_on_command_line].other_colour%256;
      Er_on_command_line[data.dielectrics_on_command_line].green=\
      Er_on_command_line[data.dielectrics_on_command_line].other_colour/(256);
      Er_on_command_line[data.dielectrics_on_command_line].red=\
      Er_on_command_line[data.dielectrics_on_command_line].other_colour/(256*256);
      *end++; /* Gets rid of '=' sign which we put on the command line */
      Er_on_command_line[data.dielectrics_on_command_line].epsilon=atof(end);
      if (verbose > 1)
        printf("r=%x g=%x b=%x col=%x Er=%f\n",\
      Er_on_command_line[data.dielectrics_on_command_line].red,\
      Er_on_command_line[data.dielectrics_on_command_line].green, \
      Er_on_command_line[data.dielectrics_on_command_line].blue, \
      Er_on_command_line[data.dielectrics_on_command_line].other_colour, \
      Er_on_command_line[data.dielectrics_on_command_line].epsilon);
      data.dielectrics_on_command_line++;
    break;
    case 'c':
      data.cutoff=atof(my_optarg);
    break;
    case 'r':
      data.r=atof(my_optarg);
    break;
    case 's':
      data.write_bitmap_field_imagesQ=FALSE;
    break;
    case 'S':
      data.write_binary_field_imagesQ=FALSE;
    break;
    case 'F':
      strcpy(appendfile_name,my_optarg);
      append_flag=TRUE;
    break;
    case 't':
      max_threads=atol(my_optarg);
#ifndef ENABLE_MP
      error_and_exit("Error #1. The -t option can not be used on a package_version of \
atlc that was not\nconfigured with the --with-mp option, and hence built \
without the threads\nlibrary.\n",1);
#endif
    break;
    case 'i': /* Lighten or darken images of E-field */
    data.image_fiddle_factor=atof(my_optarg);
    if(data.image_fiddle_factor < 1.0)
    {
      fprintf(stderr,"Error #2.image_fiddle_factor set to %f. It must not be less than 1.\n",data.image_fiddle_factor);
      exit(2);
    }
    break;
    case 'v':
      verbose++;
      data.verbose_level++;
    break;
    case '?':
      usage_atlc();
  } /* End of the switch statement */

  /* There should only be one argument to atlc, the bitmapfile name.
  There can be a few options though. We now check that there is only
  one argument */

  if(argc-my_optind == 1)  /* This should be so hopefully !! */
  {
    strcpy(inputfile_name, argv[my_optind]);
    strcpy(outputfile_name, inputfile_name);
    read_bitmap_file_headers(inputfile_name, &offset, &size, &width, &height);
    image_data=ustring(0L,size);
    /* On Solaris systems, if the following is not executed, only one 
    thread will run at any one time, which rather defeats the object of 
    running multi-threaded. */
#ifdef ENABLE_MP
#ifdef HAVE_THR_SETCONCURRENCY
    thr_setconcurrency(max_threads);
#endif
#endif 
    
    /* Each thread solves the equations for a part of the voltage
    matrix. If there were more threads than columms we would have a
    problem. I'm not sure exactly how many can be got away with, but
    one is unlikly to have more cpus that matrix columns */

    if(max_threads > width/4)
      max_threads=width/4;

    /* In theory, it would be sensible to get atlc to be able to read
    from stdin. This is a test, that checks if the filename is '-', and
    if so assumes its reading from stdin. So far, the programme is
    unable to read from stdin, so this code is not really doing
    anything useful, but might be expanded at a later date. */
    if( strcmp(argv[my_optind],"-") != 0)
    {
      if( (image_data_fp=fopen(outputfile_name, "rb")) == NULL)
      {
        fprintf(stderr,"Error #3. Can't open %s!!!!!\n", argv[my_optind]);
        exit(3);
      }
      if(fseek(image_data_fp, offset, SEEK_SET)!=0)
      {   
        fprintf(stderr,"Error #4. Sorry, unable to seek to the correct part \
	(offset=%d) of the bmp image\n", offset);
	exit(4);
      }
    } /* end of if( strcmp(argv[my_optind],"-") != 0) */
    else
      image_data_fp=stdin;

    for(i=0; (i < (long)size ) && (feof(image_data_fp)==0); i++)
      image_data[i]=(unsigned char)fgetc(image_data_fp);
    if((ferror(image_data_fp) || (i != size)))
    {
      fprintf(stderr,"Error #5. Unable to read all of the image data properly\n");
      exit(5);
    }
    /* declare matrix's to indicate what pixels are fixed and variable */
    cell_type=imatrix(0,width,0,height);
    Vij=dmatrix(0,width,0,height);
    Er=dmatrix(0,width,0,height);
      
    /* We now fill the following 3 arrays with the correct data, based on the 
    contents of the bitmap image */

    setup_arrays(&data);
    check_for_boundaries();
    /* Now 'v' has the voltages at each grid element, 'Er' 
    the permittivites and 'cell_type' is either FIXED or variable, 
    indicating a dielectric (VARIABLE) or a metal */

    /* If there are multiple dielectrics, the impedance calculations
    needs to be done twice. We start by doing them once, for an vacuum
    dielectric. If necessary, they will be done again */
    do_fd_calculation(&data, where_to_print_fp,inputfile_name);

  }
  else
    usage_atlc();
  exit(5);
}
