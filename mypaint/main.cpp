#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib> // EXIT_SUCCES defined

#include "controller.h"
#include "model.h"
#include "view.h"
#include "input.h"

using namespace  mypaint;


class Application : public ControllerSubscriber {
public:
    static Application& Instance() {
        static Application app;
        return app;
    }

    // Controller's signal handlers
    void onTempFigureChanged(std::shared_ptr<Figure> fg) override { UNUSED(fg); }
    void onTempFigureDestroyed() override {}
    void onClose() override { f_stop_process = true; }
    int process();

private:
    Application() = default;
    Application(const Application& app) = delete;
    Application(Application&& app) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    UserInput input;
    std::unique_ptr<Model> pModel;
    std::unique_ptr<Controller> pController;
    std::shared_ptr<View> pView;
    bool f_stop_process;
};


int Application::process() {
    // Creating Model, Controller, View
    pModel.reset(new Model());
    pController.reset(new Controller(*pModel));
    pView = std::make_shared<View>(*pModel);

    // make connetion Model -> View
    pModel->addSubscriber(std::weak_ptr<ModelSubscriber>(pView));

    // make connection Conroller -> View
    pController->addSubscriber(std::weak_ptr<ControllerSubscriber>(pView));

    pView->render();

    f_stop_process = false;
    while (!f_stop_process) {
        std::unique_ptr<ICommand> pCommand = input.getCommand(pController.get());
        pCommand->execute();
    }
    return EXIT_SUCCESS;

}


int main(int, char**) {
    return Application::Instance().process();
}

