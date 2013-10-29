/////////////////////////////////////////////////////////////////////////////
// Name:        pyistream.h
// Purpose:     Classes for managing wxInputStream <--> Python streams
//
// Author:      Robin Dunn
//
// Created:     25-Sept-2000
// RCS-ID:      $Id: pyistream.h 47786 2007-07-28 17:01:57Z RD $
// Copyright:   (c) 2000 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __PYISTREAM__
#define __PYISTREAM__


//---------------------------------------------------------------------------
// Handling of wxInputStreams by Joerg Baumann
// See stream.i for implementations


// C++ class wxPyInputStream to act as base for python class wxInputStream
// You can use it in python like a python file object.
class wxPyInputStream {
public:
    // underlying wxInputStream
    wxInputStream* m_wxis;

public:
    wxPyInputStream(wxInputStream* wxis) : m_wxis(wxis) {}
    ~wxPyInputStream();

    // python file object interface for input files (most of it)
    void close();
    void flush();
    bool eof();
    void seek(int offset, int whence=0);
    int tell();

    PyObject* read(int size=-1);
    PyObject* readline(int size=-1);
    PyObject* readlines(int sizehint=-1);

    // do these later?
    //bool isatty();
    //int fileno();
    //void truncate(int size=-1);
    //PyObject* next();

    // It's an input stream, can't write to it.
    //void write(wxString data);
    //void writelines(wxStringPtrList);

    // wxInputStream methods that may come in handy...

    char Peek()           { if (m_wxis) return m_wxis->Peek(); else return -1; }
    char GetC()           { if (m_wxis) return m_wxis->GetC(); else return -1; }
    size_t LastRead()     { if (m_wxis) return m_wxis->LastRead(); else return 0; }
    bool CanRead()        { if (m_wxis) return m_wxis->CanRead(); else return false; }
    bool Eof()            { if (m_wxis) return m_wxis->Eof(); else return false; }
    bool Ungetch(char c)  { if (m_wxis) return m_wxis->Ungetch(c); else return false; }

    unsigned long SeekI(unsigned long pos, wxSeekMode mode)
          { if (m_wxis) return m_wxis->SeekI(pos, mode); else return 0; }
    unsigned long TellI() { if (m_wxis) return m_wxis->TellI(); else return 0; }
};



// This is a wxInputStream that wraps a Python file-like
// object and calls the Python methods as needed.
class wxPyCBInputStream : public wxInputStream {
public:
    ~wxPyCBInputStream();
    virtual wxFileOffset GetLength() const;

    // factory function
    static wxPyCBInputStream* create(PyObject *py, bool block=true);

    wxPyCBInputStream(const wxPyCBInputStream& other);
    
protected:
    // can only be created via the factory
    wxPyCBInputStream(PyObject *r, PyObject *s, PyObject *t, bool block);

    // wxStreamBase methods
    virtual size_t OnSysRead(void *buffer, size_t bufsize);
    virtual size_t OnSysWrite(const void *buffer, size_t bufsize);
    virtual wxFileOffset OnSysSeek(wxFileOffset off, wxSeekMode mode);
    virtual wxFileOffset OnSysTell() const;

    PyObject* m_read;
    PyObject* m_seek;
    PyObject* m_tell;
    bool      m_block;
};

//---------------------------------------------------------------------------

// C++ class wxPyOutputStream to act as base for python class wxOutputStream
// You can use it in python like a python file object.
class wxPyOutputStream {
public:
    // underlying wxOutputStream
    wxOutputStream* m_wxos;

public:
    wxPyOutputStream(wxOutputStream* wxos) : m_wxos(wxos) {}
    ~wxPyOutputStream();

    void close();
    void flush();
    bool eof();
    void seek(int offset, int whence=0);
    int tell();

    // it's an output stream, can't read from it.
    //PyObject* read(int size=-1);
    //PyObject* readline(int size=-1);
    //PyObject* readlines(int sizehint=-1);

    // do these later?
    //bool isatty();
    //int fileno();
    //void truncate(int size=-1);
    
    void write(PyObject* data);
    //void writelines(wxStringArray& arr);

    
    // wxOutputStream methods that may come in handy...
    void PutC(char c)        { if (m_wxos) m_wxos->PutC(c); }
    size_t LastWrite()       { if (m_wxos) return m_wxos->LastWrite(); else return 0; }
    unsigned long SeekO(unsigned long pos, wxSeekMode mode = wxFromStart)
          { if (m_wxos) return m_wxos->SeekO(pos, mode); else return 0; }
    unsigned long TellO() { if (m_wxos) return m_wxos->TellO(); else return 0; }
};



// This is a wxOutputStream that wraps a Python file-like
// object and calls the Python methods as needed.
class wxPyCBOutputStream : public wxOutputStream {
public:
    ~wxPyCBOutputStream();
    virtual wxFileOffset GetLength() const;

    // factory function
    static wxPyCBOutputStream* create(PyObject *py, bool block=true);

    wxPyCBOutputStream(const wxPyCBOutputStream& other);
    
protected:
    // can only be created via the factory
    wxPyCBOutputStream(PyObject *w, PyObject *s, PyObject *t, bool block);

    // wxStreamBase methods
    virtual size_t OnSysRead(void *buffer, size_t bufsize);
    virtual size_t OnSysWrite(const void *buffer, size_t bufsize);
    virtual wxFileOffset OnSysSeek(wxFileOffset off, wxSeekMode mode);
    virtual wxFileOffset OnSysTell() const;

    PyObject* m_write;
    PyObject* m_seek;
    PyObject* m_tell;
    bool      m_block;
};

//---------------------------------------------------------------------------
#endif
