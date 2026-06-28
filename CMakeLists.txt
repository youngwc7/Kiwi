cmake_minimum_required(VERSION 3.16)
project(Kiwi)
 
set(CMAKE_CXX_STANDARD 17)
 
 
# Source files
file(GLOB SOURCES
    "src/*.cpp"
)
 
add_executable(Kiwi ${SOURCES})
 
# Link SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(Kiwi sfml-graphics sfml-window sfml-system)
 
# Include headers
target_include_directories(Kiwi PRIVATE src/include)
