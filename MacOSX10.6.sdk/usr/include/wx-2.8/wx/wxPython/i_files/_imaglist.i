/////////////////////////////////////////////////////////////////////////////
// Name:        _imaglist.i
// Purpose:     SWIG interface defs for wxImageList and releated classes
//
// Author:      Robin Dunn
//
// Created:     7-July-1997
// RCS-ID:      $Id: _imaglist.i 42453 2006-10-26 15:22:43Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------

%{
%}

//---------------------------------------------------------------------------
%newgroup

enum {
    wxIMAGELIST_DRAW_NORMAL ,
    wxIMAGELIST_DRAW_TRANSPARENT,
    wxIMAGELIST_DRAW_SELECTED,
    wxIMAGELIST_DRAW_FOCUSED,
    
    wxIMAGE_LIST_NORMAL,
    wxIMAGE_LIST_SMALL,
    wxIMAGE_LIST_STATE
};


MustHaveApp(wxImageList);


//  wxImageList is used for wxListCtrl, wxTreeCtrl. These controls refer to
//  images for their items by an index into an image list.
//  A wxImageList is capable of creating images with optional masks from
//  a variety of sources - a single bitmap plus a colour to indicate the mask,
//  two bitmaps, or an icon.
class wxImageList : public wxObject {
public:
    // turn off this typemap
    %typemap(out) wxImageList*;    

    wxImageList(int width, int height, int mask=true, int initialCount=1);
    ~wxImageList();
    
    // Turn it back on again
    %typemap(out) wxImageList* { $result = wxPyMake_wxObject($1, $owner); }

    int Add(const wxBitmap& bitmap, const wxBitmap& mask = wxNullBitmap);
    %Rename(AddWithColourMask,int, Add(const wxBitmap& bitmap, const wxColour& maskColour));
    %Rename(AddIcon,int, Add(const wxIcon& icon));

    wxBitmap GetBitmap(int index) const;
    wxIcon GetIcon(int index) const;
      
    bool Replace(int index, const wxBitmap& bitmap, const wxBitmap& mask = wxNullBitmap);

    bool Draw(int index, wxDC& dc, int x, int x, int flags = wxIMAGELIST_DRAW_NORMAL,
              const bool solidBackground = false);

    int GetImageCount();
    bool Remove(int index);
    bool RemoveAll();

    DocDeclA(
        void, GetSize(int index, int& OUTPUT, int& OUTPUT),
        "GetSize(index) -> (width,height)");
        
    %property(ImageCount, GetImageCount, doc="See `GetImageCount`");
    %property(Size, GetSize, doc="See `GetSize`");
};

//---------------------------------------------------------------------------
