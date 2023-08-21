#include "reu.h"

volatile uint8_t* REU_STATUS=(void*)0xdf00;
volatile uint8_t* REU_CMD=(void*)0xdf01;
volatile uint16_t* REU_C64ADR=(void*)0xdf02;
volatile uint16_t* REU_ADDRLO=(void*)0xdf04;
volatile uint8_t* REU_ADDRHI=(void*)0xdf06;
volatile uint16_t* REU_XFERLEN=(void*)0xdf07;

uint32_t loadword_reu(uint32_t addr) {
    volatile uint32_t value;
    //*REU_CMD = 0x0;
    *REU_C64ADR = (uint16_t)(&value);
    *REU_ADDRLO = addr & 0xffff;
    *REU_ADDRHI = addr >> 16;
    *REU_XFERLEN = 4;
    *REU_CMD = 0b10010001;
    return value;
}

void saveword_reu(uint32_t addr, volatile uint32_t value) {
    //*REU_CMD = 0x0;
    *REU_C64ADR = (uint16_t)(&value);
    *REU_ADDRLO = addr & 0xffff;
    *REU_ADDRHI = addr >> 16;
    *REU_XFERLEN = 4;
    *REU_CMD = 0b10010000;
}
