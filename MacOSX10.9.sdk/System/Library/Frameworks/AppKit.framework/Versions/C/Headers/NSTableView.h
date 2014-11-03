/*
    NSTableView.h
    Application Kit
    Copyright (c) 1995-2013, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSDragging.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSTextView.h>

@class NSTableHeaderView, NSTableColumn, NSMutableArray, NSDictionary, NSIndexSet, NSMutableIndexSet, NSTableRowView, NSNib;

@protocol NSTableViewDelegate, NSTableViewDataSource;

typedef struct __TvFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        allowsColumnReordering:1;
    unsigned int        allowsColumnResizing:1;
    unsigned int        _available:1;
    unsigned int        allowsEmptySelection:1;
    unsigned int        allowsMultipleSelection:1;
    unsigned int        allowsColumnSelection:1;
    unsigned int        selectionType:2;
    unsigned int        allowGapRow:1;
    unsigned int        compareWidthWithSuperview:2;
    unsigned int        delegateWillDisplayCell:1;
    unsigned int        delegateShouldEditTableColumn:1;
    unsigned int        delegateShouldSelectRow:1;
    unsigned int        delegateShouldSelectTableColumn:1;
    unsigned int        delegateSelectionShouldChangeInTableView:1;
    unsigned int        oldAutoresizesAllColumnsToFit:1;
    unsigned int        dataSourceSetObjectValue:1;
    unsigned int        selectionPostingDisableCount:7;
    unsigned int        movedPostingDisableCount:6;
    unsigned int        refusesFirstResponder:1;
#else
    unsigned int        refusesFirstResponder:1;
    unsigned int        movedPostingDisableCount:6;
    unsigned int        selectionPostingDisableCount:7;
    unsigned int        dataSourceSetObjectValue:1;
    unsigned int        oldAutoresizesAllColumnsToFit:1;
    unsigned int        delegateSelectionShouldChangeInTableView:1;
    unsigned int        delegateShouldSelectTableColumn:1;
    unsigned int        delegateShouldSelectRow:1;
    unsigned int        delegateShouldEditTableColumn:1;
    unsigned int        delegateWillDisplayCell:1;
    unsigned int        compareWidthWithSuperview:2;
    unsigned int        allowGapRow:1;
    unsigned int        selectionType:2;
    unsigned int        allowsColumnSelection:1;
    unsigned int        allowsMultipleSelection:1;
    unsigned int        allowsEmptySelection:1;
    unsigned int        _available:1;
    unsigned int        allowsColumnResizing:1;
    unsigned int        allowsColumnReordering:1;
#endif
} _TvFlags;

/* In drag and drop, used to specify a dropOperation.  For example, given a table with N rows (numbered with row 0 at the top visually), a row of N-1 and operation of NSTableViewDropOn would specify a drop on the last row.  To specify a drop below the last row, one would use a row of N and NSTableViewDropAbove for the operation.
*/
typedef NS_ENUM(NSUInteger, NSTableViewDropOperation) {
    NSTableViewDropOn,
    NSTableViewDropAbove
};

typedef NS_ENUM(NSUInteger, NSTableViewColumnAutoresizingStyle) {
    /* Turn off column autoresizing
     */
    NSTableViewNoColumnAutoresizing = 0,
    
    /* Autoresize all columns by distributing equal shares of space simultaeously
     */
    NSTableViewUniformColumnAutoresizingStyle,
    
    /* Autoresize each table column one at a time.  Proceed to the next column when
     the current column can no longer be autoresized (when it reaches maximum/minimum size).
     */
    NSTableViewSequentialColumnAutoresizingStyle,        // Start with the last autoresizable column, proceed to the first.
    NSTableViewReverseSequentialColumnAutoresizingStyle, // Start with the first autoresizable column, proceed to the last.
    
    /* Autoresize only one table column one at a time.  When that table column can no longer be
     resized, stop autoresizing.  Normally you should use one of the Sequential autoresizing
     modes instead.
     */
    NSTableViewLastColumnOnlyAutoresizingStyle,
    NSTableViewFirstColumnOnlyAutoresizingStyle
};

/* Grid styles for the gridStyleMask.
 */
typedef NS_OPTIONS(NSUInteger, NSTableViewGridLineStyle) {
    NSTableViewGridNone                    = 0,
    NSTableViewSolidVerticalGridLineMask   = 1 << 0,
    NSTableViewSolidHorizontalGridLineMask = 1 << 1,
    NSTableViewDashedHorizontalGridLineMask NS_ENUM_AVAILABLE_MAC(10_7) = 1 << 3, // Draw the horizontal grid as a dashed line
};

typedef NS_ENUM(NSInteger, NSTableViewRowSizeStyle) {
    /* The table will use the system default layout size: small, medium or large. */
    NSTableViewRowSizeStyleDefault = -1,
    
    /* The table will use the -rowHeight or ask the delegate for a variable row height (if implemented) and cell layout is not changed. */
    NSTableViewRowSizeStyleCustom = 0,
    
    /* The table will use a row height specified for a small/medium or large table.
     It is required that all sizes be fully tested and supported if NSTableViewRowSizeStyleCustom is not used.
     Some standard Aqua metrics may be applied to cells based on the current size. */
    NSTableViewRowSizeStyleSmall = 1,
    NSTableViewRowSizeStyleMedium = 2,
    NSTableViewRowSizeStyleLarge = 3,
} NS_ENUM_AVAILABLE_MAC(10_7);

typedef NS_ENUM(NSInteger, NSTableViewSelectionHighlightStyle) {
    /* The highlight style to show no highlight at all. Available in MacOS 10.6 and higher.
     */
    NSTableViewSelectionHighlightStyleNone NS_ENUM_AVAILABLE_MAC(10_6) = -1,
    
    /* The regular highlight style of NSTableView. On the current OS, a light blue ([NSColor alternateSelectedControlColor]) or light gray color ([NSColor secondarySelectedControlColor]) is used to highlight selected rows.
     */
    NSTableViewSelectionHighlightStyleRegular = 0,
    
    /* The source list style of NSTableView. On the current OS, a light blue gradient is used to highlight selected rows. Note: Cells that have a drawsBackground property should have it set to NO. Otherwise, they will draw over the highlighting that NSTableView does. Setting this style will have the side effect of setting the background color to the "source list" background color. Additionally in NSOutlineView, the following properties are changed to get the standard "source list" look: indentationPerLevel, rowHeight and intercellSpacing. After calling setSelectionHighlightStyle: one can change any of the other properties as required.
     */
    NSTableViewSelectionHighlightStyleSourceList = 1,
};


typedef NS_ENUM(NSInteger, NSTableViewDraggingDestinationFeedbackStyle) {
    /* Provides no feedback when the user drags over the table view. This option exists to allow subclasses to implement their dragging destination highlighting, or to make it not show anything all.
     */
    NSTableViewDraggingDestinationFeedbackStyleNone = -1,
    
    /* Draws a solid round-rect background on drop target rows, and an insertion marker between rows. This style should be used in most cases.
     */
    NSTableViewDraggingDestinationFeedbackStyleRegular = 0,
    
    /* Draws an outline on drop target rows, and an insertion marker between rows. This style will automatically be set for source lists when [table setSelectionHighlightStyle:NSTableViewSelectionHighlightStyleSourceList] is called, as it is the standard look for Source Lists, but may be used in other areas as needed.
     */
    NSTableViewDraggingDestinationFeedbackStyleSourceList = 1,
    
    /* Provides a gap insertion when dragging over the table. Note that this style is only officially supported for View Based TableViews, but may partially work in Cell Based TableViews. The decision to use the gap style (compared to another style) can be made in tableView:draggingSession:willBeginAtPoint:forRowIndexes:, or it can dynamically be changed.
     */
    NSTableViewDraggingDestinationFeedbackStyleGap NS_ENUM_AVAILABLE_MAC(10_9) = 2,
    
} NS_ENUM_AVAILABLE_MAC(10_6);

