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

Some of these memory allocation routies are hacked versions of those
from the book 'Numerical Recipes in C' by Press et al. but if
the function memalign() is defined, which under Solaris at least 
void *memalign(size_t alignment, size_t size);
allocates size_t bytes on an alignment that must be a power of two. I
elected to align these since memory access should be faster */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

#define NR_END 1

#ifndef size_t         /* gcc needs this */
#define size_t int
#endif


char *string(long nl,long nh)
{
  char *v;

  //v=(char *)malloc((unsigned) (nh-nl+1));
#ifdef HAVE_MEMALIGN
  v=(char *)memalign((size_t) sizeof(long), sizeof(char)*(nh-nl+1));
#else 
  v=(char *)malloc((unsigned) (nh-nl+1));
#endif
  if (!v)
    error_and_exit("Memory allocation failure in string()",MEMORY_ALLOCATION_ERROR_IN_STRING);
  
  return v-nl;
}

unsigned char *ustring(long nl,long nh)
{
  unsigned char *v;

#ifdef HAVE_MEMALIGN
  v=(unsigned char *)memalign((size_t) sizeof(long), (size_t) sizeof(char)*(nh-nl+1));
#else
  v=(unsigned char *)malloc((size_t) sizeof(unsigned char)* (nh-nl+1));
#endif

  if (!v) 
    error_and_exit("Memory allocation failure in ustring()",MEMORY_ALLOCATION_ERROR_IN_USTRING);
  return v-nl;
}

void free_string(char *v, long nl, long nh)
/* free a string allocated with string() */
{
  if(nh <= nl)
    error_and_exit("nh <= nl in free_string()",SILLY_ARGUMENTS_IN_FREE_STRING);
  free((FREE_ARG) (v+nl));
}

void free_ustring(unsigned char *v, long nl, long nh)
/* free a string allocated with ustring() */
{
  if(nh <= nl)
    error_and_exit("nh <= nl in free_ustring()",SILLY_ARGUMENTS_IN_FREE_USTRING);
  free((FREE_ARG) (v+nl));
}

char **cmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a char matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	char **m;

	/* allocate pointers to rows */
	m=(char **) malloc((size_t)((nrow+NR_END)*sizeof(char*)));
	if (!m) 
          error_and_exit("Memory allocation failure #1 in cmatrix()",MEMORY_ALLOCATION_ERROR_IN_CMATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(char)));
	if (!m[nrl])
	  error_and_exit("Memory allocation failure #2 in cmatrix()",MEMORY_ALLOCATION_ERROR_IN_CMATRIX);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}


unsigned char **ucmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a unsigned char matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	unsigned char **m;
	/* allocate pointers to rows */
	m=(unsigned char **) malloc((size_t)((nrow+NR_END)*sizeof(unsigned char*)));
	if (!m) 
	  error_and_exit("Memory allocation failure #1 in ucmatrix()",MEMORY_ALLOCATION_ERROR_IN_UCMATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(unsigned char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(unsigned char)));
	if (!m[nrl]) 
	  error_and_exit("Memory allocation failure #2 in ucmatrix()",MEMORY_ALLOCATION_ERROR_IN_UCMATRIX);

	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

void free_cmatrix(char **m, long nrl, long nrh, long ncl, long nch)
/* free a char matrix allocated by cmatrix() */
{
  if(nrh <= nrl)
      error_and_exit("nrh <= nrl in free_cmatrix()",SILLY_ARGUMENTS_IN_FREE_CMATRIX);
  if(nch <= ncl)
      error_and_exit("nch <= ncl in free_cmatrix()",SILLY_ARGUMENTS_IN_FREE_CMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
	float *v;

	v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
	if (!v)
	  error_and_exit("Memory allocation in vector()",MEMORY_ALLOCATION_ERROR_IN_VECTOR);
	return v-nl+NR_END;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
	int *v;

	v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
	if (!v) 
	  error_and_exit("Memory allocation error in vector()",MEMORY_ALLOCATION_ERROR_IN_IVECTOR);
	return v-nl+NR_END;
}

unsigned char *cvector(long nl, long nh)
/* allocate an unsigned char vector with subscript range v[nl..nh] */
{
	unsigned char *v;

	v=(unsigned char *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(unsigned char)));
	if (!v)
	  error_and_exit("Memory allocation error in cvector()",MEMORY_ALLOCATION_ERROR_IN_CVECTOR);
	return v-nl+NR_END;
}

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
	double *v;
	v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
	if (!v)
	  error_and_exit("Memory allocation error in dvector()",MEMORY_ALLOCATION_ERROR_IN_DVECTOR);
	return v-nl+NR_END;
}

