#pragma once

#include <cstdint>

class Bus;

class Z80g
{
    public:
    
        Z80g();
        
    private:
    
        Bus *bus = nullptr;

    void Opx00();   void Opx01();   void Opx02();    void Opx03();    
    void Opx10();   void Opx11();   void Opx12();    void Opx13();
    void Opx20();   void Opx21();   void Opx22();    void Opx23();
    void Opx30();   void Opx31();   void Opx32();    void Opx33();
    void Opx40();   void Opx41();   void Opx42();    void Opx43();
    void Opx50();   void Opx51();   void Opx52();    void Opx53();
    void Opx60();   void Opx61();   void Opx62();    void Opx63();
    void Opx70();   void Opx71();   void Opx72();    void Opx73(); 
    void Opx80();   void Opx81();   void Opx82();    void Opx83();
    void Opx90();   void Opx91();   void Opx92();    void Opx93();
    void OpxA0();   void OpxA1();   void OpxA2();    void OpxA3();
    void OpxB0();   void OpxB1();   void OpxB2();    void OpxB3();
    void OpxC0();   void OpxC1();   void OpxC2();    void OpxC3();
    void OpxD0();   void OpxD1();   void OpxD2();
    void OpxE0();   void OpxE1();   void OpxE2();   
    void OpxF0();   void OpxF1();   void OpxF2();    void OpxF3();
       
    void Opx04();   void Opx05();   void Opx06();   void Opx07();                      
    void Opx14();   void Opx15();   void Opx16();   void Opx17();                      
    void Opx24();   void Opx25();   void Opx26();   void Opx27();                         
    void Opx34();   void Opx35();   void Opx36();   void Opx37();                         
    void Opx44();   void Opx45();   void Opx46();   void Opx47();                      
    void Opx54();   void Opx55();   void Opx56();   void Opx57();                      
    void Opx64();   void Opx65();   void Opx66();   void Opx67();                      
    void Opx74();   void Opx75();   void Opx76();   void Opx77();                      
    void Opx84();   void Opx85();   void Opx86();   void Opx87();                      
    void Opx94();   void Opx95();   void Opx96();   void Opx97();                      
    void OpxA4();   void OpxA5();   void OpxA6();   void OpxA7();                      
    void OpxB4();   void OpxB5();   void OpxB6();   void OpxB7();                      
    void OpxC4();   void OpxC5();   void OpxC6();   void OpxC7();                          
    void OpxD4();   void OpxD5();   void OpxD6();   void OpxD7();                          
                    void OpxE5();   void OpxE6();   void OpxE7();                      
                    void OpxF5();   void OpxF6();   void OpxF7();                      

    void Opx08();   void Opx09();   void Opx0A();   void Opx0B();
    void Opx18();   void Opx19();   void Opx1A();   void Opx1B();
    void Opx28();   void Opx29();   void Opx2A();   void Opx2B();
    void Opx38();   void Opx39();   void Opx3A();   void Opx3B();
    void Opx48();   void Opx49();   void Opx4A();   void Opx4B();
    void Opx58();   void Opx59();   void Opx5A();   void Opx5B();
    void Opx68();   void Opx69();   void Opx6A();   void Opx6B();
    void Opx78();   void Opx79();   void Opx7A();   void Opx7B();
    void Opx88();   void Opx89();   void Opx8A();   void Opx8B();
    void Opx98();   void Opx99();   void Opx9A();   void Opx9B();
    void OpxA8();   void OpxA9();   void OpxAA();   void OpxAB();
    void OpxB8();   void OpxB9();   void OpxBA();   void OpxBB();   
    void OpxC8();   void OpxC9();   void OpxCA();   
    void OpxD8();   void OpxD9();   void OpxDA();   
    void OpxE8();   void OpxE9();   void OpxEA();   
    void OpxF8();   void OpxF9();   void OpxFA();   void OpxFB();
    
