#pragma once

#include "stuff.h"
#include "window.h"

#include <string>
#include <tuple>
#include <cmath>

namespace  mypaint
{

    enum class FigureType {
        Rectangle,
        Circle,
        Line
    };


    class Figure {
    public:
        virtual void draw(Window& w) const = 0;
        virtual Rect size() = 0;
        virtual Rect boundRect() = 0;

        virtual std::tuple<FigureType, std::string> serialize() const = 0;
        virtual void deserialize(std::string data) = 0;
    };


    class IFigureCreator {
    public:
        virtual std::unique_ptr<Figure> makeFigure(Point p1, Point p2, Pen pen, Brush br) = 0;
        virtual std::unique_ptr<Figure> makeFigure(std::string data) = 0;
    };


    class Rectangle : public Figure {
    public:
        Rectangle(Rect rect, Pen pen, Brush br)
            :rect(rect), pen(pen), brush(br) {}
        void draw(Window& w) const override { /* TODO */ UNUSED(w); }
        Rect size() override { /* TODO */ return Rect(); }
        Rect boundRect() override { /* TODO */ return Rect();}
        std::tuple<FigureType, std::string> serialize() const override { /* TODO */ return {FigureType::Rectangle, ""};}
        void deserialize(std::string data) override { /* TODO */ UNUSED(data);};
    private:
        Rect rect;
        Pen pen;
        Brush brush;
    };

    class RectangleCreator : public IFigureCreator {
    public:
        std::unique_ptr<Figure> makeFigure(Point p1, Point p2, Pen pen, Brush br) override {
            return std::make_unique<Rectangle>(Rect{ p1,p2 }, pen, br);
        };
        std::unique_ptr<Figure> makeFigure(std::string data) override {
            auto f = std::make_unique<Rectangle>(Rect(), Pen(), Brush());
            f->deserialize(data);
            return f;
        };
    };


    class Circle : public Figure {
    public:
        Circle(Point p, double r, Pen pen, Brush br)
        :center(p), radius(r), pen(pen), brush(br) {}
        void draw(Window& w) const override  { /* TODO */ UNUSED(w); }
        Rect size() override { /* TODO */ return Rect(); }
        Rect boundRect() override { /* TODO */ return Rect(); }
        std::tuple<FigureType, std::string> serialize() const override { /* TODO */ return {FigureType::Circle, ""};}
        void deserialize(std::string data) override { /* TODO */ UNUSED(data);};
    private:
        Point center;
        double radius;
        Pen pen;
        Brush brush;
    };

    class CircleCreator : public IFigureCreator {
    public:
        std::unique_ptr<Figure> makeFigure(Point p1, Point p2, Pen pen, Brush br) {
            return std::make_unique<Circle>(p1, p1.length_to(p2), pen, br);
        };
        std::unique_ptr<Figure> makeFigure(std::string data) {
            auto f = std::make_unique<Circle>(Point{ 0,0 }, 0.0, Pen(), Brush());
            f->deserialize(data);
            return f;
        };
    };


    class Line : public Figure {
    public:
        Line(Point p1, Point p2, Pen pen)
            :p1(p1), p2(p2), pen(pen) {}
        void draw(Window& w) const override  { /* TODO */ UNUSED(w); }
        Rect size() override { /* TODO */ return Rect(); }
        Rect boundRect() override { /* TODO */ return Rect(); }
        std::tuple<FigureType, std::string> serialize() const override { /* TODO */ return {FigureType::Line, ""};}
        void deserialize(std::string data) override { /* TODO */ UNUSED(data);};
    private:
        Point p1, p2;
        Pen pen;
    };

    class LineCreator : public IFigureCreator {
    public:
        std::unique_ptr<Figure> makeFigure(Point p1, Point p2,  Pen pen, [[maybe_unused]] Brush br) {
            return std::make_unique<Line>(p1, p2, pen);
        };
        std::unique_ptr<Figure> makeFigure(std::string data) {
            auto f = std::make_unique<Line>(Point{ 0,0 }, Point{ 0,0 }, Pen());
            f->deserialize(data);
            return f;
        };
    };


    
    inline std::unique_ptr<IFigureCreator> makeFigureCreator(FigureType t) {
        switch (t)
        {
        case FigureType::Rectangle:
            return std::make_unique<RectangleCreator>();
            break;
        case FigureType::Circle:
            return std::make_unique<CircleCreator>();
            break;
        case FigureType::Line:
            return std::make_unique<LineCreator>();
            break;
        
        };
        return nullptr;
    }

}
