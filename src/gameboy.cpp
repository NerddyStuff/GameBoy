#include <iostream>
#include <fstream>
#include "gameboy.h"
#include "bus.h"


Z80g::Z80g()
{   
    sp = 0xFFFE;
    pc = 0x100;
    Opcode = 0;

    aReg = 0x00;    //  Resets all the registers
    bReg = 0x00;    //
    cReg = 0x00;    //
    dReg = 0x00;    //
    eReg = 0x00;    //
    hReg = 0x00;    //
    lReg = 0x00;    //

    SetFlag(Z, false);  //  Resets the flags
    SetFlag(N, false);  //
    SetFlag(H, false);  //
    SetFlag(C, false);  //
    
    write(0xFF00, 0x3F);    // Resets the button registers

    table[0x00] = {&Z80g::Opx00};   table[0x10] = {&Z80g::Opx10};   table[0x20] = {&Z80g::Opx20};   table[0x30] = {&Z80g::Opx30};   table[0x40] = {&Z80g::Opx40};   table[0x50] = {&Z80g::Opx50};   table[0x60] = {&Z80g::Opx60};   table[0x70] = {&Z80g::Opx70};
    table[0x01] = {&Z80g::Opx01};   table[0x11] = {&Z80g::Opx11};   table[0x21] = {&Z80g::Opx21};   table[0x31] = {&Z80g::Opx31};   table[0x41] = {&Z80g::Opx41};   table[0x51] = {&Z80g::Opx51};   table[0x61] = {&Z80g::Opx61};   table[0x71] = {&Z80g::Opx71};
    table[0x02] = {&Z80g::Opx02};   table[0x12] = {&Z80g::Opx12};   table[0x22] = {&Z80g::Opx22};   table[0x32] = {&Z80g::Opx32};   table[0x42] = {&Z80g::Opx42};   table[0x52] = {&Z80g::Opx52};   table[0x62] = {&Z80g::Opx62};   table[0x72] = {&Z80g::Opx72};
    table[0x03] = {&Z80g::Opx03};   table[0x13] = {&Z80g::Opx13};   table[0x23] = {&Z80g::Opx23};   table[0x33] = {&Z80g::Opx33};   table[0x43] = {&Z80g::Opx43};   table[0x53] = {&Z80g::Opx53};   table[0x63] = {&Z80g::Opx63};   table[0x73] = {&Z80g::Opx73};
    table[0x04] = {&Z80g::Opx04};   table[0x14] = {&Z80g::Opx14};   table[0x24] = {&Z80g::Opx24};   table[0x34] = {&Z80g::Opx34};   table[0x44] = {&Z80g::Opx44};   table[0x54] = {&Z80g::Opx54};   table[0x64] = {&Z80g::Opx64};   table[0x74] = {&Z80g::Opx74};
    table[0x05] = {&Z80g::Opx05};   table[0x15] = {&Z80g::Opx15};   table[0x25] = {&Z80g::Opx25};   table[0x35] = {&Z80g::Opx35};   table[0x45] = {&Z80g::Opx45};   table[0x55] = {&Z80g::Opx55};   table[0x65] = {&Z80g::Opx65};   table[0x75] = {&Z80g::Opx75};
    table[0x06] = {&Z80g::Opx06};   table[0x16] = {&Z80g::Opx16};   table[0x26] = {&Z80g::Opx26};   table[0x36] = {&Z80g::Opx36};   table[0x46] = {&Z80g::Opx46};   table[0x56] = {&Z80g::Opx56};   table[0x66] = {&Z80g::Opx66};   table[0x76] = {&Z80g::Opx76};
    table[0x07] = {&Z80g::Opx07};   table[0x17] = {&Z80g::Opx17};   table[0x27] = {&Z80g::Opx27};   table[0x37] = {&Z80g::Opx37};   table[0x47] = {&Z80g::Opx47};   table[0x57] = {&Z80g::Opx57};   table[0x67] = {&Z80g::Opx67};   table[0x77] = {&Z80g::Opx77};
    table[0x08] = {&Z80g::Opx08};   table[0x18] = {&Z80g::Opx18};   table[0x28] = {&Z80g::Opx28};   table[0x38] = {&Z80g::Opx38};   table[0x48] = {&Z80g::Opx48};   table[0x58] = {&Z80g::Opx58};   table[0x68] = {&Z80g::Opx68};   table[0x78] = {&Z80g::Opx78};
    table[0x09] = {&Z80g::Opx09};   table[0x19] = {&Z80g::Opx19};   table[0x29] = {&Z80g::Opx29};   table[0x39] = {&Z80g::Opx39};   table[0x49] = {&Z80g::Opx49};   table[0x59] = {&Z80g::Opx59};   table[0x69] = {&Z80g::Opx69};   table[0x79] = {&Z80g::Opx79};
    table[0x0A] = {&Z80g::Opx0A};   table[0x1A] = {&Z80g::Opx1A};   table[0x2A] = {&Z80g::Opx2A};   table[0x3A] = {&Z80g::Opx3A};   table[0x4A] = {&Z80g::Opx4A};   table[0x5A] = {&Z80g::Opx5A};   table[0x6A] = {&Z80g::Opx6A};   table[0x7A] = {&Z80g::Opx7A};
    table[0x0B] = {&Z80g::Opx0B};   table[0x1B] = {&Z80g::Opx1B};   table[0x2B] = {&Z80g::Opx2B};   table[0x3B] = {&Z80g::Opx3B};   table[0x4B] = {&Z80g::Opx4B};   table[0x5B] = {&Z80g::Opx5B};   table[0x6B] = {&Z80g::Opx6B};   table[0x7B] = {&Z80g::Opx7B};
    table[0x0C] = {&Z80g::Opx0C};   table[0x1C] = {&Z80g::Opx1C};   table[0x2C] = {&Z80g::Opx2C};   table[0x3C] = {&Z80g::Opx3C};   table[0x4C] = {&Z80g::Opx4C};   table[0x5C] = {&Z80g::Opx5C};   table[0x6C] = {&Z80g::Opx6C};   table[0x7C] = {&Z80g::Opx7C};
    table[0x0D] = {&Z80g::Opx0D};   table[0x1D] = {&Z80g::Opx1D};   table[0x2D] = {&Z80g::Opx2D};   table[0x3D] = {&Z80g::Opx3D};   table[0x4D] = {&Z80g::Opx4D};   table[0x5D] = {&Z80g::Opx5D};   table[0x6D] = {&Z80g::Opx6D};   table[0x7D] = {&Z80g::Opx7D};
    table[0x0E] = {&Z80g::Opx0E};   table[0x1E] = {&Z80g::Opx1E};   table[0x2E] = {&Z80g::Opx2E};   table[0x3E] = {&Z80g::Opx3E};   table[0x4E] = {&Z80g::Opx4E};   table[0x5E] = {&Z80g::Opx5E};   table[0x6E] = {&Z80g::Opx6E};   table[0x7E] = {&Z80g::Opx7E};
    table[0x0F] = {&Z80g::Opx0F};   table[0x1F] = {&Z80g::Opx1F};   table[0x2F] = {&Z80g::Opx2F};   table[0x3F] = {&Z80g::Opx3F};   table[0x4F] = {&Z80g::Opx4F};   table[0x5F] = {&Z80g::Opx5F};   table[0x6F] = {&Z80g::Opx6F};   table[0x7F] = {&Z80g::Opx7F};

    table[0x80] = {&Z80g::Opx80};   table[0x90] = {&Z80g::Opx90};   table[0xA0] = {&Z80g::OpxA0};   table[0xB0] = {&Z80g::OpxB0};   table[0xC0] = {&Z80g::OpxC0};   table[0xD0] = {&Z80g::OpxD0};   table[0xE0] = {&Z80g::OpxE0};   table[0xF0] = {&Z80g::OpxF0};
    table[0x81] = {&Z80g::Opx81};   table[0x91] = {&Z80g::Opx91};   table[0xA1] = {&Z80g::OpxA1};   table[0xB1] = {&Z80g::OpxB1};   table[0xC1] = {&Z80g::OpxC1};   table[0xD1] = {&Z80g::OpxD1};   table[0xE1] = {&Z80g::OpxE1};   table[0xF1] = {&Z80g::OpxF1};
    table[0x82] = {&Z80g::Opx82};   table[0x92] = {&Z80g::Opx92};   table[0xA2] = {&Z80g::OpxA2};   table[0xB2] = {&Z80g::OpxB2};   table[0xC2] = {&Z80g::OpxC2};   table[0xD2] = {&Z80g::OpxD2};   table[0xE2] = {&Z80g::OpxE2};   table[0xF2] = {&Z80g::OpxF2};
    table[0x83] = {&Z80g::Opx83};   table[0x93] = {&Z80g::Opx93};   table[0xA3] = {&Z80g::OpxA3};   table[0xB3] = {&Z80g::OpxB3};   table[0xC3] = {&Z80g::OpxC3};   table[0xD3] = {&Z80g::Opx00};   table[0xE3] = {&Z80g::Opx00};   table[0xF3] = {&Z80g::OpxF3};
    table[0x84] = {&Z80g::Opx84};   table[0x94] = {&Z80g::Opx94};   table[0xA4] = {&Z80g::OpxA4};   table[0xB4] = {&Z80g::OpxB4};   table[0xC4] = {&Z80g::OpxC4};   table[0xD4] = {&Z80g::OpxD4};   table[0xE4] = {&Z80g::Opx00};   table[0xF4] = {&Z80g::Opx00};
    table[0x85] = {&Z80g::Opx85};   table[0x95] = {&Z80g::Opx95};   table[0xA5] = {&Z80g::OpxA5};   table[0xB5] = {&Z80g::OpxB5};   table[0xC5] = {&Z80g::OpxC5};   table[0xD5] = {&Z80g::OpxD5};   table[0xE5] = {&Z80g::OpxE5};   table[0xF5] = {&Z80g::OpxF5};
    table[0x86] = {&Z80g::Opx86};   table[0x96] = {&Z80g::Opx96};   table[0xA6] = {&Z80g::OpxA6};   table[0xB6] = {&Z80g::OpxB6};   table[0xC6] = {&Z80g::OpxC6};   table[0xD6] = {&Z80g::OpxD6};   table[0xE6] = {&Z80g::OpxE6};   table[0xF6] = {&Z80g::OpxF6};
    table[0x87] = {&Z80g::Opx87};   table[0x97] = {&Z80g::Opx97};   table[0xA7] = {&Z80g::OpxA7};   table[0xB7] = {&Z80g::OpxB7};   table[0xC7] = {&Z80g::OpxC7};   table[0xD7] = {&Z80g::OpxD7};   table[0xE7] = {&Z80g::OpxE7};   table[0xF7] = {&Z80g::OpxF7};
    table[0x88] = {&Z80g::Opx88};   table[0x98] = {&Z80g::Opx98};   table[0xA8] = {&Z80g::OpxA8};   table[0xB8] = {&Z80g::OpxB8};   table[0xC8] = {&Z80g::OpxC8};   table[0xD8] = {&Z80g::OpxD8};   table[0xE8] = {&Z80g::OpxE8};   table[0xF8] = {&Z80g::OpxF8};
    table[0x89] = {&Z80g::Opx89};   table[0x99] = {&Z80g::Opx99};   table[0xA9] = {&Z80g::OpxA9};   table[0xB9] = {&Z80g::OpxB9};   table[0xC9] = {&Z80g::OpxC9};   table[0xD9] = {&Z80g::OpxD9};   table[0xE9] = {&Z80g::OpxE9};   table[0xF9] = {&Z80g::OpxF9};
    table[0x8A] = {&Z80g::Opx8A};   table[0x9A] = {&Z80g::Opx9A};   table[0xAA] = {&Z80g::OpxAA};   table[0xBA] = {&Z80g::OpxBA};   table[0xCA] = {&Z80g::OpxCA};   table[0xDA] = {&Z80g::OpxDA};   table[0xEA] = {&Z80g::OpxEA};   table[0xFA] = {&Z80g::OpxFA};
    table[0x8B] = {&Z80g::Opx8B};   table[0x9B] = {&Z80g::Opx9B};   table[0xAB] = {&Z80g::OpxAB};   table[0xBB] = {&Z80g::OpxBB};   /* Opcode CB does not exist*/   table[0xDB] = {&Z80g::Opx00};   table[0xEB] = {&Z80g::Opx00};   table[0xFB] = {&Z80g::OpxFB};
    table[0x8C] = {&Z80g::Opx8C};   table[0x9C] = {&Z80g::Opx9C};   table[0xAC] = {&Z80g::OpxAC};   table[0xBC] = {&Z80g::OpxBC};   table[0xCC] = {&Z80g::OpxCC};   table[0xDC] = {&Z80g::OpxDC};   table[0xEC] = {&Z80g::Opx00};   table[0xFC] = {&Z80g::Opx00};
    table[0x8D] = {&Z80g::Opx8D};   table[0x9D] = {&Z80g::Opx9D};   table[0xAD] = {&Z80g::OpxAD};   table[0xBD] = {&Z80g::OpxBD};   table[0xCD] = {&Z80g::OpxCD};   table[0xDD] = {&Z80g::Opx00};   table[0xED] = {&Z80g::Opx00};   table[0xFD] = {&Z80g::Opx00};
    table[0x8E] = {&Z80g::Opx8E};   table[0x9E] = {&Z80g::Opx9E};   table[0xAE] = {&Z80g::OpxAE};   table[0xBE] = {&Z80g::OpxBE};   table[0xCE] = {&Z80g::OpxCE};   table[0xDE] = {&Z80g::OpxDE};   table[0xEE] = {&Z80g::OpxEE};   table[0xFE] = {&Z80g::OpxFE};
    table[0x8F] = {&Z80g::Opx8F};   table[0x9F] = {&Z80g::Opx9F};   table[0xAF] = {&Z80g::OpxAF};   table[0xBF] = {&Z80g::OpxBF};   table[0xCF] = {&Z80g::OpxCF};   table[0xDF] = {&Z80g::OpxDF};   table[0xEF] = {&Z80g::OpxEF};   table[0xFF] = {&Z80g::OpxFF};

    
    
    tableCB[0x00] = {&Z80g::OpxCB00};   tableCB[0x10] = {&Z80g::OpxCB10};   tableCB[0x20] = {&Z80g::OpxCB20};   tableCB[0x30] = {&Z80g::OpxCB30};   tableCB[0x40] = {&Z80g::OpxCB40};   tableCB[0x50] = {&Z80g::OpxCB50};   tableCB[0x60] = {&Z80g::OpxCB60};   tableCB[0x70] = {&Z80g::OpxCB70};
    tableCB[0x01] = {&Z80g::OpxCB01};   tableCB[0x11] = {&Z80g::OpxCB11};   tableCB[0x21] = {&Z80g::OpxCB21};   tableCB[0x31] = {&Z80g::OpxCB31};   tableCB[0x41] = {&Z80g::OpxCB41};   tableCB[0x51] = {&Z80g::OpxCB51};   tableCB[0x61] = {&Z80g::OpxCB61};   tableCB[0x71] = {&Z80g::OpxCB71};
    tableCB[0x02] = {&Z80g::OpxCB02};   tableCB[0x12] = {&Z80g::OpxCB12};   tableCB[0x22] = {&Z80g::OpxCB22};   tableCB[0x32] = {&Z80g::OpxCB32};   tableCB[0x42] = {&Z80g::OpxCB42};   tableCB[0x52] = {&Z80g::OpxCB52};   tableCB[0x62] = {&Z80g::OpxCB62};   tableCB[0x72] = {&Z80g::OpxCB72};
    tableCB[0x03] = {&Z80g::OpxCB03};   tableCB[0x13] = {&Z80g::OpxCB13};   tableCB[0x23] = {&Z80g::OpxCB23};   tableCB[0x33] = {&Z80g::OpxCB33};   tableCB[0x43] = {&Z80g::OpxCB43};   tableCB[0x53] = {&Z80g::OpxCB53};   tableCB[0x63] = {&Z80g::OpxCB63};   tableCB[0x73] = {&Z80g::OpxCB73};
    tableCB[0x04] = {&Z80g::OpxCB04};   tableCB[0x14] = {&Z80g::OpxCB14};   tableCB[0x24] = {&Z80g::OpxCB24};   tableCB[0x34] = {&Z80g::OpxCB34};   tableCB[0x44] = {&Z80g::OpxCB44};   tableCB[0x54] = {&Z80g::OpxCB54};   tableCB[0x64] = {&Z80g::OpxCB64};   tableCB[0x74] = {&Z80g::OpxCB74};
    tableCB[0x05] = {&Z80g::OpxCB05};   tableCB[0x15] = {&Z80g::OpxCB15};   tableCB[0x25] = {&Z80g::OpxCB25};   tableCB[0x35] = {&Z80g::OpxCB35};   tableCB[0x45] = {&Z80g::OpxCB45};   tableCB[0x55] = {&Z80g::OpxCB55};   tableCB[0x65] = {&Z80g::OpxCB65};   tableCB[0x75] = {&Z80g::OpxCB75};
    tableCB[0x06] = {&Z80g::OpxCB06};   tableCB[0x16] = {&Z80g::OpxCB16};   tableCB[0x26] = {&Z80g::OpxCB26};   tableCB[0x36] = {&Z80g::OpxCB36};   tableCB[0x46] = {&Z80g::OpxCB46};   tableCB[0x56] = {&Z80g::OpxCB56};   tableCB[0x66] = {&Z80g::OpxCB66};   tableCB[0x76] = {&Z80g::OpxCB76};
    tableCB[0x07] = {&Z80g::OpxCB07};   tableCB[0x17] = {&Z80g::OpxCB17};   tableCB[0x27] = {&Z80g::OpxCB27};   tableCB[0x37] = {&Z80g::OpxCB37};   tableCB[0x47] = {&Z80g::OpxCB47};   tableCB[0x57] = {&Z80g::OpxCB57};   tableCB[0x67] = {&Z80g::OpxCB67};   tableCB[0x77] = {&Z80g::OpxCB77};
    tableCB[0x08] = {&Z80g::OpxCB08};   tableCB[0x18] = {&Z80g::OpxCB18};   tableCB[0x28] = {&Z80g::OpxCB28};   tableCB[0x38] = {&Z80g::OpxCB38};   tableCB[0x48] = {&Z80g::OpxCB48};   tableCB[0x58] = {&Z80g::OpxCB58};   tableCB[0x68] = {&Z80g::OpxCB68};   tableCB[0x78] = {&Z80g::OpxCB78};
    tableCB[0x09] = {&Z80g::OpxCB09};   tableCB[0x19] = {&Z80g::OpxCB19};   tableCB[0x29] = {&Z80g::OpxCB29};   tableCB[0x39] = {&Z80g::OpxCB39};   tableCB[0x49] = {&Z80g::OpxCB49};   tableCB[0x59] = {&Z80g::OpxCB59};   tableCB[0x69] = {&Z80g::OpxCB69};   tableCB[0x79] = {&Z80g::OpxCB79};
    tableCB[0x0A] = {&Z80g::OpxCB0A};   tableCB[0x1A] = {&Z80g::OpxCB1A};   tableCB[0x2A] = {&Z80g::OpxCB2A};   tableCB[0x3A] = {&Z80g::OpxCB3A};   tableCB[0x4A] = {&Z80g::OpxCB4A};   tableCB[0x5A] = {&Z80g::OpxCB5A};   tableCB[0x6A] = {&Z80g::OpxCB6A};   tableCB[0x7A] = {&Z80g::OpxCB7A};
    tableCB[0x0B] = {&Z80g::OpxCB0B};   tableCB[0x1B] = {&Z80g::OpxCB1B};   tableCB[0x2B] = {&Z80g::OpxCB2B};   tableCB[0x3B] = {&Z80g::OpxCB3B};   tableCB[0x4B] = {&Z80g::OpxCB4B};   tableCB[0x5B] = {&Z80g::OpxCB5B};   tableCB[0x6B] = {&Z80g::OpxCB6B};   tableCB[0x7B] = {&Z80g::OpxCB7B};
    tableCB[0x0C] = {&Z80g::OpxCB0C};   tableCB[0x1C] = {&Z80g::OpxCB1C};   tableCB[0x2C] = {&Z80g::OpxCB2C};   tableCB[0x3C] = {&Z80g::OpxCB3C};   tableCB[0x4C] = {&Z80g::OpxCB4C};   tableCB[0x5C] = {&Z80g::OpxCB5C};   tableCB[0x6C] = {&Z80g::OpxCB6C};   tableCB[0x7C] = {&Z80g::OpxCB7C};
    tableCB[0x0D] = {&Z80g::OpxCB0D};   tableCB[0x1D] = {&Z80g::OpxCB1D};   tableCB[0x2D] = {&Z80g::OpxCB2D};   tableCB[0x3D] = {&Z80g::OpxCB3D};   tableCB[0x4D] = {&Z80g::OpxCB4D};   tableCB[0x5D] = {&Z80g::OpxCB5D};   tableCB[0x6D] = {&Z80g::OpxCB6D};   tableCB[0x7D] = {&Z80g::OpxCB7D};
    tableCB[0x0E] = {&Z80g::OpxCB0E};   tableCB[0x1E] = {&Z80g::OpxCB1E};   tableCB[0x2E] = {&Z80g::OpxCB2E};   tableCB[0x3E] = {&Z80g::OpxCB3E};   tableCB[0x4E] = {&Z80g::OpxCB4E};   tableCB[0x5E] = {&Z80g::OpxCB5E};   tableCB[0x6E] = {&Z80g::OpxCB6E};   tableCB[0x7E] = {&Z80g::OpxCB7E};
    tableCB[0x0F] = {&Z80g::OpxCB0F};   tableCB[0x1F] = {&Z80g::OpxCB1F};   tableCB[0x2F] = {&Z80g::OpxCB2F};   tableCB[0x3F] = {&Z80g::OpxCB3F};   tableCB[0x4F] = {&Z80g::OpxCB4F};   tableCB[0x5F] = {&Z80g::OpxCB5F};   tableCB[0x6F] = {&Z80g::OpxCB6F};   tableCB[0x7F] = {&Z80g::OpxCB7F};

    tableCB[0x80] = {&Z80g::OpxCB80};   tableCB[0x90] = {&Z80g::OpxCB90};   tableCB[0xA0] = {&Z80g::OpxCBA0};   tableCB[0xB0] = {&Z80g::OpxCBB0};   tableCB[0xC0] = {&Z80g::OpxCBC0};   tableCB[0xD0] = {&Z80g::OpxCBD0};   tableCB[0xE0] = {&Z80g::OpxCBE0};   tableCB[0xF0] = {&Z80g::OpxCBF0};
    tableCB[0x81] = {&Z80g::OpxCB81};   tableCB[0x91] = {&Z80g::OpxCB91};   tableCB[0xA1] = {&Z80g::OpxCBA1};   tableCB[0xB1] = {&Z80g::OpxCBB1};   tableCB[0xC1] = {&Z80g::OpxCBC1};   tableCB[0xD1] = {&Z80g::OpxCBD1};   tableCB[0xE1] = {&Z80g::OpxCBE1};   tableCB[0xF1] = {&Z80g::OpxCBF1};
    tableCB[0x82] = {&Z80g::OpxCB82};   tableCB[0x92] = {&Z80g::OpxCB92};   tableCB[0xA2] = {&Z80g::OpxCBA2};   tableCB[0xB2] = {&Z80g::OpxCBB2};   tableCB[0xC2] = {&Z80g::OpxCBC2};   tableCB[0xD2] = {&Z80g::OpxCBD2};   tableCB[0xE2] = {&Z80g::OpxCBE2};   tableCB[0xF2] = {&Z80g::OpxCBF2};
    tableCB[0x83] = {&Z80g::OpxCB83};   tableCB[0x93] = {&Z80g::OpxCB93};   tableCB[0xA3] = {&Z80g::OpxCBA3};   tableCB[0xB3] = {&Z80g::OpxCBB3};   tableCB[0xC3] = {&Z80g::OpxCBC3};   tableCB[0xD3] = {&Z80g::OpxCB00};   tableCB[0xE3] = {&Z80g::OpxCB00};   tableCB[0xF3] = {&Z80g::OpxCBF3};
    tableCB[0x84] = {&Z80g::OpxCB84};   tableCB[0x94] = {&Z80g::OpxCB94};   tableCB[0xA4] = {&Z80g::OpxCBA4};   tableCB[0xB4] = {&Z80g::OpxCBB4};   tableCB[0xC4] = {&Z80g::OpxCBC4};   tableCB[0xD4] = {&Z80g::OpxCBD4};   tableCB[0xE4] = {&Z80g::OpxCB00};   tableCB[0xF4] = {&Z80g::OpxCB00};
    tableCB[0x85] = {&Z80g::OpxCB85};   tableCB[0x95] = {&Z80g::OpxCB95};   tableCB[0xA5] = {&Z80g::OpxCBA5};   tableCB[0xB5] = {&Z80g::OpxCBB5};   tableCB[0xC5] = {&Z80g::OpxCBC5};   tableCB[0xD5] = {&Z80g::OpxCBD5};   tableCB[0xE5] = {&Z80g::OpxCBE5};   tableCB[0xF5] = {&Z80g::OpxCBF5};
    tableCB[0x86] = {&Z80g::OpxCB86};   tableCB[0x96] = {&Z80g::OpxCB96};   tableCB[0xA6] = {&Z80g::OpxCBA6};   tableCB[0xB6] = {&Z80g::OpxCBB6};   tableCB[0xC6] = {&Z80g::OpxCBC6};   tableCB[0xD6] = {&Z80g::OpxCBD6};   tableCB[0xE6] = {&Z80g::OpxCBE6};   tableCB[0xF6] = {&Z80g::OpxCBF6};
    tableCB[0x87] = {&Z80g::OpxCB87};   tableCB[0x97] = {&Z80g::OpxCB97};   tableCB[0xA7] = {&Z80g::OpxCBA7};   tableCB[0xB7] = {&Z80g::OpxCBB7};   tableCB[0xC7] = {&Z80g::OpxCBC7};   tableCB[0xD7] = {&Z80g::OpxCBD7};   tableCB[0xE7] = {&Z80g::OpxCBE7};   tableCB[0xF7] = {&Z80g::OpxCBF7};
    tableCB[0x88] = {&Z80g::OpxCB88};   tableCB[0x98] = {&Z80g::OpxCB98};   tableCB[0xA8] = {&Z80g::OpxCBA8};   tableCB[0xB8] = {&Z80g::OpxCBB8};   tableCB[0xC8] = {&Z80g::OpxCBC8};   tableCB[0xD8] = {&Z80g::OpxCBD8};   tableCB[0xE8] = {&Z80g::OpxCBE8};   tableCB[0xF8] = {&Z80g::OpxCBF8};
    tableCB[0x89] = {&Z80g::OpxCB89};   tableCB[0x99] = {&Z80g::OpxCB99};   tableCB[0xA9] = {&Z80g::OpxCBA9};   tableCB[0xB9] = {&Z80g::OpxCBB9};   tableCB[0xC9] = {&Z80g::OpxCBC9};   tableCB[0xD9] = {&Z80g::OpxCBD9};   tableCB[0xE9] = {&Z80g::OpxCBE9};   tableCB[0xF9] = {&Z80g::OpxCBF9};
    tableCB[0x8A] = {&Z80g::OpxCB8A};   tableCB[0x9A] = {&Z80g::OpxCB9A};   tableCB[0xAA] = {&Z80g::OpxCBAA};   tableCB[0xBA] = {&Z80g::OpxCBBA};   tableCB[0xCA] = {&Z80g::OpxCBCA};   tableCB[0xDA] = {&Z80g::OpxCBDA};   tableCB[0xEA] = {&Z80g::OpxCBEA};   tableCB[0xFA] = {&Z80g::OpxCBFA};
    tableCB[0x8B] = {&Z80g::OpxCB8B};   tableCB[0x9B] = {&Z80g::OpxCB9B};   tableCB[0xAB] = {&Z80g::OpxCBAB};   tableCB[0xBB] = {&Z80g::OpxCBBB};   tableCB[0xCB] = {&Z80g::OpxCBCB};   tableCB[0xDB] = {&Z80g::OpxCB00};   tableCB[0xEB] = {&Z80g::OpxCB00};   tableCB[0xFB] = {&Z80g::OpxCBFB};
    tableCB[0x8C] = {&Z80g::OpxCB8C};   tableCB[0x9C] = {&Z80g::OpxCB9C};   tableCB[0xAC] = {&Z80g::OpxCBAC};   tableCB[0xBC] = {&Z80g::OpxCBBC};   tableCB[0xCC] = {&Z80g::OpxCBCC};   tableCB[0xDC] = {&Z80g::OpxCBDC};   tableCB[0xEC] = {&Z80g::OpxCB00};   tableCB[0xFC] = {&Z80g::OpxCB00};
    tableCB[0x8D] = {&Z80g::OpxCB8D};   tableCB[0x9D] = {&Z80g::OpxCB9D};   tableCB[0xAD] = {&Z80g::OpxCBAD};   tableCB[0xBD] = {&Z80g::OpxCBBD};   tableCB[0xCD] = {&Z80g::OpxCBCD};   tableCB[0xDD] = {&Z80g::OpxCB00};   tableCB[0xED] = {&Z80g::OpxCB00};   tableCB[0xFD] = {&Z80g::OpxCB00};
    tableCB[0x8E] = {&Z80g::OpxCB8E};   tableCB[0x9E] = {&Z80g::OpxCB9E};   tableCB[0xAE] = {&Z80g::OpxCBAE};   tableCB[0xBE] = {&Z80g::OpxCBBE};   tableCB[0xCE] = {&Z80g::OpxCBCE};   tableCB[0xDE] = {&Z80g::OpxCBDE};   tableCB[0xEE] = {&Z80g::OpxCBEE};   tableCB[0xFE] = {&Z80g::OpxCBFE};
    tableCB[0x8F] = {&Z80g::OpxCB8F};   tableCB[0x9F] = {&Z80g::OpxCB9F};   tableCB[0xAF] = {&Z80g::OpxCBAF};   tableCB[0xBF] = {&Z80g::OpxCBBF};   tableCB[0xCF] = {&Z80g::OpxCBCF};   tableCB[0xDF] = {&Z80g::OpxCBDF};   tableCB[0xEF] = {&Z80g::OpxCBEF};   tableCB[0xFF] = {&Z80g::OpxCBFF};
}

