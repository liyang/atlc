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


#ifdef ENABLE_MPI
#include <mpi.h>
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
#ifdef ENABLE_MPI
int num_pes=0;
int width_height[2];
struct strip strip_map[MAX_PES+1];  /* PE 0 will use two map entries */
double strip_weights[MAX_PES];
MPI_Request strip_params_send_requests[MAX_PES];
MPI_Request cell_type_send_requests[MAX_PES];
MPI_Request er_send_requests[MAX_PES];
MPI_Request control_send_requests[MAX_PES];
MPI_Status ignored_statuses[MAX_PES];
#endif /* ENABLE_MPI */
unsigned char *image_data;
int width, height;
extern int errno;
double found_this_dielectric=1000000.0;
int avoid_use_of_fast_convergence_method=FALSE;
size_t size;
int max_threads=MAX_THREADS, non_vacuum_found=FALSE;
int append_flag=FALSE;
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
#ifdef ENABLE_MPI
  int my_rank;
  int width_height[2];
  int strip_params[2];
  int control;
  int start_col, num_cols;
  int strip_width, leftover;
  char *end_ptr;
  double sum_of_weights;
#endif

  
#ifdef ENABLE_MPI
  MPI_Init(&argc,&argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_pes);

  if (num_pes < 2) {
	error_and_exit("You must use more than 1 PE.",5);
  }

  if (0 != my_rank) {
	mpi_worker(my_rank);
	error_and_exit("",5);
  } else {
	for(i=0; i<num_pes; i++) {
	  strip_weights[i]=1.0;
	}
  }
