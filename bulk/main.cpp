#include "bulk.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>


static void process_bulk(Bulk* bulk) {
    if (bulk == nullptr)
        return;
    
  
}


int main(int argc, char* argv[]) {

    std::string cmd;
    int n = (argc > 1) ? atoi(argv[1]) : 3;
    std::unique_ptr<Bulk> bulk(new StaticBulk(n));
    while (true) {
        std::getline(std::cin, cmd);
        if (!std::cin.good()) {
            break;
        }
        if (cmd.size() == 0) {
            continue;
        }
        auto new_bulk = bulk->add_command(cmd);
        if (new_bulk) {
            process_bulk(bulk.get());
            bulk = std::move(new_bulk);
        }
    }

    return EXIT_SUCCESS;
}