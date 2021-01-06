#include "bulk.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>

int main(int argc, char* argv[]) {

    std::string cmd;
    int n = (argc>1) ? atoi(argv[1]) : 3;
    std::unique_ptr<Bulk> pBulk(new StaticBulk(n));
    while (true) {
        std::getline(std::cin, cmd);
        
        if (!std::cin.good()) {
            break;
        }

        if (cmd.size()==0){
            continue;
        }
        
        auto newBulk = pBulk->addCommand(cmd);
        if (newBulk) {
            //std::swap(pBulk, newBulk);
            pBulk=std::move(newBulk);
        }
    }

    return EXIT_SUCCESS;
}