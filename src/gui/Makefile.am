#This is atlc-x.y.z/src/gui/Makefile.am

bin_PROGRAMS = atlc

CPP_FILES = atlcApp.cpp atlcFrm.cpp RoundCoaxFrm.cpp CoaxFrm.cpp \
FiniteDifferenceFrame.cpp EccentricCoaxFrame.cpp 

HEADER_FILES = CoaxFrm.h EccentricCoaxFrame.h FiniteDifferenceFrame.h \
RoundCoaxFrm.h atlcApp.h atlcFrame.h atlcFrm.h resource.h

ICONS = atlc.xpm CircInRect.xpm EccentricCoax.xpm \
FiniteDifference.xpm RectInCirc.xpm RectInRect.xpm \
RoundCoax.xpm StriplineCoupler.xpm SymmetricalStripline.xpm \
SquareOuterRoundInner.xpm

atlc_SOURCES = $(CPP_FILES) $(HEADER_FILES) $(ICONS)

INCLUDES = @EXTRA_WXWINDOWS_CFLAGS@
atlc_LDADD =  @EXTRA_WXWINDOWS_LIBS@

EXTRA_DIST = README tips.txt
