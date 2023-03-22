#pragma once

#include <string>

#include "Argument.hpp"

class NumberArgument : public Argument
{
public:
  NumberArgument(const double &value);

  virtual ArgumentType getType() const override;
  const double &getValue() const;

private:
  double value;
};