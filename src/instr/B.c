#include <assert.h>
#include "B.h"
#include "machine.h"

extern machine_t guest;

// TODO understand at a later point
void decode_B(instr_t * const insn) {
    int32_t instr = insn->insnbits;

    int64_t imm26 = GETBF(instr, 0, 26) << 2;
    insn-> imm = imm26;
    return;
}

void execute_B(instr_t * const insn) {
    insn->branch_PC = guest.proc->PC.bits->xval + insn->imm;
    return;
}