#include "bulk.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>


int main(int argc, char* argv[]) {

    int n = (argc > 1) ? atoi(argv[1]) : 3;
    std::unique_ptr<Bulk> bulk(new StaticBulk(n));
    
    while (std::cin.good()) {
        std::string cmd;
        std::getline(std::cin, cmd);
        auto new_bulk = bulk->add_command(cmd);
        if (new_bulk) {
            bulk = std::move(new_bulk);
        }
    }

    return EXIT_SUCCESS;
}