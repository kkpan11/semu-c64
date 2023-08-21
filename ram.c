#include "riscv.h"
#include "riscv_private.h"
#if C64
#include "reu.h"
#endif

/* RAM handlers (address must be relative, assumes it is within bounds) */
#if C64
#define RAM_FUNC(width, code, write)                      \
    do {                                                  \
        if (unlikely((addr & (width - 1)))) {             \
            vm_set_exception(vm, exc_cause, vm->exc_val); \
            break;                                        \
        }                                                 \
        UNUSED uint8_t offset = (addr & 0b11) * 8;        \
        uint32_t addr4 = addr & 0xfffffffc;               \
        uint32_t v;                                       \
        uint32_t *cell = &v;                              \
        v=loadword_reu(addr4);                            \
        code;                                             \
        if (write) saveword_reu(addr4, v);                \
    } while (0)
#else
#define RAM_FUNC(width, code, write)                      \
    do {                                                  \
        if (unlikely((addr & (width - 1)))) {             \
            vm_set_exception(vm, exc_cause, vm->exc_val); \
            break;                                        \
        }                                                 \
        UNUSED uint8_t offset = (addr & 0b11) * 8;        \
        uint32_t *cell = &mem[addr >> 2];                 \
        code;                                             \
    } while (0)
#endif

void ram_read(vm_t *vm,
              uint32_t *mem,
              const uint32_t addr,
              const uint8_t width,
              uint32_t *value)
{
    const uint32_t exc_cause = RV_EXC_LOAD_MISALIGN;
    switch (width) {
    case RV_MEM_LW:
        RAM_FUNC(4, *value = *cell, false);
        break;
    case RV_MEM_LHU:
        RAM_FUNC(2, *value = (uint32_t) (uint16_t) ((*cell) >> offset), false);
        break;
    case RV_MEM_LH:
        RAM_FUNC(2,
                 *value = (uint32_t) (int32_t) (int16_t) ((*cell) >> offset), false);
        break;
    case RV_MEM_LBU:
        RAM_FUNC(1, *value = (uint32_t) (uint8_t) ((*cell) >> offset), false);
        break;
    case RV_MEM_LB:
        RAM_FUNC(1, *value = (uint32_t) (int32_t) (int8_t) ((*cell) >> offset), false);
        break;
    default:
        vm_set_exception(vm, RV_EXC_ILLEGAL_INSTR, 0);
        return;
    }
}

void ram_write(vm_t *vm,
               uint32_t *mem,
               const uint32_t addr,
               const uint8_t width,
               const uint32_t value)
{
    const uint32_t exc_cause = RV_EXC_STORE_MISALIGN;
    switch (width) {
    case RV_MEM_SW:
        RAM_FUNC(4, *cell = value, true);
        break;
    case RV_MEM_SH:
        RAM_FUNC(2, *cell = ((*cell) & ~(MASK(16) << offset)) |
                 (value & MASK(16)) << offset, true);
        break;
    case RV_MEM_SB:
        RAM_FUNC(1, *cell = ((*cell) & ~(MASK(8) << offset)) | (value & MASK(8))
                 << offset, true);
        break;
    default:
        vm_set_exception(vm, RV_EXC_ILLEGAL_INSTR, 0);
        return;
    }
}
