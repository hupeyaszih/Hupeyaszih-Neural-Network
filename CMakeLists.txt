cmake_minimum_required(VERSION 3.16)

project(hupeyaszih-neural-network LANGUAGES C)

set(CMAKE_C\_STANDARD 11)
set(CMAKE_C\_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hupeyaszih-neural-network
    src/main.c
)

target_include_directories(hupeyaszih-neural-network
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_custom_target(run
    COMMAND hupeyaszih-neural-network
    DEPENDS hupeyaszih-neural-network
    COMMENT "Hupeyaszih Neural Network is running"
)

add_custom_target(docs
    COMMAND doxygen Doxyfile
    WORKING_DIRECTORY ../
    COMMENT "Doxygen documentation is generating!"
)
