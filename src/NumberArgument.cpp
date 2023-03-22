#include "NumberArgument.hpp"

NumberArgument::NumberArgument(const double &value) : value(value) {}

ArgumentType NumberArgument::getType() const
{
  return ArgumentType::Number;
}

const double &NumberArgument::getValue() const
{
  return this->value;
}
