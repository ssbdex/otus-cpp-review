cmake_minimum_required(VERSION 3.0.0)

set(project_name "bulk") 

function(append_warn_flags target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else ()
       target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif() 
endfunction()


project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
add_executable( ${project_name} main.cpp bulk.cpp )

set_target_properties(${project_name} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

append_warn_flags(${project_name})

# Package setup
install(TARGETS ${project_name} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT ssbdex@yandex.ru)
include(CPack)


include(CTest)
enable_testing()



