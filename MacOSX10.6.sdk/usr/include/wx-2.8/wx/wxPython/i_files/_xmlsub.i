/////////////////////////////////////////////////////////////////////////////
// Name:        _xmlres.i
// Purpose:     SWIG interface for wxXmlSubclassFactory
//
// Author:      Robin Dunn
//
// Created:     4-June-2001
// RCS-ID:      $Id: _xmlsub.i 43425 2006-11-14 22:03:54Z RD $
// Copyright:   (c) 2003 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------
%newgroup



%{
class wxPyXmlSubclassFactory : public wxXmlSubclassFactory
{
public:
    wxPyXmlSubclassFactory() {}
    DEC_PYCALLBACK_OBJECT_STRING_pure(Create);
    PYPRIVATE;
};

IMP_PYCALLBACK_OBJECT_STRING_pure(wxPyXmlSubclassFactory, wxXmlSubclassFactory, Create);
%}



%rename(XmlSubclassFactory) wxPyXmlSubclassFactory;
class wxPyXmlSubclassFactory {
public:
    %pythonAppend wxPyXmlSubclassFactory setCallbackInfo(XmlSubclassFactory)
    wxPyXmlSubclassFactory();
    void _setCallbackInfo(PyObject* self, PyObject* _class);
};


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