@interface NSTableView : NSControl <NSUserInterfaceValidations, NSTextViewDelegate, NSDraggingSource>
{
    /* All instance variables are private */
    NSTableHeaderView   *_headerView;
    NSView              *_cornerView;
    NSMutableArray      *_tableColumns;
    NSCell              *_editingCell;
    id                  _delegate;
    id                  _dataSource;
    NSSize              _intercellSpacing;
    CGFloat             _rowHeight;
    NSInteger           _lastSelectedColumn;
    NSInteger           _lastSelectedRow;
    NSInteger           _editingRow;
    NSInteger           _editingColumn;
    NSMutableIndexSet   *_selectedColumns;
    NSMutableIndexSet   *_selectedRows;
    id                  _columnDragInfoX;
    NSColor             *_backgroundColor;
    NSColor             *_gridColor;
    id                  _rowDataX;
    id                  _target;
    SEL                 _action;
    SEL                 _doubleAction;
    NSRect              _rectOfLastColumn;
    NSInteger           _lastCachedRectColumn;
    NSRect              _rectOfLastRow; // UNUSED and will be removed
    NSInteger           _lastCachedRectRow; // UNUSED and will be removed
    _TvFlags            _tvFlags;
    id                  _reserved;
}

/* Get and set the dataSource. The dataSource can implement methods in the protocol NSTableViewDataSource. Some methods are required, unless bindings are used, in which case they are optional. The dataSource is a weak reference (non retained) in non garbage collected applications. Under garbage collected apps, it is a strong reference. The default value is 'nil'.
 */
- (void)setDataSource:(id <NSTableViewDataSource>)aSource;
- (id <NSTableViewDataSource>)dataSource;

/* Get and set the delegate. The delegate can implement methods in the protocol NSTableViewDelegate. All delegate methods are optional. The delegate is a weak reference (non retained) in non garbage collected applications. Under garbage collected apps, it is a strong reference. The default value is 'nil'.
 */
- (void)setDelegate:(id <NSTableViewDelegate>)delegate;
- (id <NSTableViewDelegate>)delegate;

/* Get and set the headerView. Calling -setHeaderView:nil will remove the headerView. Calling -setHeaderView: may have the side effect of tiling the enclosingScrollView to accommodate the size change. The default value is a new NSTableHeaderView instance.
 */
- (void)setHeaderView:(NSTableHeaderView *)headerView;
- (NSTableHeaderView *)headerView;

/* Get and set the cornerView. The cornerView is the view that appears directly to the right of the headerView above the vertical NSScroller. The scroller must be present for the cornerView to be shown. Calling -setCornerView: may have the side effect of tiling the enclosingScrollView to accomodate the size change. The default value is an internal class that properly fills in the corner.
 */
- (void)setCornerView:(NSView *)cornerView;
- (NSView *)cornerView;

/* Get and set the allowsColumnReordering. Controls whether or not columns can be drag-reordered. The default value is YES.
 */
- (void)setAllowsColumnReordering:(BOOL)flag;
- (BOOL)allowsColumnReordering;

/* Get and set the allowsColumnResizing. Controls whether the user can attempt to resize columns by dragging between headers. If flag is YES the user can resize columns; if flag is NO the user can't. Columns can only be resized if a column allows user resizing. See -[NSTableColumn setResizingMask:] for more details. You can always change columns programmatically regardless of this setting. The default value is YES. 
 */
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;

/* Get and set the columnAutoresizingStyle. This controls resizing in response to a tableView frame size change, usually done by dragging a window larger that has an auto-resized tableView inside it. The default value is NSTableViewLastColumnOnlyAutoresizingStyle.
   Compatability Note: This method replaces -setAutoresizesAllColumnsToFit: on 10.4 and higher.
 */
- (void)setColumnAutoresizingStyle:(NSTableViewColumnAutoresizingStyle)style;
- (NSTableViewColumnAutoresizingStyle)columnAutoresizingStyle;

/* Get and set the gridStyleMask. Values can be bitwise or'ed together, however, only one horizontal style can be used at a time. The default value is NSTableViewGridNone. 
 */
- (void)setGridStyleMask:(NSTableViewGridLineStyle)gridStyle;
- (NSTableViewGridLineStyle)gridStyleMask;

/* Get and set the intercellSpacing. This is the spacing that appears between cells. The default value is NSMakeSize(3, 2).
 */
- (void)setIntercellSpacing:(NSSize)aSize;
- (NSSize)intercellSpacing;

/* Get and set the use of alternatingRowBackgroundColors. This configures the table to use either the standard alternating row colors, or a solid color for its background. The default value is NO.
 */
- (void)setUsesAlternatingRowBackgroundColors:(BOOL)useAlternatingRowColors;
- (BOOL)usesAlternatingRowBackgroundColors;

/* Get and set the backgroundColor. On Mac OS 10.5 and higher, the alpha portion of 'color' is properly used when drawing the backgroundColor. To have a transparent tableView, set the backgroundColor to [NSColor clearColor], and set the enclosing NSScrollView to not draw its background with: [[tableView enclosingScrollView] setDrawsBackground:NO]. NSTableView uses NSCompositeSourceOver when drawing the background color. The default value is [NSColor controlBackgroundColor]. 
 */
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

/* Get and set the gridColor. This value is only used when the gridStyleMask is not equal to NSTableViewGridNone. The default value is [NSColor gridColor].
 */
- (void)setGridColor:(NSColor *)color;
- (NSColor *)gridColor;

/* Get and set the rowSizeStyle. The default value is NSTableViewRowSizeStyleCustom, which allows the table to behave as it traditionally has. If the value is not NSTableViewRowSizeStyleCustom, then all three sizes must be properly supported by the view or cell. Changing the rowSizeStyle will automatically update the rowHeight if NSTableViewRowSizeStyleCustom is not used, and the rowHeight should not be changed. It is a recommendation that the variable row height delegate method should generally NOT be implemented when using a non-custom style, and instead the standard provided row heights should be used.
 */
- (void)setRowSizeStyle:(NSTableViewRowSizeStyle)rowSizeStyle NS_AVAILABLE_MAC(10_7);
- (NSTableViewRowSizeStyle)rowSizeStyle NS_AVAILABLE_MAC(10_7);

/* Returns the effective row size style for the table. If the rowSizeStyle is NSTableViewRowSizeStyleDefault, then this method returns the default size for this particular table.
 */
- (NSTableViewRowSizeStyle)effectiveRowSizeStyle NS_AVAILABLE_MAC(10_7);


/* Get and set the rowHeight. The value must be greater than 0. Calling -setRowHeight: with a non-pixel aligning (fractional) value will be forced to a pixel aligning (integral) value. For variable row height tableViews (ones that have the delegate implement -tableView:heightOfRow:), -rowHeight will be used to draw alternating rows past the last row in the tableView. The actual -rectOfRow: is equal to the -rowHeight plus the intercellSpacing.height. The default value is 17.0 for applications linked on 10.5 and higher (the height acceptable for [NSFont systemFontSize]). The default value is 16.0 for 10.4 and lower.
 */
- (void)setRowHeight:(CGFloat)rowHeight;
- (CGFloat)rowHeight;

/* If the delegate implements -tableView:heightOfRow:, this method immediately re-tiles the table view using row heights it provides.
*/
- (void)noteHeightOfRowsWithIndexesChanged:(NSIndexSet *)indexSet;

/* Returns a reference to the array of NSTableColumn instances in the NSTableView. Includes columns that are -isHidden. It is recommended to make a copy of the array if you are going to manipulate the NSTableView by using -addTableColumn:, -removeTableColumn: or -moveColumn:toColumn:.
 */
