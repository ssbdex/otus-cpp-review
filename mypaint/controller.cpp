#include "controller.h"

#include <fstream>

namespace  mypaint {

    Controller::Controller(Model& model) : model(model) {}


    void Controller::setMode(Mode ctrlMode) {
        this->drawingMode = ctrlMode;
        figureFabric = makeFigureCreator(
            Controller::FigureTypeByMode[drawingMode]);
    }


    void Controller::newDocument() {
        model.clearData();
    }


    void Controller::importDocument(std::string filepath) {
        model.clearData();
        std::ifstream f(filepath);
        int fg_type;
        std::string data;
        while (f>>fg_type){
            auto fabric = makeFigureCreator(static_cast<FigureType>(fg_type));
            f>>data;
            if (fabric){
                model.addFigure(fabric->makeFigure(data)); 
            }
        }
    }


    void Controller::exportDocument(std::string filepath) {
        std::ofstream f(filepath);
        for (auto fg : model.getData()) {
             FigureType type;
             std::string data;
             std::tie(type, data) = fg->serialize();
             f<<static_cast<int>(type)<<data;
        }   
    }


    void Controller::startDrawAction(Point p) {
        startPoint = p;
    }


    void Controller::stopDrawAction(Point p) {
        std::for_each(observers.begin(), observers.end(), [](auto& s) {
            if (auto spt = s.lock()) {
                spt->onTempFigureDestroyed();
            };
            });

        if (figureFabric) {
            auto figure = figureFabric->makeFigure(startPoint, p, pen, brush);
            std::shared_ptr<Figure> s_ptr{ std::move(figure) };
            model.addFigure(s_ptr);
        }
    }


    void Controller::whileDrawAction(Point p) {
        if (figureFabric) {
            tempFigure = figureFabric->makeFigure(startPoint, p, pen, brush);
            std::for_each(observers.begin(), observers.end(), [t = tempFigure](auto& s) {
                if (auto spt = s.lock()) {
                    spt->onTempFigureChanged(t);
                };
                });
        }
    }


    void Controller::removeFigure(Figure* fg) {
        model.removeFigure(fg);
    }


    void Controller::close() {
        std::for_each(observers.begin(), observers.end(),
            [](auto& s) {
                if (auto spt = s.lock()) {
                    spt->onClose();
                };
            });
    }


    void Controller::addSubscriber(std::weak_ptr<ControllerSubscriber> handler) {
        observers.push_back(handler);
    }


    void Controller::setPen(Pen pen) {
        this->pen = pen;
    }


    void Controller::setBrush(Brush brush) {
        this->brush = brush;
    }


}