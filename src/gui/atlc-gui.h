#ifndef ATLC_GUI_H
#define ATLC_GUI_H

#ifdef __GNUG__
#pragma implementation "help.cpp"
#pragma interface "help.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/wxhtml.h>
#include <wx/filesys.h>
#include <wx/fs_zip.h>
#include <wx/tipdlg.h>
#include <iostream.h>

enum
{
  ID_Open = 1,
  ID_Quit = 2,
  ID_RectInRect = 3,
  ID_CircInCirc = 4,
  ID_RectInCirc = 5,
  ID_CircInRect = 6,
  ID_SymStrip = 7,
  ID_Coupler = 8,
  ID_FiniteDifference = 9,
  ID_RoundCoax = 10,
  ID_EccentricCoax = 11,
  ID_SquareCoax = 12,
  ID_Stripline=13,
  ID_CouplerStripline=14,
  ID_Help = 15,
  ID_Options = 16,
  ID_CalculateCoupler = 17,
  ID_CalculateChecksum = 18,
  ID_ShowTip = 19,
  ID_Save = 20,
  ID_Close = 21,
  ID_FileMenuClose = 22,
  ID_About
};
#endif
