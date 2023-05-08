#include <iostream>
#include <fstream>
#include "Z8080.h"
#include "bus.h"

Z8080::Z8080()
{
    table[0x00] = {&Z8080::Opx00};
    table[0x10] = {&Z8080::Opx10};
    table[0x20] = {&Z8080::Opx20};
    table[0x30] = {&Z8080::Opx30};
    table[0x40] = {&Z8080::Opx40};
    table[0x50] = {&Z8080::Opx50};
    table[0x60] = {&Z8080::Opx60};
    table[0x70] = {&Z8080::Opx70};
    table[0x01] = {&Z8080::Opx01};
    table[0x11] = {&Z8080::Opx11};
    table[0x21] = {&Z8080::Opx21};
    table[0x31] = {&Z8080::Opx31};
    table[0x41] = {&Z8080::Opx41};
    table[0x51] = {&Z8080::Opx51};
    table[0x61] = {&Z8080::Opx61};
    table[0x71] = {&Z8080::Opx71};
    table[0x02] = {&Z8080::Opx02};
    table[0x12] = {&Z8080::Opx12};
    table[0x22] = {&Z8080::Opx22};
    table[0x32] = {&Z8080::Opx32};
    table[0x42] = {&Z8080::Opx42};
    table[0x52] = {&Z8080::Opx52};
    table[0x62] = {&Z8080::Opx62};
    table[0x72] = {&Z8080::Opx72};
    table[0x03] = {&Z8080::Opx03};
    table[0x13] = {&Z8080::Opx13};
    table[0x23] = {&Z8080::Opx23};
    table[0x33] = {&Z8080::Opx33};
    table[0x43] = {&Z8080::Opx43};
    table[0x53] = {&Z8080::Opx53};
    table[0x63] = {&Z8080::Opx63};
    table[0x73] = {&Z8080::Opx73};
    table[0x04] = {&Z8080::Opx04};
    table[0x14] = {&Z8080::Opx14};
    table[0x24] = {&Z8080::Opx24};
    table[0x34] = {&Z8080::Opx34};
    table[0x44] = {&Z8080::Opx44};
    table[0x54] = {&Z8080::Opx54};
    table[0x64] = {&Z8080::Opx64};
    table[0x74] = {&Z8080::Opx74};
    table[0x05] = {&Z8080::Opx05};
    table[0x15] = {&Z8080::Opx15};
    table[0x25] = {&Z8080::Opx25};
    table[0x35] = {&Z8080::Opx35};
    table[0x45] = {&Z8080::Opx45};
    table[0x55] = {&Z8080::Opx55};
    table[0x65] = {&Z8080::Opx65};
    table[0x75] = {&Z8080::Opx75};
    table[0x06] = {&Z8080::Opx06};
    table[0x16] = {&Z8080::Opx16};
    table[0x26] = {&Z8080::Opx26};
    table[0x36] = {&Z8080::Opx36};
    table[0x46] = {&Z8080::Opx46};
    table[0x56] = {&Z8080::Opx56};
    table[0x66] = {&Z8080::Opx66};
    table[0x76] = {&Z8080::Opx76};
    table[0x07] = {&Z8080::Opx07};
    table[0x17] = {&Z8080::Opx17};
    table[0x27] = {&Z8080::Opx27};
    table[0x37] = {&Z8080::Opx37};
    table[0x47] = {&Z8080::Opx47};
    table[0x57] = {&Z8080::Opx57};
    table[0x67] = {&Z8080::Opx67};
    table[0x77] = {&Z8080::Opx77};
    table[0x08] = {&Z8080::Opx08};
    table[0x18] = {&Z8080::Opx18};
    table[0x28] = {&Z8080::Opx28};
    table[0x38] = {&Z8080::Opx38};
    table[0x48] = {&Z8080::Opx48};
    table[0x58] = {&Z8080::Opx58};
    table[0x68] = {&Z8080::Opx68};
    table[0x78] = {&Z8080::Opx78};
    table[0x09] = {&Z8080::Opx09};
    table[0x19] = {&Z8080::Opx19};
    table[0x29] = {&Z8080::Opx29};
    table[0x39] = {&Z8080::Opx39};
    table[0x49] = {&Z8080::Opx49};
    table[0x59] = {&Z8080::Opx59};
    table[0x69] = {&Z8080::Opx69};
    table[0x79] = {&Z8080::Opx79};
    table[0x0A] = {&Z8080::Opx0A};
    table[0x1A] = {&Z8080::Opx1A};
    table[0x2A] = {&Z8080::Opx2A};
    table[0x3A] = {&Z8080::Opx3A};
    table[0x4A] = {&Z8080::Opx4A};
    table[0x5A] = {&Z8080::Opx5A};
    table[0x6A] = {&Z8080::Opx6A};
    table[0x7A] = {&Z8080::Opx7A};
    table[0x0B] = {&Z8080::Opx0B};
    table[0x1B] = {&Z8080::Opx1B};
    table[0x2B] = {&Z8080::Opx2B};
    table[0x3B] = {&Z8080::Opx3B};
    table[0x4B] = {&Z8080::Opx4B};
    table[0x5B] = {&Z8080::Opx5B};
    table[0x6B] = {&Z8080::Opx6B};
    table[0x7B] = {&Z8080::Opx7B};
    table[0x0C] = {&Z8080::Opx0C};
    table[0x1C] = {&Z8080::Opx1C};
    table[0x2C] = {&Z8080::Opx2C};
    table[0x3C] = {&Z8080::Opx3C};
    table[0x4C] = {&Z8080::Opx4C};
    table[0x5C] = {&Z8080::Opx5C};
    table[0x6C] = {&Z8080::Opx6C};
    table[0x7C] = {&Z8080::Opx7C};
    table[0x0D] = {&Z8080::Opx0D};
    table[0x1D] = {&Z8080::Opx1D};
    table[0x2D] = {&Z8080::Opx2D};
    table[0x3D] = {&Z8080::Opx3D};
    table[0x4D] = {&Z8080::Opx4D};
    table[0x5D] = {&Z8080::Opx5D};
    table[0x6D] = {&Z8080::Opx6D};
    table[0x7D] = {&Z8080::Opx7D};
    table[0x0E] = {&Z8080::Opx0E};
    table[0x1E] = {&Z8080::Opx1E};
    table[0x2E] = {&Z8080::Opx2E};
    table[0x3E] = {&Z8080::Opx3E};
    table[0x4E] = {&Z8080::Opx4E};
    table[0x5E] = {&Z8080::Opx5E};
    table[0x6E] = {&Z8080::Opx6E};
    table[0x7E] = {&Z8080::Opx7E};
    table[0x0F] = {&Z8080::Opx0F};
    table[0x1F] = {&Z8080::Opx1F};
    table[0x2F] = {&Z8080::Opx2F};
    table[0x3F] = {&Z8080::Opx3F};
    table[0x4F] = {&Z8080::Opx4F};
    table[0x5F] = {&Z8080::Opx5F};
    table[0x6F] = {&Z8080::Opx6F};
    table[0x7F] = {&Z8080::Opx7F};

    table[0x80] = {&Z8080::Opx80};
    table[0x90] = {&Z8080::Opx90};
    table[0xA0] = {&Z8080::OpxA0};
    table[0xB0] = {&Z8080::OpxB0};
    table[0xC0] = {&Z8080::OpxC0};
    table[0xD0] = {&Z8080::OpxD0};
    table[0xE0] = {&Z8080::OpxE0};
    table[0xF0] = {&Z8080::OpxF0};
    table[0x81] = {&Z8080::Opx81};
    table[0x91] = {&Z8080::Opx91};
    table[0xA1] = {&Z8080::OpxA1};
    table[0xB1] = {&Z8080::OpxB1};
    table[0xC1] = {&Z8080::OpxC1};
    table[0xD1] = {&Z8080::OpxD1};
    table[0xE1] = {&Z8080::OpxE1};
    table[0xF1] = {&Z8080::OpxF1};
    table[0x82] = {&Z8080::Opx82};
    table[0x92] = {&Z8080::Opx92};
    table[0xA2] = {&Z8080::OpxA2};
    table[0xB2] = {&Z8080::OpxB2};
    table[0xC2] = {&Z8080::OpxC2};
    table[0xD2] = {&Z8080::OpxD2};
    table[0xE2] = {&Z8080::OpxE2};
    table[0xF2] = {&Z8080::OpxF2};
    table[0x83] = {&Z8080::Opx83};
    table[0x93] = {&Z8080::Opx93};
    table[0xA3] = {&Z8080::OpxA3};
    table[0xB3] = {&Z8080::OpxB3};
    table[0xC3] = {&Z8080::OpxC3};
    table[0xD3] = {&Z8080::Opx00};
    table[0xE3] = {&Z8080::Opx00};
    table[0xF3] = {&Z8080::OpxF3};
    table[0x84] = {&Z8080::Opx84};
    table[0x94] = {&Z8080::Opx94};
    table[0xA4] = {&Z8080::OpxA4};
    table[0xB4] = {&Z8080::OpxB4};
    table[0xC4] = {&Z8080::OpxC4};
    table[0xD4] = {&Z8080::OpxD4};
    table[0xE4] = {&Z8080::Opx00};
    table[0xF4] = {&Z8080::Opx00};
    table[0x85] = {&Z8080::Opx85};
    table[0x95] = {&Z8080::Opx95};
    table[0xA5] = {&Z8080::OpxA5};
    table[0xB5] = {&Z8080::OpxB5};
    table[0xC5] = {&Z8080::OpxC5};
    table[0xD5] = {&Z8080::OpxD5};
    table[0xE5] = {&Z8080::OpxE5};
    table[0xF5] = {&Z8080::OpxF5};
    table[0x86] = {&Z8080::Opx86};
    table[0x96] = {&Z8080::Opx96};
    table[0xA6] = {&Z8080::OpxA6};
    table[0xB6] = {&Z8080::OpxB6};
    table[0xC6] = {&Z8080::OpxC6};
    table[0xD6] = {&Z8080::OpxD6};
    table[0xE6] = {&Z8080::OpxE6};
    table[0xF6] = {&Z8080::OpxF6};
    table[0x87] = {&Z8080::Opx87};
    table[0x97] = {&Z8080::Opx97};
    table[0xA7] = {&Z8080::OpxA7};
    table[0xB7] = {&Z8080::OpxB7};
    table[0xC7] = {&Z8080::OpxC7};
    table[0xD7] = {&Z8080::OpxD7};
    table[0xE7] = {&Z8080::OpxE7};
    table[0xF7] = {&Z8080::OpxF7};
    table[0x88] = {&Z8080::Opx88};
    table[0x98] = {&Z8080::Opx98};
    table[0xA8] = {&Z8080::OpxA8};
    table[0xB8] = {&Z8080::OpxB8};
    table[0xC8] = {&Z8080::OpxC8};
    table[0xD8] = {&Z8080::OpxD8};
    table[0xE8] = {&Z8080::OpxE8};
    table[0xF8] = {&Z8080::OpxF8};
    table[0x89] = {&Z8080::Opx89};
    table[0x99] = {&Z8080::Opx99};
    table[0xA9] = {&Z8080::OpxA9};
    table[0xB9] = {&Z8080::OpxB9};
    table[0xC9] = {&Z8080::OpxC9};
    table[0xD9] = {&Z8080::OpxD9};
    table[0xE9] = {&Z8080::OpxE9};
    table[0xF9] = {&Z8080::OpxF9};
    table[0x8A] = {&Z8080::Opx8A};
    table[0x9A] = {&Z8080::Opx9A};
    table[0xAA] = {&Z8080::OpxAA};
    table[0xBA] = {&Z8080::OpxBA};
    table[0xCA] = {&Z8080::OpxCA};
    table[0xDA] = {&Z8080::OpxDA};
    table[0xEA] = {&Z8080::OpxEA};
    table[0xFA] = {&Z8080::OpxFA};
    table[0x8B] = {&Z8080::Opx8B};
    table[0x9B] = {&Z8080::Opx9B};
    table[0xAB] = {&Z8080::OpxAB};
    table[0xBB] = {&Z8080::OpxBB}; /* Opcode CB does not exist*/
    table[0xDB] = {&Z8080::Opx00};
    table[0xEB] = {&Z8080::Opx00};
    table[0xFB] = {&Z8080::OpxFB};
    table[0x8C] = {&Z8080::Opx8C};
    table[0x9C] = {&Z8080::Opx9C};
    table[0xAC] = {&Z8080::OpxAC};
    table[0xBC] = {&Z8080::OpxBC};
    table[0xCC] = {&Z8080::OpxCC};
    table[0xDC] = {&Z8080::OpxDC};
    table[0xEC] = {&Z8080::Opx00};
    table[0xFC] = {&Z8080::Opx00};
    table[0x8D] = {&Z8080::Opx8D};
    table[0x9D] = {&Z8080::Opx9D};
    table[0xAD] = {&Z8080::OpxAD};
    table[0xBD] = {&Z8080::OpxBD};
    table[0xCD] = {&Z8080::OpxCD};
    table[0xDD] = {&Z8080::Opx00};
    table[0xED] = {&Z8080::Opx00};
    table[0xFD] = {&Z8080::Opx00};
    table[0x8E] = {&Z8080::Opx8E};
    table[0x9E] = {&Z8080::Opx9E};
    table[0xAE] = {&Z8080::OpxAE};
    table[0xBE] = {&Z8080::OpxBE};
    table[0xCE] = {&Z8080::OpxCE};
    table[0xDE] = {&Z8080::OpxDE};
    table[0xEE] = {&Z8080::OpxEE};
    table[0xFE] = {&Z8080::OpxFE};
    table[0x8F] = {&Z8080::Opx8F};
    table[0x9F] = {&Z8080::Opx9F};
    table[0xAF] = {&Z8080::OpxAF};
    table[0xBF] = {&Z8080::OpxBF};
    table[0xCF] = {&Z8080::OpxCF};
    table[0xDF] = {&Z8080::OpxDF};
    table[0xEF] = {&Z8080::OpxEF};
    table[0xFF] = {&Z8080::OpxFF};

    tableCB[0x00] = {&Z8080::OpxCB00};
    tableCB[0x10] = {&Z8080::OpxCB10};
    tableCB[0x20] = {&Z8080::OpxCB20};
    tableCB[0x30] = {&Z8080::OpxCB30};
    tableCB[0x40] = {&Z8080::OpxCB40};
    tableCB[0x50] = {&Z8080::OpxCB50};
    tableCB[0x60] = {&Z8080::OpxCB60};
    tableCB[0x70] = {&Z8080::OpxCB70};
    tableCB[0x01] = {&Z8080::OpxCB01};
    tableCB[0x11] = {&Z8080::OpxCB11};
    tableCB[0x21] = {&Z8080::OpxCB21};
    tableCB[0x31] = {&Z8080::OpxCB31};
    tableCB[0x41] = {&Z8080::OpxCB41};
    tableCB[0x51] = {&Z8080::OpxCB51};
    tableCB[0x61] = {&Z8080::OpxCB61};
    tableCB[0x71] = {&Z8080::OpxCB71};
    tableCB[0x02] = {&Z8080::OpxCB02};
    tableCB[0x12] = {&Z8080::OpxCB12};
    tableCB[0x22] = {&Z8080::OpxCB22};
    tableCB[0x32] = {&Z8080::OpxCB32};
    tableCB[0x42] = {&Z8080::OpxCB42};
    tableCB[0x52] = {&Z8080::OpxCB52};
    tableCB[0x62] = {&Z8080::OpxCB62};
    tableCB[0x72] = {&Z8080::OpxCB72};
    tableCB[0x03] = {&Z8080::OpxCB03};
    tableCB[0x13] = {&Z8080::OpxCB13};
    tableCB[0x23] = {&Z8080::OpxCB23};
    tableCB[0x33] = {&Z8080::OpxCB33};
    tableCB[0x43] = {&Z8080::OpxCB43};
    tableCB[0x53] = {&Z8080::OpxCB53};
    tableCB[0x63] = {&Z8080::OpxCB63};
    tableCB[0x73] = {&Z8080::OpxCB73};
    tableCB[0x04] = {&Z8080::OpxCB04};
    tableCB[0x14] = {&Z8080::OpxCB14};
    tableCB[0x24] = {&Z8080::OpxCB24};
    tableCB[0x34] = {&Z8080::OpxCB34};
    tableCB[0x44] = {&Z8080::OpxCB44};
    tableCB[0x54] = {&Z8080::OpxCB54};
    tableCB[0x64] = {&Z8080::OpxCB64};
    tableCB[0x74] = {&Z8080::OpxCB74};
    tableCB[0x05] = {&Z8080::OpxCB05};
    tableCB[0x15] = {&Z8080::OpxCB15};
    tableCB[0x25] = {&Z8080::OpxCB25};
    tableCB[0x35] = {&Z8080::OpxCB35};
    tableCB[0x45] = {&Z8080::OpxCB45};
    tableCB[0x55] = {&Z8080::OpxCB55};
    tableCB[0x65] = {&Z8080::OpxCB65};
    tableCB[0x75] = {&Z8080::OpxCB75};
    tableCB[0x06] = {&Z8080::OpxCB06};
    tableCB[0x16] = {&Z8080::OpxCB16};
    tableCB[0x26] = {&Z8080::OpxCB26};
    tableCB[0x36] = {&Z8080::OpxCB36};
    tableCB[0x46] = {&Z8080::OpxCB46};
    tableCB[0x56] = {&Z8080::OpxCB56};
    tableCB[0x66] = {&Z8080::OpxCB66};
    tableCB[0x76] = {&Z8080::OpxCB76};
    tableCB[0x07] = {&Z8080::OpxCB07};
    tableCB[0x17] = {&Z8080::OpxCB17};
    tableCB[0x27] = {&Z8080::OpxCB27};
    tableCB[0x37] = {&Z8080::OpxCB37};
    tableCB[0x47] = {&Z8080::OpxCB47};
    tableCB[0x57] = {&Z8080::OpxCB57};
    tableCB[0x67] = {&Z8080::OpxCB67};
    tableCB[0x77] = {&Z8080::OpxCB77};
    tableCB[0x08] = {&Z8080::OpxCB08};
    tableCB[0x18] = {&Z8080::OpxCB18};
    tableCB[0x28] = {&Z8080::OpxCB28};
    tableCB[0x38] = {&Z8080::OpxCB38};
    tableCB[0x48] = {&Z8080::OpxCB48};
    tableCB[0x58] = {&Z8080::OpxCB58};
    tableCB[0x68] = {&Z8080::OpxCB68};
    tableCB[0x78] = {&Z8080::OpxCB78};
    tableCB[0x09] = {&Z8080::OpxCB09};
    tableCB[0x19] = {&Z8080::OpxCB19};
    tableCB[0x29] = {&Z8080::OpxCB29};
    tableCB[0x39] = {&Z8080::OpxCB39};
    tableCB[0x49] = {&Z8080::OpxCB49};
    tableCB[0x59] = {&Z8080::OpxCB59};
    tableCB[0x69] = {&Z8080::OpxCB69};
    tableCB[0x79] = {&Z8080::OpxCB79};
    tableCB[0x0A] = {&Z8080::OpxCB0A};
    tableCB[0x1A] = {&Z8080::OpxCB1A};
    tableCB[0x2A] = {&Z8080::OpxCB2A};
    tableCB[0x3A] = {&Z8080::OpxCB3A};
    tableCB[0x4A] = {&Z8080::OpxCB4A};
    tableCB[0x5A] = {&Z8080::OpxCB5A};
    tableCB[0x6A] = {&Z8080::OpxCB6A};
    tableCB[0x7A] = {&Z8080::OpxCB7A};
    tableCB[0x0B] = {&Z8080::OpxCB0B};
    tableCB[0x1B] = {&Z8080::OpxCB1B};
    tableCB[0x2B] = {&Z8080::OpxCB2B};
    tableCB[0x3B] = {&Z8080::OpxCB3B};
    tableCB[0x4B] = {&Z8080::OpxCB4B};
    tableCB[0x5B] = {&Z8080::OpxCB5B};
    tableCB[0x6B] = {&Z8080::OpxCB6B};
    tableCB[0x7B] = {&Z8080::OpxCB7B};
    tableCB[0x0C] = {&Z8080::OpxCB0C};
    tableCB[0x1C] = {&Z8080::OpxCB1C};
    tableCB[0x2C] = {&Z8080::OpxCB2C};
    tableCB[0x3C] = {&Z8080::OpxCB3C};
    tableCB[0x4C] = {&Z8080::OpxCB4C};
    tableCB[0x5C] = {&Z8080::OpxCB5C};
    tableCB[0x6C] = {&Z8080::OpxCB6C};
    tableCB[0x7C] = {&Z8080::OpxCB7C};
    tableCB[0x0D] = {&Z8080::OpxCB0D};
    tableCB[0x1D] = {&Z8080::OpxCB1D};
    tableCB[0x2D] = {&Z8080::OpxCB2D};
    tableCB[0x3D] = {&Z8080::OpxCB3D};
    tableCB[0x4D] = {&Z8080::OpxCB4D};
    tableCB[0x5D] = {&Z8080::OpxCB5D};
    tableCB[0x6D] = {&Z8080::OpxCB6D};
    tableCB[0x7D] = {&Z8080::OpxCB7D};
    tableCB[0x0E] = {&Z8080::OpxCB0E};
    tableCB[0x1E] = {&Z8080::OpxCB1E};
    tableCB[0x2E] = {&Z8080::OpxCB2E};
    tableCB[0x3E] = {&Z8080::OpxCB3E};
    tableCB[0x4E] = {&Z8080::OpxCB4E};
    tableCB[0x5E] = {&Z8080::OpxCB5E};
    tableCB[0x6E] = {&Z8080::OpxCB6E};
    tableCB[0x7E] = {&Z8080::OpxCB7E};
    tableCB[0x0F] = {&Z8080::OpxCB0F};
    tableCB[0x1F] = {&Z8080::OpxCB1F};
    tableCB[0x2F] = {&Z8080::OpxCB2F};
    tableCB[0x3F] = {&Z8080::OpxCB3F};
    tableCB[0x4F] = {&Z8080::OpxCB4F};
    tableCB[0x5F] = {&Z8080::OpxCB5F};
    tableCB[0x6F] = {&Z8080::OpxCB6F};
    tableCB[0x7F] = {&Z8080::OpxCB7F};

    tableCB[0x80] = {&Z8080::OpxCB80};
    tableCB[0x90] = {&Z8080::OpxCB90};
    tableCB[0xA0] = {&Z8080::OpxCBA0};
    tableCB[0xB0] = {&Z8080::OpxCBB0};
    tableCB[0xC0] = {&Z8080::OpxCBC0};
    tableCB[0xD0] = {&Z8080::OpxCBD0};
    tableCB[0xE0] = {&Z8080::OpxCBE0};
    tableCB[0xF0] = {&Z8080::OpxCBF0};
    tableCB[0x81] = {&Z8080::OpxCB81};
    tableCB[0x91] = {&Z8080::OpxCB91};
    tableCB[0xA1] = {&Z8080::OpxCBA1};
    tableCB[0xB1] = {&Z8080::OpxCBB1};
    tableCB[0xC1] = {&Z8080::OpxCBC1};
    tableCB[0xD1] = {&Z8080::OpxCBD1};
    tableCB[0xE1] = {&Z8080::OpxCBE1};
    tableCB[0xF1] = {&Z8080::OpxCBF1};
    tableCB[0x82] = {&Z8080::OpxCB82};
    tableCB[0x92] = {&Z8080::OpxCB92};
    tableCB[0xA2] = {&Z8080::OpxCBA2};
    tableCB[0xB2] = {&Z8080::OpxCBB2};
    tableCB[0xC2] = {&Z8080::OpxCBC2};
    tableCB[0xD2] = {&Z8080::OpxCBD2};
    tableCB[0xE2] = {&Z8080::OpxCBE2};
    tableCB[0xF2] = {&Z8080::OpxCBF2};
    tableCB[0x83] = {&Z8080::OpxCB83};
    tableCB[0x93] = {&Z8080::OpxCB93};
    tableCB[0xA3] = {&Z8080::OpxCBA3};
    tableCB[0xB3] = {&Z8080::OpxCBB3};
    tableCB[0xC3] = {&Z8080::OpxCBC3};
    tableCB[0xD3] = {&Z8080::OpxCB00};
    tableCB[0xE3] = {&Z8080::OpxCB00};
    tableCB[0xF3] = {&Z8080::OpxCBF3};
    tableCB[0x84] = {&Z8080::OpxCB84};
    tableCB[0x94] = {&Z8080::OpxCB94};
    tableCB[0xA4] = {&Z8080::OpxCBA4};
    tableCB[0xB4] = {&Z8080::OpxCBB4};
    tableCB[0xC4] = {&Z8080::OpxCBC4};
    tableCB[0xD4] = {&Z8080::OpxCBD4};
    tableCB[0xE4] = {&Z8080::OpxCB00};
    tableCB[0xF4] = {&Z8080::OpxCB00};
    tableCB[0x85] = {&Z8080::OpxCB85};
    tableCB[0x95] = {&Z8080::OpxCB95};
    tableCB[0xA5] = {&Z8080::OpxCBA5};
    tableCB[0xB5] = {&Z8080::OpxCBB5};
    tableCB[0xC5] = {&Z8080::OpxCBC5};
    tableCB[0xD5] = {&Z8080::OpxCBD5};
    tableCB[0xE5] = {&Z8080::OpxCBE5};
    tableCB[0xF5] = {&Z8080::OpxCBF5};
    tableCB[0x86] = {&Z8080::OpxCB86};
    tableCB[0x96] = {&Z8080::OpxCB96};
    tableCB[0xA6] = {&Z8080::OpxCBA6};
    tableCB[0xB6] = {&Z8080::OpxCBB6};
    tableCB[0xC6] = {&Z8080::OpxCBC6};
    tableCB[0xD6] = {&Z8080::OpxCBD6};
    tableCB[0xE6] = {&Z8080::OpxCBE6};
    tableCB[0xF6] = {&Z8080::OpxCBF6};
    tableCB[0x87] = {&Z8080::OpxCB87};
    tableCB[0x97] = {&Z8080::OpxCB97};
    tableCB[0xA7] = {&Z8080::OpxCBA7};
    tableCB[0xB7] = {&Z8080::OpxCBB7};
    tableCB[0xC7] = {&Z8080::OpxCBC7};
    tableCB[0xD7] = {&Z8080::OpxCBD7};
    tableCB[0xE7] = {&Z8080::OpxCBE7};
    tableCB[0xF7] = {&Z8080::OpxCBF7};
    tableCB[0x88] = {&Z8080::OpxCB88};
    tableCB[0x98] = {&Z8080::OpxCB98};
    tableCB[0xA8] = {&Z8080::OpxCBA8};
    tableCB[0xB8] = {&Z8080::OpxCBB8};
    tableCB[0xC8] = {&Z8080::OpxCBC8};
    tableCB[0xD8] = {&Z8080::OpxCBD8};
    tableCB[0xE8] = {&Z8080::OpxCBE8};
    tableCB[0xF8] = {&Z8080::OpxCBF8};
    tableCB[0x89] = {&Z8080::OpxCB89};
    tableCB[0x99] = {&Z8080::OpxCB99};
    tableCB[0xA9] = {&Z8080::OpxCBA9};
    tableCB[0xB9] = {&Z8080::OpxCBB9};
    tableCB[0xC9] = {&Z8080::OpxCBC9};
    tableCB[0xD9] = {&Z8080::OpxCBD9};
    tableCB[0xE9] = {&Z8080::OpxCBE9};
    tableCB[0xF9] = {&Z8080::OpxCBF9};
    tableCB[0x8A] = {&Z8080::OpxCB8A};
    tableCB[0x9A] = {&Z8080::OpxCB9A};
    tableCB[0xAA] = {&Z8080::OpxCBAA};
    tableCB[0xBA] = {&Z8080::OpxCBBA};
    tableCB[0xCA] = {&Z8080::OpxCBCA};
    tableCB[0xDA] = {&Z8080::OpxCBDA};
    tableCB[0xEA] = {&Z8080::OpxCBEA};
    tableCB[0xFA] = {&Z8080::OpxCBFA};
    tableCB[0x8B] = {&Z8080::OpxCB8B};
    tableCB[0x9B] = {&Z8080::OpxCB9B};
    tableCB[0xAB] = {&Z8080::OpxCBAB};
    tableCB[0xBB] = {&Z8080::OpxCBBB};
    tableCB[0xCB] = {&Z8080::OpxCBCB};
    tableCB[0xDB] = {&Z8080::OpxCB00};
    tableCB[0xEB] = {&Z8080::OpxCB00};
    tableCB[0xFB] = {&Z8080::OpxCBFB};
    tableCB[0x8C] = {&Z8080::OpxCB8C};
    tableCB[0x9C] = {&Z8080::OpxCB9C};
    tableCB[0xAC] = {&Z8080::OpxCBAC};
    tableCB[0xBC] = {&Z8080::OpxCBBC};
    tableCB[0xCC] = {&Z8080::OpxCBCC};
    tableCB[0xDC] = {&Z8080::OpxCBDC};
    tableCB[0xEC] = {&Z8080::OpxCB00};
    tableCB[0xFC] = {&Z8080::OpxCB00};
    tableCB[0x8D] = {&Z8080::OpxCB8D};
    tableCB[0x9D] = {&Z8080::OpxCB9D};
    tableCB[0xAD] = {&Z8080::OpxCBAD};
    tableCB[0xBD] = {&Z8080::OpxCBBD};
    tableCB[0xCD] = {&Z8080::OpxCBCD};
    tableCB[0xDD] = {&Z8080::OpxCB00};
    tableCB[0xED] = {&Z8080::OpxCB00};
    tableCB[0xFD] = {&Z8080::OpxCB00};
    tableCB[0x8E] = {&Z8080::OpxCB8E};
    tableCB[0x9E] = {&Z8080::OpxCB9E};
    tableCB[0xAE] = {&Z8080::OpxCBAE};
    tableCB[0xBE] = {&Z8080::OpxCBBE};
    tableCB[0xCE] = {&Z8080::OpxCBCE};
    tableCB[0xDE] = {&Z8080::OpxCBDE};
    tableCB[0xEE] = {&Z8080::OpxCBEE};
    tableCB[0xFE] = {&Z8080::OpxCBFE};
    tableCB[0x8F] = {&Z8080::OpxCB8F};
    tableCB[0x9F] = {&Z8080::OpxCB9F};
    tableCB[0xAF] = {&Z8080::OpxCBAF};
    tableCB[0xBF] = {&Z8080::OpxCBBF};
    tableCB[0xCF] = {&Z8080::OpxCBCF};
    tableCB[0xDF] = {&Z8080::OpxCBDF};
    tableCB[0xEF] = {&Z8080::OpxCBEF};
    tableCB[0xFF] = {&Z8080::OpxCBFF};
}