- (NSArray *)tableColumns;

/* Simply a cover method to return the number of NSTableColumn instances in the NSTableView. Includes columns that are -isHidden.
 */
- (NSInteger)numberOfColumns;

/* Returns the numberOfRows. It may call to the dataSource to aquire the count. numberOfRows will return 0 if there are no visible columns.
 */
- (NSInteger)numberOfRows;

/* Adds 'tableColumn' to the end of the -tableColumns array and retiles the tableView. 'tableColumn' must be non-nil, otherwise an exception will be raised.
 */
- (void)addTableColumn:(NSTableColumn *)tableColumn;

/* Removes 'tableColumn' from the -tableColumns array and retiles the tableView.
 */
- (void)removeTableColumn:(NSTableColumn *)tableColumn;

/* Moves the the tableColumn at 'oldIndex' to 'newIndex'. 'oldIndex' and 'newIndex' must be in the range: 0 to [tableView numberOfColumns]-1, otherwise an exception will be raised.
 */
- (void)moveColumn:(NSInteger)oldIndex toColumn:(NSInteger)newIndex;

/* Returns the first index of the NSTableColumn instance with the -identifier that isEqual to 'identifier'. Returns -1 if 'identifier' can not be found. In 10.7, the identifier was changed from NSString to id.
 */
- (NSInteger)columnWithIdentifier:(NSString *)identifier;

/* Returns the first NSTableColumn instance with the -identifier that isEqual to 'identifier'. Returns nil if 'identifier' can not be found. In 10.7, the identifier was changed from NSString to id.
 */
- (NSTableColumn *)tableColumnWithIdentifier:(NSString *)identifier;

/* Causes the table to tile in size appropriate for the content. This method will be called automatically when necessary, and generally does not need to be called.
 */
- (void)tile;
- (void)sizeToFit;
- (void)sizeLastColumnToFit;

- (void)scrollRowToVisible:(NSInteger)row;
- (void)scrollColumnToVisible:(NSInteger)column;

/* Reloads the table.
   View Based TableView: This drops all known views, and row heights, and lazily reloads all information. The selected rows are not maintained. To properly maintain selection, use the insert/remove/move API.
 */
- (void)reloadData;

/* 
 Cell Based TableView: This method tells the table that there may be more (or less) rows available and to reload state based on that information.
 View Based TableView: This method can only be used to increase or decrease the number of rows in the table. The table will query the datasource for the new number of rows, and properly insert (or remove) rows at the end of the table as necessary with an animation. This method does *NOT* work for NSOutlineView, and should not be called.
 */
- (void)noteNumberOfRowsChanged;

/* Updates a particular row of cells for a given set of 'rowIndexes' in 'columnIndexes'. For cells that are visible, appropriate dataSource and delegate methods will be called and the cells will be redrawn. For tables that support variable row heights, the row height will not be re-queried from the delegate; -noteHeightOfRowsWithIndexesChanged: should be used if a row height change is required.
 */
- (void)reloadDataForRowIndexes:(NSIndexSet *)rowIndexes columnIndexes:(NSIndexSet *)columnIndexes NS_AVAILABLE_MAC(10_6);

/* 
 Cell Based TableView: Returns the column and row that is being edited. editedRow will be -1 if there is no editing session happening. editedColumn will be -1 if there is no editing session, or the currently edited row is a "full width" row.
 View Based TableView: Not applicable. Subviews are responsible for editing.
 */
- (NSInteger)editedColumn;
- (NSInteger)editedRow;

- (NSInteger)clickedColumn;
- (NSInteger)clickedRow;

- (void)setDoubleAction:(SEL)aSelector;
- (SEL)doubleAction;

/* Sorting Support
    The array of sort descriptors is archived.  Sort descriptors will persist along with other column information if an -autosaveName is set. Calling -setSortDescriptors: may have the side effect of calling -tableView:sortDescriptorsDidChange: on the -dataSource/
*/
- (void)setSortDescriptors:(NSArray *)array;
- (NSArray *)sortDescriptors;

/* Support for little "indicator" images in table header cells.
*/
- (void)setIndicatorImage:(NSImage *)anImage inTableColumn:(NSTableColumn *)tableColumn;
- (NSImage *)indicatorImageInTableColumn:(NSTableColumn *)tableColumn;

/* Support for highlightable column header, for use with row selection.
*/
- (void)setHighlightedTableColumn:(NSTableColumn *)tableColumn;
- (NSTableColumn *)highlightedTableColumn;

#pragma mark -
#pragma mark ***** Drag and Drop *****

/* Get and set verticalMotionCanBeginDrag. If -verticalMotionCanBeginDrag is YES, then click + a vertical drag of the mouse will drag the clicked item(s). If NO, it will do a "drag select". The default value is YES.
 */
- (void)setVerticalMotionCanBeginDrag:(BOOL)flag;
- (BOOL)verticalMotionCanBeginDrag;

/* The return value indicates whether the receiver can attempt to initiate a row drag at 'mouseDownPoint'. Return NO to disallow initiating drags at the given location. 
    
    For applications linked on and after Leopard, NSCell hit testing will determine if a row can be dragged or not. Custom cells should properly implement [NSCell(NSCellHitTest) hitTestForEvent:inRect:ofView]; see NSCell.h for more information. NSTableView will not begin a drag if cell returns NSCellHitTrackableArea (ie: NSButtonCells).
*/
- (BOOL)canDragRowsWithIndexes:(NSIndexSet *)rowIndexes atPoint:(NSPoint)mouseDownPoint;

/* This method computes and returns an image to use for dragging.  Override this to return a custom image.  'dragRows' represents the rows participating in the drag.  'tableColumns' represent the columns that should be in the output image.  Note that drawing may be clipped to the visible rows, and columns.  'dragEvent' is a reference to the mouse down event that began the drag.  'dragImageOffset' is an in/out parameter.  This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image.  A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse.

   Compatability Note: This method replaces dragImageForRows:event:dragImageOffset:.  If present, this is used instead of the deprecated method.
*/
- (NSImage *)dragImageForRowsWithIndexes:(NSIndexSet *)dragRows tableColumns:(NSArray *)tableColumns event:(NSEvent*)dragEvent offset:(NSPointPointer)dragImageOffset;

/* Configures the default value returned from -draggingSourceOperationMaskForLocal:.  An isLocal value of YES indicates that 'mask' applies when the destination object is in the same application.  A isLocal value of NO indicates that 'mask' applies when the destination object in an application outside the receiver's application.  NSTableView will archive the values you set for each isLocal setting.
*/
- (void)setDraggingSourceOperationMask:(NSDragOperation)mask forLocal:(BOOL)isLocal;

/* To be used from validateDrop: if you wish to "re-target" the proposed drop. To specify a drop on the second row, one would specify row=2, and dropOperation=NSTableViewDropOn. To specify a drop below the last row, one would specify row=[tableView numberOfRows], and dropOperation=NSTableViewDropAbove. To specify a drop on the entire tableview, one would specify row=-1 and dropOperation=NSTableViewDropOn.
*/
- (void)setDropRow:(NSInteger)row dropOperation:(NSTableViewDropOperation)dropOperation;

#pragma mark -
#pragma mark ***** Selection *****

/* Get and set allowsMultipleSelection. If -allowsMultipleSelection is YES, multiple items can be selected in various ways (modifier-clicking items, shift-arrow selection extending, etc). The default value is NO.
 */
- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;

/* Get and set allowsEmptySelection. If -allowsEmptySelection is YES, all rows can be deselected by the user. Otherwise, it is enforced that one row must be left selected at any given time. The default value is YES.
 */
- (void)setAllowsEmptySelection:(BOOL)flag;
- (BOOL)allowsEmptySelection;

