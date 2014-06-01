#include "helper.h"

static ConstantInt* helper::foldBinaryOperator(unsigned Opcode,ConstantInt *C1, ConstantInt *C2){
  LLVMContext &context = C1->getContext();
  const APInt &c1_value = C1->getValue();
  const APInt &c2_value = C2->getValue();
  ConstantInt* result = ConstantInt::get(context, APInt::getNullValue(32));
  switch (Opcode) {
    case Instruction::Xor:
      result = ConstantInt::get(context, c1_value.Xor(c2_value));
    case Instruction::Add:
      result = ConstantInt::get(context, c1_value + c2_value);
    case Instruction::Sub:
      result = ConstantInt::get(context, c1_value - c2_value);
    case Instruction::Mul:
      result = ConstantInt::get(context, c1_value * c2_value);
    case Instruction::UDiv:
      result = ConstantInt::get(context, c1_value.udiv(c2_value));
    case Instruction::SDiv:
      result = ConstantInt::get(context, c1_value.sdiv(c2_value));
    case Instruction::URem:
      result = ConstantInt::get(context, c1_value.urem(c2_value));
    case Instruction::SRem:
      result = ConstantInt::get(context, c1_value.srem(c2_value));
    case Instruction::Or:
      result = ConstantInt::get(context, c1_value.Or(c2_value));
    case Instruction::And:
      result = ConstantInt::get(context, c1_value.And(c2_value));
    case Instruction::LShr:
      result = ConstantInt::get(context, c1_value.lshr(c2_value));
    case Instruction::AShr:
      result = ConstantInt::get(context, c1_value.ashr(c2_value));
    case Instruction::Shl:
      result = ConstantInt::get(context, c1_value.shl(c2_value));
  }
  return result;
}

