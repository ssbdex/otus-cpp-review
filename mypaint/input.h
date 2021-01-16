#pragma once

#include "controller.h"

#include <memory>

namespace  mypaint {

    class UserInput {
    public:
        UserInput() = default;
        std::unique_ptr<ICommand> getCommand(Controller* ctrl) {
            // Input there
            std::string user_cmd;
            std::cin >> user_cmd;
            std::unique_ptr<ICommand> pCmd;
            if (user_cmd == "close" || user_cmd == "exit") {
                pCmd.reset(new Cmd_Close(ctrl));
            }
            if (user_cmd == "new") {
                pCmd.reset(new Cmd_NewDocument(ctrl));
            }
            if (user_cmd == "load") {
                std::string filename;
                std::cin >> filename;
                pCmd.reset(new Cmd_ImportDocument(ctrl, filename));
            }
            if (user_cmd == "save") {
                std::string filename;
                std::cin >> filename;
                pCmd.reset(new Cmd_ExportDocument(ctrl, filename));
            }
            else if (user_cmd == "circle") {
                pCmd.reset(new Cmd_SwitchMode(ctrl, Controller::Mode::insertCircle));
            }
            else if (user_cmd == "rect") {
                pCmd.reset(new Cmd_SwitchMode(ctrl, Controller::Mode::insertRectangle));
            }
            else if (user_cmd == "line") {
                pCmd.reset(new Cmd_SwitchMode(ctrl, Controller::Mode::insertLine));
            }
            else if (user_cmd == "select") {
                pCmd.reset(new Cmd_SwitchMode(ctrl, Controller::Mode::selection));
            }
            else if (user_cmd == "mouse_down") {
                int x, y;
                std::cin >> x >> y;
                pCmd.reset(new Cmd_StartAction(ctrl, x, y));
            }
            else if (user_cmd == "mouse_up") {
                int x, y;
                std::cin >> x >> y;
                pCmd.reset(new Cmd_StopAction(ctrl, x, y));
            }
            else if (user_cmd == "mouse_over") {
                int x, y;
                std::cin >> x >> y;
                pCmd.reset(new Cmd_WhileAction(ctrl, x, y));
            }
            else if (user_cmd == "pen") {
                int style, color, width;
                std::cin >> style >> color >> width;
                pCmd.reset(new Cmd_SetPen(ctrl, Pen{ static_cast<PenStyle>(style),static_cast<Color>(color), width }));
            }
            else if (user_cmd == "brush") {
                int style, color;
                std::cin >> style >> color;
                pCmd.reset(new Cmd_SetBrush(ctrl, Brush{ static_cast<BrushStyle>(style), static_cast<Color>(color) }));
            }
            else {
                ; // ignoring unknown command
            }
            return pCmd;
        };

    };

}
