#pragma once
#include <cstdint>
#include <fstream>
#include <memory>


class Bus;

class Cartridge
{
    public:
    
    Cartridge();
    ~Cartridge();
    
    Bus *bus = nullptr;

    uint8_t m_header;

    
    
    
    
    void LoadRom(char const* filename);
    void connectCartridge(Bus *p){bus = p;}

};