////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRID_H__
#define __GUI_GRID_H__


#include <NsCore/Noesis.h>
#include <NsCore/Vector.h>
#include <NsCore/HashMap.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Panel.h>
#include <NsGui/GridLength.h>


namespace Noesis
{

class ColumnDefinition;
class RowDefinition;
class SharedSizeScope;

template<class T> class UICollection;
typedef UICollection<ColumnDefinition> ColumnDefinitionCollection;
typedef UICollection<RowDefinition> RowDefinitionCollection;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a flexible grid area that consists of columns and rows.
///
/// .. code-block:: xml
///    :caption: XAML
///
///    <Grid Width="400" Height="400">
///      <Grid.ColumnDefinitions>
///        <ColumnDefinition Width="100" />
///        <ColumnDefinition Width="*" />
///      </Grid.ColumnDefinitions>
///      <Grid.RowDefinitions>
///        <RowDefinition Height="50" />
///        <RowDefinition Height="*" />
///        <RowDefinition Height="50" />
///      </Grid.RowDefinitions>
///      <Rectangle Grid.Row="0" Grid.Column="0" Grid.ColumnSpan="2" Fill="YellowGreen" />
///      <Rectangle Grid.Row="1" Grid.Column="0" Fill="Gray" />
///      <Rectangle Grid.Row="1" Grid.Column="1" Fill="Silver" />
///      <Rectangle Grid.Row="2" Grid.Column="0" Grid.ColumnSpan="2" Fill="Orange" />
///    </Grid>
///
/// A Grid contains a collection of UIElement objects, which are in the Children property.
///
/// Columns and rows that are defined within a Grid can take advantage of Star sizing to distribute
/// remaining space proportionally. When Star is selected as the height or width of a row or column,
/// that column or row receives a weighted proportion of the remaining available space. This is in
/// contrast to Auto, which distributes space evenly based on the size of the content that is within
/// a column or row. This value is expressed as * or 2* when you use Extensible Application
/// Markup Language (XAML). In the first case, the row or column would receive one times the
/// available space, while in the second case, the row or column would receive two times the
/// available space, and so on. By combining this technique to proportionally distribute space with
/// a HorizontalAlignment and VerticalAlignment value of Stretch, it is possible to partition layout
/// space by percentage of screen space. Grid is the only layout panel that can distribute space in
/// this manner.
///
/// By default, rows and columns take up the least amount of space necessary to accommodate the
/// largest content within any cell contained in a given row or column. For example, if a column has
/// one cell with a long word like "hippopotamus" contained within it but all the other cells in the
/// column have smaller words like "dog", the width of the column will be the width of the largest
/// word (hippopotamus).
///
/// You can precisely position child elements of a Grid by using a combination of the Margin
/// property and alignment properties.
/// 
/// Child elements of a Grid are drawn in the order in which they appear in markup or code. As a
/// consequence, layered order (also known as z-order) can be achieved when elements share the same
/// coordinates.
///
/// Grid uses the GridLength object to define the sizing characteristics of a RowDefinition or
/// ColumnDefinition. For a definition of each unit type, see GridUnitType.
///
/// If a child element is added to a column within a Grid, and the column has its Width property set
/// to Auto, the child will be measured without restrictions. This behavior can prevent horizontal
/// scroll bars from displaying if a ScrollViewer is being used, as the child element is measured as
/// unbounded. For purposes of display, the child is clipped rather than scrolled.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.grid.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Grid: public Panel
{
public:
    Grid();
    ~Grid();

    /// Gets a ColumnDefinitionCollection defined on this instance of Grid
    ColumnDefinitionCollection* GetColumnDefinitions() const;

    /// Gets or sets a value that indicates which column child within a Grid should appear in
    //@{
    static uint32_t GetColumn(const DependencyObject* element);
    static void SetColumn(DependencyObject* element, uint32_t column);
    //@}

    /// Gets or sets a value that indicates the number of columns that child spans within a Grid
    //@{
    static uint32_t GetColumnSpan(const DependencyObject* element);
    static void SetColumnSpan(DependencyObject* element, uint32_t columnSpan);
    //@}

    /// Gets or sets a value that indicates that multiple Grid elements are sharing size information
    //@{
    static bool GetIsSharedSizeScope(const DependencyObject* element);
    static void SetIsSharedSizeScope(DependencyObject* element, bool value);
    //@}

    /// Gets a RowDefinitionCollection defined on this instance of Grid
    RowDefinitionCollection* GetRowDefinitions() const;

    /// Gets or sets a value that indicates which row child within a Grid should appear in
    //@{
    static uint32_t GetRow(const DependencyObject* element);
    static void SetRow(DependencyObject* element, uint32_t row);
    //@}

    /// Gets or sets a value that indicates the number of rows that child spans within a Grid
    //@{
    static uint32_t GetRowSpan(const DependencyObject* element);
    static void SetRowSpan(DependencyObject* element, uint32_t rowSpan);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ColumnProperty; // attached property
    static const DependencyProperty* ColumnSpanProperty; // attached property
    static const DependencyProperty* IsSharedSizeScopeProperty; // attached property
    static const DependencyProperty* RowProperty; // attached property
    static const DependencyProperty* RowSpanProperty; // attached property
    //@}

protected:
    /// From DependencyObject
    //@{
    void OnInit() override;
    int32_t OnDestroy() override;
    //@}

    /// From Visual
    //@{
    uint32_t GetVisualChildrenCount() const override;
    Visual* GetVisualChild(uint32_t index) const override;
    void OnVisualChildrenChanged(Visual* added, Visual* removed) override;
    //@}

    /// From FrameworkElement
    //@{
    void CloneOverride(FrameworkElement* clone, FrameworkTemplate* template_) const override;
    uint32_t GetLogicalChildrenCount() const override;
    Ptr<BaseComponent> GetLogicalChild(uint32_t index) const override;
    Size MeasureOverride(const Size& availableSize) override;
    Size ArrangeOverride(const Size& finalSize) override;
    //@}

private:
    friend class BaseDefinition;
    friend class SharedSizeGroup;

    // Simple measure of children
    Size SimpleMeasure(const Size& availableSize);

    // Simple arrange of children
    Size SimpleArrange(const Size& finalSize);

    // Updates private cell structures
    void UpdateCellStructure();
    void UpdateElementCache();

    // Gets element column and row info
    //@{
    void GetColumnInfo(const UIElement* child, uint32_t numCols,
        uint32_t& col, uint32_t& colSpan) const;
    void GetRowInfo(const UIElement* child, uint32_t numRows,
        uint32_t& row, uint32_t& rowSpan) const;
    //@}

    struct DefinitionsInfo;
    struct DefinitionCache
    {
        GridUnitType type;
        float size;
        float minSize;
        float maxSize;
        const char* sharedGroup;
        bool useSharedSize;

        DefinitionCache();
        DefinitionCache(GridUnitType t, float s, float mins, float maxs, const char* g);
    };

    typedef Vector<DefinitionCache> DefinitionCacheVector;
    typedef Vector<float> FloatVector;

    // Measure helpers
    //@{
    Size DoMeasure(const Size& availableSize);
    void MeasureElements(const Size& availableSize, uint32_t start, uint32_t end, bool colsSolved,
        bool rowsSolved);
    float MeasureSizes(const DefinitionCacheVector& defVec, FloatVector& sizes);
    void UpdateSizes(const DefinitionCacheVector& defVec, uint32_t index, uint32_t span,
        float size, FloatVector& sizes);
    void SolveDef(float availableSize, const DefinitionsInfo& info, const FloatVector& sizes,
        FloatVector& constraints, float& usedSize);
    //@}

    // Arrange helpers
    //@{
    void DoArrange(const Size& finalSize);
    void ArrangeDef(float finalSize, float desiredSize, bool isDesiredSize,
        const DefinitionsInfo& info, const FloatVector& measureSizes,
        FloatVector& arrangeSizes, FloatVector& arrangePositions);
    void UpdateArrangeSize(uint32_t index, FloatVector& arrangeSizes, float size, float minSize,
        float& usedSize);
    //@}

    // Determines if grid size is determined by children
    void IsDesiredSize(const Size& size, bool& isDesiredWidth, bool& isDesiredHeight);
    bool IsDesiredSize(float finalSize, float desiredSize, float localSize) const;

    // Distributes desired size within the cell span
    void DistributeSize(uint32_t index, uint32_t span, float size,
        const DefinitionCacheVector& defVec, FloatVector& sizes) const;

    // Calculates the size of a range of cells
    float GetSpanSize(const DefinitionCacheVector& defVec, const FloatVector& sizes,
        float constraint, uint32_t index, uint32_t span, bool defsSolved) const;

    // Indicates if all cells in the span are auto
    void GetAllAutoSpanAndOrder(const DefinitionCacheVector& defVec, uint32_t index, uint32_t span,
        bool& allAutoSpan, uint32_t& orderType) const;

    // Notifies when a collection of column or row definitions changed
    void OnCollectionChanged(BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    // Notifies when the definition of a column or row changes
    void OnDefinitionChanged(BaseComponent* sender,
        const DependencyPropertyChangedEventArgs& args);

    // Invalidates grid cell cache
    void InvalidateCellCache();

    // Creates column/row definitions if necessary
    void EnsureColumns();
    void DisconnectColumns();
    void EnsureRows();
    void DisconnectRows();

    void UseSharedSize(uint32_t index, bool useSharedSize);
    float MeasureSize(uint32_t index) const;
    float ArrangeSize(uint32_t index) const;
    float SharedSize(const DefinitionCache& def) const;

private:
    mutable Ptr<ColumnDefinitionCollection> mColumnDefinitions;
    mutable Ptr<RowDefinitionCollection> mRowDefinitions;

    bool mDirtyCellStructure;
    bool mDirtyElementCache;

    struct ElementInfo
    {
        UIElement* element;
        uint32_t col;
        uint32_t colSpan;
        uint32_t row;
        uint32_t rowSpan;
        uint32_t order;
        bool allAutoRowSpan;
        bool allAutoColSpan;
    };

    typedef Vector<ElementInfo> ElementInfoVector;
    typedef Vector<uint32_t> IndexVector;

    struct DefinitionsInfo
    {
        DefinitionCacheVector definitions;
        IndexVector pixelDefinitions;
        IndexVector autoDefinitions;
        IndexVector starDefinitions;
        float starTotal;

        DefinitionsInfo();
        void Reset();
        void Reserve(uint32_t count);
        void AddDefinition(const DefinitionCache& def);
    };

    struct MeasureInfo
    {
        // Contains the constraints applied to each cell element
        FloatVector colConstraints;
        FloatVector rowConstraints;

        // Stores the desired size of each cell
        FloatVector colSizes;
        FloatVector rowSizes;

        // During measure process stores the used size by Pixel and Auto cells, to calculate the
        // remaining space for Star cells. After measure represents the desired size of the grid
        float usedWidth;
        float usedHeight;
    };

    struct ArrangeInfo
    {
        FloatVector colSizes;
        FloatVector rowSizes;
        FloatVector colPositions;
        FloatVector rowPositions;
    };

    typedef HashMap<uint32_t, IndexVector> OrderedIndices;

    struct CellStructureInfo
    {
        SharedSizeScope* scope;

        DefinitionsInfo colInfo;
        DefinitionsInfo rowInfo;
        ElementInfoVector elements;
        OrderedIndices orderedIndices;
        IndexVector orderedElements;
        uint32_t solveColsIndex;
        uint32_t solveRowsIndex;
        MeasureInfo measureInfo;
        ArrangeInfo arrangeInfo;

        void ResetCellInfo();
        void ResetElementCache();
        void ResetMeasureInfo(IView* view);
        void ResetArrangeInfo();

        uint32_t GetNumOrderedIndices(uint32_t cell);
        void AddOrderedElements(uint32_t cell);

    private:
        void ResetMeasureDef(IView* view, const DefinitionsInfo& info, FloatVector& constraints,
            FloatVector& sizes, float& usedSize);
        void ResetArrangeDef(const DefinitionsInfo& info, FloatVector& sizes,
            FloatVector& positions);
    };

    CellStructureInfo* mCellInfo;

    NS_DECLARE_REFLECTION(Grid, Panel)
};

NS_WARNING_POP

}


#endif
