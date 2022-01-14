#pragma once
#include <cstdint>
#include <fstream>
#include <memory>

#include "NoMBC.h"

class Cartridge
{
    public:
    
    Cartridge(const std::string Filename);
    ~Cartridge();
    
    std::unique_ptr<uint8_t[]> m_Ram;   
    std::unique_ptr<uint8_t[]> m_Rom;


    std::unique_ptr<MBC_Base> m_MemoryController;

    
    

    bool c_Read(uint16_t addr, uint8_t &data);
    bool c_Write(uint16_t addr, uint8_t data);

};