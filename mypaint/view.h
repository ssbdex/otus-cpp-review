#pragma once

#include <memory>
#include "stuff.h"
#include "window.h"
#include "figure.h"
#include "controller.h"
#include "model.h"

namespace  mypaint {

    class View : public ControllerSubscriber,
        public ModelSubscriber {
    public:
        View(const Model& model) :
            model(model),
            bgPen{ PenStyle::solid, Color::white, 1 },
            bgBrush{ BrushStyle::filled, Color::white } {
        }

        // Signals from Model
        void onFigureChanged(Figure* beforeFigure, Figure* afterFigure) override {
            Rect renderRect;
            if (beforeFigure) {
                renderRect += beforeFigure->boundRect();
            }
            if (afterFigure) {
                renderRect += afterFigure->boundRect();
            }

        };

        void onDataCleared() override {
            w->clear();
        };

        // Signals from Controller
        void onTempFigureChanged(std::shared_ptr<Figure> fg) override {
            renderArea(tempFigure->boundRect());
            tempFigure = fg;
            tempFigure->draw(*w);
        };

        void onTempFigureDestroyed() override {
            renderArea(tempFigure->boundRect());
        };
        void onClose() override {};

        // rendering all
        void render() {
            w->setBrush(bgBrush);
            w->clear();
            for (auto fg : model.getData()) {
                fg->draw(*w);
            }
        }

    private:

        void renderArea(Rect rect) {
            w->setBrush(bgBrush);
            w->clearRect(rect);
            for (auto fg : model.getData()) {
                if (rect && fg->boundRect()) {
                    fg->draw(*w);
                }
            }
        };

        const Model& model;
        std::unique_ptr<Window> w;
        Pen bgPen;
        Brush bgBrush;
        std::shared_ptr<Figure> tempFigure;
    };

}