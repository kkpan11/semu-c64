#pragma once
#include <stdint.h>

uint32_t loadword_reu(uint32_t addr);
void saveword_reu(uint32_t addr, uint32_t value);

void load_from_reu(void* dest, uint32_t reu_addr, uint16_t len);
void save_to_reu(uint32_t reu_addr, void* src, uint16_t len);
