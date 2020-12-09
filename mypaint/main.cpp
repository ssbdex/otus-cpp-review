#include <iostream>
#include <vector>
#include <memory>
#include "stuff.h"
#include "window.h"
#include "figure.h"

namespace  mypaint {

    typedef void (*DataChangeHandler)(std::weak_ptr<Figure> f);
    using ModelData = std::vector< std::weak_ptr<Figure> >;

    class Model {
    public:
        Model();
        void setData(ModelData& data);
        ModelData getData() const;
        void subscribe(DataChangeHandler handler);

    private:
        ModelData data;
        DataChangeHandler eventFunc = nullptr;
    };


    class View {
    public:
        View(const Model& model) {
            this->model = model;
        }
        View() {}
        void SetModel(const Model& model) {
            this->model = model;
        }
        void Render() {
            // rendering all
        }
    private:
        Model model;
        Window w;
    };


    class Controller {
    public:
        Controller(const Model& model, const View& view) {
            this->SetModel(model);
            this->SetView(view);
        }
        void SetModel(const Model& model) {
            this->model = model;
        }
        void SetView(const View& view) {
            this->view = view;
        }
        // when application starts
        void OnLoad() {
            this->view.Render();
        }
    private:
        Model model;
        View view;
    };


    class Application {
    public:
        static Application& Instance() {
            static Application app;
            return app;
        }

        int process(){
            pModel.reset(new Model());
            pView.reset(new View(*pModel));
            pController.reset(new Controller(*pModel,*pView));
            Model model("Model");
            View view(model)
        }

    private:
        Application();
        Application(const Application& app);
        Application(Application&& app);
    

        std::unique_ptr<Model> pModel;
        std::unique_ptr<Controller> pController;
        std::unique_ptr<View> pView;
    }

};


int main(int, char**) {

    return mypaint::Application::Instance().process();


}
