dnl Process this file with autoconf to produce a configure script.

dnl Order of itmes is suggested in the autoconf documentation to be that
dnl below, to be as below. Let's try to stick to it.

dnl AC_INIT(file)
dnl checks for programs
dnl checks for libraries
dnl checks for header files
dnl checks for typedefs
dnl checks for structures
dnl checks for compiler characteristics
dnl checks for library functions
dnl checks for system services
dnl AC_OUTPUT([file...])

AC_INIT(atlc, 4.2.11, drkirkby@ntlworld.com)
AM_INIT_AUTOMAKE(atlc, 4.2.11, drkirkby@ntlworld.com)

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_RANLIB
AC_ISC_POSIX

dnl AC_OUTPUT_COMMANDS([exit])

dnl Checks for libraries.
AC_CHECK_LIB(m,main)
AC_CHECK_LIB(c,memalign, AC_DEFINE(HAVE_MEMALIGN))

dnl check for optimised math library on SPARC
dnl AC_CHECK_LIB(mopt,main)
dnl check for the optimised
dnl AC_CHECK_LIB(copt,main)

dnl Checks for header files.

dnl AC_STDC_HEADERS
AC_HAVE_HEADERS(stdio.h math.h errno.h stdlib.h string.h)

dnl checks for typedefs (none need to be tested)

dnl checks for structures (none need to be tested)

dnl checks for compiler characteristics
AC_C_BIGENDIAN
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(size_t)


dnl checks for system services

dnl Check if the user wants a GUI. If so makes sure GTK and wxWindows are around.
dnl The macro is in the file gtk.m4, so it must be read it here. 
sinclude(gtk.m4)
AC_ARG_WITH(gui, AC_HELP_STRING([--with-gui=[no]],[Add a GUI (needs GTK >= 1.2.7 installed) but the GUI does not work!! ]))
if test "x$with_gui" = "xyes"; then
        AC_PATH_GTK(1.2.7, GTK127=1)
        if test "$GTK127" != 1; then
            AC_MSG_ERROR([
                Please check that gtk-config is in path, the directory
                where GTK+ libraries are installed (returned by
                'gtk-config --libs' command) is in LD_LIBRARY_PATH or
                equivalent variable and GTK+ is version 1.2.7 or above.
            ])
        fi
	AC_CHECK_PROG(WXWINDOWS,wx-config, 1, 0)   
        if test "$WXWINDOWS" != 1; then
            AC_MSG_ERROR([
	       wxWindows must be installed to use the GUI version of atlc
        ])
        fi
        AC_SUBST(EXTRA_WXWINDOWS_LIBS,`wx-config --libs`)
        AC_SUBST(EXTRA_WXWINDOWS_CFLAGS,`wx-config --cflags`)
        AC_SUBST(GUI_DIRECTORY,gui)
fi


AC_ARG_WITH(gsl=yes,[  --without-gsl           disable use of gsl library (by default it's enabled)])
if test "x$with_gsl" = "xno"; then
AC_MSG_WARN([Use of the gsl library has been disabled - some self-tests will fail])
else
AC_CHECK_LIB(gslcblas,main)
AC_CHECK_LIB(gsl,main,,AC_MSG_WARN([To get full functionality you should link atlc with the GNU Scientific Library (gsl)
available at http://sources.redhat.com/gsl. Some self-tests will fail without gsl.]))
fi  
dnl Multi-Processor Support
sinclude(acx_pthread.m4)
AC_ARG_WITH(threads, 
[  --with-threads          support thread-based parallel computation - this 
                          needs a POSIX thread library (pthreads or similar) 
                          installed])

if test "x$with_threads" = "xyes"; then
ACX_PTHREAD([AC_DEFINE(ENABLE_POSIX_THREADS)])
LIBS="$PTHREAD_LIBS $LIBS"
CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
CC="$PTHREAD_CC"
fi

dnl MPI and MPE Support
AC_ARG_WITH(mpi, AC_HELP_STRING([--with-mpi=[mpi_install_prefix]],[support MPI-based parallel computation (needs MPICH installed)]))
AC_ARG_WITH(mpe, AC_HELP_STRING([--with-mpe=[mpi_install_prefix]],[implies --with-mpi and additionally links in MPE logging support]))

if test "x$with_mpi" != "x" \
|| test "x$with_mpe" != "x"; then

  if test "x$with_mp" = "xyes"; then
    AC_MSG_ERROR([it does not make sense to use --with-mp with --with-mpi or --with-mpe])
  fi  
  AC_HAVE_HEADERS(mpi.h)
  AC_DEFINE(ENABLE_MPI)
  AC_CHECK_LIB(socket, getsockopt)
  AC_CHECK_LIB(nsl, xdr_void)
  AC_CHECK_LIB(rt, sched_yield)
  if test "x$with_mpe" != "x"; then 
    if test "x$with_mpe" = "xyes"; then
	path_to_mpe=/usr/local
    else
	path_to_mpe=$with_mpe
    fi	
    CFLAGS="$CFLAGS -I$path_to_mpe/include -L$path_to_mpe/lib"
    AC_CHECK_LIB(pmpich,  MPI_Init , , [AC_MSG_ERROR([Could not link test program with libpmpich.a])])
    AC_CHECK_LIB(mpe,  MPE_Init_log , , [AC_MSG_ERROR([Could not link test program with libmpe.a])])
    AC_CHECK_LIB(lmpe,  MPE_Init_log , ,[AC_MSG_ERROR([Could not link test program with liblmpe.a])] , -lmpe)
  else
    if test "x$with_mpi" = "xyes"; then
	path_to_mpi=/usr/local
    else
	path_to_mpi=$with_mpi
    fi	
    CFLAGS="$CFLAGS -I$path_to_mpi/include -L$path_to_mpi/lib"
    AC_CHECK_LIB(mpich,  MPI_Init, , [AC_MSG_ERROR([Could not link test program with libmpich.a])])
  fi
fi
AC_OUTPUT([\
Makefile                                        \
src/Makefile                                    \
src/non_gui/Makefile                            \
src/gui/Makefile                                \
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
