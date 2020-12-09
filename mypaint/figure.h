#include "stuff.h"
#include "window.h"

namespace  mypaint {
  
    class Figure {
    public:
        virtual void draw(Window& w)=0;
        virtual Rect size()=0;
        virtual Point position()=0;
        virtual Rect boundRect()=0;
    };

    class Rectangle: public Figure{
        public:
        Rectangle(Rect rect, Pen pen, Brush br);
        void draw(Window& w) override;
        Rect size() override;
        Rect boundRect() override;
        private:
            Rect rect;
            Pen pen;
            Brush brush;
    };


    class Circle: public Figure{
        public:
        Circle(Point p, unsigned radius, Pen pen, Brush br);
        void draw(Window& w) override;
        Rect size() override;
        Rect boundRect() override;
        private:
        Point center;
        unsigned radius;
        Pen pen;
        Brush brush;
    };


    class Line: public Figure{
        public:
        Line(Point p1, Point p2, Pen pen);
        void draw(Window& w) override;
        Rect size() override;
        Rect boundRect() override;
        private:
        Point center;
        unsigned radius;
        Pen pen;
 
    };


}
