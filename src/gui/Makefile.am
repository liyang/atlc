#This is atlc-x.y.z/src/gui/Makefile.am

bin_PROGRAMS = atlc

CPP_FILES = atlcApp.cpp atlcFrm.cpp RoundCoaxFrm.cpp CoaxFrm.cpp \
FiniteDifferenceFrame.cpp EccentricCoaxFrame.cpp ExFieldFrame.cpp \
EyFieldFrame.cpp VoltageFrame.cpp PermittivityFrame.cpp \
EnergyFrame.cpp EFieldFrame.cpp 

HEADER_FILES = CoaxFrm.h EccentricCoaxFrame.h FiniteDifferenceFrame.h \
RoundCoaxFrm.h atlcApp.h atlcFrame.h atlcFrm.h resource.h \
ExFieldFrame.h EyFieldFrame.h EFieldFrame.h VoltageFrame.h \
PermittivityFrame.h  EnergyFrame.h

ICONS = atlc.xpm CircInRect.xpm EccentricCoax.xpm \
FiniteDifference.xpm RectInCirc.xpm RectInRect.xpm \
RoundCoax.xpm StriplineCoupler.xpm SymmetricalStripline.xpm \
SquareOuterRoundInner.xpm icon.Ex.xpm icon.Ey.xpm \
icon.E.xpm icon.U.xpm icon.V.xpm icon.Er.xpm

atlc_SOURCES = $(CPP_FILES) $(HEADER_FILES) $(ICONS)

INCLUDES = @EXTRA_WXWINDOWS_CFLAGS@
atlc_LDADD =  @EXTRA_WXWINDOWS_LIBS@

EXTRA_DIST = README tips.txt
