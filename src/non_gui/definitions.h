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

#ifdef HAVE_MATH_H
#include <math.h>
#endif 

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#define EXIT_READ_FAILURE

#define       FREE_ARG char*
#define       NR_END 1

#define    CONDUCTOR_FLOATING          -3000
#define    CONDUCTOR_ZERO_V            -1000 
#define    CONDUCTOR_PLUS_ONE_V         -999 
#define    CONDUCTOR_MINUS_ONE_V       -1001 
#define    DIELECTRIC                      0 
#define    DIFFERENT_DIELECTRIC_NEARBY     1
#define    METAL_LEFT                      2
#define    METAL_RIGHT                     4
#define    METAL_BELOW                     8
#define    METAL_ABOVE                    16

/* The following two determine what happens when a coupler is present
and the voltages have to be swapped from negative to positive in the
simulation. */

#define POS_TO_NEG                         1
#define NEG_TO_POS                         -1
#define METAL_ER  1e9

#define ZERO_ELEMENTS_FIRST 0       

#ifndef TRUE 
#define TRUE 1
#define FALSE 0
#endif

#define DONT_CARE                          0
#define ODD                                1
#define EVEN                               2

#define MAX_DIFFERENT_PERMITTIVITIES   10000
#define MAX_ER 12

#define COLOUR 0
#define MONOCHROME 1
#define MIXED      2
#define Z0                              1

#define Z_ODD_SINGLE_DIELECTRIC         1
#define Z_EVEN_SINGLE_DIELECTRIC        2
#define Z_ODD_MULTIPLE_DIELECTRIC       3
#define Z_EVEN_MULTIPLE_DIELECTRIC      4

#define Z_ALL                       5

/* The value of EPSILON_0 is taken from the UK National Physical
Laboratory's list of physical constants found on the web. */

#define EPSILON_0 8.854187817e-12
#define MU_0 M_PI*4e-7
#define MAX_THREADS  4
#define BORDER   5 /* The border to put around images. 1 is minimum, but 5 looks better */

#define TINY 1e-12
#define VERY_LARGE 1e15
#define DEFAULT_BMPSIZE 6
#define DEFAULT_COUPLER_BITMAP_SIZE 18

#define IMAGE_FIDDLE_FACTOR 2.0
#define ACCEPTABLE_ERROR 0.02
#define UNACCEPTABLE_ERROR 0.05

#define RECT_IN_RECT 1
#define CIRC_IN_CIRC 2
#define CIRC_IN_RECT 3
#define RECT_IN_CIRC 4

#define DEFAULT_GMIN 0.5
#define DEFAULT_GMAX 5.0
#define DEFAULT_GSTEP 0.5

#define DEFAULT_SMIN 0.5
#define DEFAULT_SMAX 5.0
#define DEFAULT_SSTEP 0.5

#define DEFAULT_WMIN 0.5
#define DEFAULT_WMAX 5.0
#define DEFAULT_WSTEP 0.5


#ifdef ENABLE_MPI
#define MAX_PES 256
#define MSG_TAG_WIDTH_HEIGHT 1
#define MSG_TAG_STRIP_PARAMS 2
#define MSG_TAG_CELL_TYPE    3
#define MSG_TAG_ER           4
#define MSG_TAG_CONTROL      5
#define MSG_TAG_ITERATIONS   6
#define MSG_TAG_VIJ          7
#define MSG_TAG_VIJ_LBORDER  8
#define MSG_TAG_VIJ_RBORDER  9
#define MSG_TAG_ENERGY      10
#define MSG_TAG_DIELECTRICS 11

#define CONTROL_VALUE_RECEIVE_DATA     0
#define CONTROL_VALUE_SEND_DATA        1
#define CONTROL_VALUE_DO_ITERATIONS    2
#define CONTROL_VALUE_EXIT             3
#endif /* ENABLE_MPI */


extern char *my_optarg;
/* I needed to invent add my_ in front of the usual name for optind,
opterr, optopt etc, since they are defined by the system, and I'm using
a local package_version of getopts (get_options) so it exists with the PC too.
Most systems do not seem to mind if these names exist or not, but a
Power Machintosh powerpc running Darwin Kernel Package_version 5.3 gave this as
a warning. Hence I'll avoid the problem by adding my_ */

extern int my_optind, my_opterr, my_optopt;

