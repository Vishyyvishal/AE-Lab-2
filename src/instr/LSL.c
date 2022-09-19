#include <assert.h>
#include "LSL.h"
#include "machine.h"

extern machine_t guest;

void decode_LSL(instr_t * const insn) {
    return;
}

void execute_LSL(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval << (insn->shift);
    return;
}