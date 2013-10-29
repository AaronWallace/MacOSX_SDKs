/////////////////////////////////////////////////////////////////////////////
// Name:        _richtextctrl.i
// Purpose:     wxRichTextCtrl and related classes
//
// Author:      Robin Dunn
//
// Created:     11-April-2006
// RCS-ID:      $Id: _richtextctrl.i 54571 2008-07-10 01:35:30Z RD $
// Copyright:   (c) 2006 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------

%{
%}

//---------------------------------------------------------------------------
%newgroup

enum {
    wxRE_READONLY,
    wxRE_MULTILINE,

    wxRICHTEXT_SHIFT_DOWN,
    wxRICHTEXT_CTRL_DOWN,
    wxRICHTEXT_ALT_DOWN,

    wxRICHTEXT_SELECTED,
    wxRICHTEXT_TAGGED,
    wxRICHTEXT_FOCUSSED,
    wxRICHTEXT_IS_FOCUS,

};


//---------------------------------------------------------------------------

MAKE_CONST_WXSTRING2(RichTextCtrlNameStr, wxT("richText"));

MustHaveApp(wxRichTextCtrl);


DocStr(wxRichTextCtrl,
"", "");


// NOTE: This really derives from wxScrollHelper and wxTextCtrlBase.  To
// workaround the lack of wrappers for these we'll just copy the method decls
// into this class.

class wxRichTextCtrl : public wxControl
{
public:
    %pythonAppend wxRichTextCtrl         "self._setOORInfo(self)"
    %pythonAppend wxRichTextCtrl()       ""

    wxRichTextCtrl( wxWindow* parent,
                    wxWindowID id = -1,
                    const wxString& value = wxPyEmptyString,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxRE_MULTILINE,
                    const wxValidator& validator = wxDefaultValidator,
                    const wxString& name = wxPyRichTextCtrlNameStr );
    %RenameCtor(PreRichTextCtrl, wxRichTextCtrl());


    bool Create( wxWindow* parent,
                 wxWindowID id = -1,
                 const wxString& value = wxPyEmptyString,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = wxRE_MULTILINE,
                 const wxValidator& validator = wxDefaultValidator,
                 const wxString& name = wxPyRichTextCtrlNameStr );


    DocDeclStr(
        virtual wxString , GetValue() const,
        "", "");

    DocDeclStr(
        virtual void , SetValue(const wxString& value),
        "", "");


    DocDeclStr(
        virtual wxString , GetRange(long from, long to) const,
        "", "");


    DocDeclStr(
        virtual int , GetLineLength(long lineNo) const ,
        "", "");

    DocDeclStr(
        virtual wxString , GetLineText(long lineNo) const ,
        "", "");

    DocDeclStr(
        virtual int , GetNumberOfLines() const ,
        "", "");


    DocDeclStr(
        virtual bool , IsModified() const ,
        "", "");

    DocDeclStr(
        virtual bool , IsEditable() const ,
        "", "");


    // more readable flag testing methods
    DocDeclStr(
        bool , IsSingleLine() const,
        "", "");

    DocDeclStr(
        bool , IsMultiLine() const,
        "", "");


