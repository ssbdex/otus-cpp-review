/**
 * @file bulk.h
 * @author  Sergey Simonov
 * @brief Bulk, StaticBulk and DynamicBulk structures implementation
 */

#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>

#include "bulk.h"

 /*---------- Bulk -------------------------------------------------*/

const std::string Bulk::cmd_bulk_open = "{";
const std::string Bulk::cmd_bulk_close = "}";

/**
 * @brief Construct a new Bulk:: Bulk object
 * @param n maximum commands in Bulk
 */
Bulk::Bulk(size_t n) :max_commands(n) {
}

/**
 * @brief Return timestamp of Bulk start time
 * @return  time_t (posix time) 
 */
time_t Bulk::start_time() const {
    return std::chrono::system_clock::to_time_t(start);
}

/**
 * @brief Put bulk content to ouput stream
 * Format is "bulk: cmd1 cmd2 ... cmdn {newline}"
 * @param os
 */
void Bulk::output(std::ostream& os) const {
    os << "bulk: ";
    if (commands.size()) {
        auto last = std::prev(commands.end());
        std::copy(commands.begin(), last, std::ostream_iterator<std::string>(os, ", "));
        os << *last << std::endl;
    }
    else {
        os << std::endl;
    }
}

/**
 * @brief Log bulk to cout and file
 */
void Bulk::log() {
    output(std::cout);
    
    std::string fnamebase = "bulk" + std::to_string(start_time());
    std::string ext = ".log";
    // Ensure each bulk has unique file
    std::filesystem::path fpath = fnamebase + ext;
    for (int i = 0; std::filesystem::exists(fpath); i++) {
        fpath = fnamebase + "." + std::to_string(i) + ext;
    };
    std::ofstream f(fpath.generic_string());
    if (f) {
        output(f);
    };
}

 /*---------- Static Bulk ------------------------------------------*/

 /**
  * @brief Construct a new Static Bulk:: Static Bulk object
  * @param n maximum commands in  Bulk
  */
StaticBulk::StaticBulk(size_t n) :Bulk(n) {
    start = std::chrono::system_clock::now();
}

StaticBulk::~StaticBulk() {
    if (commands.size()) {
        log();
    }
}

/**
 * @brief Add command to Bulk
 * When Bulk is compleated or interrupted with new Dynamic bulk
 * it constructs and return pointer to new Bulk
 * @param cmd command
 * @return std::unique_ptr<Bulk> (nullptr) if bulk is not filled
 * @return std::unique_ptr<Bulk> to new Bulk if this bulk is filled
 */
std::unique_ptr<Bulk> StaticBulk::add_command(std::string cmd) {
    if (cmd == Bulk::cmd_bulk_open) {
        return std::unique_ptr<Bulk>(new DynamicBulk(max_commands));
    }
    else if (cmd == Bulk::cmd_bulk_close || cmd.empty()) {
        return nullptr; // input error? ignore it
    }

    commands.push_back(cmd);
    
    if (commands.size() == 1) {
        start = std::chrono::system_clock::now();
    }
    if (commands.size() == max_commands) {
        return std::unique_ptr<Bulk>(new StaticBulk(max_commands));
    }
    return nullptr;
}


/*---------- Dynamic Bulk -----------------------------------------*/

/**
 * @brief Construct a new Dynamic Bulk:: Dynamic Bulk object
 * @param n maximum commands in Bulk (Static Bulk)
 */
DynamicBulk::DynamicBulk(size_t n) :Bulk(n), brace_level(1) {
    // Dynamic bulk starts when it's created with open brace {
    start = std::chrono::system_clock::now();
}

DynamicBulk::~DynamicBulk() {
    if (brace_level == 0) {
        log();
    }
}

/**
 * @brief Add command to Bulk
 * When Bulk is compleated construct and return pointer to new Static Bulk
 * @param cmd command
 * @return std::unique_ptr<Bulk> (nullptr) if bulk is not compleate
 * @return std::unique_ptr<Bulk> to new Bulk if bulk is compleate
 */
std::unique_ptr<Bulk> DynamicBulk::add_command(std::string cmd) {
    if (cmd.empty()) {
        return nullptr;
    }
    else if (cmd == Bulk::cmd_bulk_open) {
        brace_level++;
    }
    else if (cmd == Bulk::cmd_bulk_close) {
        brace_level--;
        if (brace_level == 0) {
            return std::unique_ptr<Bulk>(new StaticBulk(max_commands));
        }
    }
    else {
        commands.push_back(cmd);
    }
    return nullptr;
}