void Z80g::write(uint16_t ad, uint8_t da)
{
    bus->write(ad, da);
}

uint8_t Z80g::read(uint16_t ad)
{
    return bus->read(ad);
}

uint8_t Z80g::GetFlag(FLAGS f)
{
    return ((fReg & f) > 0) ? 1 : 0;
}

void Z80g::SetFlag(FLAGS f, bool v)
{
    if (v)
    {
        fReg |= f;
    }

    else
    {
        fReg &= ~f;
    }

}


void Z80g::Clock()
{
    if(cycles == 0)
    {
        Opcode = read(pc);
        
        if (Opcode == 0xCB)
        {
            Opcode <<= 8;
            pc++;
            Opcode |= read(pc);
            pc++;

            (this->*(tableCB[Opcode & 0xFF]))();
        }
        
        else
        {
            (this->*(table [Opcode & 0xFF]))();

            pc++;
        }
    }

    cycles--;
}   

void Z80g::ResetCpu()
{
    sp = 0xFFFE;
    pc = 0x100;
    Opcode = 0;

    aReg = 0x00;
    bReg = 0x00;
    cReg = 0x00;
    dReg = 0x00;
    eReg = 0x00;
    hReg = 0x00;
    lReg = 0x00;

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);

    write(0xFF00, 0x3F);
}