    DocDeclAStr(
        virtual void , GetSelection(long* OUTPUT, long* OUTPUT) const,
        "GetSelection() --> (start, end)",
        "Returns the start and end positions of the current selection.  If the
values are the same then there is no selection.", "");


    DocDeclStr(
        virtual wxString , GetStringSelection() const,
        "", "");


    DocDeclStr(
        wxString , GetFilename() const,
        "", "");


    DocDeclStr(
        void , SetFilename(const wxString& filename),
        "", "");


    DocDeclStr(
        void , SetDelayedLayoutThreshold(long threshold),
        "Set the threshold in character positions for doing layout optimization
during sizing.", "");


    DocDeclStr(
        long , GetDelayedLayoutThreshold() const,
        "Get the threshold in character positions for doing layout optimization
during sizing.", "");


    DocDeclStr(
        void , SetTextCursor(const wxCursor& cursor ),
        "Set text cursor", "");
    

    DocDeclStr(
        wxCursor , GetTextCursor() const,
        "Get text cursor", "");
    

    DocDeclStr(
        void , SetURLCursor(const wxCursor& cursor ),
        "Set URL cursor", "");
    

    DocDeclStr(
        wxCursor , GetURLCursor() const,
        "Get URL cursor", "");
    

    

    DocDeclStr(
        virtual void , Clear(),
        "", "");

    DocDeclStr(
        virtual void , Replace(long from, long to, const wxString& value),
        "", "");

    DocDeclStr(
        virtual void , Remove(long from, long to),
        "", "");


    DocDeclStr(
        virtual bool , LoadFile(const wxString& file, int type = wxRICHTEXT_TYPE_ANY),
        "Load the contents of the document from the given filename.", "");

    DocDeclStr(
        virtual bool , SaveFile(const wxString& file = wxPyEmptyString,
                                int type = wxRICHTEXT_TYPE_ANY),
        "Save the contents of the document to the given filename, or if the
empty string is passed then to the filename set with `SetFilename`.", "");


    DocDeclStr(
        void , SetHandlerFlags(int flags), 
        "Set the handler flags, controlling loading and saving.", "");

    DocDeclStr(
        int , GetHandlerFlags() const, 
        "Get the handler flags, controlling loading and saving.", "");

    // sets/clears the dirty flag
    DocDeclStr(
        virtual void , MarkDirty(),
        "Sets the dirty flag, meaning that the contents of the control have
changed and need to be saved.", "");

    DocDeclStr(
        virtual void , DiscardEdits(),
        "Clears the dirty flag.
:see: `MarkDirty`", "");


    DocDeclStr(
        virtual void , SetMaxLength(unsigned long len),
        "Set the max number of characters which may be entered in a single line
text control.", "");


    DocDeclStr(
        virtual void , WriteText(const wxString& text),
        "Insert text at the current position.", "");

    DocDeclStr(
        virtual void , AppendText(const wxString& text),
        "Append text to the end of the document.", "");


    DocDeclStr(
        virtual bool , SetStyle(const wxRichTextRange& range, const wxTextAttrEx& style),
        "Set the style for the text in ``range`` to ``style``", "");

    DocDeclStr(
        virtual bool , GetStyle(long position, wxTextAttrEx& style),
        "Retrieve the style used at the given position.  Copies the style
values at ``position`` into the ``style`` parameter and returns ``True``
if successful.  Returns ``False`` otherwise.", "");


    DocDeclStr(
        virtual bool , GetStyleForRange(const wxRichTextRange& range, wxTextAttrEx& style),
        "Get the common set of styles for the range", "");
    

    DocDeclStr(
        virtual bool , SetStyleEx(const wxRichTextRange& range, const wxTextAttrEx& style,
                                  int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO),
        "Extended style setting operation with flags including:
RICHTEXT_SETSTYLE_WITH_UNDO, RICHTEXT_SETSTYLE_OPTIMIZE,
RICHTEXT_SETSTYLE_PARAGRAPHS_ONLY, RICHTEXT_SETSTYLE_CHARACTERS_ONLY", "");
    

    
    DocDeclStr(
        virtual bool , GetUncombinedStyle(long position, wxTextAttrEx& style),
        "Get the content (uncombined) attributes for this position.  Copies the
style values at ``position`` into the ``style`` parameter and returns
``True`` if successful.  Returns ``False`` otherwise.", "");


    DocDeclStr(
        virtual bool , SetDefaultStyle(const wxTextAttrEx& style),
        "Set the style used by default for the rich text document.", "");


    DocDeclStrName(
        virtual const wxTextAttrEx , GetDefaultStyleEx() const,
        "Retrieves a copy of the default style object.", "",
        GetDefaultStyle);


// TODO:  Select which of these to keep or rename
    
    /// Set list style
//     virtual bool SetListStyle(const wxRichTextRange& range,
//                               wxRichTextListStyleDefinition* def,
//                               int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO,
//                               int startFrom = 1, int specifiedLevel = -1);
    virtual bool SetListStyle(const wxRichTextRange& range,
                              const wxString& defName,
                              int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO,
                              int startFrom = 1, int specifiedLevel = -1);

    /// Clear list for given range
    virtual bool ClearListStyle(const wxRichTextRange& range, int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO);

    /// Number/renumber any list elements in the given range
    /// def/defName can be NULL/empty to indicate that the existing list style should be used.
//     virtual bool NumberList(const wxRichTextRange& range,
//                             wxRichTextListStyleDefinition* def = NULL,
//                             int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO,
//                             int startFrom = 1, int specifiedLevel = -1);
    virtual bool NumberList(const wxRichTextRange& range,
                            const wxString& defName,
                            int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO,
                            int startFrom = 1, int specifiedLevel = -1);

    /// Promote the list items within the given range. promoteBy can be a positive or negative number, e.g. 1 or -1
    /// def/defName can be NULL/empty to indicate that the existing list style should be used.
//     virtual bool PromoteList(int promoteBy, const wxRichTextRange& range,
//                              wxRichTextListStyleDefinition* def = NULL,
//                              int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO,
//                              int specifiedLevel = -1);
    virtual bool PromoteList(int promoteBy, const wxRichTextRange& range,
                             const wxString& defName,
                             int flags = wxRICHTEXT_SETSTYLE_WITH_UNDO,
                             int specifiedLevel = -1);

    /// Deletes the content in the given range
    virtual bool Delete(const wxRichTextRange& range);


    

    DocDeclStr(
        virtual long , XYToPosition(long x, long y) const,
        "Translate a col,row coordinants into a document position.", "");

    DocDeclAStr(
        virtual void , PositionToXY(long pos, long *OUTPUT, long *OUTPUT) const,
        "PositionToXY(self, long pos) --> (x, y)",
        "Retrieves the col,row for the given position within the document", "");


    DocDeclStr(
        virtual void , ShowPosition(long position),
        "Ensure that the given position in the document is visible.", "");


    DocDeclAStr(
        virtual wxTextCtrlHitTestResult , HitTest(const wxPoint& pt, long *OUTPUT) const,
        "HitTest(self, Point pt) --> (result, pos)",
        "Returns the character position at the given point in pixels.  Note
that ``pt`` should be given in device coordinates, and not be adjusted
for the client area origin nor for scrolling.  The return value is a
tuple of the hit test result and the position.", "

Possible result values are a bitmask of these flags:

    =========================  ====================================
    RICHTEXT_HITTEST_NONE      The point was not on this object.
    RICHTEXT_HITTEST_BEFORE    The point was before the position
                                  returned from HitTest.
    RICHTEXT_HITTEST_AFTER     The point was after the position
                               returned from HitTest.
    RICHTEXT_HITTEST_ON        The point was on the position
                               returned from HitTest
    =========================  ====================================
");

    DocDeclAStrName(
        virtual wxTextCtrlHitTestResult , HitTest(const wxPoint& pt,
                                                  wxTextCoord *OUTPUT,
                                                  wxTextCoord *OUTPUT) const,
        "HitTestRC(self, Point pt) --> (result, col, row)",
        "Returns the column and row of the given point in pixels.  Note that
``pt`` should be given in device coordinates, and not be adjusted for
the client area origin nor for scrolling.  The return value is a tuple
of the hit test result and the column and row values.", "
:see: `HitTest`",
        HitTestXY);


    // Clipboard operations
    DocDeclStr(
        virtual void , Copy(),
        "Copies the selected text to the clipboard.", "");

    DocDeclStr(
        virtual void , Cut(),
        "Copies the selected text to the clipboard and removes the selection.", "");

    DocDeclStr(
        virtual void , Paste(),
        "Pastes text from the clipboard into the document at the current
insertion point.", "");

    DocDeclStr(
        virtual void , DeleteSelection(),
        "Remove the current selection.", "");


    DocDeclStr(
        virtual bool , CanCopy() const,
        "Returns ``True`` if the selection can be copied to the clipboard.", "");

    DocDeclStr(
        virtual bool , CanCut() const,
        "Returns ``True`` if the selection can be cut to the clipboard.", "");

    DocDeclStr(
        virtual bool , CanPaste() const,
        "Returns ``True`` if the current contents of the clipboard can be
pasted into the document.", "");

    DocDeclStr(
        virtual bool , CanDeleteSelection() const,
        "Returns ``True`` if the selection can be removed from the document.", "");


    // Undo/redo
    DocDeclStr(
        virtual void , Undo(),
        "If the last operation can be undone, undoes the last operation.", "");

    DocDeclStr(
        virtual void , Redo(),
        "If the last operation can be redone, redoes the last operation.", "");


    DocDeclStr(
        virtual bool , CanUndo() const,
        "Returns ``True`` if the last operation can be undone.", "");

    DocDeclStr(
        virtual bool , CanRedo() const,
        "Returns ``True`` if the last operation can be redone.", "");


    // Insertion point
    DocDeclStr(
        virtual void , SetInsertionPoint(long pos),
        "Sets the insertion point at the given position.", "");

    DocDeclStr(
        virtual void , SetInsertionPointEnd(),
        "Moves the insertion point to the end of the document.", "");

    DocDeclStr(
        virtual long , GetInsertionPoint() const,
        "Returns the insertion point. This is defined as the zero based index
of the character position to the right of the insertion point.", "");

    DocDeclStr(
        virtual long , GetLastPosition() const,
        "Returns the zero based index of the last position in the document.", "");


    DocDeclStr(
        virtual void , SetSelection(long from, long to),
        "Selects the text starting at the first position up to (but not
including) the character at the last position. If both parameters are
equal to -1 then all text in the control is selected.", "");

    DocDeclStr(
        virtual void , SelectAll(),
        "Select all text in the document.", "");

    DocDeclStr(
        virtual void , SetEditable(bool editable),
        "Makes the document editable or read-only, overriding the RE_READONLY
flag.", "");


    DocDeclStr(
        virtual bool , HasSelection() const,
        "", "");


///// Functionality specific to wxRichTextCtrl

    DocDeclStr(
        virtual bool , WriteImage(const wxImage& image, int bitmapType = wxBITMAP_TYPE_PNG),
        "Write an image at the current insertion point. Supply optional type to
use for internal and file storage of the raw data.
", "");


    DocDeclStrName(
        virtual bool , WriteImage(const wxBitmap& bitmap, int bitmapType = wxBITMAP_TYPE_PNG),
        "Write a bitmap at the current insertion point. Supply optional type to
use for internal and file storage of the raw data.", "",
        WriteBitmap);


    DocDeclStrName(
        virtual bool , WriteImage(const wxString& filename, int bitmapType),
        "Load an image from file and write at the current insertion point.", "",
        WriteImageFile);


    DocDeclStrName(
        virtual bool , WriteImage(const wxRichTextImageBlock& imageBlock),
        "Write an image block at the current insertion point.", "",
        WriteImageBlock);


    DocDeclStr(
        virtual bool , Newline(),
        "Insert a newline (actually paragraph) at the current insertion point.", "");


    DocDeclStr(
        virtual bool , LineBreak(),
        "Insert a line break at the current insertion point.", "");
    

    
    DocDeclStr(
        virtual void , SetBasicStyle(const wxTextAttrEx& style),
        "", "");


    DocDeclStr(
        virtual const wxTextAttrEx , GetBasicStyle() const,
        "Get basic (overall) style", "");


    DocDeclStr(
        virtual bool , BeginStyle(const wxTextAttrEx& style),
        "Begin using a style", "");

    
    DocDeclStr(
        virtual bool , EndStyle(),
        "End the style", "");


    DocDeclStr(
        virtual bool , EndAllStyles(),
        "End all styles", "");


    DocDeclStr(
        bool , BeginBold(),
        "Begin using bold", "");


    DocDeclStr(
        bool , EndBold(),
        "End using bold", "");


    DocDeclStr(
        bool , BeginItalic(),
        "Begin using italic", "");


    DocDeclStr(
        bool , EndItalic(),
        "End using italic", "");


    DocDeclStr(
        bool , BeginUnderline(),
        "Begin using underline", "");


    DocDeclStr(
        bool , EndUnderline(),
        "End using underline", "");


    DocDeclStr(
        bool , BeginFontSize(int pointSize),
        "Begin using point size", "");


    DocDeclStr(
        bool , EndFontSize(),
        "End using point size", "");


    DocDeclStr(
        bool , BeginFont(const wxFont& font),
        "Begin using this font", "");


    DocDeclStr(
        bool , EndFont(),
        "End using a font", "");


    DocDeclStr(
        bool , BeginTextColour(const wxColour& colour),
        "Begin using this colour", "");


    DocDeclStr(
        bool , EndTextColour(),
        "End using a colour", "");


    DocDeclStr(
        bool , BeginAlignment(wxTextAttrAlignment alignment),
        "Begin using alignment", "");


    DocDeclStr(
        bool , EndAlignment(),
        "End alignment", "");


    DocDeclStr(
        bool , BeginLeftIndent(int leftIndent, int leftSubIndent = 0),
        "Begin left indent", "");


    DocDeclStr(
        bool , EndLeftIndent(),
        "End left indent", "");


    DocDeclStr(
        bool , BeginRightIndent(int rightIndent),
        "Begin right indent", "");


    DocDeclStr(
        bool , EndRightIndent(),
        "End right indent", "");


    DocDeclStr(
        bool , BeginParagraphSpacing(int before, int after),
        "Begin paragraph spacing", "");


    DocDeclStr(
        bool , EndParagraphSpacing(),
        "End paragraph spacing", "");


    DocDeclStr(
        bool , BeginLineSpacing(int lineSpacing),
        "Begin line spacing", "");


    DocDeclStr(
        bool , EndLineSpacing(),
        "End line spacing", "");


    DocDeclStr(
        bool , BeginNumberedBullet(int bulletNumber,
                                   int leftIndent,
                                   int leftSubIndent,
                                   int bulletStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD),
        "Begin numbered bullet", "");


    DocDeclStr(
        bool , EndNumberedBullet(),
        "End numbered bullet", "");


    DocDeclStr(
        bool , BeginSymbolBullet(const wxString& symbol,
                                 int leftIndent,
                                 int leftSubIndent,
                                 int bulletStyle = wxTEXT_ATTR_BULLET_STYLE_SYMBOL),
        "Begin symbol bullet", "");


    DocDeclStr(
        bool , EndSymbolBullet(),
        "End symbol bullet", "");


    DocDeclStr(
        bool , BeginStandardBullet(const wxString& bulletName,
                                   int leftIndent,
                                   int leftSubIndent,
                                   int bulletStyle = wxTEXT_ATTR_BULLET_STYLE_STANDARD),
        "Begin standard bullet", "");
    


    DocDeclStr(
        bool , EndStandardBullet(),
        "End standard bullet", "");
    
    
    DocDeclStr(
        bool , BeginCharacterStyle(const wxString& characterStyle),
        "Begin named character style", "");


    DocDeclStr(
        bool , EndCharacterStyle(),
        "End named character style", "");


    DocDeclStr(
        bool , BeginParagraphStyle(const wxString& paragraphStyle),
        "Begin named paragraph style", "");


    DocDeclStr(
        bool , EndParagraphStyle(),
        "End named character style", "");


    DocDeclStr(
        bool , BeginListStyle(const wxString& listStyle, int level = 1, int number = 1),
        "Begin named list style.", "");
        
    DocDeclStr(
        bool , EndListStyle(), "End named list style.", "");

    DocDeclStr(
        bool , BeginURL(const wxString& url, const wxString& characterStyle = wxEmptyString),
            "Begin URL.", "");
    
    DocDeclStr(
        bool , EndURL(), "End URL.", "");

    DocDeclStr(
        bool , SetDefaultStyleToCursorStyle(),
        "Sets the default style to the style under the cursor", "");


    DocDeclStr(
        virtual void , SelectNone(),
        "Clear the selection", "");


    DocDeclStr(
        virtual bool , SelectWord(long position),
        "Select the word at the given character position", "");


    DocDeclStr(
        wxRichTextRange , GetSelectionRange() const,
        "Get the selection range in character positions.", "");

    DocDeclStr(
        void , SetSelectionRange(const wxRichTextRange& range),
        "Set the selection range in character positions. -1, -1 means no selection.", "");


    DocDeclStr(
        const wxRichTextRange& , GetInternalSelectionRange() const,
        "Get the selection range in character positions. -1, -1 means no
selection.  The range is in internal format, i.e. a single character
selection is denoted by (n, n).
", "");

    DocDeclStr(
        void , SetInternalSelectionRange(const wxRichTextRange& range),
        "Set the selection range in character positions. -1, -1 means no
selection.  The range is in internal format, i.e. a single character
selection is denoted by (n, n).", "");



    DocDeclStr(
        virtual wxRichTextRange , AddParagraph(const wxString& text),
        "Add a new paragraph of text to the end of the buffer", "");


    DocDeclStr(
        virtual wxRichTextRange , AddImage(const wxImage& image),
        "Add an image", "");


    DocDeclStr(
        virtual bool , LayoutContent(bool onlyVisibleRect = false),
        "Layout the buffer: which we must do before certain operations, such as
setting the caret position.", "");


    DocDeclStr(
        virtual bool , MoveCaret(long pos, bool showAtLineStart = false),
        "Move the caret to the given character position", "");


    DocDeclStr(
        virtual bool , MoveRight(int noPositions = 1, int flags = 0),
        "Move right", "");


    DocDeclStr(
        virtual bool , MoveLeft(int noPositions = 1, int flags = 0),
        "Move left", "");


    DocDeclStr(
        virtual bool , MoveUp(int noLines = 1, int flags = 0),
        "Move up", "");


    DocDeclStr(
        virtual bool , MoveDown(int noLines = 1, int flags = 0),
        "Move down", "");


    DocDeclStr(
        virtual bool , MoveToLineEnd(int flags = 0),
        "Move to the end of the line", "");


    DocDeclStr(
        virtual bool , MoveToLineStart(int flags = 0),
        "Move to the start of the line", "");


    DocDeclStr(
        virtual bool , MoveToParagraphEnd(int flags = 0),
        "Move to the end of the paragraph", "");


    DocDeclStr(
        virtual bool , MoveToParagraphStart(int flags = 0),
        "Move to the start of the paragraph", "");


    DocDeclStr(
        virtual bool , MoveHome(int flags = 0),
        "Move to the start of the buffer", "");


    DocDeclStr(
        virtual bool , MoveEnd(int flags = 0),
        "Move to the end of the buffer", "");


    DocDeclStr(
        virtual bool , PageUp(int noPages = 1, int flags = 0),
        "Move n pages up", "");


    DocDeclStr(
        virtual bool , PageDown(int noPages = 1, int flags = 0),
        "Move n pages down", "");


    DocDeclStr(
        virtual bool , WordLeft(int noPages = 1, int flags = 0),
        "Move n words left", "");


    DocDeclStr(
        virtual bool , WordRight(int noPages = 1, int flags = 0),
        "Move n words right", "");


    DocDeclStr(
        wxRichTextBuffer& , GetBuffer(),
        "Returns the buffer associated with the control.
", "");


    DocDeclStr(
        virtual bool , BeginBatchUndo(const wxString& cmdName),
        "Start batching undo history for commands", "");


    DocDeclStr(
        virtual bool , EndBatchUndo(),
        "End batching undo history for commands.", "");


    DocDeclStr(
        virtual bool , BatchingUndo() const,
        "Are we batching undo history for commands?", "");


    DocDeclStr(
        virtual bool , BeginSuppressUndo(),
        "Start suppressing undo history for commands.", "");


    DocDeclStr(
        virtual bool , EndSuppressUndo(),
        "End suppressing undo history for commands.", "");


    DocDeclStr(
        virtual bool , SuppressingUndo() const,
        "Are we suppressing undo history for commands?", "");


    DocDeclStr(
        virtual bool , HasCharacterAttributes(const wxRichTextRange& range,
                                              const wxTextAttrEx& style) const,
        "Test if this whole range has character attributes of the specified
kind. If any of the attributes are different within the range, the
test fails. You can use this to implement, for example, bold button
updating. ``style`` must have flags indicating which attributes are of
interest.
", "");



    DocDeclStr(
        virtual bool , HasParagraphAttributes(const wxRichTextRange& range,
                                              const wxTextAttrEx& style) const,
        "Test if this whole range has paragraph attributes of the specified
kind. If any of the attributes are different within the range, the
test fails. You can use this to implement, for example, centering
button updating. style must have flags indicating which attributes are
of interest.
", "");



    DocDeclStr(
        virtual bool , IsSelectionBold(),
        "Is all of the selection bold?", "");


    DocDeclStr(
        virtual bool , IsSelectionItalics(),
        "Is all of the selection italics?", "");


    DocDeclStr(
        virtual bool , IsSelectionUnderlined(),
        "Is all of the selection underlined?", "");


    DocDeclStr(
        virtual bool , IsSelectionAligned(wxTextAttrAlignment alignment),
        "Is all of the selection aligned according to the specified flag?", "");


    DocDeclStr(
        virtual bool , ApplyBoldToSelection(),
        "Apply bold to the selection", "");


    DocDeclStr(
        virtual bool , ApplyItalicToSelection(),
        "Apply italic to the selection", "");


    DocDeclStr(
        virtual bool , ApplyUnderlineToSelection(),
        "Apply underline to the selection", "");


    DocDeclStr(
        virtual bool , ApplyAlignmentToSelection(wxTextAttrAlignment alignment),
        "Apply alignment to the selection", "");


    DocDeclStr(
        virtual bool , ApplyStyle(wxRichTextStyleDefinition* def),
        "Apply a named style to the selection", "");
    

    DocDeclStr(
        void , SetStyleSheet(wxRichTextStyleSheet* styleSheet),
        "Set style sheet, if any.", "");

    DocDeclStr(
        wxRichTextStyleSheet* , GetStyleSheet() const,
        "", "");


    DocDeclStr(
        bool , PushStyleSheet(wxRichTextStyleSheet* styleSheet),
        "Push style sheet to top of stack", "");
    

    
    DocDeclStr(
        wxRichTextStyleSheet* , PopStyleSheet(),
        "Pop style sheet from top of stack", "");
    

    
    DocDeclStr(
        bool , ApplyStyleSheet(wxRichTextStyleSheet* styleSheet = NULL),
        "Apply the style sheet to the buffer, for example if the styles have
changed.", "");



    %property(Buffer, GetBuffer, doc="See `GetBuffer`");
    %property(DefaultStyle, GetDefaultStyle, SetDefaultStyle, doc="See `GetDefaultStyle` and `SetDefaultStyle`");
    %property(DelayedLayoutThreshold, GetDelayedLayoutThreshold, SetDelayedLayoutThreshold, doc="See `GetDelayedLayoutThreshold` and `SetDelayedLayoutThreshold`");
    %property(Filename, GetFilename, SetFilename, doc="See `GetFilename` and `SetFilename`");
    %property(InsertionPoint, GetInsertionPoint, SetInsertionPoint, doc="See `GetInsertionPoint` and `SetInsertionPoint`");
    %property(InternalSelectionRange, GetInternalSelectionRange, SetInternalSelectionRange, doc="See `GetInternalSelectionRange` and `SetInternalSelectionRange`");
    %property(LastPosition, GetLastPosition, doc="See `GetLastPosition`");
    %property(NumberOfLines, GetNumberOfLines, doc="See `GetNumberOfLines`");
    %property(Selection, GetSelection, SetSelectionRange, doc="See `GetSelection` and `SetSelection`");
    %property(SelectionRange, GetSelectionRange, SetSelectionRange, doc="See `GetSelectionRange` and `SetSelectionRange`");
    %property(StringSelection, GetStringSelection, doc="See `GetStringSelection`");
    %property(StyleSheet, GetStyleSheet, SetStyleSheet, doc="See `GetStyleSheet` and `SetStyleSheet`");
    %property(Value, GetValue, SetValue, doc="See `GetValue` and `SetValue`");


    //-------------------------------------------------------------
    // Methods from wxScrollHelper

    // configure the scrolling
    virtual void SetScrollbars(int pixelsPerUnitX, int pixelsPerUnitY,
                               int noUnitsX, int noUnitsY,
                               int xPos = 0, int yPos = 0,
                               bool noRefresh = false );

    // scroll to the given (in logical coords) position
    virtual void Scroll(int x, int y);

    // get/set the page size for this orientation (wxVERTICAL/wxHORIZONTAL)
    int GetScrollPageSize(int orient) const;
    void SetScrollPageSize(int orient, int pageSize);

//     // get the number of lines the window can scroll, 
//     // returns 0 if no scrollbars are there.
//     int GetScrollLines( int orient ) const;
    
    // Set the x, y scrolling increments.
    void SetScrollRate( int xstep, int ystep );

    DocDeclAStr(
        virtual void, GetScrollPixelsPerUnit(int *OUTPUT, int *OUTPUT) const,
        "GetScrollPixelsPerUnit() -> (xUnit, yUnit)",
        "Get the size of one logical unit in physical units.", "");

    // Enable/disable Windows scrolling in either direction. If True, wxWindows
    // scrolls the canvas and only a bit of the canvas is invalidated; no
    // Clear() is necessary. If False, the whole canvas is invalidated and a
    // Clear() is necessary. Disable for when the scroll increment is used to
    // actually scroll a non-constant distance
    virtual void EnableScrolling(bool x_scrolling, bool y_scrolling);


    DocDeclAStr( 
        virtual void, GetViewStart(int *OUTPUT, int *OUTPUT) const,
        "GetViewStart() -> (x,y)",
        "Get the view start", "");
    
    // Set the scale factor, used in PrepareDC
    void SetScale(double xs, double ys);
    double GetScaleX() const;
    double GetScaleY() const;


    %nokwargs CalcScrolledPosition;
    %nokwargs CalcUnscrolledPosition;
    
    DocStr(CalcScrolledPosition, "Translate between scrolled and unscrolled coordinates.", "");
    wxPoint CalcScrolledPosition(const wxPoint& pt) const;
    DocDeclA(
        void, CalcScrolledPosition(int x, int y, int *OUTPUT, int *OUTPUT) const,
        "CalcScrolledPosition(int x, int y) -> (sx, sy)");

    
    DocStr(CalcUnscrolledPosition, "Translate between scrolled and unscrolled coordinates.", "");
    wxPoint CalcUnscrolledPosition(const wxPoint& pt) const;
    DocDeclA(
        void, CalcUnscrolledPosition(int x, int y, int *OUTPUT, int *OUTPUT) const,
        "CalcUnscrolledPosition(int x, int y) -> (ux, uy)");


    
// TODO: use directors?
//     virtual void DoCalcScrolledPosition(int x, int y, int *xx, int *yy) const;
//     virtual void DoCalcUnscrolledPosition(int x, int y, int *xx, int *yy) const;

    // Adjust the scrollbars
    virtual void AdjustScrollbars();

    // Calculate scroll increment
    virtual int CalcScrollInc(wxScrollWinEvent& event);

    // Normally the wxScrolledWindow will scroll itself, but in some rare
    // occasions you might want it to scroll [part of] another window (e.g. a
    // child of it in order to scroll only a portion the area between the
    // scrollbars (spreadsheet: only cell area will move).
    virtual void SetTargetWindow(wxWindow *target);
    virtual wxWindow *GetTargetWindow() const;

#ifndef __WXGTK__
    void SetTargetRect(const wxRect& rect);
    wxRect GetTargetRect() const;
#endif


    
    //------------------------------------------------------------
    // Methods from wxtextCtrlBase
    
    virtual bool IsEmpty() const;
    virtual void ChangeValue(const wxString &value);
    void SetModified(bool modified);
    
    // insert the character which would have resulted from this key event,
    // return True if anything has been inserted
    virtual bool EmulateKeyPress(const wxKeyEvent& event);

};


//---------------------------------------------------------------------------
%newgroup


%constant wxEventType wxEVT_COMMAND_RICHTEXT_LEFT_CLICK;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_RIGHT_CLICK;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_MIDDLE_CLICK;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_LEFT_DCLICK;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_RETURN;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_CHARACTER;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_DELETE;

%constant wxEventType wxEVT_COMMAND_RICHTEXT_STYLESHEET_CHANGING;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_STYLESHEET_CHANGED;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_STYLESHEET_REPLACING;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_STYLESHEET_REPLACED;

%constant wxEventType wxEVT_COMMAND_RICHTEXT_CONTENT_INSERTED;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_CONTENT_DELETED;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_STYLE_CHANGED;
%constant wxEventType wxEVT_COMMAND_RICHTEXT_SELECTION_CHANGED;

%pythoncode {
EVT_RICHTEXT_LEFT_CLICK = wx.PyEventBinder(wxEVT_COMMAND_RICHTEXT_LEFT_CLICK, 1)
EVT_RICHTEXT_RIGHT_CLICK = wx.PyEventBinder(wxEVT_COMMAND_RICHTEXT_RIGHT_CLICK, 1)
EVT_RICHTEXT_MIDDLE_CLICK = wx.PyEventBinder(wxEVT_COMMAND_RICHTEXT_MIDDLE_CLICK, 1)
EVT_RICHTEXT_LEFT_DCLICK = wx.PyEventBinder(wxEVT_COMMAND_RICHTEXT_LEFT_DCLICK, 1)
EVT_RICHTEXT_RETURN = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_RETURN, 1)
EVT_RICHTEXT_CHARACTER = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_CHARACTER, 1)
EVT_RICHTEXT_DELETE = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_DELETE, 1)

EVT_RICHTEXT_STYLESHEET_CHANGING = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_STYLESHEET_CHANGING, 1)
EVT_RICHTEXT_STYLESHEET_CHANGED = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_STYLESHEET_CHANGED, 1)
EVT_RICHTEXT_STYLESHEET_REPLACING = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_STYLESHEET_REPLACING, 1)
EVT_RICHTEXT_STYLESHEET_REPLACED = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_STYLESHEET_REPLACED, 1)

EVT_RICHTEXT_CONTENT_INSERTED = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_CONTENT_INSERTED, 1)
EVT_RICHTEXT_CONTENT_DELETED = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_CONTENT_DELETED, 1)
EVT_RICHTEXT_STYLE_CHANGED = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_STYLE_CHANGED, 1)
EVT_RICHTEXT_SELECTION_CHANGED = wx.PyEventBinder( wxEVT_COMMAND_RICHTEXT_SELECTION_CHANGED, 1)    
}


class wxRichTextEvent : public wxNotifyEvent
{
public:
    wxRichTextEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);

    int GetPosition() const;
    void SetPosition(int n);

    int GetFlags() const;
    void SetFlags(int flags);

    wxRichTextStyleSheet* GetOldStyleSheet() const;
    void SetOldStyleSheet(wxRichTextStyleSheet* sheet);

    wxRichTextStyleSheet* GetNewStyleSheet() const;
    void SetNewStyleSheet(wxRichTextStyleSheet* sheet);

    const wxRichTextRange& GetRange() const;
    void SetRange(const wxRichTextRange& range);

    wxChar GetCharacter() const;
    void SetCharacter(wxChar ch);

    
    %property(Flags, GetFlags, SetFlags);
    %property(Index, GetPosition, SetPosition);
    %property(OldStyleSheet, GetOldStyleSheet, SetOldStyleSheet);
    %property(NewStyleSheet, GetNewStyleSheet, SetNewStyleSheet);
    %property(Range, GetRange, SetRange);
    %property(Character, GetCharacter, SetCharacter);
};


//---------------------------------------------------------------------------
