#include <assert.h>
#include "BL.h"
#include "machine.h"

extern machine_t guest;

// TODO understand at a later point
void decode_BL(instr_t * const insn) {
    int32_t instr = insn->insnbits;

    int64_t imm26 = GETBF(instr, 0, 26) << 2;
    insn-> imm = imm26;

    return;
}

void execute_BL(instr_t * const insn) {
    guest.proc->GPR.names64[30].bits->xval = guest.proc->PC.bits->xval + 4;
    insn->branch_PC = guest.proc->PC.bits->xval + insn->imm;
    return;
}