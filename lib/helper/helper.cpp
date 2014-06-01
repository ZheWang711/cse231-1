#include "helper.h"

ConstantInt* helper::foldBinaryOperator(unsigned Opcode,ConstantInt *C1, ConstantInt *C2){
  LLVMContext &context = C1->getContext();
  const APInt &c1_value = C1->getValue();
  const APInt &c2_value = C2->getValue();
  ConstantInt* result = ConstantInt::get(context, APInt::getNullValue(32));
  switch (Opcode) {
    case Instruction::Xor:
      const APInt &result_value  = c1_value.Xor(c2_value);
      result = ConstantInt::get(context, result_value);
    case Instruction::Add:
      const APInt &result_value1  = c1_value + c2_value;
      result = ConstantInt::get(context, result_value1);
    case Instruction::Sub:
      const APInt &result_value2  = c1_value - c2_value;
      result = ConstantInt::get(context, result_value2);
    case Instruction::Mul:
      const APInt &result_value3  = c1_value * c2_value;
      result = ConstantInt::get(context, result_value3);
    case Instruction::Udiv:
      const APInt &result_value4  = c1_value.udiv(c2_value);
      result = ConstantInt::get(context, result_value4);
    case Instruction::Sdiv:
      const APInt &result_value5  = c1_value.sdiv(c2_value);
      result = ConstantInt::get(context, result_value5);
    case Instruction::URem:
      const APInt &result_value6  = c1_value.urem(c2_value);
      result = ConstantInt::get(context, result_value6);
    case Instruction::SRem:
      const APInt &result_value7  = c1_value.srem(c2_value);
      result = ConstantInt::get(context, result_value7);
    case Instruction::Or:
      const APInt &result_value8  = c1_value.Or(c2_value);
      result = ConstantInt::get(context, result_value8);
    case Instruction::And:
      const APInt &result_value9  = c1_value.And(c2_value);
      result = ConstantInt::get(context, result_value9);
    case Instruction::LShr:
      const APInt &result_value10  = c1_value.lshr(c2_value);
      result = ConstantInt::get(context, result_value10);
    case Instruction::AShr:
      const APInt &result_value11  = c1_value.ashr(c2_value);
      result = ConstantInt::get(context, result_value11);
    case Instruction::Shl:
      const APInt &result_value12  = c1_value.shl(c2_value);
      result = ConstantInt::get(context, result_value12);
  }
  return result;
}

