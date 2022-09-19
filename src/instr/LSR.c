#include <assert.h>
#include "LSR.h"
#include "machine.h"

extern machine_t guest;

void decode_LSR(instr_t * const insn) {
    return;
}

void execute_LSR(instr_t * const insn) {
    insn->val_ex.xval = (unsigned long) insn->opnd1.xval >> (insn->shift);
    return;
}