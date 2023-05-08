cmake_minimum_required(VERSION 3.18.4)
project(gameboy)

find_package(SDL2 REQUIRED)

add_executable(gameboy
    src/main.cpp
    src/Z8080.cpp
    src/bus.cpp
    src/cbOpcodes.cpp
    src/cartridge.cpp
    src/NoMBC.cpp
    src/MBC.cpp
    src/MBC1.cpp
    src/Timer.cpp
    src/PPU.cpp 
)

target_link_libraries(gameboy PRIVATE ${SDL2_LIBRARIES})



