#include <assert.h>
#include "UBFM.h"
#include "machine.h"

extern machine_t guest;

void decode_UBFM(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    // assert(EXTRACT(instr, 0xFF800000, 23) == 0x122U);
    uint8_t d = GETBF(instr, 0, 5);
    uint8_t n = GETBF(instr, 5, 5);

    uint16_t imms = GETBF(instr, 10, 6);
    uint16_t immr = GETBF(instr, 16, 6);

    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + d);
    insn->src1 = (n == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + n);
    
    if((imms + 1) == immr) {
        insn->op = OP_LSL;
        insn->shift = (64 - immr);
    } else {
        insn->op = OP_LSR;
        insn->shift = immr;
    }
    insn->opnd1.xval = insn->src1->bits->xval;
    return;
}

void execute_UBFM(instr_t * const insn) {
    return;
}
