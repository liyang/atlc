#This is atlc-x.y.z/src/gui/Makefile.am

bin_PROGRAMS = atlc

CPP_FILES = atlcApp.cpp atlcFrm.cpp RoundCoaxFrm.cpp CoaxFrm.cpp \
FiniteDifferenceFrame.cpp EccentricCoaxFrame.cpp 

HEADER_FILES = EccentricCoaxFrame.h CoaxFrm.h FiniteDifferenceFrame.h \
RoundCoaxFrm.h atlcApp.h atlcFrm.h resource.h 

ICONS = atlc.xpm CircInRect.xpm EccentricCoax.xpm \
FiniteDifference.xpm RectInCirc.xpm RectInRect.xpm \
RoundCoax.xpm StriplineCoupler.xpm SymmetricalStripline.xpm 

atlc_SOURCES = $(CPPFILES) $(HEADER_FILES) $(ICONS)

INCLUDES = @EXTRA_WXWINDOWS_CFLAGS@
atlc_LDADD =  @EXTRA_WXWINDOWS_LIBS@

EXTRA_DIST = README tips.txt
