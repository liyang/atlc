# Process this file with autoconf to produce a configure script.

# Order of itmes is suggested in the autoconf documentation to be that
# below, to be as below. Let's try to stick to it.

# checks for programs
# checks for libraries
# checks for header files
# checks for typedefs
# checks for structures
# checks for compiler characteristics
# checks for library functions
# checks for system services
# AC_OUTPUT([file...])

AC_INIT([atlc], [4.3.1], [drkirkby@ntlworld.com])
AM_INIT_AUTOMAKE
AC_PREREQ([2.57])
AC_CONFIG_SRCDIR([tools/src/myfilelength.c])
# defining a config.h might be useful as it can prevent a command line becoming
# too long, but I find it more of a pain than it is useful. To 
# make use of it, it would be necessary to hack every source file to 
# include it. I can't be bother yet. 
# AC_CONFIG_HEADER([config.h])


# Checks for programs.
#AC_PROG_CXX # Test for C++ compiler characteristics
AC_ISC_POSIX

# AC_OUTPUT_COMMANDS([exit])

# Checks for libraries.
# check for optimised math library on SPARC
# AC_CHECK_LIB([mopt],[main])
# check for the optimised
# AC_CHECK_LIB([copt],[main])
#AC_CHECK_LIB(m,log)

# Checks for header files.

AC_CHECK_HEADERS([stdio.h math.h malloc.h stdlib.h string.h time.h ])
AC_CHECK_HEADERS([strings.h sys/types.h machine/hal_sysinfo.h sys/sysinfo.h ])
AC_CHECK_HEADERS([sys/processor.h sched.h ])

# Checks for typedefs
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# checks for structures (none need to be tested)

# checks for compiler characteristics
AC_C_BIGENDIAN
AC_CHECK_SIZEOF([int])
AC_CHECK_SIZEOF([long])
AC_CHECK_SIZEOF([size_t])

# checks for library functions
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memset strchr strtol processor_info getsysinfo pthread_num_processors_np ])
#AC_CHECK_FUNCS([memset pow sqrt strchr strtol])

# checks for system services

# Check if the user wants a GUI. If so makes sure GTK and wxWindows are around.
# The macro is in the file gtk.m4 in the 'm4' subdirectory.

#AC_ARG_WITH(gui, AC_HELP_STRING([--with-gui=[no]],[Add a GUI (needs GTK >= 1.2.7 installed) but the GUI does not work!! ]))
#if test "x$with_gui" = "xyes"; then
#        AC_PATH_GTK(1.2.7, GTK127=1)
#        if test "$GTK127" != 1; then
#            AC_MSG_ERROR([
#                Please check that gtk-config is in path, the directory
#                where GTK+ libraries are installed (returned by
#                'gtk-config --libs' command) is in LD_LIBRARY_PATH or
#                equivalent variable and GTK+ is version 1.2.7 or above.
#            ])
#        fi
#	AC_CHECK_PROG(WXWINDOWS,wx-config, 1, 0)   
#        if test "$WXWINDOWS" != 1; then
#            AC_MSG_ERROR([
#	       wxWindows must be installed to use the GUI version of atlc
#        ])
#        fi
#        AC_SUBST(EXTRA_WXWINDOWS_LIBS,`wx-config --libs`)
#        AC_SUBST(EXTRA_WXWINDOWS_CFLAGS,`wx-config --cflags`)
#        AC_SUBST(GUI_DIRECTORY,gui)
#fi

# First give the user the chance to disable the gsl library. This
# was handy to do when configured with --with-mpi and it kept
# being unable to find the library. 
AC_ARG_WITH([gsl],
     AC_HELP_STRING([--with-gsl], [use gsl library (default is YES)]),
     [ac_cv_use_gsl=$withval], [ac_cv_use_gsl=yes])

