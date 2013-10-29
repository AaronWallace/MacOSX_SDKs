/////////////////////////////////////////////////////////////////////////////
// Name:        _wxobj.i
// Purpose:     SWIG interface for wxObject
//
// Author:      Robin Dunn
//
// Created:     9-Aug-2003
// RCS-ID:      $Id: _obj.i 42801 2006-10-31 00:57:21Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------
%newgroup

DocStr(wxObject,
"The base class for most wx objects, although in wxPython not
much functionality is needed nor exposed.", "");

class wxObject {
public:

    %extend {
        DocStr(GetClassName,
               "Returns the class name of the C++ class using wxRTTI.", "");
        wxString GetClassName() {
            return self->GetClassInfo()->GetClassName();
        }

        %pythonPrepend Destroy "args[0].this.own(False)"
        DocStr(Destroy,
               "Deletes the C++ object this Python object is a proxy for.", "");
        void Destroy() {
            delete self;
        }
    }

    DocDeclStr(
        bool , IsSameAs(const wxObject& p) const,
        "For wx.Objects that use C++ reference counting internally, this method
can be used to determine if two objects are referencing the same data
object.", "");
    

    %property(ClassName, GetClassName, doc="See `GetClassName`");
};


//---------------------------------------------------------------------------
