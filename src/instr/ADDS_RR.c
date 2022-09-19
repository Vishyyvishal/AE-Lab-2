#include <assert.h>
#include "ADDS_RR.h"
#include "machine.h"

extern machine_t guest;

void decode_ADDS_RR(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    // assert(EXTRACT(instr, 0xFF000000, 24) == 0x122U); as TA if

    uint8_t d = GETBF(instr, 0, 5);
    uint8_t n = GETBF(instr, 5, 5);
    uint8_t m = GETBF(instr, 16, 5);
    // uint8_t sh = EXTRACT(instr, 400000U, 22);

    // insn->op = is_aliased ? OP_MOV : OP_ADD;
    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + d);
    insn->src1 = (n == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + n);
    insn->src2 = (m == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + m);

    insn->opnd1.xval = insn->src1->bits->xval;
    insn->opnd2.xval = insn->src2->bits->xval;
    return;
}

void execute_ADDS_RR(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    int64_t sum = insn->opnd1.xval + insn->opnd2.xval;

    //TODO PACK_CC. WHAT IS THIS??
    bool negativeFlag = (sum < 0) ? 1 : 0;
    bool zeroFlag =  (sum < 0) ? 1 : 0;
    bool signedFlag = ((insn->opnd1.xval) > 0 && (insn->opnd2.xval) > 0 && sum < 0) | ((insn->opnd1.xval < 0 && insn->opnd2.xval < 0) && sum > 0) ? 1 : 0;
    bool unsignedFlag = ((sum < insn->opnd1.xval) | sum < insn->opnd2.xval) ? 1 : 0;
    guest.proc->NZCV.bits->ccval == PACK_CC(negativeFlag, zeroFlag, unsignedFlag, signedFlag);
    return;
}