/* Get and set allowsColumnSelection. If -allowsColumnSelection is YES, clicking on column headers can select that column (which is reflected in -selectedColumnIndexes). The default value is NO.
 */
- (void)setAllowsColumnSelection:(BOOL)flag;
- (BOOL)allowsColumnSelection;

- (void)selectAll:(id)sender;

- (void)deselectAll:(id)sender;

/* Sets the column selection using the indexes.  Selection is set/extended based on the extend flag. 
   Compatability Note: This method replaces selectColumn:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectColumn:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectColumnIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectColumnIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend;

/* Sets the row selection using 'indexes'. Selection is set/extended based on the extend flag. On 10.5 and greater, selectRowIndexes:byExtendingSelection: will allow you to progrmatically select more than one index, regardless of the allowsMultipleSelection and allowsEmptySelection options set on the table.
 
   View Based TableViews: This method is animatable by using the animator proxy. IE: [tableView.animator selectRowIndexes:.. byExtendingSelection:..];
 
   Compatability Note: This method replaces selectRow:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectRow:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectRowIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectRowIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend;

- (NSIndexSet *)selectedColumnIndexes;
- (NSIndexSet *)selectedRowIndexes;

- (void)deselectColumn:(NSInteger)column;
- (void)deselectRow:(NSInteger)row;
- (NSInteger)selectedColumn;
- (NSInteger)selectedRow;
- (BOOL)isColumnSelected:(NSInteger)column;
- (BOOL)isRowSelected:(NSInteger)row;
- (NSInteger)numberOfSelectedColumns;
- (NSInteger)numberOfSelectedRows;

#pragma mark -
#pragma mark ***** Properties *****

/* Allow type selection in this tableView. The default value is YES.
 */

- (BOOL)allowsTypeSelect NS_AVAILABLE_MAC(10_5);
- (void)setAllowsTypeSelect:(BOOL)value NS_AVAILABLE_MAC(10_5);

/* Gets and sets the current selection highlight style. The default value is NSTableViewSelectionHighlightStyleRegular.
 */
- (NSTableViewSelectionHighlightStyle)selectionHighlightStyle NS_AVAILABLE_MAC(10_5);
- (void)setSelectionHighlightStyle:(NSTableViewSelectionHighlightStyle)selectionHighlightStyle NS_AVAILABLE_MAC(10_5);

/* Gets and sets the dragging destination feedback style. The default value is NSTableViewDraggingDestinationFeedbackStyleRegular for all tables. However, changing the -selectionHighlightStyle to NSTableViewSelectionHighlightStyleSourceList will automatically change the -draggingDestinationFeedbackStyle to NSTableViewDraggingDestinationFeedbackStyleSourceList.
 */
- (void)setDraggingDestinationFeedbackStyle:(NSTableViewDraggingDestinationFeedbackStyle)style NS_AVAILABLE_MAC(10_6);
- (NSTableViewDraggingDestinationFeedbackStyle)draggingDestinationFeedbackStyle NS_AVAILABLE_MAC(10_6);

/* Returns the rectangle for 'column'. Returns NSZeroRect if the NSTableColumn at 'column' has -isHidden == YES, or if 'column' is less than 0, or if 'column' is greater than or equal to the number of columns in the NSTableView.
 */
- (NSRect)rectOfColumn:(NSInteger)column;

/* Returns the rectange for 'row'. If 'row' is < 0 or >= [self numberOfRows], then NSZeroRect is returned.
 */
- (NSRect)rectOfRow:(NSInteger)row;

/* Returns the indexes for columns in 'rect'. NSTableColumns which have -isHidden == YES are not returned. If 'rect' is empty, no indexes will be returned. Introduced in Mac OS 10.5. 
 */
- (NSIndexSet *)columnIndexesInRect:(NSRect)rect NS_AVAILABLE_MAC(10_5);

/* Returns the range of rows in 'rect'. If 'rect' is empty, or if there are no rows, an empty range will be returned. If 'rect' is outside of -[NSTableView bounds], 'rect' will be intersected to only look in the bounds.
 */
- (NSRange)rowsInRect:(NSRect)rect;

/* Returns the column index at 'point', or -1 if 'point' is outside of all table columns.
 */
- (NSInteger)columnAtPoint:(NSPoint)point;

- (NSInteger)rowAtPoint:(NSPoint)point;

/* Returns the frame of the cell at 'row' / 'column'. If the 'row' is a "full width" row, the frame returned will be equal to the width of the row. If the NSTableColumn at 'column' has -isHidden == YES, or if the values are outside acceptable ranges, NSZeroRect is returned.
 */
- (NSRect)frameOfCellAtColumn:(NSInteger)column row:(NSInteger)row;

/* Returns the fully prepared cell that the view will normally use for drawing or any processing. The value for the cell will be correctly set, and the delegate method 'willDisplayCell:' will have be called. You can override this method to do any additional setting up of the cell that is required, or call it to retrieve a cell that will have its contents properly set for the particular column and row.
*/
- (NSCell *)preparedCellAtColumn:(NSInteger)column row:(NSInteger)row NS_AVAILABLE_MAC(10_5);

/*
 * Text delegate methods. These are only applicable for the "Cell Based" NSTableView.
 */
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;

/*
 * Persistence methods
 */
- (void)setAutosaveName:(NSString *)name;
- (NSString *)autosaveName;

/* On Mac OS 10.4 and higher, the NSTableColumn width and location is saved. On Mac OS 10.5 and higher, the NSTableColumn 'isHidden' state is also saved. The 'autosaveName' must be set for 'autosaveTableColumns' to take effect.
*/
- (void)setAutosaveTableColumns:(BOOL)save;
- (BOOL)autosaveTableColumns;

/* On Mac OS 10.5 and higher, NSTableView supports sub-cell focusing. The following set of methods control the focusing.
 */

/* Cell Based TableView: Returns YES if the fully prepared 'cell' at 'row'/'column' can be made the focused cell or not. By default, only cells that are enabled can be focused. In addition, if the cell is an NSTextFieldCell, it will can only be focused if it is selectable or editable, and the delegate responds YES to -table:shouldEditTableColumn:row:. Subclasses can override this to further control what cells can and cannot be made focused.
 */
- (BOOL)shouldFocusCell:(NSCell *)cell atColumn:(NSInteger)column row:(NSInteger)row NS_AVAILABLE_MAC(10_6);

/* Cell Based TableView: Returns the focused column that the user has tabbed to, or -1 if there is no focused column. The focus interaction will always be on [tableView selectedRow]. If the selectedRow is a "full width" cell, then focusedColumn will return "1" if focused.
 */
- (NSInteger)focusedColumn NS_AVAILABLE_MAC(10_5);

/* Cell Based TableView: Sets the focused column, redisplays the old 'focusedColumn', and redisplays the new 'focusedColumn' (if required). The focused column has a focus ring drawn around the [tableView selectedRow] that intersects with 'focusedColumn'. A value of -1 indicates there is no focused column. You should not override this method.
 */
- (void)setFocusedColumn:(NSInteger)focusedColumn NS_AVAILABLE_MAC(10_6);

/* Cell Based TableView: Acquires the preparedCell located at 'column'/'row', copies it, invokes performClick: or performClickWithFrame:inView: (for NSPopUpButtonCell), and then updates the datasource - if required. This method does not do any checks to see if the cell is enabled.
 */
- (void)performClickOnCellAtColumn:(NSInteger)column row:(NSInteger)row NS_AVAILABLE_MAC(10_6);

/* View Based TableView: This method attempts to make the view at 'column/row' the first responder, which will begin editing if the view supports editing.
   Cell Based TableView: This method edits the NSCell located at 'column/row' by calling the following NSCell method:
 
 - (void)editWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject event:(NSEvent *)theEvent;
 
 or, if 'select' is YES:
 
 - (void)selectWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject start:(NSInteger)selStart length:(NSInteger)selLength;
 
 */
