#include <assert.h>
#include "MOVK.h"
#include "machine.h"

extern machine_t guest;

void decode_MOVK(instr_t * const insn) {
    int32_t instr = insn->insnbits;

    uint8_t d = GETBF(instr, 0, 5);
    uint16_t hw = GETBF(instr, 21, 2);
    uint64_t imm16 = GETBF(instr, 5, 16);

    insn->op = OP_MOVK;

    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + d);

    // TODO opnd1 = insn->dst->bits->xval
    // TODO opnd2 = imm16 << hw * 16
    insn->opnd1.xval = insn->dst->bits->xval;
    
    insn->imm = imm16;

    if(hw == 0) {
        insn->opnd2.xval = imm16;
    } else if (hw == 1) {
        insn->opnd2.xval = imm16 << 16;
    } else if(hw == 2) {
        insn->opnd2.xval = imm16 << 32;
    } else if(hw == 3) {
        insn->opnd2.xval = imm16 << 48;
    }

    uint64_t mask;
    uint64_t result = insn->opnd1.xval;
    if(hw == 0) {
        mask = 0xFFFFFFFFFFFF0000;
    } else if (hw == 1) {
        mask = 0xFFFFFFFF0000FFFF;
    } else if(hw == 2) {
        mask = 0xFFFF0000FFFFFFFF;
    } else if(hw == 3) {
        mask = 0x0000FFFFFFFFFFFF;
    }

    result = result & mask;
    insn->opnd1.xval = result;


    return;
}

void execute_MOVK(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    return;
}