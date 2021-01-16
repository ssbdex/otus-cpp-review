#pragma once

#include "window.h"
#include "figure.h"
#include <list>

namespace mypaint
{

    class ModelSubscriber {
    public:
        virtual void onFigureChanged(Figure* beforeFigure, Figure* afterFigure) = 0;
        virtual void onDataCleared() = 0;
    };


    class Model {
    public:

        using Model_Data = std::list< std::shared_ptr<Figure> >;

        Model() {}

        const Model_Data& getData() const {
            return data;
        }

        void clearData() {
            data.clear();
        }

        void addFigure(std::shared_ptr<Figure> fg) {
            data.emplace_back(fg);
        }

        void removeFigure(Figure* fg) {
            data.remove_if([fg](auto sp) { return sp.get() == fg; });
        }

        void addSubscriber(std::weak_ptr<ModelSubscriber> handler) {
            observers.push_back(handler);
        };

    private:
        Model_Data data;
        std::vector<std::weak_ptr<ModelSubscriber>> observers;
    };

}