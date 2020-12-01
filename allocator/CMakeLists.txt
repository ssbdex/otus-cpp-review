cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

function(append_warn_flags target)
    if (MSVC)
        target_compile_options( ${target} PRIVATE /W4)
    else ()
       target_compile_options( ${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif() 
endfunction()

# Project setup 
project(ssb-alloc VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#find_package(Boost REQUIRED) 
add_executable(ssb-alloc main.cpp)
configure_file(config.h.in config.h)
target_include_directories(ssb-alloc 
    PRIVATE ${CMAKE_BINARY_DIR}
    #${Boost_INCLUDE_DIRS}
    )
set_target_properties(ssb-alloc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
append_warn_flags(ssb-alloc)

# Package setup
install(TARGETS ssb-alloc RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT ssbdex@yandex.ru)
include(CPack)

# Install rule
install(TARGETS ssb-alloc DESTINATION bin)