float **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;

	/* allocate pointers to rows */
#ifdef HAVE_MEMALIGN
	m=(float **) memalign((size_t) sizeof(long),(size_t)((nrow+NR_END)*sizeof(float*)));
#else
	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
#endif
	if (!m) 
	  error_and_exit("Memory allocation error #1 in matrix()",MEMORY_ALLOCATION_ERROR_IN_MATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
#ifdef HAVE_MEMALIGN
	m[nrl]=(float *) memalign((size_t) sizeof(long),(size_t)((nrow*ncol+NR_END)*sizeof(float)));
#else
	m[nrl]=(float *) malloc((size_t) ((nrow*ncol+NR_END)*sizeof(float)));
#endif
	if (!m[nrl]) 
	  error_and_exit("Memory allocation error #2 in matrix()",MEMORY_ALLOCATION_ERROR_IN_MATRIX);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;

	/* allocate pointers to rows */
#ifdef HAVE_MEMALIGN
	m=(double **) memalign((size_t) sizeof(long),(size_t)((nrow+NR_END)*sizeof(double*)));
#else
	m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
#endif
	if (!m) 
	  error_and_exit("Memory allocation error #1 in dmatrix()",MEMORY_ALLOCATION_ERROR_IN_DMATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
#ifdef HAVE_MEMALIGN
	m[nrl]=(double *) memalign((size_t) sizeof(long),(size_t)((nrow*ncol+NR_END)*sizeof(double)));
#else
	m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
#endif
	if (!m[nrl]) 
	  error_and_exit("Memory allocation error #2 in dmatrix()",MEMORY_ALLOCATION_ERROR_IN_DMATRIX);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	int **m;

	/* allocate pointers to rows */
	m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if (!m) 
	  error_and_exit("Memory allocation error #1 in imatrix()",MEMORY_ALLOCATION_ERROR_IN_IMATRIX);
	m += NR_END;
	m -= nrl;


	/* allocate rows and set pointers to them */
	m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
	if (!m[nrl]) 
	  error_and_exit("Memory allocation error #2 in imatrix()",MEMORY_ALLOCATION_ERROR_IN_IMATRIX);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

void free_vector(float *v, long nl, long nh)
/* free a float vector allocated with vector() */
{
  if(nh <= nl)
    error_and_exit("nh is <= nl in call to free_vector",SILLY_ARGUMENTS_IN_FREE_VECTOR);
  free((FREE_ARG) (v+nl-NR_END));
}

void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{
  if(nh <= nl)
    error_and_exit("nh is <= nl in call to free_ivector",SILLY_ARGUMENTS_IN_FREE_IVECTOR);
  free((FREE_ARG) (v+nl-NR_END));
}

void free_cvector(unsigned char *v, long nl, long nh)
/* free an unsigned char vector allocated with cvector() */
{
  if(nh <= nl)
    error_and_exit("nh is <= nl in call to free_cvector",SILLY_ARGUMENTS_IN_FREE_CVECTOR);
  free((FREE_ARG) (v+nl-NR_END));
}


void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{
  if(nh <= nl)
    error_and_exit("nh is <= nl in call to free_dvector",SILLY_ARGUMENTS_IN_FREE_DVECTOR);
  free((FREE_ARG) (v+nl-NR_END));
}

void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by dmatrix() */
{
  if(nrh <= nrl)
    error_and_exit("nhh is <= nl in call to free_dmatrix",SILLY_ARGUMENTS_IN_FREE_DMATRIX);
  if(nch <= ncl)
    error_and_exit("nch is <= nl in call to free_dmatrix",SILLY_ARGUMENTS_IN_FREE_DMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_cx(char **m, long nrl, long nrh, long ncl, long nch)
/* free a char matrix allocated by cmatrix() */
{
  if(nrh <= nrl)
    error_and_exit("nrh is <= nrl in call to free_charmatrix",SILLY_ARGUMENTS_IN_FREE_CMATRIX);
  if(nch <= ncl)
    error_and_exit("nch is <= ncl in call to free_charmatrix",SILLY_ARGUMENTS_IN_FREE_CMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
/* free an int matrix allocated by imatrix() */
{
  if(nrh <= nrl)
    error_and_exit("nrh is <= nrl in call to free_imatrix",SILLY_ARGUMENTS_IN_FREE_IMATRIX);
  if(nch <= ncl)
    error_and_exit("nch is <= ncl in call to free_imatrix",SILLY_ARGUMENTS_IN_FREE_IMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}
