#pragma once
#include <cstdint>

class Bus;

class Cartridge
{
    Bus *ConnectCartridge = nullptr;
    
    private:

        uint8_t m_title;

};