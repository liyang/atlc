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
double image_fiddle_factor;
int **cell_type; 
unsigned char *image_data;
int width, height;
extern int errno;
double found_this_dielectric=1000000.0;
int avoid_use_of_fast_convergence_method=FALSE;
size_t size;
int max_threads=MAX_THREADS, non_vacuum_found=FALSE;
int append_flag=FALSE;
int verbose=FALSE;
int dielectrics_to_consider_just_now;
int coupler=FALSE;
double r=1.95;

extern int main(int argc, char **argv) /* Read parameters from command line */
{
  long i;
  int q, offset, dielectrics_on_command_line=0, dielectrics_in_bitmap=0;
  int write_field_images=1;
  double capacitance, inductance, Zo, velocity, vf;
  double cutoff=0.0001, c, Zodd, Zeven;
  char *end, *output_filename, *input_filename;
  char *appendfile;
  FILE *image_data_fp, *appendfile_fp, *resultfile_fp;

  image_fiddle_factor=IMAGE_FIDDLE_FACTOR;
  end=string(0,1000);
  output_filename=string(0,1000);
  appendfile=string(0,1000);
  input_filename=string(0,1000);
  /* only use this if we have both a multi-threaded application and that 
  with have the function */
  while((q=get_options(argc,argv,"Cr:vsc:d:F:i:t:")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright( (char *) "1996-2002");
      exit(1);
    break;
    case 'd':
      /* Read a colour from the command line */
      Er_on_command_line[dielectrics_on_command_line].other_colour=\
      strtol(my_optarg, &end, 16);
      /* Sepparte it into the Red, Green and Blue components */
      Er_on_command_line[dielectrics_on_command_line].blue=\
      Er_on_command_line[dielectrics_on_command_line].other_colour%256;
      Er_on_command_line[dielectrics_on_command_line].green=\
      Er_on_command_line[dielectrics_on_command_line].other_colour/(256);
      Er_on_command_line[dielectrics_on_command_line].red=\
      Er_on_command_line[dielectrics_on_command_line].other_colour/(256*256);
      *end++; /* Gets rid of '=' sign which we put on the command line */
      Er_on_command_line[dielectrics_on_command_line].epsilon=atof(end);
      if (verbose)
        printf("r=%x g=%x b=%x col=%x Er=%f\n",\
      Er_on_command_line[dielectrics_on_command_line].red,\
      Er_on_command_line[dielectrics_on_command_line].green, \
      Er_on_command_line[dielectrics_on_command_line].blue, \
      Er_on_command_line[dielectrics_on_command_line].other_colour, \
      Er_on_command_line[dielectrics_on_command_line].epsilon);
      dielectrics_on_command_line++;
    break;
    case 'c':
      cutoff=atof(my_optarg);
    break;
    case 'r':
      r=atof(my_optarg);
    break;
    case 's':
      write_field_images=0;
    break;
    case 'F':
      strcpy(appendfile,my_optarg);
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
    image_fiddle_factor=atof(my_optarg);
    if(image_fiddle_factor < 1.0)
    {
      fprintf(stderr,"Error #2.image_fiddle_factor set to %f. It must not be less than 1.\n",image_fiddle_factor);
      exit(2);
    }
    break;
    case 'v':
      verbose=TRUE;
    break;
    case '?':
      usage_atlc();
  } /* End of the switch statement */

  /* There should only be one argument to atlc, the bitmapfile name.
  There can be a few options though. We now check that there is only
  one argument */

  if(argc-my_optind == 1)  /* This should be so hopefully !! */
  {
    strcpy(input_filename, argv[my_optind]);
    strcpy(output_filename, input_filename);
    resultfile_fp=get_file_pointer_with_right_filename(input_filename,".txt");
    read_bitmap_file_headers(input_filename, &offset, &size, &width, &height);
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
      if( (image_data_fp=fopen(output_filename, "rb")) == NULL)
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

    setup_arrays(&dielectrics_in_bitmap, dielectrics_on_command_line);
    check_for_boundaries();
    /* Now 'v' has the voltages at each grid element, 'Er' 
    the permittivites and 'cell_type' is either FIXED or variable, 
    indicating a dielectric (VARIABLE) or a metal */

    /* If there are multiple dielectrics, the impedance calculations
    needs to be done twice. We start by doing them once, for an vacuum
    dielectric. If necessary, they will be done again */

    
    dielectrics_to_consider_just_now=1;

    if(coupler==FALSE)
      do_fd_calculation(&capacitance, &inductance, &Zo, &Zodd, &Zeven, Z0, \
      &velocity, &vf, stdout, cutoff, dielectrics_to_consider_just_now, \
      input_filename,REQUIRE_FD_CALCULATIONS);
    else if(coupler==TRUE)
    {
      /* ***************************************/
      /* Do odd mode, as it what must be drawn */
      do_fd_calculation(&capacitance, &inductance, &Zo, &Zodd, &Zeven, Z_ODD, \
      &velocity, &vf, stdout, cutoff, dielectrics_to_consider_just_now, \
      argv[my_optind],REQUIRE_FD_CALCULATIONS);

      /* Swap the negative voltages to positive, so the even mode can be
      done. */

      swap_conductor_voltages(NEG_TO_POS);

      /* Do the even mode calculation */
      do_fd_calculation(&capacitance, &inductance, &Zo, &Zodd, &Zeven, Z_ALL, \
      &velocity, &vf, stdout, cutoff, dielectrics_to_consider_just_now, \
      argv[my_optind],REQUIRE_FD_CALCULATIONS);

      //swap_conductor_voltages(POS_TO_NEG);
      /* ***************************************/
    } /* end of      else if(coupler==TRUE) */




    /* The calculation of inductance above is correct, and does not
    need to be altered. However, if there are multiple dielectrics,
    then the capacitance needs to be computed again, this time taking
    into account the different dielectrics. If it just a single
    dielectric (like on a coax cable), then there is no need to repeat
    a lenghty FD calculation, but just to scale C by the relative
    permittivity of the dielectric. */

    if(dielectrics_in_bitmap > 1) /* Only do if there is a mixed dielectric */
    {
      dielectrics_to_consider_just_now=dielectrics_in_bitmap;
      do_fd_calculation(&capacitance, &inductance, &Zo, &Zodd, &Zeven,Z0 , &velocity, &vf, stdout, cutoff, dielectrics_to_consider_just_now, argv[my_optind],REQUIRE_FD_CALCULATIONS);
    }
    /* Now we have findished all the time-consuming FD bits */

    /* If there is more than one dielectric, but it is not vacuum, then
    the original calculation of C assuming vacuum just needs scaling by
    the relative permittivity of the dielectric. Very easy to do 
    and there is *NO* need for any more finite difference calculations*/
    if((dielectrics_in_bitmap == 1) && (non_vacuum_found==TRUE))
    {
      capacitance*=found_this_dielectric;
      /* inductance is alreadly correct */
      Zo=sqrt(inductance/capacitance);
      velocity=1.0/pow(inductance*capacitance,0.5);
      c=1.0/(sqrt(MU_0 * EPSILON_0));
      vf=velocity/c;
      if(verbose)
      {
        print_data(stdout,argv[my_optind],found_this_dielectric,\
	capacitance,inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
        if(append_flag==TRUE)
        {
          appendfile_fp=fopen(appendfile,"a");
	  if(appendfile_fp==NULL)
	  {
	    fprintf(stderr,"Error #8. Can't open file for appending data in atlc.c\n");
	    exit(8);
          }
	  print_data(appendfile_fp,argv[my_optind],found_this_dielectric,\
	  capacitance,inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
          fclose(appendfile_fp);
        } /* end of        if(append_flag==TRUE) */
      } /* end of    if(verbose) */
    } /* end of checking for a single dielectric, that is not vacuum */
    if(dielectrics_in_bitmap > 1)
    {
      if(coupler==FALSE)
      {
        print_data(stdout,argv[my_optind],-1.0,capacitance,\
        inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
        print_data(resultfile_fp,argv[my_optind],-1.0,capacitance,\
        inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
      } /* if(coupler==FALSE) */
      else if (coupler==TRUE)
      {
	printf("pcb type coupler\n");
        print_data(stdout,argv[my_optind],-1.0,capacitance,inductance,Zo,Zodd,Zeven,Z_ALL,velocity,vf);
        print_data(resultfile_fp,argv[my_optind],-1.0,capacitance,inductance,Zo,Zodd,Zeven,Z_ALL,velocity,vf);
      } 
      if(append_flag==TRUE)
      {
        appendfile_fp=fopen(appendfile,"a");
        print_data(appendfile_fp,argv[my_optind],-1.0,capacitance,\
	inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
        fclose(appendfile_fp);
      }
    }
    else if((dielectrics_in_bitmap == 1) && (non_vacuum_found==TRUE))
    {
      print_data(stdout,argv[my_optind],found_this_dielectric,capacitance,\
      inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
      print_data(resultfile_fp,argv[my_optind],found_this_dielectric,\
      capacitance,inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
      if(append_flag==TRUE)
      {
        appendfile_fp=fopen(appendfile,"a");
        print_data(appendfile_fp,argv[my_optind],found_this_dielectric,\
        capacitance,inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
        fclose(appendfile_fp);
      }
    } /* end of     if((dielectrics_in_bitmap == 1) && (non_vacuum_found==TRUE)) */
    //else 
    else  if ((dielectrics_in_bitmap == 1) && (non_vacuum_found==FALSE))
    {
      if(coupler==FALSE)
      {
        /* one dielectric, vacuum, not a coupler */
         print_data(stdout,argv[my_optind],1.0,capacitance,inductance,\
         Zo,Zodd,Zeven,Z0,velocity,vf);

         print_data(resultfile_fp,argv[my_optind],1.0,capacitance,\
	 inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
      }
      else if(coupler==TRUE)
      {
        print_data(stdout,argv[my_optind],1.0,capacitance,inductance,\
	  Zo,Zodd,Zeven,Z_ALL,velocity,vf);

        print_data(resultfile_fp,argv[my_optind],1.0,capacitance,\
	  inductance,Zo,Zodd,Zeven,Z_ALL,velocity,vf);
      }
      if(append_flag==TRUE && coupler==FALSE)
      {
        appendfile_fp=fopen(appendfile,"a");
        print_data(appendfile_fp,argv[my_optind],1.0,capacitance,\
        inductance,Zo,Zodd,Zeven,Z0,velocity,vf);
        fclose(appendfile_fp);
      }
      else if(append_flag==TRUE && coupler==TRUE)
      {
        appendfile_fp=fopen(appendfile,"a");
        print_data(appendfile_fp,argv[my_optind],1.0,capacitance,\
	   inductance,Zo,Zodd,Zeven,Z_ALL,velocity,vf);
           fclose(appendfile_fp);
      }
    } /* end of ... else  if ((dielectrics_in_bitmap == 1) && (non_vacuum_found==FALSE)) */

    /* The function write_fields needs to have a file with the
    extension .bmp. We need to be sure this is the case, so if not, we
    append .bmp
      
    Currently the fields on couplers are not properly defined
    so I won't plot them. */
      
    if(write_field_images==TRUE && coupler==FALSE)
      write_fields(output_filename);
    free_dmatrix(Vij,0,width,0,height);
      free_dmatrix(Er,0,width,0,height);
    exit(0);
  }
  else
    usage_atlc();
  exit(5);
}
