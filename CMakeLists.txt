cmake_minimum_required(VERSION 3.28)
project(baitapQ1805)

set(CMAKE_CXX_STANDARD 17)

add_executable(baitapQ1805 main.cpp
        Game.cpp
        Game.h)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "F:/SFML/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)

include_directories(F:/SFML/SFML-2.6.1/include)

target_link_libraries(baitapQ1805 sfml-graphics sfml-audio)
