#include "gameboy.h"

using a = Z80g;

void a::OpxCB00()
{
    cycles = 2;
    
    uint8_t msb = (bReg & 0x80) >> 7;
    
    SetFlag(C, (bReg & 0x80) == 1);
    
    bReg << 1;
    bReg |= msb;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB01()
{
    cycles = 2;
    
    uint8_t msb = (cReg & 0x80) >> 7;
    
    SetFlag(C, (cReg & 0x80) == 1);
    
    cReg << 1;
    cReg |= msb;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB02()
{
    cycles = 2;
    
    uint8_t msb = (dReg & 0x80) >> 7;
    
    SetFlag(C, (dReg & 0x80) == 1);
    
    dReg << 1;
    dReg |= msb;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB03()
{
    cycles = 2;
    
    uint8_t msb = (eReg & 0x80) >> 7;
    
    SetFlag(C, (eReg & 0x80) == 1);
    
    eReg << 1;
    eReg |= msb;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB04()
{
    cycles = 2;
    
    uint8_t msb = (hReg & 0x80) >> 7;
    
    SetFlag(C, (hReg & 0x80) == 1);
    
    hReg << 1;
    hReg |= msb;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB05()
{
    cycles = 2;
    
    uint8_t msb = (lReg & 0x80) >> 7;
    
    SetFlag(C, (lReg & 0x80) == 1);
    
    lReg << 1;
    lReg |= msb;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB06()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);


    uint8_t msb = (data & 0x80) >> 7;
    
    SetFlag(C, (data & 0x80) == 1);
    
    data << 1;
    data |= msb;

    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB07()
{
    cycles = 2;
    
    uint8_t msb = (aReg & 0x80) >> 7;
    
    SetFlag(C, (aReg & 0x80) == 1);
    
    aReg << 1;
    aReg |= msb;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB08()
{
    cycles = 2;
    
    uint8_t lsb = (bReg & 0x01) << 7;
    
    SetFlag(C, (bReg & 0x01) == 1);
    
    bReg >> 1;
    bReg |= lsb;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB09()
{
    cycles = 2;
    
    uint8_t lsb = (cReg & 0x01) << 7;
    
    SetFlag(C, (cReg & 0x01) == 1);
    
    cReg >> 1;
    cReg |= lsb;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB0A()
{
    cycles = 2;
    
    uint8_t lsb = (dReg & 0x01) << 7;
    
    SetFlag(C, (dReg & 0x01) == 1);
    
    dReg >> 1;
    dReg |= lsb;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB0B()
{
    cycles = 2;
    
    uint8_t lsb = (eReg & 0x01) << 7;
    
    SetFlag(C, (eReg & 0x01) == 1);
    
    eReg >> 1;
    eReg |= lsb;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB0C()
{
    cycles = 2;
    
    uint8_t lsb = (hReg & 0x01) << 7;
    
    SetFlag(C, (hReg & 0x01) == 1);
    
    hReg >> 1;
    hReg |= lsb;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB0D()
{
    cycles = 2;
    
    uint8_t lsb = (lReg & 0x01) << 7;
    
    SetFlag(C, (lReg & 0x01) == 1);
    
    lReg >> 1;
    lReg |= lsb;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB0E()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);


    uint8_t lsb = (data & 0x01) << 7;
    
    SetFlag(C, (data & 0x01) == 1);
    
    data >> 1;
    data |= lsb;

    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB0F()
{
    cycles = 2;
    
    uint8_t lsb = (aReg & 0x01) << 7;
    
    SetFlag(C, (aReg & 0x01) == 1);
    
    aReg >> 1;
    aReg |= lsb;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB10()
{
    cycles = 2;
        
    bReg << 1;
    if (GetFlag(C) == 1)
    {
        bReg |= 0x01;
    }

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB11()
{
    cycles = 2;
        
    cReg << 1;
    if (GetFlag(C) == 1)
    {
        cReg |= 0x01;
    }

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB12()
{
    cycles = 2;
        
    dReg << 1;
    if (GetFlag(C) == 1)
    {
        dReg |= 0x01;
    }

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB13()
{
    cycles = 2;
        
    eReg << 1;
    if (GetFlag(C) == 1)
    {
        eReg |= 0x01;
    }

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB14()
{
    cycles = 2;
        
    hReg << 1;
    if (GetFlag(C) == 1)
    {
        hReg |= 0x01;
    }

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB15()
{
    cycles = 2;
        
    lReg << 1;
    if (GetFlag(C) == 1)
    {
        lReg |= 0x01;
    }

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB16()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data << 1;
    if (GetFlag(C) == 1)
    {
        data |= 0x01;
    }
    
    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB17()
{
    cycles = 2;
        
    aReg << 1;
    if (GetFlag(C) == 1)
    {
        aReg |= 0x01;
    }

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB18()
{
    cycles = 2;
        
    bReg >> 1;
    if (GetFlag(C) == 1)
    {
        bReg |= 0x80;
    }

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB19()
{
    cycles = 2;
        
    cReg >> 1;
    if (GetFlag(C) == 1)
    {
        cReg |= 0x80;
    }

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB1A()
{
    cycles = 2;
        
    dReg >> 1;
    if (GetFlag(C) == 1)
    {
        dReg |= 0x80;
    }

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB1B()
{
    cycles = 2;
        
    eReg >> 1;
    if (GetFlag(C) == 1)
    {
        eReg |= 0x80;
    }

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB1C()
{
    cycles = 2;
        
    hReg >> 1;
    if (GetFlag(C) == 1)
    {
        hReg |= 0x80;
    }

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB1D()
{
    cycles = 2;
        
    lReg >> 1;
    if (GetFlag(C) == 1)
    {
        lReg |= 0x80;
    }

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB1E()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data >> 1;
    if (GetFlag(C) == 1)
    {
        data |= 0x80;
    }
    
    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB1F()
{
    cycles = 2;
        
    aReg >> 1;
    if (GetFlag(C) == 1)
    {
        aReg |= 0x80;
    }

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    
}
void a::OpxCB20()
{
    cycles = 2;
    
    SetFlag(C, (bReg & 0x80) == 1);

    bReg << 1;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB21()
{
    cycles = 2;
    
    SetFlag(C, (cReg & 0x80) == 1);

    cReg << 1;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB22()
{
    cycles = 2;
    
    SetFlag(C, (dReg & 0x80) == 1);

    dReg << 1;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB23()
{
    cycles = 2;
    
    SetFlag(C, (eReg & 0x80) == 1);

    eReg << 1;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB24()
{
    cycles = 2;
    
    SetFlag(C, (hReg & 0x80) == 1);

    hReg << 1;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB25()
{
    cycles = 2;
    
    SetFlag(C, (lReg & 0x80) == 1);

    lReg << 1;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB26()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    SetFlag(C, (data & 0x80) == 1);

    data << 1;
    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB27()
{
    cycles = 2;
    
    SetFlag(C, (aReg & 0x80) == 1);

    aReg << 1;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB28()
{
    cycles = 2;
    uint8_t msb = (bReg & 0x80);
    SetFlag(C, (bReg & 0x01) == 1);

    bReg >> 1;
    bReg |= msb;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB29()
{
    cycles = 2;
    uint8_t msb = (cReg & 0x80);
    SetFlag(C, (cReg & 0x01) == 1);

    cReg >> 1;
    cReg |= msb;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB2A()
{
    cycles = 2;
    uint8_t msb = (dReg & 0x80);
    SetFlag(C, (dReg & 0x01) == 1);

    dReg >> 1;
    dReg |= msb;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB2B()
{
    cycles = 2;
    uint8_t msb = (eReg & 0x80);
    SetFlag(C, (eReg & 0x01) == 1);

    eReg >> 1;
    eReg |= msb;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB2C()
{
    cycles = 2;
    uint8_t msb = (hReg & 0x80);
    SetFlag(C, (hReg & 0x01) == 1);

    hReg >> 1;
    hReg |= msb;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB2D()
{
    cycles = 2;
    uint8_t msb = (lReg & 0x80);
    SetFlag(C, (lReg & 0x01) == 1);

    lReg >> 1;
    lReg |= msb;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB2E()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    uint8_t msb = (data & 0x80);

    SetFlag(C, (data & 0x01) == 1);

    data >> 1;
    data |= msb;
    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB2F()
{
    cycles = 2;
    uint8_t msb = (aReg & 0x80);

    SetFlag(C, (aReg & 0x01) == 1);

    aReg >> 1;
    aReg |= msb;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB30()
{
    cycles = 2;
    
    uint8_t lo = (bReg & 0x0F) << 4;
    uint8_t hi = (bReg & 0xF0) >> 4;

    bReg = 0x00;
    bReg |= lo;
    bReg |= hi;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB31()
{
    cycles = 2;
    
    uint8_t lo = (cReg & 0x0F) << 4;
    uint8_t hi = (cReg & 0xF0) >> 4;

    cReg = 0x00;
    cReg |= lo;
    cReg |= hi;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB32()
{
    cycles = 2;
    
    uint8_t lo = (dReg & 0x0F) << 4;
    uint8_t hi = (dReg & 0xF0) >> 4;

    dReg = 0x00;
    dReg |= lo;
    dReg |= hi;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB33()
{
    cycles = 2;
    
    uint8_t lo = (eReg & 0x0F) << 4;
    uint8_t hi = (eReg & 0xF0) >> 4;

    eReg = 0x00;
    eReg |= lo;
    eReg |= hi;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB34()
{
    cycles = 2;
    
    uint8_t lo = (hReg & 0x0F) << 4;
    uint8_t hi = (hReg & 0xF0) >> 4;

    hReg = 0x00;
    hReg |= lo;
    hReg |= hi;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB35()
{
    cycles = 2;
    
    uint8_t lo = (lReg & 0x0F) << 4;
    uint8_t hi = (lReg & 0xF0) >> 4;

    lReg = 0x00;
    lReg |= lo;
    lReg |= hi;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB36()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    uint8_t lo = (data & 0x0F) << 4;
    uint8_t hi = (data & 0xF0) >> 4;

    data = 0x00;
    data |= lo;
    data |= hi;

    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB37()
{
    cycles = 2;
    
    uint8_t lo = (aReg & 0x0F) << 4;
    uint8_t hi = (aReg & 0xF0) >> 4;

    aReg = 0x00;
    aReg |= lo;
    aReg |= hi;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void a::OpxCB38()
{
    cycles = 2;

    SetFlag(C, (bReg & 0x01) == 1);

    bReg >> 1;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB39()
{
    cycles = 2;

    SetFlag(C, (cReg & 0x01) == 1);

    cReg >> 1;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB3A()
{
    cycles = 2;

    SetFlag(C, (dReg & 0x01) == 1);

    dReg >> 1;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB3B()
{
    cycles = 2;

    SetFlag(C, (eReg & 0x01) == 1);

    eReg >> 1;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB3C()
{
    cycles = 2;

    SetFlag(C, (hReg & 0x01) == 1);

    hReg >> 1;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB3D()
{
    cycles = 2;

    SetFlag(C, (lReg & 0x01) == 1);

    lReg >> 1;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB3E()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    SetFlag(C, (data & 0x01) == 1);
    
    data >> 1;
    write(HL, data);

    SetFlag(Z, data == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB3F()
{
    cycles = 2;
    
    SetFlag(C, (aReg & 0x01) == 1);
    
    aReg >> 1;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
}
void a::OpxCB40()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB41()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB42()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB43()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB44()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB45()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB46()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    
    SetFlag(Z, ((read(HL)) & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB47()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x01) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB48()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB49()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB4A()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB4B()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB4C()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB4D()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB4E()
{
    cycles = 4;

    uint16_t HL = ((hReg << 8) | lReg);
    
    SetFlag(Z, ((read(HL)) & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB4F()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x02) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB50()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB51()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB52()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB53()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB54()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB55()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB56()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(Z, ((read(HL)) & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB57()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x04) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB58()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB59()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB5A()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB5B()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB5C()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB5D()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB5E()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(Z, ((read(HL)) & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB5F()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x08) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB60()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB61()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB62()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB63()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB64()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB65()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB66()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(Z, ((read(HL)) & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB67()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x10) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB68()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB69()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB6A()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB6B()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB6C()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB6D()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB6E()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(Z, ((read(HL)) & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB6F()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x20) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB70()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB71()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB72()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB73()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB74()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB75()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB76()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(Z, ((read(HL)) & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB77()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x40) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB78()
{
    cycles = 2;
    
    SetFlag(Z, (bReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB79()
{
    cycles = 2;
    
    SetFlag(Z, (cReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB7A()
{
    cycles = 2;
    
    SetFlag(Z, (dReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB7B()
{
    cycles = 2;
    
    SetFlag(Z, (eReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB7C()
{
    cycles = 2;
    
    SetFlag(Z, (hReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB7D()
{
    cycles = 2;
    
    SetFlag(Z, (lReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB7E()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(Z, ((read(HL)) & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB7F()
{
    cycles = 2;
    
    SetFlag(Z, (aReg & 0x80) == 0);
    SetFlag(N, false);
    SetFlag(H, true);
}
void a::OpxCB80()
{
    cycles = 2;
    
    bReg &= ~(1 << 0);
}
void a::OpxCB81()
{
    cycles = 2;
    
    cReg &= ~(1 << 0);
}
void a::OpxCB82()
{
    cycles = 2;
    
    dReg &= ~(1 << 0);
}
void a::OpxCB83()
{
    cycles = 2;
    
    eReg &= ~(1 << 0);
}
void a::OpxCB84()
{
    cycles = 2;
    
    hReg &= ~(1 << 0);
}
void a::OpxCB85()
{
    cycles = 2;
    
    lReg &= ~(1 << 0);
}
void a::OpxCB86()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 0);

    write(HL, data);
}
void a::OpxCB87()
{
    cycles = 2;
    
    aReg &= ~(1 << 0);
}
void a::OpxCB88()
{
    cycles = 2;
    
    bReg &= ~(1 << 1);
}
void a::OpxCB89()
{
    cycles = 2;
    
    cReg &= ~(1 << 1);
}
void a::OpxCB8A()
{
    cycles = 2;
    
    dReg &= ~(1 << 1);
}
void a::OpxCB8B()
{
    cycles = 2;
    
    eReg &= ~(1 << 1);
}
void a::OpxCB8C()
{
    cycles = 2;
    
    hReg &= ~(1 << 1);
}
void a::OpxCB8D()
{
    cycles = 2;
    
    lReg &= ~(1 << 1);
}
void a::OpxCB8E()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 1);

    write(HL, data);
}
void a::OpxCB8F()
{
    cycles = 2;
    
    aReg &= ~(1 << 1);
}
void a::OpxCB90()
{
    cycles = 2;
    
    bReg &= ~(1 << 2);
}
void a::OpxCB91()
{
    cycles = 2;
    
    cReg &= ~(1 << 2);
}
void a::OpxCB92()
{
    cycles = 2;
    
    dReg &= ~(1 << 2);
}
void a::OpxCB93()
{
    cycles = 2;
    
    eReg &= ~(1 << 2);
}
void a::OpxCB94()
{
    cycles = 2;
    
    hReg &= ~(1 << 2);
}
void a::OpxCB95()
{
    cycles = 2;
    
    lReg &= ~(1 << 2);
}
void a::OpxCB96()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 2);

    write(HL, data);
}
void a::OpxCB97()
{
    cycles = 2;
    
    aReg &= ~(1 << 2);
}
void a::OpxCB98()
{
    cycles = 2;
    
    bReg &= ~(1 << 3);
}
void a::OpxCB99()
{
    cycles = 2;
    
    cReg &= ~(1 << 3);
}
void a::OpxCB9A()
{
    cycles = 2;
    
    dReg &= ~(1 << 3);
}
void a::OpxCB9B()
{
    cycles = 2;
    
    eReg &= ~(1 << 3);
}
void a::OpxCB9C()
{
    cycles = 2;
    
    hReg &= ~(1 << 3);
}
void a::OpxCB9D()
{
    cycles = 2;
    
    lReg &= ~(1 << 3);
}
void a::OpxCB9E()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 3);

    write(HL, data);
}
void a::OpxCB9F()
{
    cycles = 2;
    
    aReg &= ~(1 << 3);
}
void a::OpxCBA0()
{
    cycles = 2;
    
    bReg &= ~(1 << 4);
}
void a::OpxCBA1()
{
    cycles = 2;
    
    cReg &= ~(1 << 4);
}
void a::OpxCBA2()
{
    cycles = 2;
    
    dReg &= ~(1 << 4);
}
void a::OpxCBA3()
{
    cycles = 2;
    
    eReg &= ~(1 << 4);
}
void a::OpxCBA4()
{
    cycles = 2;
    
    hReg &= ~(1 << 4);
}
void a::OpxCBA5()
{
    cycles = 2;
    
    lReg &= ~(1 << 4);
}
void a::OpxCBA6()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 4);

    write(HL, data);
}
void a::OpxCBA7()
{
    cycles = 2;
    
    aReg &= ~(1 << 4);
}
void a::OpxCBA8()
{
    cycles = 2;
    
    bReg &= ~(1 << 5);
}
void a::OpxCBA9()
{
    cycles = 2;
    
    cReg &= ~(1 << 5);
}
void a::OpxCBAA()
{
    cycles = 2;
    
    dReg &= ~(1 << 5);
}
void a::OpxCBAB()
{
    cycles = 2;
    
    eReg &= ~(1 << 5);
}
void a::OpxCBAC()
{
    cycles = 2;
    
    hReg &= ~(1 << 5);
}
void a::OpxCBAD()
{
    cycles = 2;
    
    lReg &= ~(1 << 5);
}
void a::OpxCBAE()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 5);

    write(HL, data);
}
void a::OpxCBAF()
{
    cycles = 2;
    
    aReg &= ~(1 << 5);
}
void a::OpxCBB0()
{
    cycles = 2;
    
    bReg &= ~(1 << 6);
}
void a::OpxCBB1()
{
    cycles = 2;
    
    cReg &= ~(1 << 6);
}
void a::OpxCBB2()
{
    cycles = 2;
    
    dReg &= ~(1 << 6);
}
void a::OpxCBB3()
{
    cycles = 2;
    
    eReg &= ~(1 << 6);
}
void a::OpxCBB4()
{
    cycles = 2;
    
    hReg &= ~(1 << 6);
}
void a::OpxCBB5()
{
    cycles = 2;
    
    lReg &= ~(1 << 6);
}
void a::OpxCBB6()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 6);

    write(HL, data);
}
void a::OpxCBB7()
{
    cycles = 2;
    
    aReg &= ~(1 << 6);
}
void a::OpxCBB8()
{
    cycles = 2;
    
    bReg &= ~(1 << 7);
}
void a::OpxCBB9()
{
    cycles = 2;
    
    cReg &= ~(1 << 7);
}
void a::OpxCBBA()
{
    cycles = 2;
    
    dReg &= ~(1 << 7);
}
void a::OpxCBBB()
{
    cycles = 2;
    
    eReg &= ~(1 << 7);
}
void a::OpxCBBC()
{
    cycles = 2;
    
    hReg &= ~(1 << 7);
}
void a::OpxCBBD()
{
    cycles = 2;
    
    lReg &= ~(1 << 7);
}
void a::OpxCBBE()
{
    cycles = 4;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);

    data &= ~(1 << 7);

    write(HL, data);
}
void a::OpxCBBF()
{
    cycles = 2;
    
    aReg &= ~(1 << 7);
}
void a::OpxCBC0()
{
    cycles = 2;
    
    bReg |= 0x01;
}
void a::OpxCBC1()
{
    cycles = 2;
    
    cReg |= 0x01;
}
void a::OpxCBC2()
{
    cycles = 2;

    dReg |= 0x01;
}
void a::OpxCBC3()
{
    cycles = 2;

    eReg |= 0x01;
}
void a::OpxCBC4()
{
    cycles = 2;

    hReg |= 0x01;
}
void a::OpxCBC5()
{
    cycles = 2;

    lReg |= 0x01;
}
void a::OpxCBC6()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x01;

    write(HL, data);
}
void a::OpxCBC7()
{
    aReg |= 0x01;
}
void a::OpxCBC8()
{
    cycles = 2;

    bReg |= 0x02;
}
void a::OpxCBC9()
{
    cycles = 2;

    cReg |= 0x02;
}
void a::OpxCBCA()
{
    cycles = 2;

    dReg |= 0x02;
}
void a::OpxCBCB()
{
    cycles = 2;

    eReg |= 0x2;
}
void a::OpxCBCC()
{
    cycles = 2;

    hReg |= 0x02;
}
void a::OpxCBCD()
{
    cycles = 2;

    lReg |= 0x02;
}
void a::OpxCBCE()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x02;

    write(HL, data);
}
void a::OpxCBCF()
{
    cycles = 2;

    aReg |= 0x02;
}
void a::OpxCBD0()
{
    cycles = 2;

    bReg |= 0x04;
}
void a::OpxCBD1()
{
    cycles = 2;

    cReg |= 0x04;
}
void a::OpxCBD2()
{
    cycles = 2;

    dReg |= 0x04;
}
void a::OpxCBD3()
{
    cycles = 2;

    eReg |= 0x04;
}
void a::OpxCBD4()
{
    cycles = 2;

    hReg |= 0x04;
}
void a::OpxCBD5()
{
    cycles = 2;

    lReg |= 0x04;
}
void a::OpxCBD6()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x04;

    write(HL, data);
}
void a::OpxCBD7()
{
    cycles = 2;

    aReg |= 0x04;
}
void a::OpxCBD8()
{
    cycles = 2;

    bReg |= 0x08;
}
void a::OpxCBD9()
{
    cycles = 2;

    cReg |= 0x08;
}
void a::OpxCBDA()
{
    cycles = 2;

    dReg |= 0x08;
}
void a::OpxCBDB()
{
    cycles = 2;

    eReg |= 0x08;
}
void a::OpxCBDC()
{
    cycles = 2;

    hReg |= 0x08;
}
void a::OpxCBDD()
{
    cycles = 2;

    lReg |= 0x08;
}
void a::OpxCBDE()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x08;

    write(HL, data);
}
void a::OpxCBDF()
{
    cycles = 2;

    aReg |= 0x08;
}
void a::OpxCBE0()
{
    cycles = 2;

    bReg |= 0x10;
}
void a::OpxCBE1()
{
    cycles = 2;

    cReg |= 0x10;
}
void a::OpxCBE2()
{
    cycles = 2;

    dReg |= 0x10;
}
void a::OpxCBE3()
{
    cycles = 2;

    eReg |= 0x10;
}
void a::OpxCBE4()
{
    cycles = 2;

    hReg |= 0x10;
}
void a::OpxCBE5()
{
    cycles = 2;

    lReg |= 0x10;
}
void a::OpxCBE6()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x10;

    write(HL, data);
}
void a::OpxCBE7()
{
    cycles = 2;

    aReg |= 0x10;
}
void a::OpxCBE8()
{
    cycles = 2;

    bReg |= 0x20;
}
void a::OpxCBE9()
{
    cycles = 2;

    cReg |= 0x20;
}
void a::OpxCBEA()
{
    cycles = 2;

    dReg |= 0x20;
}
void a::OpxCBEB()
{
    cycles = 2;

    eReg |= 0x20;
}
void a::OpxCBEC()
{
    cycles = 2;

    hReg |= 0x20;
}
void a::OpxCBED()
{
    cycles = 2;

    lReg |= 0x20;
}
void a::OpxCBEE()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x20;

    write(HL, data);
}
void a::OpxCBEF()
{
    cycles = 2;

    aReg |= 0x20;
}
void a::OpxCBF0()
{
    cycles = 2;

    bReg |= 0x40;
}
void a::OpxCBF1()
{
    cycles = 2;

    cReg |= 0x40;
}
void a::OpxCBF2()
{
    cycles = 2;

    dReg |= 0x40;
}
void a::OpxCBF3()
{
    cycles = 2;

    eReg |= 0x40;
}
void a::OpxCBF4()
{
    cycles = 2;

    hReg |= 0x40;
}
void a::OpxCBF5()
{
    cycles = 2;

    lReg |= 0x40;
}
void a::OpxCBF6()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x40;

    write(HL, data);
}
void a::OpxCBF7()
{
    cycles = 2;

    aReg |= 0x40;
}
void a::OpxCBF8()
{
    cycles = 2;

    bReg |= 0x80;
}
void a::OpxCBF9()
{
    cycles = 2;

    cReg |= 0x80;
}
void a::OpxCBFA()
{
    cycles = 2;

    dReg |= 0x80;
}
void a::OpxCBFB()
{
    cycles = 2;

    eReg |= 0x80;
}
void a::OpxCBFC()
{
    cycles = 2;

    hReg |= 0x80;
}
void a::OpxCBFD()
{
    cycles = 2;

    lReg |= 0x80;
}
void a::OpxCBFE()
{
    cycles = 4;
    
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t data = read(HL);
    
    data |= 0x80;

    write(HL, data);
}
void a::OpxCBFF()
{
    cycles = 2;

    aReg |= 0x80;
}