    void Opx0C();   void Opx0D();   void Opx0E();   void Opx0F();  
    void Opx1C();   void Opx1D();   void Opx1E();   void Opx1F();    
    void Opx2C();   void Opx2D();   void Opx2E();   void Opx2F(); 
    void Opx3C();   void Opx3D();   void Opx3E();   void Opx3F();
    void Opx4C();   void Opx4D();   void Opx4E();   void Opx4F();    
    void Opx5C();   void Opx5D();   void Opx5E();   void Opx5F();    
    void Opx6C();   void Opx6D();   void Opx6E();   void Opx6F(); 
    void Opx7C();   void Opx7D();   void Opx7E();   void Opx7F();
    void Opx8C();   void Opx8D();   void Opx8E();   void Opx8F();    
    void Opx9C();   void Opx9D();   void Opx9E();   void Opx9F();    
    void OpxAC();   void OpxAD();   void OpxAE();   void OpxAF();   
    void OpxBC();   void OpxBD();   void OpxBE();   void OpxBF();
    void OpxCC();   void OpxCD();   void OpxCE();   void OpxCF();   
    void OpxDC();                   void OpxDE();   void OpxDF();   
                                    void OpxEE();   void OpxEF();   
                                    void OpxFE();   void OpxFF();

    void nullop(){};

    // CB Opcodes
    void OpxCB00();   void OpxCB01();   void OpxCB02();   void OpxCB03();
    void OpxCB10();   void OpxCB11();   void OpxCB12();   void OpxCB13();
    void OpxCB20();   void OpxCB21();   void OpxCB22();   void OpxCB23();
    void OpxCB30();   void OpxCB31();   void OpxCB32();   void OpxCB33();
    void OpxCB40();   void OpxCB41();   void OpxCB42();   void OpxCB43();
    void OpxCB50();   void OpxCB51();   void OpxCB52();   void OpxCB53();
    void OpxCB60();   void OpxCB61();   void OpxCB62();   void OpxCB63();
    void OpxCB70();   void OpxCB71();   void OpxCB72();   void OpxCB73();
    void OpxCB80();   void OpxCB81();   void OpxCB82();   void OpxCB83();
    void OpxCB90();   void OpxCB91();   void OpxCB92();   void OpxCB93();
    void OpxCBA0();   void OpxCBA1();   void OpxCBA2();   void OpxCBA3();
    void OpxCBB0();   void OpxCBB1();   void OpxCBB2();   void OpxCBB3();
    void OpxCBC0();   void OpxCBC1();   void OpxCBC2();   void OpxCBC3();
    void OpxCBD0();   void OpxCBD1();   void OpxCBD2();   void OpxCBD3();
    void OpxCBE0();   void OpxCBE1();   void OpxCBE2();   void OpxCBE3();
    void OpxCBF0();   void OpxCBF1();   void OpxCBF2();   void OpxCBF3();
       
    void OpxCB04();   void OpxCB05();   void OpxCB06();   void OpxCB07(); 
    void OpxCB14();   void OpxCB15();   void OpxCB16();   void OpxCB17(); 
    void OpxCB24();   void OpxCB25();   void OpxCB26();   void OpxCB27(); 
    void OpxCB34();   void OpxCB35();   void OpxCB36();   void OpxCB37(); 
    void OpxCB44();   void OpxCB45();   void OpxCB46();   void OpxCB47(); 
    void OpxCB54();   void OpxCB55();   void OpxCB56();   void OpxCB57(); 
    void OpxCB64();   void OpxCB65();   void OpxCB66();   void OpxCB67(); 
    void OpxCB74();   void OpxCB75();   void OpxCB76();   void OpxCB77(); 
    void OpxCB84();   void OpxCB85();   void OpxCB86();   void OpxCB87(); 
    void OpxCB94();   void OpxCB95();   void OpxCB96();   void OpxCB97(); 
    void OpxCBA4();   void OpxCBA5();   void OpxCBA6();   void OpxCBA7(); 
    void OpxCBB4();   void OpxCBB5();   void OpxCBB6();   void OpxCBB7(); 
    void OpxCBC4();   void OpxCBC5();   void OpxCBC6();   void OpxCBC7(); 
    void OpxCBD4();   void OpxCBD5();   void OpxCBD6();   void OpxCBD7(); 
    void OpxCBE4();   void OpxCBE5();   void OpxCBE6();   void OpxCBE7(); 
    void OpxCBF4();   void OpxCBF5();   void OpxCBF6();   void OpxCBF7(); 