void Z8080::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
}

uint8_t Z8080::read(uint16_t addr)
{
    return bus->read(addr);
}

uint8_t Z8080::GetFlag(FLAGS f)
{
    return ((fReg & f) > 0) ? 1 : 0;
}

void Z8080::SetFlag(FLAGS f, bool v)
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

void Z8080::Clock()
{
    if (cycles == 0 && !halted)
    {
        Opcode = read(pc);
        pc++;

        if (Opcode == 0xCB)
        {
            Opcode = read(pc);
            pc++;

            (this->*(tableCB[Opcode & 0xFF]))();
        }

        else
        {
            (this->*(table[Opcode & 0xFF]))();
        }
    }

    ServiceInterrupts();

    if (!halted)
    {
        cycles--;
    }
    
}
void Z8080::DoDmaTransfer(uint16_t addr, uint8_t data)
{
    cycles = 156;

    uint16_t FixedAddr = (data << 8);
    for (size_t i = 0; i < 0xA0; i++)
    {
        uint8_t oamdata = read(FixedAddr + i);
        write(OAM + i, oamdata);
    }
}
void Z8080::ResetCpu()
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
    fReg = 0x00;

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::ServiceInterrupts()
{
    bool IRHandled = false; // Flag to check if the interrupt request was handled
    
    if (bus->m_IMEFlag)
    {
        if (bus->m_IEFlag.reg != 0)
        {
            for (uint8_t i = 1; i <= 17; i = i * 2)
            {
                uint8_t IRFlag = read(0xFF0F);

                if (((bus->m_IEFlag.reg & i) == 1) && (IRFlag & i) == 1)
                {
                    //  Call apropirate interrupt here
                    switch (i)
                    {
                    case 1:
                        //  Call VBlank interrupt and stop halt
                        halted = false;
                        write(sp, (pc & 0xFF00));
                        sp--;
                        write(sp, (pc & 0x00FF));
                        sp--;
                        pc = 0x0040;
                        IRHandled = true;
                        bus->m_IMEFlag = !bus->m_IMEFlag;
                        break;
                    case 2:
                        //  Call STAT interrupt
                        halted = false;
                        write(sp, (pc & 0xFF00));
                        sp--;
                        write(sp, (pc & 0x00FF));
                        sp--;
                        pc = 0x0048;
                        IRHandled = true;
                        bus->m_IMEFlag = !bus->m_IMEFlag;
                        break;
                    case 4:
                        //  Call Timer interrupt
                        halted = false;
                        write(sp, (pc & 0xFF00));
                        sp--;
                        write(sp, (pc & 0x00FF));
                        sp--;
                        pc = 0x0050;
                        IRHandled = true;
                        bus->m_IMEFlag = !bus->m_IMEFlag;
                        break;
                    case 8:
                        //  Call Serial interrupt
                        halted = false;
                        write(sp, (pc & 0xFF00));
                        sp--;
                        write(sp, (pc & 0x00FF));
                        sp--;
                        pc = 0x0058;
                        IRHandled = true;
                        bus->m_IMEFlag = !bus->m_IMEFlag;
                        break;
                    case 16:
                        //  Call Joypad interrupt
                        halted = false;
                        write(sp, (pc & 0xFF00));
                        sp--;
                        write(sp, (pc & 0x00FF));
                        sp--;
                        pc = 0x0060;
                        IRHandled = true;
                        bus->m_IMEFlag = !bus->m_IMEFlag;
                        break;
                    default:
                        break;
                    }
                }
                if (i == 16 || IRHandled)
                    return;
            }
        }
    }
}

