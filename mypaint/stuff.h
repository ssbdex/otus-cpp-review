#pragma once
namespace mypaint
{
    class Point {
        int x, y;
    public:
        Point(int x, int y) :x(x), y(x) {};
    };

    class Rect {
        Point p1, p2;
    public:
        Rect(Point p1, Point p2) :p1(p1), p2(p2) {};
    };

    enum struct Color {
        red,
        green,
        blue,
        //...
        black
    };


    enum struct PenStyle {
        solid,
        // ...
        dotted
    };

    enum struct BrushStyle {
        filled,
        // ...
        invisible
    };


    class Pen {
    public:
        Pen(PenStyle ps, Color color, int width);
    private:
        PenStyle style;
        Color color;
        int width;
    };


    struct Brush {
        Brush(BrushStyle bs, Color color);
        private:
        BrushStyle style;
        Color color;
    };



} 
