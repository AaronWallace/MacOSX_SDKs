/////////////////////////////////////////////////////////////////////////////
// Name:        _tipwin.i
// Purpose:     SWIG interface defs for wxTipWindow
//
// Author:      Robin Dunn
//
// Created:     22-Dec-1998
// RCS-ID:      $Id: _tipwin.i 27565 2004-06-01 21:38:05Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------

%{
#include <wx/tipwin.h>
%}

//---------------------------------------------------------------------------
%newgroup;


MustHaveApp(wxTipWindow);

class wxTipWindow :
#ifndef __WXMAC__
    public wxPyPopupTransientWindow
#else
    public wxFrame
#endif
{
public:
    %pythonAppend wxTipWindow         "self._setOORInfo(self)"
    
    %extend {
        wxTipWindow(wxWindow *parent,
                    const wxString& text,
                    wxCoord maxLength = 100,
                    wxRect* rectBound = NULL) {
            return new wxTipWindow(parent, text, maxLength, NULL, rectBound);
        }
    }


    // If rectBound is not NULL, the window will disappear automatically when
    // the mouse leave the specified rect: note that rectBound should be in the
    // screen coordinates!
    void SetBoundingRect(const wxRect& rectBound);

    // Hide and destroy the window
    void Close();
};

//---------------------------------------------------------------------------