- (void)editColumn:(NSInteger)column row:(NSInteger)row withEvent:(NSEvent *)theEvent select:(BOOL)select;

/* View Based TableView: This method should not be subclassed or overridden for a "View Based TableView". Instead, row drawing customization can be done by subclassing NSTableRowView.
   Cell Based TableView: This method can be overriden to customize drawing for 'row'. 
 */
- (void)drawRow:(NSInteger)row clipRect:(NSRect)clipRect;
 
/* View Based TableView: This method should not be subclassed or overridden for a "View Based TableView". Instead, row drawing customization can be done by subclassing NSTableRowView.
 Cell Based TableView: This method can be overriden to customize selection highlighting. 
 */
- (void)highlightSelectionInClipRect:(NSRect)clipRect;

/* Override to customize grid drawing.
 */
- (void)drawGridInClipRect:(NSRect)clipRect;

/* Override to customize background drawing.
 */
- (void)drawBackgroundInClipRect:(NSRect)clipRect;

#pragma mark -
#pragma mark ***** View Based TableView Support *****

/* View Based TableView: Access to a view (or row view) for a particular 'row' / 'column'. Returns 'nil' if there is no view at that location. An exception will be thrown if 'row' is not within the numberOfRows. The returned result is always an 'id' for easy assignment to local types, however, -viewAtColumn:row: will always return an NSView, and rowViewAtRow: will always return an NSTableRowView (or subclass thereof). The returned result should generally not be held onto for longer than the current run loop cycle.
 
 This method will first attempt to return a currently displayed view in the visible area. If there is no visible view, and makeIfNecessary is YES, a prepared temporary view is returned. If makeIfNecessary is NO, and the view is not visible, nil will be returned. In general, makeIfNecessary should be YES if you require a resulting view, and NO if you only want to update properties on a view only if it is available (generally this means it is visible).
 */

- (id)viewAtColumn:(NSInteger)column row:(NSInteger)row makeIfNecessary:(BOOL)makeIfNecessary NS_AVAILABLE_MAC(10_7);
- (id)rowViewAtRow:(NSInteger)row makeIfNecessary:(BOOL)makeIfNecessary NS_AVAILABLE_MAC(10_7);

/* View Based TableView: Access to the row/column for a particular view. Returns -1 if the view is not an instance of, or a subview of  NSTableRowView. This is typically needed in the action method for an NSButton (or NSControl) to find out what row (and column) the action should be performed on. The implementation is O(n) where n is the number of visible rows, so this method should generally not be called within a loop.
 */
- (NSInteger)rowForView:(NSView *)view NS_AVAILABLE_MAC(10_7);
- (NSInteger)columnForView:(NSView *)view NS_AVAILABLE_MAC(10_7);

/* View Based TableView: Returns an autoreleased view with a particular 'identifier'. Typically the 'identifier' is associated with a particular "cell view" in IB. The TableView will automatically instantiate the embedded view with the provided owner. This method will typically be called by the delegate in -viewForTableColumn:row:, but it can also be overridden to provide custom views for a particular 'identifier'. This method may also return a reused view with the same 'identifier' that was no longer available on screen. 'identifier' can not be nil. Note that 'owner' will get an 'awakeFromNib:' call each time the object is instantiated.
 */ 
- (id)makeViewWithIdentifier:(NSString *)identifier owner:(id)owner NS_AVAILABLE_MAC(10_7);

#if NS_BLOCKS_AVAILABLE
/* Enumerates all available NSTableRowViews. This includes all views in the -visibleRect, however, it may also include ones that are "in flight" due to animations or other various attributes of the table.
 */
- (void)enumerateAvailableRowViewsUsingBlock:(void (^)(NSTableRowView *rowView, NSInteger row))handler NS_AVAILABLE_MAC(10_7);
#endif 

/* View Based TableView: Group rows can optionally appear floating. Group rows are rows that the delegate responds YES to tableView:isGroupRow:. NSOutlineView will only float expandable group rows that are expanded. The default value is YES. This property is encoded and decoded in the nib.
 */
- (BOOL)floatsGroupRows NS_AVAILABLE_MAC(10_7);
- (void)setFloatsGroupRows:(BOOL)value NS_AVAILABLE_MAC(10_7);

#pragma mark -
#pragma mark ***** Insert / Remove / Delete Rows *****

/* NSTableView Animation Options */

typedef NS_OPTIONS(NSUInteger, NSTableViewAnimationOptions) {
/* Use to not apply any animation effect (the default). Specifying any animation from the effect groups below negates this effect.
 */
    NSTableViewAnimationEffectNone = 0x0,

/* Row animation Effect (optional). The effect can be combined with other any NSTableViewRowAnimationSlide* option.
 */
    NSTableViewAnimationEffectFade = 0x1, // Fades in new rows.
    NSTableViewAnimationEffectGap = 0x2, // Creates a gap for newly inserted rows. This is useful for drag and drop animations that animate to a newly opened gap and should be used in -tableView:acceptDrop:row:dropOperation:.

/* Row Animation Sliding (optional). Currently only one option from this group may be specified at a time.
 */
    NSTableViewAnimationSlideUp    = 0x10, // Animates a row in or out by sliding upward.
    NSTableViewAnimationSlideDown  = 0x20, // Animates a row in or out by sliding downward.
    NSTableViewAnimationSlideLeft  = 0x30, // Animates a row in by sliding from the left. Animates a row out by sliding towards the left.
    NSTableViewAnimationSlideRight = 0x40, // Animates a row in by sliding from the right. Animates a row out by sliding towards the right.
} NS_ENUM_AVAILABLE_MAC(10_7);

    
/* View Based TableView: Multiple row changes (inserts/deletes/moves/scrolling) can be animated simultaneously by surrounding calls around a beginUpdates/endUpdates pair. When changing rows, the prior state before -beginUpdates is the starting point assumed for all deletion and move calls. Calls are nestable. -selectedRowIndexes is properly maintained based on the series of inserts/deletes/moves. If a selected row is deleted, a selection changed notification will happen after endUpdates is called. It is not necessary to call beginUpdates/endUpdates if only one insertion/deletion/move is happening. Note that these methods should be called to reflect changes in your model; they do not make any underlying model changes.
 
   Cell Based TableView: Any row modifications must first be wrapped in a -beginUpdates/-endUpdates block -- this is required to properly maintain state and to allow animations to happen.
 */
- (void)beginUpdates NS_AVAILABLE_MAC(10_7);
- (void)endUpdates NS_AVAILABLE_MAC(10_7);

/* Inserts a new rows located at the final positions passed to by 'indexes'. This is similar to NSMutableArray's -insertObjects:atIndexes:  The -numberOfRows in the TableView will automatically be increased by the count in 'indexes'. Calling this method multiple times within the same beginUpdates/endUpdates block is allowed, and changes are processed incrementally. This method should not be called for NSOutlineView (use -insertItemsAtIndexes:inParent:withAnimation: instead). The "Cell Based TableView" must first call -beginUpdates before calling this method.
 */
- (void)insertRowsAtIndexes:(NSIndexSet *)indexes withAnimation:(NSTableViewAnimationOptions)animationOptions NS_AVAILABLE_MAC(10_7);

/* Removes a row currently at each row in 'indexes'. This is similar to NSMutableArray's -removeObjectsAtIndexes:. The row indexes should be with respect to the current state displayed in the TableView, and not the final state (since the rows do not exist in the final state). The -numberOfRows in the TableView will automatically be decreased by the count in 'indexes'. Calling this method multiple times within the same beginUpdates/endUpdates block is allowed, and changes are processed incrementally. This method should not be called for NSOutlineView (use -removeItemsAtIndexes:inParent:withAnimation: instead). The "Cell Based TableView" must first call -beginUpdates before calling this method. 
 */