#endif /* ENABLE_MPI */

  set_data_to_sensible_starting_values(&data);
  inputfile_name=string(0,1000);
  outputfile_name=string(0,1000);
  appendfile_name=string(0,1000);
  /* only use this if we have both a multi-threaded application and that 
  with have the function */
  while((q=get_options(argc,argv,"Cr:vsSc:d:F:i:t:w:")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright( (char *) "1996-2002");
      error_and_exit("",1);
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
      end++; /* Gets rid of '=' sign which we put on the command line */
      Er_on_command_line[data.dielectrics_on_command_line].epsilon=atof(end);
      if (data.verbose_level > 1)
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
    case 'w':
#ifdef ENABLE_MPI
	  i = 0;
	  end_ptr = my_optarg;
	  do {
		strip_weights[i] = strtod(my_optarg, &end_ptr);
		if (*end_ptr != ':' && *end_ptr != '\0') {
		  error_and_exit("bad weight string", 6);
		}
		if (end_ptr == my_optarg) {
		  error_and_exit("bad weight string", 6);
		}
		my_optarg = end_ptr + 1;
		i++;
	  }	while(*end_ptr != '\0');

	  if (i != num_pes) {
		error_and_exit("number of weight string entries much match number of PEs",6);
	  }

	  for(i=0; i<num_pes; i++) {
		printf("PE %i weight: %f\n", i, strip_weights[i]);
	  }
#else
	  error_and_exit("bad argument -- w", 5);
#endif
	break;
    case 'i': /* Lighten or darken images of E-field */
    data.image_fiddle_factor=atof(my_optarg);
    if(data.image_fiddle_factor < 1.0)
    {
      fprintf(stderr,"Error #2.image_fiddle_factor set to %f. It must not be less than 1.\n",data.image_fiddle_factor);
      error_and_exit("",2);
    }
    break;
    case 'v':
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

#ifdef ENABLE_MPI
	if(num_pes > width/4) {
	  num_pes = width/4;
	}

	sum_of_weights = 0.0;
	for(i=0; i<num_pes; i++) {
	  sum_of_weights += strip_weights[i];
	}

	/* distribute the bulk of the columns evenly across the PEs */
	leftover = width;
	for (i=0, start_col=0; i<num_pes; i++, start_col+=strip_width) {
	  strip_width = width*strip_weights[i]/sum_of_weights;

	  strip_map[i].start_col = start_col;
	  strip_map[i].num_cols = strip_width;

	  leftover -= strip_width;
	}

	/* give a leftover column to each PE until they are all gone */
	if (leftover) {
	  strip_map[0].num_cols++;
	}
	for(i=1; i<leftover; i++) {
	  strip_map[i].start_col = strip_map[i-1].start_col + strip_map[i-1].num_cols;
	  strip_map[i].num_cols++;
	}
	for(i=leftover; i<num_pes; i++) {
	  strip_map[i].start_col = strip_map[i-1].start_col + strip_map[i-1].num_cols;
	}


	/* now rotate the map left half of the PE 0 strip_width, assigning PE 0 the
	   resulting left and right half-strips, so that it handles
	   both the left and right edge conditions.  this allows us to conserve
	   memory on the worker PEs, simplify the indexing on the workers a bit, 
	   and leave the existing computational routines unchanged in the face of all 
	   of that. */
	strip_width = strip_map[0].num_cols;
	for(i=1; i<num_pes; i++) {
	  strip_map[i].start_col -= strip_width/2;
	}
	strip_map[0].num_cols -= strip_width/2;

	/* add an additional entry to the map to cover the rightmost strip_width/2 
	   columns that wereuncovered by the shift to the left */
	strip_map[num_pes].start_col = 
	  strip_map[num_pes-1].start_col + 
	  strip_map[num_pes-1].num_cols;
	strip_map[num_pes].num_cols = width - strip_map[num_pes].start_col;

	if (data.verbose_level > 1) {
	  printf("map: ");
	  for(i=0; i<=num_pes; i++) {
		printf("(%d:%d), ", strip_map[i].start_col, 
			   strip_map[i].start_col + strip_map[i].num_cols - 1);
	  }
	  printf(" (end)\n");
	}

	width_height[0]= width;
	width_height[1]= height;

	for(i=1; i<num_pes; i++) {
	  MPI_Send(&width_height,
			   2,
			   MPI_INT,
			   i,
			   MSG_TAG_WIDTH_HEIGHT,
			   MPI_COMM_WORLD);
	}
#endif /* ENABLE_MPI */

    /* In theory, it would be sensible to get atlc to be able to read
    from stdin. This is a test, that checks if the filename is '-', and
    if so assumes its reading from stdin. So far, the program is
    unable to read from stdin, so this code is not really doing
    anything useful, but might be expanded at a later date. */
    if( strcmp(argv[my_optind],"-") != 0)
    {
      if( (image_data_fp=fopen(outputfile_name, "rb")) == NULL)
      {
        fprintf(stderr,"Error #3. Can't open %s!!!!!\n", argv[my_optind]);
        error_and_exit("",3);
      }
      if(fseek(image_data_fp, offset, SEEK_SET)!=0)
      {   
        fprintf(stderr,"Error #4. Sorry, unable to seek to the correct part \
	(offset=%d) of the bmp image\n", offset);
	error_and_exit("",4);
      }
    } /* end of if( strcmp(argv[my_optind],"-") != 0) */
    else
      image_data_fp=stdin;

#if 0
    for(i=0; (i < (long)size ) && (feof(image_data_fp)==0); i++)
      image_data[i]=(unsigned char)fgetc(image_data_fp);
#else
	i = fread(image_data, 1, size, image_data_fp);
#endif
    if((ferror(image_data_fp) || (i != size)))
    {
      fprintf(stderr,"Error #5. Unable to read all of the image data properly\n");
      error_and_exit("",5);
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


#ifdef ENABLE_MPI
	/* each worker PE needs to know what part of the matrix it has
	   been given, and needs a copy of the cell_type and Er arrays
	   corresponding to its strip.
	 */

	for(i=1; i<num_pes; i++) {
	  start_col = strip_map[i].start_col;
	  num_cols = strip_map[i].num_cols;
	  
	  strip_params[0] = start_col;
	  strip_params[1] = num_cols;
	
	  MPI_Isend(strip_params,
				2,
				MPI_INT,
				i,
				MSG_TAG_STRIP_PARAMS,
				MPI_COMM_WORLD,
				&strip_params_send_requests[i-1]);
	
	/* each worker is given two extra columns to 
	   the left of its strip and one to the right.
	   see the comments in finite_difference_mpi.c
	   for details */
	  
	  MPI_Isend(cell_type[start_col-2],
				(num_cols+3)*height,
				MPI_INT,
				i,
				MSG_TAG_CELL_TYPE,
				MPI_COMM_WORLD,
				&cell_type_send_requests[i-1]);
	  
	  MPI_Isend(Er[start_col-2],
				(num_cols+3)*height,
				MPI_DOUBLE,
				i,
				MSG_TAG_ER,
				MPI_COMM_WORLD,
				&er_send_requests[i-1]);
			 
	}

	MPI_Waitall(num_pes-1, strip_params_send_requests, ignored_statuses);
	MPI_Waitall(num_pes-1, cell_type_send_requests, ignored_statuses);
	MPI_Waitall(num_pes-1, er_send_requests, ignored_statuses);
#endif /* ENABLE_MPI */


    /* If there are multiple dielectrics, the impedance calculations
    needs to be done twice. We start by doing them once, for an vacuum
    dielectric. If necessary, they will be done again */
    do_fd_calculation(&data, where_to_print_fp,inputfile_name);

#ifdef ENABLE_MPI
	/* kill off all of the worker PEs*/
	for(i=1; i<num_pes; i++) {
	  control = 1;
	  MPI_Isend(&control,
				1,
				MPI_INT,
				i,
				MSG_TAG_CONTROL,
				MPI_COMM_WORLD,
				&control_send_requests[i-1]);
	}
	MPI_Waitall(num_pes-1, control_send_requests, ignored_statuses);

	
#endif /* ENABLE_MPI */

  }
  else
    usage_atlc();
  error_and_exit("",5);
}
