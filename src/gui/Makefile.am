#This is atlc-x.y.z/src/gui/Makefile.am

bin_PROGRAMS = atlc

atlc_SOURCES = atlcApp.cpp atlcFrm.cpp RoundCoaxFrm.cpp CoaxFrm.cpp \
CoaxFrm.h RoundCoaxFrm.h atlcApp.h atlcFrm.h resource.h \
FiniteDifferenceFrame.cpp FiniteDifferenceFrame.h

INCLUDES = @EXTRA_WXWINDOWS_CFLAGS@
atlc_LDADD =  @EXTRA_WXWINDOWS_LIBS@

EXTRA_DIST = README tips.txt
