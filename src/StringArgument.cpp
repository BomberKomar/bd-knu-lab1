#include "StringArgument.hpp"

StringArgument::StringArgument(const std::string &value) : value(value) {}

ArgumentType StringArgument::getType() const
{
  return ArgumentType::String;
}

const std::string &StringArgument::getValue() const
{
  return this->value;
}