- (void)removeRowsAtIndexes:(NSIndexSet *)indexes withAnimation:(NSTableViewAnimationOptions)animationOptions NS_AVAILABLE_MAC(10_7);

/* Moves a row from the prior 'oldIndex' to 'newIndex' in an animated fashion (if needed). This is similar to removing a row at 'oldIndex' and inserting it back at 'newIndex', except the same view is used and simply has its position updated to the new location. This method can be called multiple times within the same beginUpdates/endUpdates block. This method should not be called for NSOutlineView (use -moveItemAtIndex:inParent:toIndex:inParent: instead). The "Cell Based TableView" must first call -beginUpdates before calling this method. 
 */
- (void)moveRowAtIndex:(NSInteger)oldIndex toIndex:(NSInteger)newIndex NS_AVAILABLE_MAC(10_7);

/* View Based TableView: Registers (or associates) the 'nib' with 'identifier' so the table can instantiate views from it when a view with 'identifier' is requested. Generally, this means one calls -makeViewWithIdentifier:'identifier' owner:, and there was no NIB created at design time for this particular table view that could be found. This allows dynamic loading of nibs that can be associated with the table. To remove a previously associated NIB for a given identifier, pass in 'nil' for the nib value.
 */
- (void)registerNib:(NSNib *)nib forIdentifier:(NSString *)identifier NS_AVAILABLE_MAC(10_8);

/* View Based TableView: Returns a dictionary of all registered nibs. The keys are the identifier, and the value is the NSNib that is registered.
 */
- (NSDictionary *)registeredNibsByIdentifier NS_AVAILABLE_MAC(10_8);

/* View Based TableView: The subclass can implement this method to be alerted when a new 'rowView' has been added to the table. At this point, the subclass can choose to add in extra views, or modify any properties on 'rowView'. Be sure to call 'super'.
 */
- (void)didAddRowView:(NSTableRowView *)rowView forRow:(NSInteger)row NS_AVAILABLE_MAC(10_7);

/* View Based TableView: The subclass can implement this method to be alerted when 'rowView' has been removed from the table. The removed 'rowView' may be reused by the table, so any additionally inserted views should be removed at this point. A 'row' parameter is included. 'row' will be '-1' for rows that are being deleted from the table, and no longer have a valid row, otherwise it will be the valid row that is being removed due to it being moved off screen. Be sure to call 'super'.
 */
- (void)didRemoveRowView:(NSTableRowView *)rowView forRow:(NSInteger)row NS_AVAILABLE_MAC(10_7);

@end

#pragma mark -

@protocol NSTableViewDelegate <NSControlTextEditingDelegate>
@optional

#pragma mark -
#pragma mark ***** View Based TableView Support *****

/* View Based TableView: 
 Non-bindings: This method is required if you wish to turn on the use of NSViews instead of NSCells. The implementation of this method will usually call -[tableView makeViewWithIdentifier:[tableColumn identifier] owner:self] in order to reuse a previous view, or automatically unarchive an associated prototype view for that identifier. The -frame of the returned view is not important, and it will be automatically set by the table. 'tableColumn' will be nil if the row is a group row. Returning nil is acceptable, and a view will not be shown at that location. The view's properties should be properly set up before returning the result.
 
 Bindings: This method is optional if at least one identifier has been associated with the TableView at design time. If this method is not implemented, the table will automatically call -[self makeViewWithIdentifier:[tableColumn identifier] owner:[tableView delegate]] to attempt to reuse a previous view, or automatically unarchive an associated prototype view. If the method is implemented, the developer can setup properties that aren't using bindings.
 
 The autoresizingMask of the returned view will automatically be set to NSViewHeightSizable to resize properly on row height changes.
 */
- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row NS_AVAILABLE_MAC(10_7);

/* View Based TableView: The delegate can optionally implement this method to return a custom NSTableRowView for a particular 'row'. The reuse queue can be used in the same way as documented in tableView:viewForTableColumn:row:. The returned view will have attributes properly set to it before it is added to the tableView. Returning nil is acceptable. If nil is returned, or this method isn't implemented, a regular NSTableRowView will be created and used.
 */
- (NSTableRowView *)tableView:(NSTableView *)tableView rowViewForRow:(NSInteger)row NS_AVAILABLE_MAC(10_7);

/* View Based TableView: Optional: This delegate method can be used to know when a new 'rowView' has been added to the table. At this point, you can choose to add in extra views, or modify any properties on 'rowView'.
 */
- (void)tableView:(NSTableView *)tableView didAddRowView:(NSTableRowView *)rowView forRow:(NSInteger)row NS_AVAILABLE_MAC(10_7);

/* View Based TableView: Optional: This delegate method can be used to know when 'rowView' has been removed from the table. The removed 'rowView' may be reused by the table so any additionally inserted views should be removed at this point. A 'row' parameter is included. 'row' will be '-1' for rows that are being deleted from the table and no longer have a valid row, otherwise it will be the valid row that is being removed due to it being moved off screen.
 */
- (void)tableView:(NSTableView *)tableView didRemoveRowView:(NSTableRowView *)rowView forRow:(NSInteger)row NS_AVAILABLE_MAC(10_7);

#pragma mark -
#pragma mark ***** Cell Based TableView Support *****

/* Allows the delegate to provide further setup for 'cell' in 'tableColumn'/'row'. It is not safe to do drawing inside this method, and you should only setup state for 'cell'.
 */ 
- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
- (BOOL)tableView:(NSTableView *)tableView shouldEditTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Optional - Tool Tip Support
 When the user pauses over a cell, the value returned from this method will be displayed in a tooltip.  'point' represents the current mouse location in view coordinates.  If you don't want a tooltip at that location, return nil or the empty string.  On entry, 'rect' represents the proposed active area of the tooltip.  By default, rect is computed as [cell drawingRectForBounds:cellFrame].  To control the default active area, you can modify the 'rect' parameter.
 */
- (NSString *)tableView:(NSTableView *)tableView toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect tableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row mouseLocation:(NSPoint)mouseLocation;

/* Optional - Expansion ToolTip support
    View Based TableView: This method is not called or used.
    Cell Based TableView: Implement this method and return NO to prevent an expansion tooltip from appearing for a particular cell in a given row and tableColumn. See NSCell.h for more information on expansion tool tips. 
 */
- (BOOL)tableView:(NSTableView *)tableView shouldShowCellExpansionForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row NS_AVAILABLE_MAC(10_5);

/*  Optional - Custom tracking support
 It is possible to control the ability to track a cell or not. Normally, only selectable or selected cells can be tracked. If you implement this method, cells which are not selectable or selected can be tracked, and vice-versa. For instance, this allows you to have an NSButtonCell in a table which does not change the selection, but can still be clicked on and tracked.
 */
- (BOOL)tableView:(NSTableView *)tableView shouldTrackCell:(NSCell *)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row NS_AVAILABLE_MAC(10_5);

/*  Optional - Different cells for each row
 A different data cell can be returned for any particular tableColumn and row, or a cell that will be used for the entire row (a full width cell). The returned cell should properly implement copyWithZone:, since the cell may be copied by NSTableView. If the tableColumn is non-nil, and nil is returned, then the table will use the default cell from [tableColumn dataCellForRow:row].
 
 When each row is being drawn, this method will first be called with a nil tableColumn. At this time, you can return a cell that will be used to draw the entire row, acting like a group. If you do return a cell for the 'nil' tableColumn, be prepared to have the other corresponding datasource and delegate methods to be called with a 'nil' tableColumn value. If don't return a cell, the method will be called once for each tableColumn in the tableView, as usual.
 */
- (NSCell *)tableView:(NSTableView *)tableView dataCellForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row NS_AVAILABLE_MAC(10_5);

