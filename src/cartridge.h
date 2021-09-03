#pragma once
#include <cstdint>
#include <fstream>
#include <memory>


class Bus;

class Cartridge
{
    public:
    Bus *bus = nullptr;

    uint8_t m_header;

    
    
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
    
    void LoadRom(char const* filename);
    void connectCartridge(Bus *p){bus = p;}

};