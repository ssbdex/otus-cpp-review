#pragma once
#include <cmath>

#define UNUSED(variable) (void)variable

namespace mypaint
{

    class Point {
        int x, y;
    public:
        Point() :Point(0, 0) {};
        Point(int x, int y) :x(x), y(y) {};
        double length_to(Point p) {
            return std::hypot((x - p.x), (y - p.y));
        }
    };


    class Rect {
        Point p1, p2;
    public:
        Rect(Point p1, Point p2) :p1(p1), p2(p2) {};
        Rect() :Rect(Point{ 0,0 }, Point{ 0,0 }) {};

        /**
         * @return true, if rect has intersection with rval
         * */
        bool operator && (const Rect& rval) {
            //TODO: correct realisation
            UNUSED(rval);
            return true;
        };

        /**
         * @return  rect, that can fill left and rigth rects
        */
        Rect& operator += (const Rect& rval) {
            //TODO: correct realisation
            UNUSED(rval);
            return *this;
        };
    };


    enum struct Color {
        white,
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


    struct Pen {
        PenStyle style;
        Color color;
        int width;
    };


    struct Brush {
        BrushStyle style = BrushStyle::filled;
        Color color;
    };

}
