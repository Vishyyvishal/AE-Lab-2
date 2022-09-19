#include <assert.h>
#include "B_COND.h"
#include "machine.h"

extern machine_t guest;

// TODO understand at a later point
void decode_B_COND(instr_t * const insn) {
    int32_t instr = insn->insnbits;

    uint64_t cond = GETBF(instr, 0, 4);

    uint64_t imm19 = GETBF(instr, 5, 19) << 2;
    insn-> imm = imm19;

    uint8_t cc = guest.proc->NZCV.bits->xval;

    if(cond == 0) {
        insn->cond_holds = (GET_ZF(cc) == 1);
    }


    return;
}

void execute_B_COND(instr_t * const insn) {
    insn->branch_PC = guest.proc->PC.bits->xval + insn->imm;
    return;
}