    void OpxCB08();   void OpxCB09();   void OpxCB0A();   void OpxCB0B();
    void OpxCB18();   void OpxCB19();   void OpxCB1A();   void OpxCB1B();
    void OpxCB28();   void OpxCB29();   void OpxCB2A();   void OpxCB2B();
    void OpxCB38();   void OpxCB39();   void OpxCB3A();   void OpxCB3B();
    void OpxCB48();   void OpxCB49();   void OpxCB4A();   void OpxCB4B();
    void OpxCB58();   void OpxCB59();   void OpxCB5A();   void OpxCB5B();
    void OpxCB68();   void OpxCB69();   void OpxCB6A();   void OpxCB6B();
    void OpxCB78();   void OpxCB79();   void OpxCB7A();   void OpxCB7B();
    void OpxCB88();   void OpxCB89();   void OpxCB8A();   void OpxCB8B();
    void OpxCB98();   void OpxCB99();   void OpxCB9A();   void OpxCB9B();
    void OpxCBA8();   void OpxCBA9();   void OpxCBAA();   void OpxCBAB();
    void OpxCBB8();   void OpxCBB9();   void OpxCBBA();   void OpxCBBB(); 
    void OpxCBC8();   void OpxCBC9();   void OpxCBCA();   void OpxCBCB();
    void OpxCBD8();   void OpxCBD9();   void OpxCBDA();   void OpxCBDB();
    void OpxCBE8();   void OpxCBE9();   void OpxCBEA();   void OpxCBEB();
    void OpxCBF8();   void OpxCBF9();   void OpxCBFA();   void OpxCBFB();

    
    void OpxCB0C();   void OpxCB0D();   void OpxCB0E();   void OpxCB0F(); 
    void OpxCB1C();   void OpxCB1D();   void OpxCB1E();   void OpxCB1F(); 
    void OpxCB2C();   void OpxCB2D();   void OpxCB2E();   void OpxCB2F(); 
    void OpxCB3C();   void OpxCB3D();   void OpxCB3E();   void OpxCB3F();
    void OpxCB4C();   void OpxCB4D();   void OpxCB4E();   void OpxCB4F(); 
    void OpxCB5C();   void OpxCB5D();   void OpxCB5E();   void OpxCB5F(); 
    void OpxCB6C();   void OpxCB6D();   void OpxCB6E();   void OpxCB6F(); 
    void OpxCB7C();   void OpxCB7D();   void OpxCB7E();   void OpxCB7F();
    void OpxCB8C();   void OpxCB8D();   void OpxCB8E();   void OpxCB8F(); 
    void OpxCB9C();   void OpxCB9D();   void OpxCB9E();   void OpxCB9F(); 
    void OpxCBAC();   void OpxCBAD();   void OpxCBAE();   void OpxCBAF(); 
    void OpxCBBC();   void OpxCBBD();   void OpxCBBE();   void OpxCBBF();
    void OpxCBCC();   void OpxCBCD();   void OpxCBCE();   void OpxCBCF(); 
    void OpxCBDC();   void OpxCBDD();   void OpxCBDE();   void OpxCBDF(); 
    void OpxCBEC();   void OpxCBED();   void OpxCBEE();   void OpxCBEF(); 
    void OpxCBFC();   void OpxCBFD();   void OpxCBFE();   void OpxCBFF();

    public:
    

    // These are all treated as registers
    uint8_t aReg{0x1}, fReg{0x0};   //A and F registers are treated as 2 8 bit registers, but can be combined.
    uint8_t bReg{0x0}, cReg{0x13};   //B and C registers are treated exactly as A and F.
    uint8_t dReg{0x0}, eReg{0xD8};   //D and E are exactly the same as BC
    uint8_t hReg{0x1}, lReg{0x4D};   //Can be used as 2 8-bit registers or combine them to make a 16-bit register used to point at memory locations
    uint16_t sp{0xFFFE};             //Stack Pointer
    uint16_t pc = 0x100;             //Program Counter
    uint16_t Opcode{};
    
    uint8_t cycles{};
    
    

    bool Stop = false;
    

    enum FLAGS : uint8_t
    {
        Z = (1 << 7),   //Zero Flag
        N = (1 << 6),   //Subtraction Flag
        H = (1 << 5),   //Half carry Flag
        C = (1 << 4),   //Carry Flag
    };
    
    uint8_t GetFlag(FLAGS f);
    void    SetFlag(FLAGS f, bool v);
    


    void Clock();
    void ResetCpu();
    void ServiceInterrupts();
    void DoDmaTransfer(uint16_t addr, uint8_t data);


    
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);


    typedef void(Z80g::*FunctionPointers)(void);
    FunctionPointers table[0xFF + 1]{&Z80g::nullop};
    FunctionPointers tableCB[0xFF +1]{&Z80g::nullop};
    
    
    void connectBus(Bus *p){bus = p;}
};