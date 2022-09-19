#include <assert.h>
#include "SUBS_RR.h"
#include "machine.h"

extern machine_t guest;

void decode_SUBS_RR(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    //assert(EXTRACT(instr, 0xFF000000, 24) == 0x122U);

    uint8_t Rd = GETBF(instr, 0, 5);
    uint8_t Rn = GETBF(instr, 5, 5);
    uint16_t Rm = GETBF(instr, 16, 5);
    // uint8_t sh = EXTRACT(instr, 400000U, 22);

    // insn->op = is_aliased ? OP_MOV : OP_ADD;
    insn->dst = (Rd == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + Rd);
    insn->src1 = (Rn == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + Rn);
    insn->src2 = (Rm == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + Rm);

    insn->opnd1.xval = insn->src1->bits->xval;
    insn->opnd2.xval = insn->src2->bits->xval;
    return;
}

void execute_SUBS_RR(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval - insn->opnd2.xval;

    // TODO condition flags 
    return;
}