#pragma mark -
#pragma mark ***** Common Delegate Methods *****

/* Optional - called whenever the user is about to change the selection. Return NO to prevent the selection from being changed at that time.
 */
- (BOOL)selectionShouldChangeInTableView:(NSTableView *)tableView;

/* Optional - Return YES if 'row' should be selected and NO if it should not. For better performance and better control over the selection, you should use tableView:selectionIndexesForProposedSelection:. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row;

/* Optional - Return a set of new indexes to select when the user changes the selection with the keyboard or mouse. If implemented, this method will be called instead of tableView:shouldSelectRow:. This method may be called multiple times with one new index added to the existing selection to find out if a particular index can be selected when the user is extending the selection with the keyboard or mouse. Note that 'proposedSelectionIndexes' will contain the entire newly suggested selection, and you can return the exsiting selection to avoid changing the selection.
*/
- (NSIndexSet *)tableView:(NSTableView *)tableView selectionIndexesForProposedSelection:(NSIndexSet *)proposedSelectionIndexes NS_AVAILABLE_MAC(10_5);

- (BOOL)tableView:(NSTableView *)tableView shouldSelectTableColumn:(NSTableColumn *)tableColumn;

- (void)tableView:(NSTableView *)tableView mouseDownInHeaderOfTableColumn:(NSTableColumn *)tableColumn;
- (void)tableView:(NSTableView *)tableView didClickTableColumn:(NSTableColumn *)tableColumn;
- (void)tableView:(NSTableView *)tableView didDragTableColumn:(NSTableColumn *)tableColumn;

/* Optional - Variable Row Heights
    Implement this method to support a table with varying row heights. The height returned by this method should not include intercell spacing and must be greater than zero. Performance Considerations: For large tables in particular, you should make sure that this method is efficient. NSTableView may cache the values this method returns, but this should NOT be depended on, as all values may not be cached. To signal a row height change, call -noteHeightOfRowsWithIndexesChanged:. For a given row, the same row height should always be returned until -noteHeightOfRowsWithIndexesChanged: is called, otherwise unpredicable results will happen. NSTableView automatically invalidates its entire row height cache in -reloadData, and -noteNumberOfRowsChanged.
*/
- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row;

/* Optional - Type select support
    Implement this method if you want to control the string that is used for type selection. You may want to change what is searched for based on what is displayed, or simply return nil for that 'tableColumn' or 'row' to not be searched. By default, all cells with text in them are searched. The default value when this delegate method is not implemented is [[tableView preparedCellAtColumn:tableColumn row:row] stringValue], and this value can be returned from the delegate method if desired.
*/
- (NSString *)tableView:(NSTableView *)tableView typeSelectStringForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row NS_AVAILABLE_MAC(10_5);

/* Optional - Type select support
    Implement this method if you want to control how type selection works. Return the first row that matches searchString from within the range of startRow to endRow. It is possible for endRow to be less than startRow if the search will wrap. Return -1 when there is no match. Include startRow as a possible match, but do not include endRow. It is not necessary to implement this method in order to support type select.
*/
- (NSInteger)tableView:(NSTableView *)tableView nextTypeSelectMatchFromRow:(NSInteger)startRow toRow:(NSInteger)endRow forString:(NSString *)searchString NS_AVAILABLE_MAC(10_5);

/* Optional - Type select support
    Implement this method if you would like to prevent a type select from happening based on the current event and current search string. Generally, this will be called from keyDown: and the event will be a key event. The search string will be nil if no type select has began. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldTypeSelectForEvent:(NSEvent *)event withCurrentSearchString:(NSString *)searchString NS_AVAILABLE_MAC(10_5);

/* Optional - Group rows. 
    Implement this method and return YES to indicate a particular row should have the "group row" style drawn for that row. If the cell in that row is an NSTextFieldCell and contains only a stringValue, the "group row" style attributes will automatically be applied for that cell. Group rows are drawn differently depending on the selectionHighlightStyle. For NSTableViewSelectionHighlightStyleRegular, there is a blue gradient background. For NSTableViewSelectionHighlightStyleSourceList, the text is light blue, and there is no background. Also see the related floatsGroupRows property.
*/
- (BOOL)tableView:(NSTableView *)tableView isGroupRow:(NSInteger)row NS_AVAILABLE_MAC(10_5);

/* Optional - Autosizing table columns
 Implement this method if you want to control how wide a column is made when the user double clicks on the resize divider. By default, NSTableView iterates every row in the table, accesses a cell via preparedCellAtRow:column:, and requests the "cellSize" to find the appropriate largest width to use. For large row counts, a monte carlo simulation is done instead of interating every row. For performance and accurate results, it is recommended that this method is implemented when using large tables.
 */
- (CGFloat)tableView:(NSTableView *)tableView sizeToFitWidthOfColumn:(NSInteger)column NS_AVAILABLE_MAC(10_6);

/*  Optional - Control of column reordering.
 Specifies if the column can be reordered to a new location, or not. 'columnIndex' is the column that is being dragged. The actual NSTableColumn instance can be retrieved from the [tableView tableColumns] array. 'newColumnIndex' is the new proposed target location for 'columnIndex'. When a column is initially dragged by the user, the delegate is first called with a 'newColumnIndex' of -1. Returning NO will disallow that column from being reordered at all. Returning YES allows it to be reordered, and the delegate will be called again when the column reaches a new location. If this method is not implemented, all columns are considered reorderable. 
 */
- (BOOL)tableView:(NSTableView *)tableView shouldReorderColumn:(NSInteger)columnIndex toColumn:(NSInteger)newColumnIndex NS_AVAILABLE_MAC(10_6);

#pragma mark -
#pragma mark ***** Notifications *****

- (void)tableViewSelectionDidChange:(NSNotification *)notification;
- (void)tableViewColumnDidMove:(NSNotification *)notification;
- (void)tableViewColumnDidResize:(NSNotification *)notification;
    
/* Optional -  Called when the selection is about to be changed, but note, tableViewSelectionIsChanging: is only called when mouse events are changing the selection and not keyboard events.
 */
- (void)tableViewSelectionIsChanging:(NSNotification *)notification;

@end

APPKIT_EXTERN NSString *NSTableViewSelectionDidChangeNotification;
APPKIT_EXTERN NSString *NSTableViewColumnDidMoveNotification;       // @"NSOldColumn", @"NSNewColumn"
APPKIT_EXTERN NSString *NSTableViewColumnDidResizeNotification;     // @"NSTableColumn", @"NSOldWidth"
APPKIT_EXTERN NSString *NSTableViewSelectionIsChangingNotification;

// The NSTableViewRowViewKey is the key that View Based TableView uses to identify the NIB containing the template row view. You can specify a custom row view (without any code) by associating this key with the appropriate NIB name in IB.
APPKIT_EXTERN NSString *const NSTableViewRowViewKey NS_AVAILABLE_MAC(10_7); // @"NSTableViewRowViewKey"

#pragma mark -

@protocol NSTableViewDataSource <NSObject>
@optional

#pragma mark -
#pragma mark ***** Required Methods (unless bindings are used) *****

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;

/* This method is required for the "Cell Based" TableView, and is optional for the "View Based" TableView. If implemented in the latter case, the value will be set to the view at a given row/column if the view responds to -setObjectValue: (such as NSControl and NSTableCellView).
 */
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

#pragma mark -
#pragma mark ***** Optional Methods *****

/* NOTE: This method is not called for the View Based TableView.
 */
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Sorting support
   This is the indication that sorting needs to be done.  Typically the data source will sort its data, reload, and adjust selections.
*/
- (void)tableView:(NSTableView *)tableView sortDescriptorsDidChange:(NSArray *)oldDescriptors;

