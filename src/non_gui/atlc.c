/*
atlc - arbitrary transmission line calculator, for the analysis of
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

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

#ifdef ENABLE_POSIX_THREADS
#include <pthread.h>
#endif


#ifdef ENABLE_MPI
#include <mpi.h>
#endif


#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif


#ifdef ENABLE_MPI

void mpi_setup_strip_map(int verbose_level);
void mpi_send_initial_data();
void mpi_kill_workers();

#endif /* ENABLE_MPI */

//#define DEBUG


struct pixels Er_on_command_line[MAX_DIFFERENT_PERMITTIVITIES];
struct pixels Er_in_bitmap[MAX_DIFFERENT_PERMITTIVITIES];

double **Vij;
double **Er;
char **cell_type; 
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
size_t size;
int max_threads=MAX_THREADS, non_vacuum_found=FALSE;
int dielectrics_to_consider_just_now;
int coupler=FALSE;
double r=1.95;

char *inputfile_name;
extern int main(int argc, char **argv) /* Read parameters from command line */
{
  FILE *where_to_print_fp=stdout, *image_data_fp;
  char *outputfile_name, *appendfile_name, *output_prefix;
  long i;
  int offset;
  int q;
  char *end;
  struct transmission_line_properties data;
#ifdef ENABLE_MPI
  int my_rank;
  int width_height[2];
  char *end_ptr;
#endif

  errno=0; 
#ifdef ENABLE_MPI
  MPI_Init(&argc,&argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_pes);

  if (num_pes < 2) {
	fprintf(stderr,"You must use more than 1 PE\n");
	fprintf(stderr,"You must *not* run atlc directly when configured to use the MPI\n");
	fprintf(stderr,"library. Instead use: mpirun -map machine1:machine2:machine3 atlc my_design.bmp\n");
	exit_with_msg_and_exit_code("You must use more than 1 PE.",5);
  }

  if (0 != my_rank) {
	mpi_worker(my_rank);
	exit_with_msg_and_exit_code("",5);
  } else {
	for(i=0; i<num_pes; i++) {
	  strip_weights[i]=1.0;
	}
  }
#endif /* ENABLE_MPI */
#ifdef DEBUG
  printf("errno=%d in atlc.c #1\n",errno);
#endif
  set_data_to_sensible_starting_values(&data);
  inputfile_name=string(0,1024);
  outputfile_name=string(0,1024);
  appendfile_name=string(0,1024);
  output_prefix=string(0,1024);
  /* only use this if we have both a multi-threaded application and that 
  with have the function */
  strcpy(output_prefix,"");
  while((q=get_options(argc,argv,"Cr:vsSc:d:p:i:t:w:")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright( (char *) "1996-2002");
      exit_with_msg_and_exit_code("",1);
    break;
    case 'b':
      data.should_binary_data_be_written_tooQ=TRUE;
    break;
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
    case 'p':
      strcpy(output_prefix,my_optarg);
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
    case 't':
      max_threads=atol(my_optarg);
#ifndef ENABLE_POSIX_THREADS
      exit_with_msg_and_exit_code("Error #1. The -t option can not be used on a package_version of \
atlc that was not\nconfigured with the --with-threads option, and hence built \
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
		  exit_with_msg_and_exit_code("bad weight string", 6);
		}
		if (end_ptr == my_optarg) {
		  exit_with_msg_and_exit_code("bad weight string", 6);
		}
		my_optarg = end_ptr + 1;
		i++;
	  }	while(*end_ptr != '\0');

	  if (i != num_pes) {
		exit_with_msg_and_exit_code("number of weight string entries much match number of PEs",6);
	  }

	  for(i=0; i<num_pes; i++) {
		printf("PE %ld weight: %f\n", i, strip_weights[i]);
	  }
#else
	  exit_with_msg_and_exit_code("bad argument -- w", 5);
#endif
	break;
    case 'i': /* Lighten or darken images of E-field */
    data.image_fiddle_factor=atof(my_optarg);
    if(data.image_fiddle_factor < 1.0)
    {
      fprintf(stderr,"Error #2.image_fiddle_factor set to %f. It must not be less than 1.\n",data.image_fiddle_factor);
      exit_with_msg_and_exit_code("",2);
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
#ifdef DEBUG
  printf("errno=%d in atlc.c #2\n",errno);
#endif
    strcpy(inputfile_name, argv[my_optind]);
    //strcpy(outputfile_name, inputfile_name);
    strcpy(outputfile_name, output_prefix);
    strcat(output_prefix,inputfile_name);
    strcpy(outputfile_name,output_prefix);
    free_string(output_prefix,0,1024);
    read_bitmap_file_headers(inputfile_name, &offset, &size, &width, &height);
    /* Allocate all ram now, so atlc is sure to have it. There is no point
    in getting some now, starting work then finding atlc can't get the 
    rest of what is needed. */
    image_data=ustring(0L,size);
    cell_type=cmatrix(0,width-1,0,height-1);
    Vij=dmatrix(0,width-1,0,height-1);
    Er=dmatrix(0,width-1,0,height-1);
    /* On Solaris systems, if the following is not executed, only one 
    thread will run at any one time, which rather defeats the object of 
    running multi-threaded. */
#ifdef ENABLE_POSIX_THREADS
#ifdef HAVE_PTHREAD_SETCONCURRENCY
    pthread_setconcurrency(max_threads);
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

	mpi_setup_strip_map(data.verbose_level);

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
#ifdef DEBUG
  printf("errno=%d in atlc.c #3\n",errno);
#endif
    if( strcmp(argv[my_optind],"-") != 0)
    {
      //if( (image_data_fp=fopen(outputfile_name, "rb")) == NULL)
      if( (image_data_fp=fopen(inputfile_name, "rb")) == NULL)
      {
        fprintf(stderr,"Error #3. Can't open %s!!!!!\n", argv[my_optind]);
        exit_with_msg_and_exit_code("",3);
      }
      if(fseek(image_data_fp, offset, SEEK_SET)!=0)
      {   
        fprintf(stderr,"Error #4. Sorry, unable to seek to the correct part \
	(offset=%d) of the bmp image\n", offset);
	exit_with_msg_and_exit_code("",4);
      }
    } /* end of if( strcmp(argv[my_optind],"-") != 0) */
    else
      image_data_fp=stdin;
    /* For some unknown reason Microsoft's Visual C++ was unhappy to read
    the bitmap image using an fread() call. Instead, the following two 
    stupid lines fixed that issue. This will only get compiled under 
    Windoze, the more sensible fread call being used on other operating 
    systems. */
#ifdef WINDOWS
    for(i=0; (i < (long)size ) && (feof(image_data_fp)==0); i++)
      image_data[i]=(unsigned char)fgetc(image_data_fp);
#else
	i = fread(image_data, 1, size, image_data_fp);
#endif
    if((ferror(image_data_fp) || (i != size)))
    {
      fprintf(stderr,"Error #5. Unable to read all of the image data properly\n");
      exit_with_msg_and_exit_code("",5);
    }
    /* declare matrix's to indicate what pixels are fixed and variable */
    /* We now fill the following 3 arrays with the correct data, based on the 
    contents of the bitmap image */

    setup_arrays(&data);
    check_for_boundaries();
    /* Now 'v' has the voltages at each grid element, 'Er' 
    the permittivites and 'cell_type' is either FIXED or variable, 
    indicating a dielectric (VARIABLE) or a metal */

#ifdef ENABLE_MPI
	mpi_send_initial_data();
#endif /* ENABLE_MPI */

    /* If there are multiple dielectrics, the impedance calculations
    needs to be done twice. We start by doing them once, for an vacuum
    dielectric. If necessary, they will be done again */
#ifdef DEBUG
  printf("errno=%d in atlc.c #4\n",errno);
#endif
    do_fd_calculation(&data, where_to_print_fp,outputfile_name);
#ifdef DEBUG
  printf("errno=%d in atlc.c #5\n",errno);
#endif

#ifdef ENABLE_MPI
	mpi_kill_workers();

	MPI_Finalize();
#endif /* ENABLE_MPI */

  }
  else
  {
    usage_atlc();
    return(PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS); 
  }
  free_string(inputfile_name,0,1024);
  free_string(outputfile_name,0,1024);
  free_string(appendfile_name,0,1024);
  free_ustring(image_data,0L,size);
  free_cmatrix(cell_type,0,width-1,0,height-1);
  free_dmatrix(Vij, 0,width-1,0,height-1);
  free_dmatrix(Er,0,width-1,0,height-1);

  return(OKAY); 
}



#ifdef ENABLE_MPI


void mpi_setup_strip_map (int verbose_level) {
  int i, strip_width, leftover;
  int start_col;
  double sum_of_weights;

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

  if (verbose_level > 1) {
	printf("map: ");
	for(i=0; i<=num_pes; i++) {
	  printf("(%d:%d), ", strip_map[i].start_col, 
			 strip_map[i].start_col + strip_map[i].num_cols - 1);
	}
	printf(" (end)\n");
  }

}


void mpi_send_initial_data() {
  int i;
  int start_col, num_cols;
  int strip_params[2];

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
			  (num_cols+4)*height,
			  MPI_INT,
			  i,
			  MSG_TAG_CELL_TYPE,
			  MPI_COMM_WORLD,
			  &cell_type_send_requests[i-1]);
	  
	MPI_Isend(Er[start_col-2],
			  (num_cols+4)*height,
			  MPI_DOUBLE,
			  i,
			  MSG_TAG_ER,
			  MPI_COMM_WORLD,
			  &er_send_requests[i-1]);
			 
  }

  MPI_Waitall(num_pes-1, strip_params_send_requests, ignored_statuses);
  MPI_Waitall(num_pes-1, cell_type_send_requests, ignored_statuses);
  MPI_Waitall(num_pes-1, er_send_requests, ignored_statuses);
}


void mpi_kill_workers() {
  int control, i;
	/* kill off all of the worker PEs*/
	control = CONTROL_VALUE_EXIT;
	for(i=1; i<num_pes; i++) {
	  MPI_Isend(&control,
				1,
				MPI_INT,
				i,
				MSG_TAG_CONTROL,
				MPI_COMM_WORLD,
				&control_send_requests[i-1]);
	}
	MPI_Waitall(num_pes-1, control_send_requests, ignored_statuses);
}

#endif /* ENABLE_MPI */
