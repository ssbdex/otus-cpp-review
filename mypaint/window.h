#pragma once
#include "stuff.h"
#include <memory>
#include <vector>

namespace mypaint
{

    class Window {
    public:
        virtual Pen setPen(Pen pen) = 0;
        virtual Brush setBrush(Brush brush) = 0;
        virtual void drawPixel(Point p) = 0;
        virtual void drawLine(Point p1, Point p2) = 0;
        virtual void drawPolygone(std::vector<Point> points) = 0;
        virtual void clear() = 0;
        virtual void clearRect(Rect rect) = 0;
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
        void clear() override;
        void clearRect(Rect rect) override;
    private:
        int width, height;
        std::unique_ptr<GraphDeviceContext> ctx;
        Brush m_brush;
        Brush m_bg_brush;
        Pen m_pen;
    };

}