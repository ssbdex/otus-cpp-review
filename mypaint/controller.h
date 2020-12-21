#pragma once

#include "model.h"
#include "stuff.h"
#include "figure.h"

#include <memory>
#include <algorithm>
#include <map>

namespace  mypaint {

    class ControllerSubscriber {
    public:
        virtual void onTempFigureChanged(std::shared_ptr<Figure> fg) = 0;
        virtual void onTempFigureDestroyed() = 0;
        virtual void onClose() = 0;
    };


    class Controller {
    public:
        Controller(Model& model);

        enum class Mode {
            insertCircle,
            insertRectangle,
            insertLine,
            selection
        };

        void setMode(Mode ctrlMode);

        void newDocument();
        void importDocument(std::string filepath);
        void exportDocument(std::string filepath);
        void startDrawAction(Point p);
        void stopDrawAction(Point p);
        void whileDrawAction(Point p);
        void removeFigure(Figure* f);
        void setPen(Pen pen);
        void setBrush(Brush brush);
        void close();

        void addSubscriber(std::weak_ptr<ControllerSubscriber> handler);

    private:
        Model& model;
        Mode drawingMode;
        std::shared_ptr<Figure> tempFigure;
        std::vector<std::weak_ptr<ControllerSubscriber> > observers;
        Point startPoint;
        Pen pen;
        Brush brush;
        std::unique_ptr<IFigureCreator> figureFabric;

        static inline std::map<Mode, FigureType> FigureTypeByMode = {
            {Mode::insertCircle, FigureType::Circle},
            {Mode::insertRectangle, FigureType::Rectangle},
            {Mode::insertLine, FigureType::Line},
            {Mode::selection, FigureType::Rectangle}
        };
    };


    struct ICommand {
        virtual void execute() = 0;
        virtual ~ICommand() = default;
    };


    struct ControllerCommand : public ICommand {
        ControllerCommand(Controller* c) :controller(c) {};
    protected:
        Controller* controller;
    };


    struct Cmd_NewDocument : public ControllerCommand {
        Cmd_NewDocument(Controller* controller) :ControllerCommand(controller) {};
        void execute() override {
            controller->newDocument();
        }
    };


    struct Cmd_Close : public ControllerCommand {
        Cmd_Close(Controller* controller) :ControllerCommand(controller) {};
        void execute() override {
            controller->close();
        }
    };


    struct Cmd_ImportDocument : public ControllerCommand {
        Cmd_ImportDocument(Controller* controller, std::string filename) :
            ControllerCommand(controller), filename(filename) {
        }
        void execute() override {
            controller->importDocument(filename);
        }
        std::string filename;
    };


    struct Cmd_ExportDocument : public ControllerCommand {
        Cmd_ExportDocument(Controller* controller, std::string filename) :
            ControllerCommand(controller), filename(filename) {
        }
        void execute() override {
            controller->exportDocument(filename);
        }
    private:
        std::string filename;
    };


    struct Cmd_SwitchMode : public ControllerCommand {
        Cmd_SwitchMode(Controller* controller, Controller::Mode mod) :
            ControllerCommand(controller), mode(mod) {
        }
        void execute() override {
            controller->setMode(mode);
        }
    private:
        Controller::Mode mode;
    };


    struct Cmd_SetPen : public ControllerCommand {
        Cmd_SetPen(Controller* controller, Pen pen) :
            ControllerCommand(controller), pen(pen) {
        }
        void execute() override {
            controller->setPen(pen);
        }
    private:
        Pen pen;
    };


    struct Cmd_SetBrush : public ControllerCommand {
        Cmd_SetBrush(Controller* controller, Brush brush) :
            ControllerCommand(controller), brush(brush) {
        }
        void execute() override {
            controller->setBrush(brush);
        }
    private:
        Brush brush;
    };


    struct Cmd_StartAction : public ControllerCommand {
        Cmd_StartAction(Controller* controller, int x, int y) :
            ControllerCommand(controller), x(x), y(y) {
        }
        void execute() override {
            controller->startDrawAction(Point(x, y));
        }
    private:
        int x, y;
    };


    struct Cmd_StopAction : public ControllerCommand {
        Cmd_StopAction(Controller* controller, int x, int y) :
            ControllerCommand(controller), x(x), y(y) {
        }
        void execute() override {
            controller->stopDrawAction(Point(x, y));
        }
    private:
        int x, y;
    };


    struct Cmd_WhileAction : public ControllerCommand {
        Cmd_WhileAction(Controller* controller, int x, int y) :
            ControllerCommand(controller), x(x), y(y) {
        }
        void execute() override {
            controller->whileDrawAction(Point(x, y));
        }
    private:
        int x, y;
    };


    struct Cmd_RemoveFigure : public ControllerCommand {
        Cmd_RemoveFigure(Controller* controller, Figure* pFg) :
            ControllerCommand(controller), pFg(pFg) {
        }
        void execute() override {
            controller->removeFigure(pFg);
        }
    private:
        Figure* pFg;
    };

}