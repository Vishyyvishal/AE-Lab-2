#include <assert.h>
#include <stdlib.h>
#include "err_handler.h"
#include "STUR.h"
#include "machine.h"

extern machine_t guest;

// TODO check if it's right
void decode_STUR(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    unsigned opcode = GETBF(instr, 21, 11);
    // assert(0x1C0U == opcode);

    int imm9 = GETBF(instr, 12, 9);
    int64_t offset = imm9; // Check
    int n = GETBF(instr, 5, 5);
    int t = GETBF(instr, 0, 5);
    insn->op = OP_STUR;
    insn->src1 = n == 31 ? &(guest.proc->SP) : guest.proc->GPR.names64 + n;
    insn->src2 = t == 31 ? &(guest.proc->SP) : guest.proc->GPR.names64 + t;
    insn->imm = offset;
    insn->opnd1.xval = insn->src1->bits->xval;
    insn->opnd2.xval = insn->imm;
    // if (31 == n) {
    //     if (0 != insn->opnd1.xval) {
    //         logging(LOG_FATAL, "Stack pointer misaligned");
    //         exit(EXIT_FAILURE);
    //     }
    // }
    return;
}

void execute_STUR(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    insn->val_mem.xval = insn->src2->bits->xval;
    return;
}
