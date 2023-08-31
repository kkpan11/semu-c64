#if !C64
#include <assert.h>
#endif
#include "device.h"
#include "persistence.h"

void save_cpu(const vm_t *vm,
                 uint8_t **obufp) {
    for (int i=0; i<32; i++) SER32(vm->x_regs[i]);
    SER32(vm->lr_reservation);
    SER32(vm->pc);
    SER32(vm->current_pc);
    SER32(vm->insn_count);
    SER32(vm->insn_count_hi);
#if !C64
    assert(vm->error <=255);
#endif
    SER8(vm->error);
    SER32(vm->exc_cause);
    SER32(vm->exc_val);
    SER8(vm->s_mode);
    SER8(vm->sstatus_spp);
    SER8(vm->sstatus_spie);

    SER32(vm->sepc);
    SER32(vm->scause);
    SER32(vm->stval);

    SER8(vm->sstatus_mxr);
    SER8(vm->sstatus_sum);
    SER8(vm->sstatus_sie);

    SER32(vm->sie);
    SER32(vm->sip);
    SER32(vm->stvec_addr);

    SER8(vm->stvec_vectored);

    SER32(vm->sscratch);
    SER32(vm->scounteren);
    SER32(vm->satp);
    SER32(vm->page_table_addr);
}

static void save_timers(const vm_t *vm, uint8_t **obufp) {
    const emu_state_t *data = (const emu_state_t *) vm->priv;
    SER32(data->timer_lo);
    SER32(data->timer_hi);
}

void save_all(const vm_t *vm, uint8_t **obufp) {
    uint32_t version=1, marker;
    SER32(version);
    marker='M';
    SER8(marker); // machine
    save_cpu(vm, obufp);

    marker='I';
    SER8(marker); // interrupt controller
    save_plic(vm, obufp);
    marker='U';
    SER8(marker); // UART
    save_uart(vm, obufp);
    marker='T';
    SER8(marker);
    save_timers(vm, obufp);
    // FIXME: save network/blockdev devices if they are enabled
}

void load_cpu(vm_t *vm,
                 uint8_t **ibufp) {
    for (int i=0; i<32; i++) DESER32(vm->x_regs[i]);
    DESER32(vm->lr_reservation);
    DESER32(vm->pc);
    DESER32(vm->current_pc);
    DESER32(vm->insn_count);
    DESER32(vm->insn_count_hi);
    DESER8(vm->error);
    DESER32(vm->exc_cause);
    DESER32(vm->exc_val);
    DESER8(vm->s_mode);
    DESER8(vm->sstatus_spp);
    DESER8(vm->sstatus_spie);

    DESER32(vm->sepc);
    DESER32(vm->scause);
    DESER32(vm->stval);

    DESER8(vm->sstatus_mxr);
    DESER8(vm->sstatus_sum);
    DESER8(vm->sstatus_sie);

    DESER32(vm->sie);
    DESER32(vm->sip);
    DESER32(vm->stvec_addr);

    DESER8(vm->stvec_vectored);
    DESER32(vm->sscratch);
    DESER32(vm->scounteren);
    DESER32(vm->satp);
    DESER32(vm->page_table_addr);
}


static void load_timers(vm_t *vm, uint8_t **ibufp) {
    emu_state_t *data = (emu_state_t *) vm->priv;
    DESER32(data->timer_lo);
    DESER32(data->timer_hi);
}

bool load_all(vm_t *vm, uint8_t **ibufp) {
    uint32_t version, marker;
    DESER32(version); // version field
    if (version != 1) return false;
    DESER8(marker);
    if (marker != 'M') return false;
    load_cpu(vm, ibufp);
    DESER8(marker);
    if (marker != 'I') return false;
    load_plic(vm, ibufp);
    DESER8(marker);
    if (marker != 'U') return false;
    load_uart(vm, ibufp);
    DESER8(marker);
    if (marker != 'T') return false;
    load_timers(vm, ibufp);
    // FIXME: load network/blockdev devices if they are enabled
    return true;
}