struct transmission_line_properties{
double WW, HH, ww, ss, gg, hh, tt, Er1, Er2;
int  W, H, w, s, g, h, t, bmp_size;
int verbose_level; /* 0, 1 or 2 */
double Codd, Ceven, C;
double velocity_odd, velocity_factor_odd, relative_permittivity_odd;
double velocity_even, velocity_factor_even, relative_permittivity_even;
double Lodd_vacuum, Leven_vacuum, L_vacuum;
double Codd_vacuum, Ceven_vacuum, C_vacuum, C_non_vacuum;
double Zo, Zo_vacuum, Zo_non_vacuum, Zodd, Zodd_vacuum, Zeven;
double Zeven_vacuum, Zdiff, Zdiff_vacuum, Zcomm, Zcomm_vacuum;
double Er, the_single_Er, Er_odd, Er_even;
double velocity, velocity_factor, relative_permittivity;
double r; /* rate multiplier */
double image_fiddle_factor;
double cutoff; /* How small the error in subsequent itterations must be */
int compute, display; /* none, ZO, ZODD, ZEVEN. ZEVEN_VAC, ZODD_VAC; */
int should_binary_data_be_written_tooQ;
int dielectrics_to_consider_just_now;
int non_vacuum_dielectric_found;
double found_this_dielectric;
int dielectrics_on_command_line;
int dielectrics_in_bitmap;
int avoid_use_of_fast_convergence_methodQ;
int couplerQ;
int write_binary_field_imagesQ;
int write_bitmap_field_imagesQ;
double float_values[10];
int int_values[10];
int importance[10];
int odd_or_even[10];
int best[10];
int non_metallic_pixels;
int tenth_of_estimated_iterations_needed;
};

#define NOT_IMPORTANT 0   /* The importance to attach to getting the */
#define IMPORTANT 1       /* best value of integers for the grid */
#define MOST_IMPORTANT 2

struct pixels
{
   int red;          /* +1 V */
   int green;        /* 0 V */
   int blue;         /* -1 V */
   int white;        /* Vacuum */
   int other_colour;  /* mix of red, green and blue  */
   double epsilon;
};

struct max_values
{
double Ex_or_Ey_max, E_max, V_max, U_max, permittivity_max;
};


struct fit_doubles_to_integers{
int n_min, n_max, n;
int m, *in;
double *out, good, acceptable;
double largest_errror;
double rms_errror;
};

#ifdef ENABLE_MPI
struct strip {
  int start_col;
  int num_cols;
};
#endif /* ENABLE_MPI */

/* The following code has been revised, since it was bought to my
attention by Dan (mcmahill@mtl.mit.edu) that the code was broken for
64-bit processors, where long is 8 bytes. Hence the following defines
these parameters

int32 - 32 bits or 4 bytes long
int64 - 64 bits or 8 bytes long

I'm not sure why the Kerningham and Richie did not use such a schmeme
rather than short, int and long, but anyway, this is my attempt to avoid
the problem. */

#if SIZEOF_INT==4 
#define int32 int 
#elif SIZEOF_LONG==4
#define int32 long
#endif

struct Bitmap_File_Head_Struct
{
  char   zzMagic[2];	/* 00 "BM" */
  int32   bfSize;      /* 02 */
  short  zzHotX;	/* 06 */
  short  zzHotY;	/* 08 */
  int32   bfOffs;      /* 0A */
  int32   biSize;      /* 0E */
};

struct Bitmap_Head_Struct
{
  int32   biWidth;     /* 12 */
  int32   biHeight;    /* 16 */
  short  biPlanes;    /* 1A */
  short  biBitCnt;    /* 1C */
  int32   biCompr;     /* 1E */
  int32   biSizeIm;    /* 22 */
  int32   biXPels;     /* 26 */
  int32   biYPels;     /* 2A */
  int32   biClrUsed;   /* 2E */
  int32   biClrImp;    /* 32 */
                        /* 36 */
};

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884197169399375105820975
#endif

#define NUMBER_OF_DIELECTRICS_DEFINED 13

