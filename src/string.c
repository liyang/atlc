#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

/* The authors of the book 'Numerical Recipes in C' were kind enough
to make the utility routines in the files 'nrutil.c' and 'nrutil.h'
public domain. Hence I can include both without any problems */


#define NR_END 1

#ifndef size_t         /* gcc needs this */
#define size_t int
#endif

char *string(long nl,long nh)
{
  char *v;

  //v=(char *)malloc((unsigned) (nh-nl+1));
  v=(char *)calloc(nh-nl+1,sizeof(unsigned));
  if (!v) nrerror("allocation failure in string()");
  return v-nl;
}

unsigned char *ustring(long nl,long nh)
{
  unsigned char *v;

  v=(unsigned char *)malloc((unsigned) (nh-nl+1));
  if (!v) nrerror("allocation failure in ustring()");
  return v-nl;
}

void free_string(char *v, long nl, long nh)
/* free a string allocated with string() */
{
  if(nh <= nl)
  {
    fprintf(stderr,"nh <= nl in call to free_string\n");
    exit(1);
  }
  free((FREE_ARG) (v+nl));
}

void free_ustring(unsigned char *v, long nl, long nh)
/* free a string allocated with ustring() */
{
  if(nh <= nl)
  {
    fprintf(stderr,"nh <= nl in call to free_ustring\n");
    exit(1);
  }
  free((FREE_ARG) (v+nl));
}
char **cmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a char matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	char **m;

	/* allocate pointers to rows */
	m=(char **) malloc((size_t)((nrow+NR_END)*sizeof(char*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(char)));
	if (!m[nrl]) nrerror("allocation failure 2 in cmatrix()");
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
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(unsigned char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(unsigned char)));
	if (!m[nrl]) nrerror("allocation failure 2 in cmatrix()");
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
  {
    fprintf(stderr,"nrh <= nrl in call to free_cmatrix\n");
    exit(1);
  }
  if(nch <= ncl)
  {
    fprintf(stderr,"nch <= ncl in call to free_cmatrix\n");
    exit(1);
  }
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}
