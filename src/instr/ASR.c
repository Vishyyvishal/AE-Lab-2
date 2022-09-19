#include <assert.h>
#include "ASR.h"
#include "machine.h"

extern machine_t guest;

void decode_ASR(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    int8_t d = GETBF(instr, 0, 5);
    int8_t n = GETBF(instr, 5, 5);

    uint16_t imms = GETBF(instr, 10, 6);
    uint16_t immr = GETBF(instr, 16, 6);

    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + d);
    insn->src1 = (n == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + n);

    insn->opnd1.xval = insn->src1->bits->xval;
    insn->shift = immr;
    return;
}

void execute_ASR(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval >> (insn->shift);
    return;
}