int main(int argc, char **argv);
void byteswap_doubles(double *a);
void byteswap_ints(int *a);
void byteswap_shortss(short *a);
void read_bitmap_file_headers(char *filename, int *offset, size_t *size, int *width, int *height);
void get_data_interactively(void);
void help(char *filename);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void nrerror(char *error_text);
char *string(long nl,long nh);
void free_string(char *v, long nl, long nh);
unsigned char *ustring(long nl,long nh);
void swap_bytes2(unsigned char *buffer, int offset, short *answer);
void swap_bytes4(unsigned char *buffer, int offset, int *answer);
void free_ustring(unsigned char *v, long nl, long nh);
int **imatrix(long nrl, long nrh, long ncl, long nch);
void setup_arrays(struct transmission_line_properties *data);
double finite_difference(int iterations);
#ifdef ENABLE_MPI
void do_columns(int start_col, int num_cols, int calculate_edges);
void mpi_worker(int rank);
#else
void *do_columns(void *thread_arg);
#endif /* ENABLE_MPI */
void usage_atlc(void);
void write_fields_for_two_conductor_lines(char *filename, struct transmission_line_properties data);
void write_fields_for_directional_couplers(char *filename, struct transmission_line_properties data, int odd_or_even);
char **cmatrix(long nrl, long nrh, long ncl, long nch);
unsigned char **ucmatrix(long nrl, long nrh, long ncl, long nch);
int *ivector(long nl, long nh);
void get_Er1_and_Er2_colours(int *colour_Er1, int *colour_Er2);
int convert_create_bmp_for_rect_in_rect_dimensions_to_integers(int bmp_size);
int convert_create_bmp_for_circ_in_circ_dimensions_to_integers(int bmp_size);
unsigned char *ustring(long nl,long nh);
void write_bitmap(FILE *image_data_fp, struct transmission_line_properties foo);
void usage_create_bmp_for_rect_in_rect(void);
void usage_create_bmp_for_rect_cen_in_rect(void);
void write_bitmap_out(unsigned char *image_data, FILE *image_data_fp,int image_size, int W, int H);
void byteswap_ints( int *a);
void byteswap_longs( long *a);
void byteswap_shorts( short *a);
int align_bitmap_image(int W, int H, unsigned char *unaligned_image, unsigned char *byte_aligned_image);
void fill_create_bmp_for_rect_in_rect(char *image_vector, int colour_Er1, int colour_Er2);
void check_create_bmp_for_rect_in_rect_ints(void);
//void check_create_bmp_for_rect_in_rect_doubles(void);
void error_and_exit(char error_text[], int exitnumber);
void check_error(double user, int create_bmp_for_rect_in_rect, double gridsize, char
*name);
//void check_create_bmp_for_rect_in_rect_doubles(void);
void error_and_exit(char error_text[], int exitnumber);
void check_error(double user, int create_bmp_for_rect_in_rect, double gridsize, char *name);
void check_parameters_for_create_bmp_for_circ_in_circ(void);
void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2, struct transmission_line_properties x);
void usage_create_bmp_for_circ_in_circ(void);
int convert_create_bmp_for_rect_in_circ_dimensions_to_integers(int accuracy_level);
void usage_create_bmp_for_rect_in_circ(void);
int convert_create_bmp_for_circ_in_rect_dimensions_to_integers(int accuracy_level);
void usage_create_bmp_for_circ_in_rect(void);
void check_for_shorts(void);
void usage_symmetrical_strip(void);
void fill_image_vector_for_thin_strip(int W,int H, int w, unsigned char *unaligned_image_vector);
double K_over_Kdash(double k);
double calculate_symmetrical_stripline_impedance(int H, int w);
char **charmatrix(long nrl, long nrh, long ncl, long nch);
void free_charmatrix(char **m, long nrl, long nrh, long ncl, long nch);
int print_data(FILE *fp, char *filename, double Er, double C, double L, double Zo, double
Zodd, double Zeven, int whichZ, double v, double vf);
void check_for_boundaries(void);
double find_energy_per_metre(int i, int j);
void update_voltage_array(int i, int calculate_edges);
FILE *get_file_pointer_with_right_filename(char *filename, char *ext);
void find_maximum_values(struct max_values *maximum_values, int zero_elementsQ);
void calculate_colour_data(double x, double xmax, int w, int h, int offset, unsigned char *image_dat, char image_type);
double find_Ex(int w, int h) ;
double find_Ey(int w, int h);
double find_E(int w, int h);
double voltage_ij(int i, int j);
int get_options(int argc, char **argv, char *opts);
void usage_readbin(void);
void ERR(char *s, char c, char **argv);
char *index2(char *str, char c);
void swap_conductor_voltages(int way_to_swap);
void usage_create_bmp_for_stripline_coupler(void);
double calculate_integer_values(struct transmission_line_properties *optimise, int n, int accuarcy_level);
void calculate_Zodd_and_Zeven(double *Zodd, double *Zeven, double *Zo, double w, double H, double s, double er);
void usage_design_coupler(void);
void print_copyright(char *s);
void give_examples_of_using_design_coupler(void);
void *do_fd_calculation(struct transmission_line_properties *data, FILE *where_to_print_fp, char *inputfile_filename);
int print_data_for_directional_couplers(struct transmission_line_properties data, FILE *where_to_print_fp, char *inputfile_name);
int print_data_for_two_conductor_lines(struct transmission_line_properties data, FILE *where_to_print_fp, char *inputfile_name);
void set_data_to_sensible_starting_values(struct transmission_line_properties *data);
void check_parameters_of_create_bmp_for_microstrip_coupler(struct transmission_line_properties pcb);
void convert_create_create_bmp_for_coupled_microstrip_dimensions_to_integers(struct transmission_line_properties *pcb);
void usage_create_bmp_for_microstrip_coupler(void);
void usage_find_optimal_dimensions_for_microstrip_coupler();
void check_parameters_of_create_bmp_for_circ_in_circ();
void check_parameters_of_create_bmp_for_circ_in_rect();
void check_parameters_of_create_bmp_for_rect_in_circ();
void check_parameters_of_create_bmp_for_rect_in_rect(void);
void usage_create_bmp_for_symmetrical_stripline(void);