AC_SUBST(no_gsl,"yes")
# If the user has not chosen to disable gsl support, then check for 
# gsl support and see that it exists. 
# Check for the gsl library, using gsl.m4, supplied with gsl-1.3
if test "$ac_cv_use_gsl" = "yes"; then
  AM_PATH_GSL([0.8])
  # no_gsl gets defined in gsl.m4 if version is too old. 
  if test "x$no_gsl" != "xyes" ; then
    AC_DEFINE( [HAVE_LIBGSL],[1],[gsl library found])
    #LIBS="$GSL_LIBS $LIBS"
    #CFLAGS="$GSL_CFLAGS $CFLAGS"
  fi
fi

# Put a usage message so the user can use threads if wanted. 
AC_ARG_WITH(threads,
		   AC_HELP_STRING([--with-threads],
		   [support thread-based parallel computation, using a POSIX thread library (default is NO)]))

# Multi-Processor Support checked with the macro m4/acx_pthread.m4
if test "x$with_threads" = "xyes"; then
  ACX_PTHREAD([AC_DEFINE([ENABLE_POSIX_THREADS],[1],[Enabling POSIX thread support]) ])
  LIBS="$PTHREAD_LIBS $LIBS"
  CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
  CC="$PTHREAD_CC"
  # if possible for a number of threads to run at once. 
  AC_CHECK_FUNC([pthread_setconcurrency],AC_DEFINE([HAVE_PTHREAD_SETCONCURRENCY]))
  AC_SUBST(built_with_posix_threads,yes)
fi

# MPI and MPE Support
AC_ARG_WITH(mpi, AC_HELP_STRING([--with-mpi=[mpi_install_prefix]],[support MPI-based parallel computation (needs MPICH installed)]))
AC_ARG_WITH(mpe, AC_HELP_STRING([--with-mpe=[mpi_install_prefix]],[implies --with-mpi and additionally links in MPE logging support]))
 
 if test "x$with_mpi" != "x" \
 || test "x$with_mpe" != "x"; then

  if test "x$with_threads" = "xyes"; then
     AC_MSG_ERROR([it does not make sense to use --with-threads with --with-mpi or --with-mpe])
  fi  
  ACX_MPI(    [AC_DEFINE([ENABLE_MPI],[1],[Enable the use of MPICH library]) ] ,[],[AC_MSG_ERROR([Could not determine how to link MPI program])])
  CC="$MPICC"
  if test "x$with_mpe" = "xyes" ; then
    LIBS="$MPILIBS -lmpe $LIBS"
  else
    LIBS="$MPILIBS $LIBS"
  fi
  #AC_CHECK_PROG(mpirun,mpirun,yes,no,$PATH)
  #if test "x$mpirun" = "xyes"; then
  #  AC_MSG_NOTICE([Don't forget, 'mpirun' MUST be used to call atlc. Don't run atlc directly!!])
  #else
  #  AC_MSG_WARN([The program 'mpirun' needed to run atlc, can't be found])
  #fi
fi

#if test "x$with_mpi" != "x"  || test "x$with_mpe" != "x"; then
# If there is no gsl, no mpe and no mpi, then we must have -lm
#if test  "x$with_mpi"  = "x"  && test "x$with_mpe"  = "x" && test "x$no_gsl" = "xyes" ; then

if test "x$no_gsl" = "xyes" ; then
  LIBS="$LIBS -lm"
fi

dnl Only use -Wall if we have gcc
if test "x$GCC" = "xyes"; then
  if test -z "`echo "$CFLAGS" | grep "\-Wall" 2> /dev/null`" ; then
      CFLAGS="$CFLAGS -Wall"
  fi
fi

AC_OUTPUT([\
Makefile                                        \
src/Makefile                                    \
src/non_gui/Makefile                            \
m4/Makefile                                     \
man/Makefile                                    \
man/man1/Makefile                               \
examples/Makefile                               \
tools/Makefile                                  \
tools/src/Makefile                              \
tests/Makefile                                  \
docs/html-docs/Makefile                         \
docs/html-docs/jpgs/Makefile                    \
docs/qex-december-1996/Makefile                 \
docs/theory/Makefile                            \
docs/Makefile                                   ])
