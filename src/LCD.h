#pragma once

#include <memory>



class Bus;

class LCD
{
private:
    
    Bus* ptr = nullptr;
    
public:
    LCD();
    ~LCD();


    std::unique_ptr<uint8_t[]> m_VRAM;

    void connectScreen(Bus* p){ptr = p;}
};