/* Dragging Source Support - Required for multi-image dragging. Implement this method to allow the table to be an NSDraggingSource that supports multiple item dragging. Return a custom object that implements NSPasteboardWriting (or simply use NSPasteboardItem). If this method is implemented, then tableView:writeRowsWithIndexes:toPasteboard: will not be called.
 */
- (id <NSPasteboardWriting>)tableView:(NSTableView *)tableView pasteboardWriterForRow:(NSInteger)row NS_AVAILABLE_MAC(10_7);

/* Dragging Source Support - Optional. Implement this method to know when the dragging session is about to begin and to potentially modify the dragging session.'rowIndexes' are the row indexes being dragged, excluding rows that were not dragged due to tableView:pasteboardWriterForRow: returning nil. The order will directly match the pasteboard writer array used to begin the dragging session with [NSView beginDraggingSessionWithItems:event:source]. Hence, the order is deterministic, and can be used in -tableView:acceptDrop:row:dropOperation: when enumerating the NSDraggingInfo's pasteboard classes. 
 */
- (void)tableView:(NSTableView *)tableView draggingSession:(NSDraggingSession *)session willBeginAtPoint:(NSPoint)screenPoint forRowIndexes:(NSIndexSet *)rowIndexes NS_AVAILABLE_MAC(10_7);

/* Dragging Source Support - Optional. Implement this method to know when the dragging session has ended. This delegate method can be used to know when the dragging source operation ended at a specific location, such as the trash (by checking for an operation of NSDragOperationDelete).
 */
- (void)tableView:(NSTableView *)tableView draggingSession:(NSDraggingSession *)session endedAtPoint:(NSPoint)screenPoint operation:(NSDragOperation)operation NS_AVAILABLE_MAC(10_7);

/* Dragging Destination Support - Required for multi-image dragging. Implement this method to allow the table to update dragging items as they are dragged over the view. Typically this will involve calling [draggingInfo enumerateDraggingItemsWithOptions:forView:classes:searchOptions:usingBlock:] and setting the draggingItem's imageComponentsProvider to a proper image based on the content. For View Based TableViews, one can use NSTableCellView's -draggingImageComponents. For cell based TableViews, use NSCell's draggingImageComponentsWithFrame:inView:.
 */
- (void)tableView:(NSTableView *)tableView updateDraggingItemsForDrag:(id <NSDraggingInfo>)draggingInfo NS_AVAILABLE_MAC(10_7);

/* Dragging Source Support - Optional for single-image dragging. Implement this method to support single-image dragging. Use the more modern tableView:pasteboardWriterForRow: to support multi-image dragging. This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO.  To start a drag, return YES and place the drag data onto the pasteboard (data, owner, etc...).  The drag image and other drag related information will be set up and provided by the table view once this call returns with YES.  'rowIndexes' contains the row indexes that will be participating in the drag.
 */
- (BOOL)tableView:(NSTableView *)tableView writeRowsWithIndexes:(NSIndexSet *)rowIndexes toPasteboard:(NSPasteboard *)pboard;

/* Dragging Destination Support - This method is used by NSTableView to determine a valid drop target. Based on the mouse position, the table view will suggest a proposed drop 'row' and 'dropOperation'. This method must return a value that indicates which NSDragOperation the data source will perform. The data source may "re-target" a drop, if desired, by calling setDropRow:dropOperation: and returning something other than NSDragOperationNone. One may choose to re-target for various reasons (eg. for better visual feedback when inserting into a sorted position).
*/
- (NSDragOperation)tableView:(NSTableView *)tableView validateDrop:(id <NSDraggingInfo>)info proposedRow:(NSInteger)row proposedDropOperation:(NSTableViewDropOperation)dropOperation;

/* Dragging Destination Support - This method is called when the mouse is released over an NSTableView that previously decided to allow a drop via the validateDrop method. The data source should incorporate the data from the dragging pasteboard at this time. 'row' and 'dropOperation' contain the values previously set in the validateDrop: method.
*/
- (BOOL)tableView:(NSTableView *)tableView acceptDrop:(id <NSDraggingInfo>)info row:(NSInteger)row dropOperation:(NSTableViewDropOperation)dropOperation;

/* Dragging Destination Support - NSTableView data source objects can support file promised drags by adding NSFilesPromisePboardType to the pasteboard in tableView:writeRowsWithIndexes:toPasteboard:.  NSTableView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this data source method.  This method should returns an array of filenames for the created files (filenames only, not full paths).  The URL represents the drop location.  For more information on file promise dragging, see documentation on the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:.
*/
- (NSArray *)tableView:(NSTableView *)tableView namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination forDraggedRowsWithIndexes:(NSIndexSet *)indexSet;

@end

@interface NSObject(NSTableViewDataSourceDeprecated)

/*
 * Deprecated delegate methods
 */
 
/* Deprecated in Mac OS 10.4.  You should implement tableView:writeRowsWithIndexes:toPasteboard: instead. See that method for more details.
*/
- (BOOL)tableView:(NSTableView *)tableView writeRows:(NSArray *)rows toPasteboard:(NSPasteboard *)pboard NS_DEPRECATED_MAC(10_0, 10_4);

@end


/* Deprecated methods */

@interface NSTableView(NSDeprecated) 

/* Deprecated in Mac OS 10.3.  Calls setGridStyleMask:, setting grid style to either None, or vertical and horizonal solid grid lines as appropriate.
*/
- (void)setDrawsGrid:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_3);

/* Deprecated in Mac OS 10.3.  Returns YES if gridStyleMask returns anything other than NSTableViewGridNone.
*/
- (BOOL)drawsGrid NS_DEPRECATED_MAC(10_0, 10_3);

/* Deprecated in Mac OS 10.3.  You should use selectColumnIndexes:byExtendingSelection: instead.  See that method for more details.
*/
- (void)selectColumn:(NSInteger)column byExtendingSelection:(BOOL)extend NS_DEPRECATED_MAC(10_0, 10_3);

/* Deprecated in Mac OS 10.3.  You should use selectRowIndexes:byExtendingSelection: instead.  See that method for more details.
*/
- (void)selectRow:(NSInteger)row byExtendingSelection:(BOOL)extend NS_DEPRECATED_MAC(10_0, 10_3);

/* Deprecated in Mac OS 10.3.  You should use selectedColumnIndexes instead.
*/
- (NSEnumerator *)selectedColumnEnumerator NS_DEPRECATED_MAC(10_0, 10_3);

/* Deprecated in Mac OS 10.3.  You should use selectedRowIndexes instead.
*/
- (NSEnumerator *)selectedRowEnumerator NS_DEPRECATED_MAC(10_0, 10_3);

/* Deprecated in Mac OS 10.4.  You should use / override dragImageForRowsWithIndexes:tableColumns:event:dragImageOffset: instead.
*/ 
- (NSImage *)dragImageForRows:(NSArray*)dragRows event:(NSEvent *)dragEvent dragImageOffset:(NSPointPointer)dragImageOffset NS_DEPRECATED_MAC(10_0, 10_4);

/* Deprecated in Mac OS 10.4.  You should use setColumnAutoresizingStyle: instead.  To preserve compatibility, if flag is YES, This method calls setColumnAutoresizingStyle:NSTableViewUniformColumnAutoresizingStyle.  If flag is NO, this method calls setColumnAutoresizingStyle:NSTableViewLastColumnOnlyAutoresizingStyle.
*/
- (void)setAutoresizesAllColumnsToFit:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_4);
- (BOOL)autoresizesAllColumnsToFit NS_DEPRECATED_MAC(10_0, 10_4);

/* Deprecated in Mac OS 10.5. Since an NSTableColumn can have visible=NO, it is no longer possible to return a valid range of columns given a rect. Use columnIndexesInRect: 
*/
- (NSRange)columnsInRect:(NSRect)rect NS_DEPRECATED_MAC(10_0, 10_5);

@end