void Z8080::Opx10() //  Stop instruction
{
}

void Z8080::Opx40()
{
    cycles = 1;
}
void Z8080::Opx41()
{
    cycles = 1;

    bReg = cReg;
}
void Z8080::Opx42()
{
    cycles = 1;

    bReg = dReg;
}
void Z8080::Opx43()
{
    cycles = 1;

    bReg = eReg;
}
void Z8080::Opx44()
{
    cycles = 1;

    bReg = hReg;
}
void Z8080::Opx45()
{
    cycles = 1;

    bReg = lReg;
}
void Z8080::Opx47()
{
    cycles = 1;

    bReg = aReg;
}
void Z8080::Opx48()
{
    cycles = 1;

    cReg = bReg;
}
void Z8080::Opx49()
{
    cycles = 1;
}
void Z8080::Opx4A()
{
    cycles = 1;

    cReg = dReg;
}
void Z8080::Opx4B()
{
    cycles = 1;

    cReg = eReg;
}
void Z8080::Opx4C()
{
    cycles = 1;

    cReg = hReg;
}
void Z8080::Opx4D()
{
    cycles = 1;

    cReg = lReg;
}
void Z8080::Opx4F()
{
    cycles = 1;

    cReg = aReg;
}
void Z8080::Opx50()
{
    cycles = 1;

    dReg = bReg;
}
void Z8080::Opx51()
{
    cycles = 1;

    dReg = cReg;
}
void Z8080::Opx52()
{
    cycles = 1;
}
void Z8080::Opx53()
{
    cycles = 1;

    dReg = eReg;
}
void Z8080::Opx54()
{
    cycles = 1;

    dReg = hReg;
}
void Z8080::Opx55()
{
    cycles = 1;

    dReg = lReg;
}
void Z8080::Opx57()
{
    cycles = 1;

    dReg = aReg;
}
void Z8080::Opx58()
{
    cycles = 1;

    eReg = bReg;
}
void Z8080::Opx59()
{
    cycles = 1;

    eReg = cReg;
}
void Z8080::Opx5A()
{
    cycles = 1;

    eReg = dReg;
}
void Z8080::Opx5B()
{

    cycles = 1;
}
void Z8080::Opx5C()
{
    cycles = 1;

    eReg = hReg;
}
void Z8080::Opx5D()
{
    cycles = 1;

    eReg = lReg;
}
void Z8080::Opx5F()
{
    cycles = 1;

    eReg = aReg;
}
void Z8080::Opx60()
{
    cycles = 1;

    hReg = bReg;
}
void Z8080::Opx61()
{
    cycles = 1;

    hReg = cReg;
}
void Z8080::Opx62()
{
    cycles = 1;

    hReg = dReg;
}
void Z8080::Opx63()
{
    cycles = 1;

    hReg = eReg;
}
void Z8080::Opx64()
{
    cycles = 1;
}
void Z8080::Opx65()
{
    cycles = 1;

    hReg = lReg;
}
void Z8080::Opx67()
{
    cycles = 1;

    hReg = aReg;
}
void Z8080::Opx68()
{
    cycles = 1;

    lReg = bReg;
}
void Z8080::Opx69()
{
    cycles = 1;

    lReg = cReg;
}
void Z8080::Opx6A()
{
    cycles = 1;

    lReg = dReg;
}
void Z8080::Opx6B()
{
    cycles = 1;

    lReg = eReg;
}
void Z8080::Opx6C()
{
    cycles = 1;

    lReg = hReg;
}
void Z8080::Opx6D()
{
    cycles = 1;
}
void Z8080::Opx6F()
{
    cycles = 1;

    lReg = aReg;
}
void Z8080::Opx78()
{
    cycles = 1;

    aReg = bReg;
}
void Z8080::Opx79()
{
    cycles = 1;

    aReg = cReg;
}
void Z8080::Opx7A()
{
    cycles = 1;

    aReg = dReg;
}
void Z8080::Opx7B()
{
    cycles = 1;

    aReg = eReg;
}
void Z8080::Opx7C()
{
    cycles = 1;

    aReg = hReg;
}
void Z8080::Opx7D()
{
    cycles = 1;

    aReg = lReg;
}
void Z8080::Opx7F()
{
    cycles = 1;
}
void Z8080::Opx06()
{
    cycles = 2;

    bReg = read(pc);
    pc++;
}
void Z8080::Opx0E()
{
    cycles = 2;
    cReg = read(pc);
    pc++;
}
void Z8080::Opx16()
{
    cycles = 2;
    dReg = read(pc);
    pc++;
}
void Z8080::Opx1E()
{
    cycles = 2;
    eReg = read(pc);
    pc++;
}
void Z8080::Opx26()
{
    cycles = 2;
    hReg = read(pc);
    pc++;
}
void Z8080::Opx2E()
{
    cycles = 2;
    lReg = read(pc);
    pc++;
}
void Z8080::Opx36()
{
    cycles = 3;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(pc);
    pc++;

    write(HL, d8);
}
void Z8080::Opx3E()
{
    cycles = 2;
    aReg = read(pc);
    pc++;
}
void Z8080::Opx46()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    bReg = read(HL);
}
void Z8080::Opx56()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    dReg = read(HL);
}
void Z8080::Opx66()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    hReg = read(HL);
}
void Z8080::Opx4E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    cReg = read(HL);
}
void Z8080::Opx5E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    eReg = read(HL);
}
void Z8080::Opx6E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    lReg = read(HL);
}
void Z8080::Opx7E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    aReg = read(HL);
}
void Z8080::Opx70()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, bReg);
}
void Z8080::Opx71()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, cReg);
}
void Z8080::Opx72()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, dReg);
}
void Z8080::Opx73()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, eReg);
}
void Z8080::Opx74()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, hReg);
}
void Z8080::Opx75()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, lReg);
}
void Z8080::Opx77()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    write(HL, aReg);
}
void Z8080::Opx02()
{
    cycles = 2;
    uint16_t BC = ((bReg << 8) | cReg);

    write(BC, aReg);
}
void Z8080::Opx12()
{
    cycles = 2;
    uint16_t DE = ((dReg << 8) | eReg);

    write(DE, aReg);
}
void Z8080::Opx22()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    write(HL, aReg);
    HL++;
    uint8_t NewH = ((HL & 0xFF00) >> 8);
    uint8_t NewL = (HL & 0x00FF);

    hReg = NewH;
    lReg = NewL;
}
void Z8080::Opx32()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    write(HL, aReg);
    HL--;
    uint8_t NewH = ((HL & 0xFF00) >> 8);
    uint8_t NewL = (HL & 0x00FF);

    hReg = NewH;
    lReg = NewL;
}
void Z8080::Opx0A()
{
    cycles = 2;
    uint16_t BC = ((bReg << 8) | cReg);

    aReg = read(BC);
}
// LD a, (DE)
void Z8080::Opx1A()
{
    cycles = 2;
    uint16_t DE = ((dReg << 8) | eReg);

    aReg = read(DE);
}
void Z8080::Opx2A()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    aReg = read(HL);
    HL++;
    uint8_t NewH = ((HL & 0xFF00) >> 8);
    uint8_t NewL = (HL & 0x00FF);

    hReg = NewH;
    lReg = NewL;
}
void Z8080::Opx3A()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    aReg = read(HL);
    HL--;
    uint8_t NewH = ((HL & 0xFF00) >> 8);
    uint8_t NewL = (HL & 0x00FF);

    hReg = NewH;
    lReg = NewL;
}
void Z8080::Opx01()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    bReg = hi;
    cReg = lo;
}
void Z8080::Opx11()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    dReg = hi;
    eReg = lo;
}
void Z8080::Opx21()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    hReg = hi;
    lReg = lo;
}
void Z8080::Opx31()
{
    cycles = 3;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    sp = ((hi << 8) | lo);
}
void Z8080::Opx03()
{
    cycles = 2;

    uint16_t BC = ((bReg << 8) | cReg);

    BC++;

    uint8_t NewB = ((BC & 0xFF00) >> 8);
    uint8_t NewC = (BC & 0x00FF);

    bReg = NewB;
    cReg = NewC;
}
void Z8080::Opx13()
{
    cycles = 2;

    uint16_t DE = ((dReg << 8) | eReg);

    DE++;
    uint8_t NewD = ((DE & 0xFF00) >> 8);
    uint8_t NewE = (DE & 0x00FF);

    dReg = NewD;
    eReg = NewE;
}
void Z8080::Opx23()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    HL++;

    uint8_t NewH = ((HL & 0xFF00) >> 8);
    uint8_t NewL = (HL & 0x00FF);

    hReg = NewH;
    lReg = NewL;
}
void Z8080::Opx33()
{
    cycles = 2;
    sp++;
}
void Z8080::Opx0B()
{
    cycles = 2;

    uint16_t BC = ((bReg << 8) | cReg);

    BC--;

    uint8_t NewB = ((BC & 0xFF00) >> 8);
    uint8_t NewC = (BC & 0x00FF);

    bReg = NewB;
    cReg = NewC;
}
void Z8080::Opx1B()
{
    cycles = 2;

    uint16_t DE = ((dReg << 8) | eReg);

    DE--;

    uint8_t NewD = ((DE & 0xFF00) >> 8);
    uint8_t NewE = (DE & 0x00FF);

    dReg = NewD;
    eReg = NewE;
}
void Z8080::Opx2B()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    HL--;

    uint8_t NewH = ((HL & 0xFF00) >> 8);
    uint8_t NewL = (HL & 0x00FF);

    hReg = NewH;
    lReg = NewL;
}
void Z8080::Opx3B()
{
    cycles = 2;
    sp--;
}
void Z8080::Opx04()
{
    cycles = 1;

    SetFlag(H, (((bReg & 0x0F) + 0x01) & 0x10) == 0x10);

    bReg++;

    SetFlag(Z, bReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx0C()
{
    cycles = 1;

    SetFlag(H, (((cReg & 0xF) + 1) & 0x10) == 0x10);
    cReg++;

    SetFlag(Z, cReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx14()
{
    cycles = 1;
    SetFlag(H, (((dReg & 0xF) + 1) & 0x10) == 0x10);

    dReg++;

    SetFlag(Z, dReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx1C()
{
    cycles = 1;
    SetFlag(H, (((eReg & 0xF) + 1) & 0x10) == 0x10);

    eReg++;

    SetFlag(Z, eReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx24()
{
    cycles = 1;
    SetFlag(H, (((hReg & 0xF) + 1) & 0x10) == 0x10);

    hReg++;

    SetFlag(Z, hReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx2C()
{
    cycles = 1;
    SetFlag(H, (((lReg & 0xF) + 1) & 0x10) == 0x10);

    lReg++;

    SetFlag(Z, lReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx34()
{
    cycles = 3;

    uint16_t HL = ((hReg << 8) | lReg);

    uint8_t cHL = read(HL);
    SetFlag(H, (((cHL & 0xF) + 1) & 0x10) == 0x10);

    cHL++;
    write(HL, cHL);

    SetFlag(Z, cHL == 0);
    SetFlag(N, false);
}
void Z8080::Opx3C()
{
    cycles = 1;

    SetFlag(H, (((aReg & 0xF) + 1) & 0x10) == 0x10);
    aReg++;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx05()
{
    cycles = 1;

    SetFlag(H, (((bReg & 0xF0) - 1) & 0x08) == 0x08);

    bReg--;

    SetFlag(Z, bReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx0D()
{
    cycles = 1;
    SetFlag(H, (((cReg & 0xF0) - 1) & 0x08) == 0x08);

    cReg--;

    SetFlag(Z, cReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx15()
{
    cycles = 1;
    SetFlag(H, (((dReg & 0xF0) - 1) & 0x08) == 0x08);

    dReg--;

    SetFlag(Z, dReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx1D()
{
    cycles = 1;

    SetFlag(H, (((eReg & 0xF0) - 1) & 0x08) == 0x08);

    eReg--;

    SetFlag(Z, eReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx25()
{
    cycles = 1;
    SetFlag(H, (((dReg & 0xF0) - 1) & 0x08) == 0x08);

    hReg--;

    SetFlag(Z, hReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx2D()
{
    cycles = 1;
    SetFlag(H, (((lReg & 0xF0) - 1) & 0x08) == 0x08);

    lReg--;

    SetFlag(Z, lReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx35()
{
    cycles = 3;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t cHL = read(HL);

    SetFlag(H, (((cHL & 0xF0) - 1) & 0x08) == 0x08);

    cHL--;

    write(HL, cHL);

    SetFlag(Z, cHL == 0);
    SetFlag(N, true);
}
void Z8080::Opx3D()
{
    cycles = 1;

    SetFlag(H, (((aReg & 0xF0) - 1) & 0x08) == 0x08);
    aReg--;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx09()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint16_t BC = ((bReg << 8) | cReg);

    SetFlag(C, (HL += BC) > 0xFFFF);
    SetFlag(H, (((HL & 0x0FFF) + (BC & 0x0FFF)) & 0x1000) == 0x1000);

    HL += BC;
    hReg = ((HL & 0xFF00) >> 8);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
}
void Z8080::Opx19()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint16_t DE = ((dReg << 8) | eReg);

    SetFlag(C, (HL += DE) > 0xFFFF);
    SetFlag(H, (((HL & 0x0FFF) + (DE & 0x0FFF)) & 0x1000) == 0x1000);

    HL += DE;
    hReg = ((HL & 0xFF00) >> 8);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
}
void Z8080::Opx29()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);
    uint16_t HL2 = ((hReg << 8) | lReg);

    SetFlag(C, (HL += HL2) > 0xFFFF);
    SetFlag(H, (((HL & 0x0FFF) + (HL2 & 0x0FFF)) & 0x1000) == 0x1000);

    HL += HL2;
    hReg = ((HL & 0xFF00) >> 8);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
}
void Z8080::Opx39()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);

    SetFlag(C, (HL += sp) > 0xFFFF);
    SetFlag(H, (((HL & 0x0FFF) + (sp & 0x0FFF)) & 0x1000) == 0x1000);

    HL += sp;
    hReg = ((HL & 0xFF00) >> 8);
    lReg = (HL & 0x00FF);

    SetFlag(N, false);
}
void Z8080::Opx07()
{
    cycles = 1;

    SetFlag(C, (aReg & 0x80) == 0x80);

    aReg <<= 1;

    if (GetFlag(C))
    {
        aReg |= 0x01;
    }

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, false);
}
void Z8080::Opx17()
{
    cycles = 1;

    if (GetFlag(C))
    {
        SetFlag(C, (aReg & 0x80) == 0x80);
        aReg <<= 1;
        aReg |= 0x01;
    }
    else
    {
        SetFlag(C, (aReg & 0x80) == 0x80);
        aReg <<= 1;
    }

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, false);
}
void Z8080::Opx0F()
{
    cycles = 1;

    SetFlag(C, (aReg & 0x01) == 0x01);
    aReg >>= 1;

    if (GetFlag(C))
    {
        aReg |= 0x80;
    }

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, false);
}
void Z8080::Opx1F()
{
    cycles = 1;

    if (GetFlag(C))
    {
        SetFlag(C, (aReg & 0x01) == 0x01);
        aReg >>= 1;
        aReg |= 0x80;
    }
    else
    {
        SetFlag(C, (aReg & 0x01) == 0x01);
        aReg >>= 1;
    }

    aReg >>= 1;

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, false);
}
void Z8080::Opx37()
{
    cycles = 1;

    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, true);
}
void Z8080::Opx2F()
{
    cycles = 1;
    aReg = ~aReg;

    SetFlag(N, true);
    SetFlag(H, true);
}
void Z8080::Opx3F()
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
void Z8080::Opx80()
{
    cycles = 1;
    SetFlag(C, (aReg += bReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (bReg & 0xF)) & 0x10) == 0x10);

    aReg += bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx81()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF) + (cReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg += cReg) > 0xFF);

    aReg += cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx82()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF) + (dReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg += dReg) > 0xFF);

    aReg += dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx83()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF) + (eReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg += eReg) > 0xFF);

    aReg += eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx84()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF) + (hReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg += hReg) > 0xFF);

    aReg += hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx85()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF) + (lReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg += lReg) > 0xFF);

    aReg += lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx86()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(HL);

    SetFlag(H, (((aReg & 0xF) + (d8 & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg += d8) > 0xFF);

    aReg += d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx87()
{
    cycles = 1;
    SetFlag(C, (aReg += aReg) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (aReg & 0xF)) & 0x10) == 0x10);

    aReg += aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx88()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (bReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += bReg) + carryStatus) > 0xFF);

    aReg += bReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx89()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (cReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += cReg) + carryStatus) > 0xFF);

    aReg += cReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx8A()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (dReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += dReg) + carryStatus) > 0xFF);

    aReg += dReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx8B()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (eReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += eReg) + carryStatus) > 0xFF);

    aReg += eReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx8C()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (hReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += hReg) + carryStatus) > 0xFF);

    aReg += hReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx8D()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (lReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += lReg) + carryStatus) > 0xFF);

    aReg += lReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx8E()
{
    cycles = 2;

    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t carryStatus = GetFlag(C);
    uint8_t d8 = read(HL);

    SetFlag(H, ((((aReg & 0xF) + (d8 & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += d8) + carryStatus) > 0xFF);

    aReg += d8;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx8F()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(H, ((((aReg & 0xF) + (aReg & 0xF)) + carryStatus) & 0x10) == 0x10);
    SetFlag(C, ((aReg += aReg) + carryStatus) > 0xFF);

    aReg += aReg;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::Opx90()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF0) - (bReg & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= bReg) < 0x00);

    aReg -= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx91()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF0) - (cReg & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= cReg) < 0x00);

    aReg -= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx92()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF0) - (dReg & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= dReg) < 0x00);

    aReg -= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx93()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF0) - (eReg & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= eReg) < 0x00);

    aReg -= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx94()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF0) - (hReg & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= hReg) < 0x00);

    aReg -= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx95()
{
    cycles = 1;
    SetFlag(H, (((aReg & 0xF0) - (lReg & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= lReg) < 0x00);

    aReg -= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx96()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(HL);

    SetFlag(H, (((aReg & 0xF0) - (d8 & 0xF0)) & 0x08) == 0x08);
    SetFlag(C, (aReg -= d8) < 0x00);

    aReg -= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx97()
{
    cycles = 1;
    uint8_t comp = (((aReg & 0xF0) - (aReg & 0xF0)) & 0x08);

    SetFlag(H, comp == 0x08);
    SetFlag(C, (aReg -= aReg) < 0x00);
    aReg -= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx98()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= bReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (bReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= bReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx99()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= cReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (cReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= cReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx9A()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= dReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (dReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= dReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx9B()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= eReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (eReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= eReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx9C()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= hReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (hReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= hReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx9D()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= lReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (lReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= lReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx9E()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t carryStatus = GetFlag(C);
    uint8_t d8 = read(HL);

    SetFlag(C, ((aReg -= d8) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (d8 & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= d8;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::Opx9F()
{
    cycles = 1;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg -= aReg) - carryStatus) < 0x00);
    SetFlag(H, ((((aReg & 0xF0) - (aReg & 0xF0)) - carryStatus) & 0x08) == 0x08);

    aReg -= aReg;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::OpxA0()
{
    cycles = 1;
    aReg &= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA1()
{
    cycles = 1;
    aReg &= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA2()
{
    cycles = 1;
    aReg &= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA3()
{
    cycles = 1;
    aReg &= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA4()
{
    cycles = 1;
    aReg &= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA5()
{
    cycles = 1;
    aReg &= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA6()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(HL);

    aReg &= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA7()
{
    cycles = 1;
    aReg &= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxA8()
{
    cycles = 1;
    aReg ^= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxA9()
{
    cycles = 1;
    aReg ^= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxAA()
{
    cycles = 1;
    aReg ^= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxAB()
{
    cycles = 1;
    aReg ^= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxAC()
{
    cycles = 1;
    aReg ^= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxAD()
{
    cycles = 1;
    aReg ^= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxAE()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t cHL = read(HL);

    aReg ^= cHL;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxAF()
{
    cycles = 1;
    aReg ^= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB0()
{
    cycles = 1;
    aReg |= bReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB1()
{
    cycles = 1;
    aReg |= cReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB2()
{
    cycles = 1;
    aReg |= dReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB3()
{
    cycles = 1;
    aReg |= eReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB4()
{
    cycles = 1;
    aReg |= hReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB5()
{
    cycles = 1;
    aReg |= lReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB6()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(HL);

    aReg |= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB7()
{
    cycles = 1;
    aReg |= aReg;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxB8()
{
    cycles = 1;
    SetFlag(Z, (aReg - bReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (bReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - bReg) < 0x00);
}
void Z8080::OpxB9()
{
    cycles = 1;
    SetFlag(Z, (aReg - cReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (cReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - cReg) < 0x00);
}
void Z8080::OpxBA()
{
    cycles = 1;
    SetFlag(Z, (aReg - dReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (dReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - dReg) < 0x00);
}
void Z8080::OpxBB()
{
    cycles = 1;
    SetFlag(Z, (aReg - eReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (eReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - eReg) < 0x00);
}
void Z8080::OpxBC()
{
    cycles = 1;
    SetFlag(Z, (aReg - hReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (hReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - hReg) < 0x00);
}
void Z8080::OpxBD()
{
    cycles = 1;
    SetFlag(Z, (aReg - lReg) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (lReg & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - lReg) < 0x00);
}
void Z8080::OpxBE()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);
    uint8_t d8 = read(HL);

    SetFlag(Z, (aReg - d8) == 0);
    SetFlag(N, true);
    SetFlag(H, (((aReg & 0xF) - (d8 & 0xF)) & 0x10) == 0x10);
    SetFlag(C, (aReg - d8) < 0x00);
}
void Z8080::OpxBF()
{
    cycles = 1;

    uint8_t hcompare = (((aReg & 0xF) - (aReg & 0xF)) & 0x10);

    SetFlag(Z, (aReg - aReg) == 0);
    SetFlag(N, true);
    SetFlag(H, hcompare == 0x10);
    SetFlag(C, (aReg - aReg) < 0x00);
}
void Z8080::OpxC6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;

    SetFlag(C, (aReg + d8) > 0xFF);
    SetFlag(H, (((aReg & 0xF) + (d8 & 0xF)) & 0x10) == 0x10);

    aReg += d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::OpxD6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;

    SetFlag(C, (aReg - d8) < 0x00);
    SetFlag(H, (((aReg & 0xF) - (d8 & 0xF)) & 0x10) == 0x10);

    aReg -= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::OpxE6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;

    aReg &= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, true);
    SetFlag(C, false);
}
void Z8080::OpxF6()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;

    aReg |= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxCE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg + d8) + carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) + (d8 & 0xF)) + carryStatus) & 0x10) == 0x10);

    aReg += d8;
    aReg += carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
}
void Z8080::OpxDE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;
    uint8_t carryStatus = GetFlag(C);

    SetFlag(C, ((aReg - d8) - carryStatus) > 0xFF);
    SetFlag(H, ((((aReg & 0xF) - (d8 & 0xF)) - carryStatus) & 0x10) == 0x10);

    aReg -= d8;
    aReg -= carryStatus;

    SetFlag(Z, aReg == 0);
    SetFlag(N, true);
}
void Z8080::OpxEE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;

    aReg ^= d8;

    SetFlag(Z, aReg == 0);
    SetFlag(N, false);
    SetFlag(H, false);
    SetFlag(C, false);
}
void Z8080::OpxFE()
{
    cycles = 2;
    uint8_t d8 = read(pc);
    pc++;

    SetFlag(Z, (aReg - d8) == 0);
    SetFlag(H, (((aReg & 0xF) - (d8 & 0xF)) & 0x10) == 0x10);
    SetFlag(N, true);
    SetFlag(C, (aReg - d8) < 0x00);
}
void Z8080::OpxE8()
{
    cycles = 4;

    int8_t r8 = read(pc);
    pc++;

    r8 = (~r8 + 1);

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(H, (((sp & 0x0FFF) + r8) & 0x1000) == 0x1000);
    SetFlag(C, (sp + r8) > 0xFFFF);

    sp += r8;
}
void Z8080::OpxF8()
{
    cycles = 3;
    uint16_t HL = ((hReg << 8) | lReg);

    int8_t r8 = read(pc);
    pc++;

    SetFlag(Z, false);
    SetFlag(N, false);
    SetFlag(C, (sp + r8) > 0xFFFF);
    SetFlag(H, (((sp & 0x0FFF) + r8) & 0x1000) == 0x1000);

    HL = sp + r8;

    hReg = ((HL & 0xFF00) >> 8);
    lReg = (HL & 0x00FF);
}
void Z8080::OpxF9()
{
    cycles = 2;
    uint16_t HL = ((hReg << 8) | lReg);

    sp = HL;
}
void Z8080::Opx20()
{
    cycles = 2;
    int8_t r8 = read(pc);
    pc++;

    if (GetFlag(Z) == 0)
    {
        pc += r8;
        cycles = 3;
    }
}
void Z8080::Opx30()
{
    cycles = 2;
    int8_t r8 = read(pc);
    pc++;

    if (GetFlag(C) == 0)
    {
        pc += r8;
        cycles = 3;
    }
}
void Z8080::Opx18()
{
    cycles = 3;
    int8_t r8 = read(pc);
    pc++;

    pc += r8;
}
void Z8080::Opx28()
{
    cycles = 2;
    int8_t r8 = read(pc);
    pc++;

    if (GetFlag(Z) == 1)
    {
        pc += r8;
        cycles = 3;
    }
}
void Z8080::Opx38()
{
    cycles = 2;
    int8_t r8 = read(pc);
    pc++;

    if (GetFlag(C) == 1)
    {
        pc += r8;
        cycles = 3;
    }
}

// LD (a16), SP
void Z8080::Opx08()
{
    cycles = 5;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    uint16_t a16 = ((hi << 8) | lo);
    uint8_t splo = (sp & 0x00FF);
    uint8_t sphi = ((sp & 0xFF00) >> 8);

    write(a16, splo);
    write((a16 + 1), sphi);
}
void Z8080::OpxFA()
{
    cycles = 4;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    uint16_t a16 = ((hi << 8) | lo);

    aReg = bus->read(a16);
}
void Z8080::OpxEA()
{
    cycles = 4;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    uint16_t a16 = ((hi << 8) | lo);

    write(a16, aReg);
}
void Z8080::OpxE0()
{
    cycles = 3;
    uint8_t d8 = read(pc);
    pc++;
    uint16_t a8 = (0xFF00 | d8);
    write(a8, aReg);
}
void Z8080::OpxF0()
{
    cycles = 3;
    uint8_t d8 = read(pc);
    pc++;
    uint16_t a16 = (0xFF00 | d8);
    aReg = bus->read(a16);
}
void Z8080::OpxE2()
{
    cycles = 2;

    uint16_t a8 = (0xFF00 | cReg);
    write(a8, aReg);
}
void Z8080::OpxF2()
{
    cycles = 2;

    uint16_t a8 = (0xFF00 | cReg);
    aReg = read(a8);
}
// PUSH BC
void Z8080::OpxC5()
{
    cycles = 4;

    write(sp, bReg);
    sp--;
    write(sp, cReg);
    sp--;
}
void Z8080::OpxD5()
{
    cycles = 4;

    write(sp, dReg);
    sp--;
    write(sp, eReg);
    sp--;
}
void Z8080::OpxE5()
{
    cycles = 4;

    write(sp, hReg);
    sp--;
    write(sp, lReg);
    sp--;
}
void Z8080::OpxF5()
{
    cycles = 4;

    write(sp, aReg);
    sp--;
    write(sp, fReg);
    sp--;
}
void Z8080::OpxC1()
{
    cycles = 3;

    sp++;
    cReg = read(sp);
    sp++;
    bReg = read(sp);
}
void Z8080::OpxD1()
{
    cycles = 3;

    sp++;
    eReg = read(sp);
    sp++;
    dReg = read(sp);
}
void Z8080::OpxE1()
{
    cycles = 3;

    sp++;
    lReg = read(sp);
    sp++;
    hReg = read(sp);
}
void Z8080::OpxF1()
{
    cycles = 3;

    sp++;
    fReg = read(sp);
    sp++;
    aReg = read(sp);
}
void Z8080::OpxF3() // Disable interrupts
{
    cycles = 1;

    bus->m_IMEFlag = false;
}
void Z8080::OpxFB() // Enable interrupts
{
    cycles = 1;

    bus->m_IMEFlag = true;
}
void Z8080::Opx27()
{
    cycles = 1;

    if (!GetFlag(N))
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

    if (GetFlag(N))
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
void Z8080::OpxC7()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0000;
}
void Z8080::OpxCF()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0008;
}
void Z8080::OpxD7()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0010;
}
void Z8080::OpxDF()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0018;
}
void Z8080::OpxE7()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0020;
}
void Z8080::OpxEF()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0028;
}
void Z8080::OpxF7()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = ((pc & 0xFF00) >> 8);

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0030;
}
void Z8080::OpxFF()
{
    cycles = 4;

    uint8_t lo = (pc & 0x00FF);
    uint8_t hi = (pc & 0xFF00) >> 8;

    write(sp, hi);
    --sp;
    write(sp, lo);
    --sp;

    pc = 0x0038;
}
void Z8080::OpxC8()
{
    cycles = 2;

    if (GetFlag(Z))
    {
        cycles = 5;

        sp++;
        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);

        pc = 0;
        pc |= (hi << 8);
        pc |= lo;
    }
}
void Z8080::OpxD8()
{
    cycles = 2;

    if (GetFlag(C) == 1)
    {
        cycles = 5;

        sp++;
        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);

        pc = 0;
        pc |= (hi << 8);
        pc |= lo;
    }
}
void Z8080::OpxC9()
{
    cycles = 4;

    sp++;
    uint8_t lo = read(sp);
    sp++;
    uint8_t hi = read(sp);

    pc = 0;
    pc |= (hi << 8);
    pc |= lo;
}
void Z8080::OpxD9()
{
    cycles = 4;

    sp++;
    uint8_t lo = read(sp);
    sp++;
    uint8_t hi = read(sp);

    pc = 0;
    pc |= (hi << 8);
    pc |= lo;

    bus->m_IMEFlag = !bus->m_IMEFlag;
}
void Z8080::OpxE9()
{
    cycles = 1;

    uint16_t HL = ((hReg << 8) | lReg);

    pc = HL;
}
void Z8080::OpxC0()
{
    cycles = 2;

    if (!GetFlag(Z))
    {
        cycles = 5;

        sp++;
        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);

        pc = 0;
        pc |= (hi << 8);
        pc |= lo;
    }
}
void Z8080::OpxD0()
{
    cycles = 2;

    if (!GetFlag(C))
    {
        cycles = 5;

        sp++;
        uint8_t lo = read(sp);
        sp++;
        uint8_t hi = read(sp);

        pc = 0;
        pc |= (hi << 8);
        pc |= lo;
    }
}
void Z8080::OpxC3()
{
    cycles = 4;

    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    uint16_t a16 = ((hi << 8) | lo);

    pc = a16;
}
void Z8080::OpxC2()
{
    cycles = 3;

    if (!GetFlag(Z))
    {
        cycles = 4;

        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);
        pc++;

        uint16_t a16 = ((hi << 8) | lo);

        pc = a16;
    }
    else
    {
        pc++;
    }
}
void Z8080::OpxD2()
{
    cycles = 3;

    if (!GetFlag(C))
    {
        cycles = 4;

        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);
        pc++;

        uint16_t a16 = ((hi << 8) | lo);

        pc = a16;
    }
    else
    {
        pc++;
    }
}
void Z8080::OpxCA()
{
    cycles = 3;

    if (GetFlag(Z))
    {
        cycles = 4;

        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);
        pc++;

        uint16_t a16 = ((hi << 8) | lo);

        pc = a16;
    }
    else
    {
        pc++;
    }
}
void Z8080::OpxDA()
{
    cycles = 3;

    if (GetFlag(C))
    {
        cycles = 4;

        uint8_t lo = read(pc);
        pc++;
        uint8_t hi = read(pc);
        pc++;

        uint16_t a16 = ((hi << 8) | lo);

        pc = a16;
    }
    else
    {
        pc++;
    }
}
void Z8080::OpxCD()
{
    cycles = 6;

    uint8_t lo;
    uint8_t hi;

    lo = read(pc);
    pc++;
    hi = read(pc);
    pc++;

    uint8_t pclo = (pc & 0x00FF);
    uint8_t pchi = ((pc & 0xFF00) >> 8);

    write(sp, pchi);
    --sp;
    write(sp, pclo);
    --sp;

    uint16_t a16 = ((hi << 8) | lo);
    pc = a16;
}
void Z8080::OpxCC()
{
    cycles = 3;

    if (GetFlag(Z))
    {
        cycles = 6;

        uint8_t lo;
        uint8_t hi;

        lo = read(pc);
        pc++;
        hi = read(pc);
        pc++;

        uint8_t pclo = (pc & 0x00FF);
        uint8_t pchi = ((pc & 0xFF00) >> 8);

        write(sp, pchi);
        --sp;
        write(sp, pclo);
        --sp;

        uint16_t a16 = ((hi << 8) | lo);
        pc = a16;
    }
}
void Z8080::OpxDC()
{
    cycles = 3;

    if (GetFlag(C))
    {
        cycles = 6;

        uint8_t lo;
        uint8_t hi;

        lo = read(pc);
        pc++;
        hi = read(pc);
        pc++;

        uint8_t pclo = (pc & 0x00FF);
        uint8_t pchi = ((pc & 0xFF00) >> 8);

        write(sp, pchi);
        --sp;
        write(sp, pclo);
        --sp;

        uint16_t a16 = ((hi << 8) | lo);
        pc = a16;
    }
}
void Z8080::OpxC4()
{
    cycles = 3;

    if (!GetFlag(Z))
    {
        cycles = 6;

        uint8_t lo;
        uint8_t hi;

        lo = read(pc);
        pc++;
        hi = read(pc);
        pc++;

        uint8_t pclo = (pc & 0x00FF);
        uint8_t pchi = ((pc & 0xFF00) >> 8);

        write(sp, pchi);
        --sp;
        write(sp, pclo);
        --sp;

        uint16_t a16 = ((hi << 8) | lo);
        pc = a16;
    }
}
void Z8080::OpxD4()
{
    cycles = 3;

    if (!GetFlag(C))
    {
        cycles = 6;

        uint8_t lo = (pc & 0x00FF);
        uint8_t hi = ((pc & 0xFF00) >> 8);

        write(sp, hi);
        --sp;
        write(sp, lo);
        --sp;

        lo = read(pc);
        pc++;
        hi = read(pc);
        pc++;

        uint16_t a16 = ((hi << 8) | lo);
        pc = a16;
    }
}
void Z8080::Opx00()
{
    cycles = 1;
    // Do nothing
}
void Z8080::Opx76() // Halt
{
    
    cycles = 1;
    halted = true;
    
}