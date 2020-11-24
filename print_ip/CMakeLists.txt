cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

function(append_warn_flags target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else ()
       target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif() 
endfunction()


project(hw3 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
add_executable(print_ip main.cpp)
set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
append_warn_flags(print_ip)


include(CTest)
enable_testing()



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
