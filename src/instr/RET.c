#include <assert.h>
#include "RET.h"
#include "machine.h"

extern machine_t guest;

void decode_RET(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    int8_t n = GETBF(instr, 5, 5);
    insn->src1 = (n == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + n);
    return;
}

void execute_RET(instr_t * const insn) {
    insn->branch_PC = insn->src1->bits->xval;
    return;
}