void Z80g::Opx10()
{
    cycles = 1;

    uint8_t InterruptEnable;
    uint8_t Input;
    
    Input = read(0xFF00);
    InterruptEnable = read(0xFFFF);
    
    if ((InterruptEnable & 0x1F) == 0x0 && (Input & 0x0F) == 0)
    {
        Stop = true;
    }
    
}

void Z80g::Opx40()
{
    cycles = 1;
}
void Z80g::Opx41()
{
    cycles = 1;

    bReg = cReg;   
}
void Z80g::Opx42()
{
    cycles = 1;

    bReg = dReg;    
}
void Z80g::Opx43()
{
    cycles = 1;

    bReg = eReg;    
}
void Z80g::Opx44()
{
    cycles = 1;

    bReg = hReg;
}
void Z80g::Opx45()
{
    cycles = 1;

    bReg = lReg;
}
void Z80g::Opx47()
{
    cycles = 1;

    bReg = aReg; 
}
void Z80g::Opx48()
{
    cycles = 1;

    cReg = bReg;
}
void Z80g::Opx49()
{
    cycles = 1;

}
void Z80g::Opx4A()
{
    cycles = 1;

    cReg = dReg;
}
void Z80g::Opx4B()
{
    cycles = 1;

    cReg = eReg;
}
void Z80g::Opx4C()
{
    cycles = 1;

    cReg = hReg;    
}
void Z80g::Opx4D()
{
    cycles = 1;

    cReg = lReg;    
}
void Z80g::Opx4F()
{
    cycles = 1;

    cReg = aReg;    
}
void Z80g::Opx50()
{
    cycles = 1;

    dReg = bReg;    
}
void Z80g::Opx51()
{
    cycles = 1;

    dReg = cReg;    
}
void Z80g::Opx52()
{
    cycles = 1;    
}
void Z80g::Opx53()
{
    cycles = 1;
    
    dReg = eReg;
}
void Z80g::Opx54()
{
    cycles = 1;

    dReg = hReg;
}
void Z80g::Opx55()
{
    cycles = 1;

    dReg = lReg;    
}
void Z80g::Opx57()
{
    cycles = 1;

    dReg = aReg;    
}
void Z80g::Opx58()
{
    cycles = 1;

    eReg = bReg;    
}
void Z80g::Opx59()
{
    cycles = 1;

    eReg = cReg;    
}
void Z80g::Opx5A()
{
    cycles = 1;

    eReg = dReg;    
}
void Z80g::Opx5B()
{

    cycles = 1;

}
void Z80g::Opx5C()
{
    cycles = 1;

    eReg = hReg;    
}
void Z80g::Opx5D()
{
    cycles = 1;

    eReg = lReg;    
}
void Z80g::Opx5F()
{
    cycles = 1;

    eReg = aReg; 
}
void Z80g::Opx60()
{
    cycles = 1;

    hReg = bReg;    
}
void Z80g::Opx61()
{
    cycles = 1;

    hReg = cReg;    
}
void Z80g::Opx62()
{
    cycles = 1;

    hReg = dReg;    
}
void Z80g::Opx63()
{
    cycles = 1;
    
    hReg = eReg;
}
void Z80g::Opx64()
{
    cycles = 1;    
}
void Z80g::Opx65()
{
    cycles = 1;

    hReg = lReg;    
}
void Z80g::Opx67()
{
    cycles = 1;

    hReg = aReg;    
}
void Z80g::Opx68()
{
    cycles = 1;

    lReg = bReg;    
}
void Z80g::Opx69()
{
    cycles = 1;

    lReg = cReg;    
}
void Z80g::Opx6A()
{
    cycles = 1;

    lReg = dReg;    
}
void Z80g::Opx6B()
{
    cycles = 1;

    lReg = eReg;    
}
void Z80g::Opx6C()
{
    cycles = 1;

    lReg = hReg;    
}
void Z80g::Opx6D()
{
    cycles = 1;
}
void Z80g::Opx6F()
{
    cycles = 1;

    lReg = aReg;    
}
void Z80g::Opx78()
{
    cycles = 1;

    aReg = bReg;    
}
void Z80g::Opx79()
{
    cycles = 1;

    aReg = cReg;    
}
void Z80g::Opx7A()
{
    cycles = 1;

    aReg = dReg;    
}
void Z80g::Opx7B()
{
    cycles = 1;

    aReg = eReg;    
}
void Z80g::Opx7C()
{
    cycles = 1;

    aReg = hReg;    
}
void Z80g::Opx7D()
{
    cycles = 1;

    aReg = lReg;    
}
void Z80g::Opx7F()
{
    cycles = 1;
}
void Z80g::Opx06()
{
    cycles = 2;

    bReg = read(pc);
}
void Z80g::Opx0E()
{
    cycles = 2;
    cReg = read(pc);
}
void Z80g::Opx16()
{
    cycles = 2;
    dReg = read(pc);
}
void Z80g::Opx1E()
{
    cycles = 2;
    eReg = read(pc);
}
void Z80g::Opx26()
{
    cycles = 2;
    hReg = read(pc);
}
void Z80g::Opx2E()
{
    cycles = 2;
    lReg = read(pc);
}
void Z80g::Opx36()
{
    cycles = 3;

    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, read(pc));
}
void Z80g::Opx3E()
{
    cycles = 2;
    aReg = read(pc);
}
void Z80g::Opx46()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    bReg = read(HL);
}
void Z80g::Opx56()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    dReg = read(HL);
}
void Z80g::Opx66()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    hReg = read(HL);
}
void Z80g::Opx4E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    cReg = read(HL);
}
void Z80g::Opx5E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    eReg = read(HL);
}
void Z80g::Opx6E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    lReg = read(HL);
}
void Z80g::Opx7E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    aReg = read(HL);
}
void Z80g::Opx70()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, bReg);
}
void Z80g::Opx71()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, cReg);
}
void Z80g::Opx72()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, dReg);
}
void Z80g::Opx73()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, eReg);
}
void Z80g::Opx74()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, hReg);
}
void Z80g::Opx75()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, lReg);
}
void Z80g::Opx77()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, aReg);
}
void Z80g::Opx02()
{
    cycles = 2;
    uint16_t BC = ((bReg << 8) | cReg);

    write(BC, aReg);
}
void Z80g::Opx12()
{
    cycles = 2;
    uint16_t DE = ((dReg << 8) | eReg);

    write(DE, aReg);
}
void Z80g::Opx22()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg) + 1;

    write(HL, aReg);
}
void Z80g::Opx32()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg) - 1;

    write(HL, aReg);
}
void Z80g::Opx0A()
{
    cycles = 2;
    uint16_t BC = ((bReg < 8) | cReg);

    aReg = read(BC);
}
void Z80g::Opx1A()
{
    cycles = 2;
    uint16_t DE = ((dReg < 8) | eReg);

    aReg = read(DE);
}
void Z80g::Opx2A()
{
    cycles = 2;
    uint16_t HL = ((hReg < 8) | lReg) + 1;

    aReg = read(HL);
}
void Z80g::Opx3A()
{
    cycles = 2;
    uint16_t HL = ((hReg < 8) | lReg) - 1;

    aReg = read(HL);
}
void Z80g::Opx01()
{
    cycles = 3;
    
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    bReg = hi;
    cReg = lo;
}
void Z80g::Opx11()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    dReg = hi;
    eReg = lo;
}
void Z80g::Opx21()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    hReg = hi;
    lReg = lo;
}
void Z80g::Opx31()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    sp = (hi << 8) | lo;

}
void Z80g::Opx03()
{
    cycles = 2;

    uint16_t BC = ((bReg << 8) | cReg);

    BC++;

    bReg = (BC & 0xFF00);
    cReg = (BC & 0x00FF);
}
void Z80g::Opx13()
{
    cycles = 2;

    uint16_t DE = ((dReg << 8) | eReg);

    DE++;

    dReg = (DE & 0xFF00);
    eReg = (DE & 0x00FF);
}
void Z80g::Opx23()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    HL++;

    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);
}
void Z80g::Opx33()
{
    cycles = 2;
    sp++;
}
void Z80g::Opx0B()
{
    cycles = 2;

    uint16_t BC = ((bReg << 8) | cReg);

    BC--;

    bReg = (BC & 0xFF00);
    cReg = (BC & 0x00FF);
}
void Z80g::Opx1B()
{
    cycles = 2;

    uint16_t DE = ((dReg << 8) | eReg);

    DE--;

    dReg = (DE & 0xFF00);
    eReg = (DE & 0x00FF);
}
void Z80g::Opx2B()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    HL--;

    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);
}
void Z80g::Opx3B()
{
    cycles = 2;
    sp--;
}
void Z80g::Opx04()
{
    cycles = 1;

    bReg++;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
    SetFlag(H, (bReg & 0x10) == 0x10);

}
void Z80g::Opx0C()
{
    cycles = 1;

    cReg++;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
    SetFlag(H, (cReg & 0x10) == 0x10);

}
void Z80g::Opx14()
{
    cycles = 1;

    dReg++;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
    SetFlag(H, (dReg & 0x10) == 0x10);

}
void Z80g::Opx1C()
{
    cycles = 1;

    eReg++;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
    SetFlag(H, (eReg & 0x10) == 0x10);

}
void Z80g::Opx24()
{
    cycles = 1;

    hReg++;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
    SetFlag(H, (hReg & 0x10) == 0x10);

}
void Z80g::Opx2C()
{
    cycles = 1;

    lReg++;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
    SetFlag(H, (lReg & 0x10) == 0x10);

}
void Z80g::Opx34()
{
    cycles = 3;

    uint16_t HL = ((hReg << 8) | lReg);
    
    uint8_t cHL = read(HL);

    cHL++;

    write(HL,cHL);

    SetFlag(Z, cHL == 0);
    SetFlag(N, false);
    SetFlag(H, (cHL & 0x10) == 0x10);

}
void Z80g::Opx3C()
{
    cycles = 1;

    aReg++;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, (aReg & 0x10) == 0x10);

}
void Z80g::Opx05()
{
    cycles = 1;

    bReg--;

    SetFlag(Z, bReg == 0);
    SetFlag(N, true);
    SetFlag(H, (bReg & 0x10) == 0x10);

}
void Z80g::Opx0D()
{
    cycles = 1;

    cReg--;

    SetFlag(Z, cReg == 0);
    SetFlag(N, true);
    SetFlag(H, (cReg & 0x10) == 0x10);

}
void Z80g::Opx15()
{
    cycles = 1;

    dReg--;

    SetFlag(Z, dReg == 0);
    SetFlag(N, true);
    SetFlag(H, (dReg & 0x10) == 0x10);

}
void Z80g::Opx1D()
{
    cycles = 1;

    eReg--;

    SetFlag(Z, eReg == 0);
    SetFlag(N, true);
    SetFlag(H, (eReg & 0x10) == 0x10);

}
void Z80g::Opx25()
{
    cycles = 1;

    hReg--;

    SetFlag(Z, hReg == 0);
    SetFlag(N, true);
    SetFlag(H, (hReg & 0x10) == 0x10);

}
void Z80g::Opx2D()
{
    cycles = 1;

    lReg--;

    SetFlag(Z, lReg == 0);
    SetFlag(N, true);
    SetFlag(H, (lReg & 0x10) == 0);

}
void Z80g::Opx35()
{
    cycles = 3;

    uint16_t HL = ((hReg << 8) | lReg);
    
    uint8_t cHL = read(HL);

    cHL--;

    write(HL,cHL);

    SetFlag(Z, cHL == 0);
    SetFlag(N, true);
    SetFlag(H, (cHL & 0x10) == 0x10);

}
void Z80g::Opx3D()
{
    cycles = 1;

    aReg--;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
    SetFlag(H, (aReg & 0x10) == 0x10);

}
void Z80g::Opx09()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint16_t BC = ((bReg << 8) | cReg);

    SetFlag(C, HL += BC > 0xFFFF);

    HL += BC;
    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
    SetFlag(H, (HL & 0x1000) == 0x1000);


}
void Z80g::Opx19()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint16_t DE = ((dReg << 8) | eReg);

    SetFlag(C,(HL += DE) > 0xFFFF);

    HL += DE;
    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
    SetFlag(H, (HL & 0x1000) == 0x1000);


}
void Z80g::Opx29()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);
    uint16_t HL2 = ((hReg << 8) | lReg);

    SetFlag(C,(HL += HL2) > 0xFFFF);

    HL += HL2;
    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
    SetFlag(H, (HL & 0x1000) == 0x1000);

}
void Z80g::Opx39()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(C,(HL += sp) > 0xFFFF);

    HL += sp;
    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
    SetFlag(H, (HL & 0x1000) == 0x1000);

}
void Z80g::Opx07()
{
    cycles = 1;
    uint16_t aRegShift = aReg <<= 1;
    aReg <<= 1;
    
    if ((aRegShift & 0x0100) == 0x0100)
    {
        aReg |= 0x0001;
    }
    
    SetFlag(C, (aRegShift & 0x0100) == 0x0100);
    SetFlag(Z, false);
    SetFlag(N, false);    
    SetFlag(H, false);
}
void Z80g::Opx17()
{
    cycles = 1;

    aReg <<= 1;

    aReg |= (GetFlag(C) >> 4);

    SetFlag(Z, false);
    SetFlag(N, false);    
    SetFlag(H, false);
}
void Z80g::Opx0F()
{
    cycles = 1;
    if ((aReg & 0x01) == 1)
    {
        aReg >>= 1;
        SetFlag(C, true);
        aReg |= 0x80;
    }
    
    else
    {
        aReg >>= 1;
        SetFlag(C, false);
    }

    SetFlag(Z, false);
    SetFlag(N, false);    
    SetFlag(H, false);
}
void Z80g::Opx1F()
{
    cycles = 1;

    aReg >>= 1;
    aReg |= (GetFlag(C) << 3);

    SetFlag(Z, false);
    SetFlag(N, false);    
    SetFlag(H, false);
}
void Z80g::Opx37()
{
    cycles = 1;

    SetFlag(C, true);
    SetFlag(N, false);
    SetFlag(H, false);
}
void Z80g::Opx2F()
{
    cycles = 1;
    aReg = ~aReg;

    SetFlag(N, true);
    SetFlag(H, true);

}
void Z80g::Opx3F()
{
    cycles = 1;
    if (GetFlag(C))
    {
        SetFlag(C, false);
    }
    
    else
    {
        SetFlag(C, true);
    }
    
    SetFlag(N, false);    
    SetFlag(H, false);        
}
void Z80g::Opx80()
{
    cycles = 1;
    SetFlag(C, (aReg += bReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (bReg & 0xF)) & 0x10) == 0x10);

    aReg += bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx81()
{
    cycles = 1;
    SetFlag(C, (aReg += cReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (cReg & 0xF)) & 0x10) == 0x10);

    aReg += cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx82()
{
    cycles = 1;
    SetFlag(C, (aReg += dReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (dReg & 0xF)) & 0x10) == 0x10);

    aReg += dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx83()
{
    cycles = 1;
    SetFlag(C, (aReg += eReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (eReg & 0xF)) & 0x10) == 0x10);

    aReg += eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx84()
{
    cycles = 1;
    SetFlag(C, (aReg += hReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (hReg & 0xF)) & 0x10) == 0x10);

    aReg += hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx85()
{
    cycles = 1;
    SetFlag(C, (aReg += lReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (lReg & 0xF)) & 0x10) == 0x10);

    aReg += lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx86()
{        
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    
    SetFlag(C, (aReg += read(HL)) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (read(HL) & 0xF)) & 0x10) == 0x10);

    aReg += read(HL);

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx87()
{          
    cycles = 1;
    SetFlag(C, (aReg += aReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (aReg & 0xF)) & 0x10) == 0x10);

    aReg += aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx88()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += bReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (bReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += bReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx89()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += cReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (cReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += cReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx8A()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += dReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (dReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += dReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx8B()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += eReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (eReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += eReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx8C()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += hReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (hReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += hReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx8D()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += lReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (lReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += lReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx8E()
{        
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t carryStatus = (GetFlag(C) >> 4);

    SetFlag(C, ((aReg += read(HL)) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (read(HL) & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += read(HL);
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx8F()
{         
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg += aReg) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (bReg & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += aReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::Opx90()
{
    cycles = 1;
    SetFlag(C, (aReg -= bReg) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (bReg & 0xF)) & 0x10) == 0x10);

    aReg -= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx91()
{
    cycles = 1;
    SetFlag(C, (aReg -= cReg) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (cReg & 0xF)) & 0x10) == 0x10);

    aReg -= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx92()
{
    cycles = 1;
    SetFlag(C, (aReg -= dReg) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (dReg & 0xF)) & 0x10) == 0x10);

    aReg -= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx93()
{
    cycles = 1;
    SetFlag(C, (aReg -= eReg) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (eReg & 0xF)) & 0x10) == 0x10);

    aReg -= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx94()
{
    cycles = 1;
    SetFlag(C, (aReg -= hReg) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (hReg & 0xF)) & 0x10) == 0x10);

    aReg -= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx95()
{
    cycles = 1;
    SetFlag(C, (aReg -= lReg) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (lReg & 0xF)) & 0x10) == 0x10);

    aReg -= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx96()
{        
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    
    SetFlag(C, (aReg -= read(HL)) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (read(HL) & 0xF)) & 0x10) == 0x10);

    aReg -= read(HL);

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx97()
{        
    cycles = 1;
    
    SetFlag(C, (aReg -= aReg) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (aReg & 0xF)) & 0x10) == 0x10));

    aReg -= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx98()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= bReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (bReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= bReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx99()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= cReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (cReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= cReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx9A()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= dReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (dReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= dReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx9B()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= eReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (eReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= eReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx9C()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= hReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (hReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= hReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx9D()
{
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= lReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (lReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= lReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx9E()
{        
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t carryStatus = (GetFlag(C) >> 4);

    SetFlag(C, ((aReg -= read(HL)) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (read(HL) & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= read(HL);
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::Opx9F()
{         
    cycles = 1;
    uint8_t carryStatus = (GetFlag(C) >> 4);
    
    SetFlag(C, ((aReg -= aReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF) - (aReg & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= aReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z80g::OpxA0()
{
    cycles = 1;
    aReg &= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA1()
{
    cycles = 1;
    aReg &= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA2()
{
    cycles = 1;
    aReg &= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA3()
{
    cycles = 1;
    aReg &= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA4()
{
    cycles = 1;
    aReg &= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA5()
{
    cycles = 1;
    aReg &= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA6()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    
    aReg &= read(HL);

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA7()
{
    cycles = 1;
    aReg &= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxA8()
{
    cycles = 1;
    aReg ^= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxA9()
{
    cycles = 1;
    aReg ^= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxAA()
{
    cycles = 1;
    aReg ^= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxAB()
{
    cycles = 1;
    aReg ^= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxAC()
{
    cycles = 1;
    aReg ^= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxAD()
{
    cycles = 1;
    aReg ^= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxAE()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    aReg ^= read(HL);

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxAF()
{
    cycles = 1;
    aReg ^= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB0()
{
    cycles = 1;
    aReg |= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB1()
{
    cycles = 1;
    aReg |= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB2()
{
    cycles = 1;
    aReg |= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB3()
{
    cycles = 1;
    aReg |= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB4()
{
    cycles = 1;
    aReg |= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB5()
{
    cycles = 1;
    aReg |= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB6()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    aReg |= read(HL);

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB7()
{
    cycles = 1;
    aReg |= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxB8()
{
    cycles = 1;
    SetFlag(Z, (aReg - bReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (bReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - bReg) < 0x00);
}
void Z80g::OpxB9()
{
    cycles = 1;
    SetFlag(Z, (aReg - cReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (cReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - cReg) < 0x00);
}
void Z80g::OpxBA()
{
    cycles = 1;
    SetFlag(Z, (aReg - dReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (dReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - dReg) < 0x00);
}
void Z80g::OpxBB()
{
    cycles = 1;
    SetFlag(Z, (aReg - eReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (eReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - eReg) < 0x00);
}
void Z80g::OpxBC()
{
    cycles = 1;
    SetFlag(Z, (aReg - hReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (hReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - hReg) < 0x00);
}
void Z80g::OpxBD()
{
    cycles = 1;
    SetFlag(Z, (aReg - lReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (lReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - lReg) < 0x00);
}
void Z80g::OpxBE()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(HL);
    
    SetFlag(Z, (aReg - d8) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (d8 & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - d8) < 0x00);
}
void Z80g::OpxBF()
{
    cycles = 1;
    SetFlag(Z, (aReg - aReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (aReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - aReg) < 0x00);
}
void Z80g::OpxC6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    
    SetFlag(C, (aReg + d8) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (d8 & 0xF)) & 0x10) == 0x10);
    
    aReg += d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);

}
void Z80g::OpxD6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    
    SetFlag(C, (aReg - d8) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (d8 & 0xF)) & 0x10) == 0x10);
    
    aReg -= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::OpxE6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    
    aReg &= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z80g::OpxF6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    
    aReg |= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxCE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    uint8_t carryStatus = (GetFlag(C) >> 4);

    SetFlag(C, ((aReg + d8) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (d8 & 0xF)) + carryStatus) & 0x10) == 0x10);
    
    aReg += d8;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);

}
void Z80g::OpxDE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    uint8_t carryStatus = (GetFlag(C) >> 4);

    SetFlag(C, ((aReg - d8) - carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) - (d8 & 0xF)) - carryStatus) & 0x10) == 0x10);
    
    aReg -= d8;
    aReg -= carryStatus;
    
    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z80g::OpxEE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    
    aReg ^= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z80g::OpxFE()
{
    cycles = 2;
    uint8_t d8 = read(pc);

    SetFlag(Z, (aReg - d8) == 0);
    SetFlag(H, (((aReg & 0xF) - (d8 & 0xF)) & 0x10) == 0x10);
    SetFlag(N, true);
    SetFlag(C, (aReg - d8) < 0x00);
}
void Z80g::OpxE8()
{
    cycles = 4;

    int8_t r8 = read(pc);

    r8 = (~r8 + 1);    
    
    SetFlag(C, (sp + r8) > 0xFF);
    
    sp += r8;

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, (((sp & 0xF) + (r8 & 0xF)) & 0x10) == 0x10);
}
void Z80g::OpxF8()
{       
    cycles = 3; 
    uint16_t HL = ((hReg << 8) | lReg);

    int8_t r8 = read(pc);
    

    HL = sp + r8;

    hReg = (HL & 0xFF00);
    lReg = (HL & 0x00FF);

}
void Z80g::OpxF9()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    sp = HL;
}
void Z80g::Opx20()
{
    cycles = 2;
    int8_t r8 = read(pc);
    
    if (GetFlag(Z) == 0)
    {
        pc += r8;
        cycles = 3;
    }
    
}
void Z80g::Opx30()
{
    cycles = 2;
    int8_t r8 = read(pc);
    
    if (GetFlag(C) == 0)
    {
        pc += r8;
        cycles = 3;
    }
    
}
void Z80g::Opx18()
{
    cycles = 3;
    int8_t r8 = read(pc);

    pc += r8;

}
void Z80g::Opx28()
{
    cycles = 2;
    int8_t r8 = read(pc);
    
    if (GetFlag(Z) == 1)
    {
        pc += r8;
        cycles = 3;
    }
}
void Z80g::Opx38()
{
    cycles = 2;
    int8_t r8 = read(pc);
    
    if (GetFlag(C) == 1)
    {
        pc += r8;
        cycles = 3;
    }
}
void Z80g::Opx08()
{
    cycles = 5;
    
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    uint16_t a16 = (hi << 8) | lo;
    uint8_t splo = (sp & 0x00FF);
    uint8_t sphi = (sp & 0xFF00);

    write(a16, splo);
    write((a16 + 1), sphi);

}
void Z80g::OpxFA()
{
    cycles = 4;
    
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    uint16_t a16 = (hi << 8) | lo;


    aReg = read(a16);
}
void Z80g::OpxEA()
{
    cycles = 4;
    
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    uint16_t a16 = (hi << 8) | lo;


    write(a16, aReg);
}
void Z80g::OpxE0()
{
    cycles = 3;

    uint16_t a8 = 0xFF00 | read(pc);
    write(a8, aReg);
}
void Z80g::OpxF0()
{
    cycles = 3;

    uint16_t a8 = 0xFF00 | read(pc);
    aReg = read(a8);
}
void Z80g::OpxE2()
{
    cycles = 2;

    uint16_t a8 = 0xFF00 | cReg;
    write(a8, aReg);
}
void Z80g::OpxF2()
{
    cycles = 2;

    uint16_t a8 = 0xFF00 | cReg;
    aReg = read(a8);
}
void Z80g::OpxC5()
{
    cycles = 4;

    sp--;
    write(sp, bReg);
    sp--;
    write(sp, cReg);
}
void Z80g::OpxD5()
{
    cycles = 4;
    
    sp--;
    write(sp, dReg);
    sp--;
    write(sp, eReg);
}
void Z80g::OpxE5()
{
    cycles = 4;
    
    sp--;
    write(sp, hReg);
    sp--;
    write(sp, lReg);
}
void Z80g::OpxF5()
{
    cycles = 4;
    
    sp--;
    write(sp, aReg);
    sp--;
    write(sp, fReg);
}
void Z80g::OpxC1()
{
    cycles = 3;
    
    bReg = read(sp);
    sp++;
    cReg = read(sp);
    sp++;
}
void Z80g::OpxD1()
{
    cycles = 3;
    
    dReg = read(sp);
    sp++;
    eReg = read(sp);
    sp++;
}
void Z80g::OpxE1()
{
    cycles = 3;
    
    hReg = read(sp);
    sp++;
    lReg = read(sp);
    sp++;
}
void Z80g::OpxF1()
{
    cycles = 3;
    
    aReg = read(sp);
    sp++;
    fReg = read(sp);
    sp++;
}
void Z80g::OpxF3()
{
    cycles = 1;
    
    write(0xFFFF, 0x00);
}
void Z80g::OpxFB()
{
    cycles = 1;
    
    write(0xFFFF, 0x1F);
}
void Z80g::Opx27()
{
    cycles = 1;
   
    if (GetFlag(N) == 0)
    {
        if (GetFlag(C) == 1 || aReg > 0x99)
        {
            aReg += 0x60;
            SetFlag(C, true);
        }

        if (GetFlag(H) == 1 || (aReg & 0x0f) > 0x09)
        {
            aReg += 0x6;
        }
        
    }

    if (GetFlag(N) != 0)
    {
        if (GetFlag(C) == 1 || aReg > 0x99)
        {
            aReg -= 0x60;
        }
        
        if (GetFlag(H) == 1 || (aReg & 0x0F) > 0x09)
        {
            aReg -= 0x6;
        }
        
    }
    
    SetFlag(H, false);
    SetFlag(Z, aReg == 0);
    
}
void Z80g::OpxC7()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0000;
}
void Z80g::OpxCF()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0008;
}
void Z80g::OpxD7()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0010;
}
void Z80g::OpxDF()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0018;
}
void Z80g::OpxE7()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0020;
}
void Z80g::OpxEF()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0028;
}
void Z80g::OpxF7()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0030;
}
void Z80g::OpxFF()
{
    cycles = 4;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc = 0x0038;
}
void Z80g::OpxC8()
{
    cycles = 2;
    
    if (GetFlag(Z) == 1)
    {
        cycles = 5;

        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);
        sp++;

        pc |= (hi << 4);
        pc |= lo;

    }
    
}
void Z80g::OpxD8()
{
    cycles = 2;
    
    if (GetFlag(C) == 1)
    {
        cycles = 5;

        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);
        sp++;

        pc |= (hi << 4);
        pc |= lo;

    }
    
}
void Z80g::OpxC9()
{
    cycles = 4;

    uint8_t lo = read(sp);
    sp++;
    uint8_t hi = read(sp);
    sp++;

    pc |= (hi << 4);
    pc |= lo;
}
void Z80g::OpxD9()
{
    cycles = 4;
    uint8_t IME = 0x1F;

    uint8_t lo = read(sp);
    sp++;
    uint8_t hi = read(sp);
    sp++;

    pc |= (hi << 4);
    pc |= lo;

    write(0xFFFF, IME);
}
void Z80g::OpxE9()
{
    cycles = 1;
    
    uint16_t HL = ((hReg << 8) | lReg);

    pc = HL;

}
void Z80g::OpxC0()
{
    cycles = 2;
    
    if (GetFlag(Z) == 0)
    {
        cycles = 5;

        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);
        sp++;

        pc |= (hi << 4);
        pc |= lo;

    }
    
}
void Z80g::OpxD0()
{
    cycles = 2;
    
    if (GetFlag(C) == 0)
    {
        cycles = 5;

        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);
        sp++;

        pc |= (hi << 4);
        pc |= lo;

    }
    
}
void Z80g::OpxC3()
{
    cycles = 4;
    
    pc++;
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);

    uint16_t a16 = (hi << 4) | lo;

    pc = a16;
}
void Z80g::OpxC2()
{
    cycles = 3;
    
    if (GetFlag(Z) == 0)
    {
        cycles = 4;
        
        pc++;
        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;

        pc = a16;
    }
    
}
void Z80g::OpxD2()
{
    cycles = 3;
    
    if (GetFlag(C) == 0)
    {
        cycles = 4;
        
        pc++;
        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;

        pc = a16;
    }
    
}
void Z80g::OpxCA()
{
    cycles = 3;
    
    if (GetFlag(Z) == 1)
    {
        cycles = 4;
        
        pc++;
        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;

        pc = a16;
    }
    
}
void Z80g::OpxDA()
{
    cycles = 3;
    
    if (GetFlag(C) == 1)
    {
        cycles = 4;
        
        pc++;
        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;

        pc = a16;
    }
    
}
void Z80g::OpxCD()
{
    cycles = 6;
    
    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00);
    
    --sp;
    write(sp, hi);
    --sp;
    write(sp, lo);

    pc++;
    lo = read(pc);
    pc++;
    hi = read(pc);

    uint16_t a16 = (hi << 4) | lo;
    pc = a16;

}
void Z80g::OpxCC()
{
    cycles = 3;
    
    if (GetFlag(Z) == 1)
    {
        cycles = 6;
    
        uint8_t lo = (pc & 0x00FF);
        uint8_t hi = (pc & 0xFF00);

        --sp;
        write(sp, hi);
        --sp;
        write(sp, lo);

        pc++;
        lo = read(pc);
        pc++;
        hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;
        pc = a16;
    }
    
}
void Z80g::OpxDC()
{
    cycles = 3;
    
    if (GetFlag(C) == 1)
    {
        cycles = 6;
    
        uint8_t lo = (pc & 0x00FF);
        uint8_t hi = (pc & 0xFF00);

        --sp;
        write(sp, hi);
        --sp;
        write(sp, lo);

        pc++;
        lo = read(pc);
        pc++;
        hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;
        pc = a16;
    }
    
}
void Z80g::OpxC4()
{
    cycles = 3;
    
    if (GetFlag(Z) == 0)
    {
        cycles = 6;
    
        uint8_t lo = (pc & 0x00FF);
        uint8_t hi = (pc & 0xFF00);

        --sp;
        write(sp, hi);
        --sp;
        write(sp, lo);

        pc++;
        lo = read(pc);
        pc++;
        hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;
        pc = a16;
    }
    
}
void Z80g::OpxD4()
{
    cycles = 3;
    
    if (GetFlag(C) == 0)
    {
        cycles = 6;
    
        uint8_t lo = (pc & 0x00FF);
        uint8_t hi = (pc & 0xFF00);

        --sp;
        write(sp, hi);
        --sp;
        write(sp, lo);

        pc++;
        lo = read(pc);
        pc++;
        hi = read(pc);

        uint16_t a16 = (hi << 4) | lo;
        pc = a16;
    }
    
}
void Z80g::Opx00()
{
    //Do nothing
}
void Z80g::Opx76()  //Halt
{
    bool haltQuit = 0;
    cycles = 1;
    
    while (!haltQuit)
    {
        uint8_t IR = read(0xFF0F);
        
        for (size_t i = 0; i <= 4; i++)
        {
            if ((IR & (1 << i)) == 1)
            {
                haltQuit = 1;
            }
            
        }  
        
    }
    
}