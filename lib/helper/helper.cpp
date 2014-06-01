#include "helper.h"

ConstantInt* helper::foldBinaryOperator(unsigned Opcode,ConstantInt *C1, ConstantInt *C2){
  LLVMContext &context = C1->getContext();
  const APInt &c1_value = C1->getValue();
  const APInt &c2_value = C2->getValue();
  const APInt &result_value = APInt::getNullValue(32);
  ConstantInt* result = ConstantInt::get(context, result_value);
  switch (Opcode) {
    case Instruction::Xor:
      result_value = c1_value.Xor(c2_value);
    case Instruction::Add:
      result_value = c1_value + c2_value;
    case Instruction::Sub:
      result_value = c1_value - c2_value;
    case Instruction::Mul:
      result_value = c1_value * c2_value;
    case Instruction::Udiv:
      result_value = c1_value.udiv(c2_value);
    case Instruction::Sdiv:
      result_value = c1_value.sdiv(c2_value);
    case Instruction::URem:
      result_value = c1_value.urem(c2_value);
    case Instruction::SRem:
      result_value = c1_value.srem(c2_value);
    case Instruction::Or:
      result_value = c1_value.Or(c2_value);
    case Instruction::And:
      result_value = c1_value.And(c2_value);
    case Instruction::LShr:
      result_value = c1_value.lshr(c2_value);
    case Instruction::AShr:
      result_value = c1_value.ashr(c2_value);
    case Instruction::Shl:
      result_value = c1_value.shl(c2_value);
  }
  return ConstantInt::get(context, result_value);
}

