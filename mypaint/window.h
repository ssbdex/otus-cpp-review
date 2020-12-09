#pragma once
#include "stuff.h"
#include <memory>
#include <vector>

namespace mypaint
{

    class Window {
    public:
        virtual Pen setPen(Pen pen);
        virtual Brush setBrush(Brush brush);
        virtual void drawPixel(Point p);
        virtual void drawLine(Point p1, Point p2);
        virtual void drawPolygone(std::vector<Point> points);
    };

    class GraphDeviceContext {
    public:
        GraphDeviceContext();
    };

    class MyWindow : public Window {
    public:
        MyWindow(int width, int hight);
        Pen setPen(Pen pen) override;
        Brush setBrush(Brush brush) override;
        void drawPixel(Point p) override;
        void drawLine(Point p1, Point p2) override;
        void drawPolygone(std::vector<Point> points) override;
    private:
        int width, height;
        std::unique_ptr<GraphDeviceContext> ctx;
        Brush m_brush;
        Brush m_bg_brush;
        Pen m_pen;
    };

}