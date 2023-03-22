#pragma once

#include <string>

#include "Argument.hpp"

class StringArgument : public Argument
{
public:
  StringArgument(const std::string &value);

  virtual ArgumentType getType() const override;
  const std::string &getValue() const;

private:
  std::string value;
};