////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_SVGPATH_H__
#define __DRAWING_SVGPATH_H__


#include <NsCore/Noesis.h>
#include <NsCore/Vector.h>
#include <NsDrawing/TypesApi.h>
#include <NsMath/Vector.h>
#include <NsMath/Transform.h>


namespace Noesis
{

struct Rect;
struct Point;
struct PathCommandIterator;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Paths represent the geometry of the outline of an object
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API SVGPath
{
    /// Empty path constructor
    SVGPath();

    /// Builds a path from SVG path commands as described in http://www.w3.org/TR/SVG11/paths.html
    /// Example: "M 100, 100 L 200, 100 200, 200 Z"
    SVGPath(const char* str);

    /// Converts to SVG string
    String ToString() const;

    /// Parses from SVG string
    static bool TryParse(const char* str, SVGPath& result);

    /// Resers any lines and curves from the path, making it empty
    void Clear();

    /// Rebuilds the path with a new SVG string
    void SetCommands(const char* str);

    /// Returns an iterator of commands describing the path
    PathCommandIterator GetCommands() const;
    PathCommandIterator GetCommands(bool forceClose) const;

    /// Appends path transformed by the given matrix
    void AddPath(const SVGPath& path, const Transform2& mtx);
    static void AddPath(BaseVector<uint32_t>& dst, ArrayRef<uint32_t> src, const Transform2& mtx);

    /// Calculates path bounds
    Rect CalculateBounds() const;

    /// Indicates whether the path contains the specified point
    bool FillContains(const Point& point) const;

    /// Determines whether the specified point is contained in the given stroke
    bool StrokeContains(const Point& point, float strokeThickness) const;

    /// Start a new sub-path at the given coordinates
    static void MoveTo(BaseVector<uint32_t>& commands, float x, float y);
    static void MoveToRel(BaseVector<uint32_t>& commands, float x, float y);

    /// Adds a straight line segment from the current point to the given point
    static void LineTo(BaseVector<uint32_t>& commands, float x, float y);
    static void LineToRel(BaseVector<uint32_t>& commands, float x, float y);

    /// Draws a horizontal line from the current point
    static void HLineTo(BaseVector<uint32_t>& commands, float coord);
    static void HLineToRel(BaseVector<uint32_t>& commands, float coord);

    /// Draws a vertical line from the current point
    static void VLineTo(BaseVector<uint32_t>& commands, float coord);
    static void VLineToRel(BaseVector<uint32_t>& commands, float coord);

    /// Draws a cubic Bezier curve from the current point
    static void CubicTo(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1,
        float x2, float y2);
    static void CubicToRel(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1,
        float x2, float y2);

    /// Draws a quadratic Bezier curve from the current point
    static void QuadTo(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1);
    static void QuadToRel(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1);

    /// Draws a smooth cubic Bezier curve from the current point
    static void SCubicTo(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1);
    static void SCubicToRel(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1);

    /// Draws a smooth quadratic Bezier curve from the current point
    static void SQuadTo(BaseVector<uint32_t>& commands, float x0, float y0);
    static void SQuadToRel(BaseVector<uint32_t>& commands, float x0, float y0);

    /// Draws an elliptical arc from the current point
    static void ArcTo(BaseVector<uint32_t>& commands, bool largeArc, bool clockwise,
        float radiusX, float radiusY, float rotation, float x, float y);
    static void ArcToRel(BaseVector<uint32_t>& commands, bool largeArc, bool clockwise,
        float radiusX, float radiusY, float rotation, float x, float y);

    /// Close the current subpath
    static void Close(BaseVector<uint32_t>& commands);

    /// Appends a line segment from (x0, y0) to (x1, y1) to the command list
    static void AddLine(BaseVector<uint32_t>& commands, float x0, float y0, float x1, float y1);

    /// Appends a rectangle with the top-left corner at (x, y) and the given width and height
    static void AddRect(BaseVector<uint32_t>& commands, float x, float y, float width, float height);

    /// Appends a rounded rectangle at (x, y) with the specified width, height, and corner radii
    static void AddRoundRect(BaseVector<uint32_t>& commands, float x, float y, float width,
        float height, float rx, float ry);

    /// Appends an ellipse centered at (x, y) with radii rx and ry
    static void AddEllipse(BaseVector<uint32_t>& commands, float x, float y, float rx, float ry);

public:
    struct Move
    {
        float x, y;
    };

    struct Line
    {
        float orgX, orgY;
        float x, y;
    };

    struct Cubic
    {
        float orgX, orgY;
        float x0, y0;
        float x1, y1;
        float x2, y2;
    };

    struct Quadratic
    {
        float orgX, orgY;
        float x0, y0;
        float x1, y1;
    };

    struct Arc
    {
        float orgX, orgY;
        float rx, ry;
        float rot;
        float x, y;

        bool isLarge;
        bool isCw;
    };

    enum FigureCommand
    {
        FigureCommand_Move,
        FigureCommand_Line,
        FigureCommand_Cubic,
        FigureCommand_Quadratic,
        FigureCommand_Arc,
        FigureCommand_Close
    };

    struct Command
    {
        FigureCommand figureCommand;

        union
        {
            Move move;
            Line line;
            Cubic cubic;
            Quadratic quadratic;
            Arc arc;
        };
    };

    enum Fill
    {
        Fill_EvenOdd,
        Fill_NonZero
    };

    Fill fillRule;
    Vector<uint32_t> commands;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_DRAWING_TYPES_API PathCommandIterator
{
    PathCommandIterator(const uint32_t* data, const uint32_t* end);
    PathCommandIterator(const uint32_t* data, const uint32_t* end, bool forceClose);

    bool End() const;
    SVGPath::Command Next();

private:
    const uint32_t* mData;
    const uint32_t* const mEnd;
    const bool mForceClose;

    Vector2 o, p, s;
    bool pendingClose;
};

NS_WARNING_POP

}

#endif
