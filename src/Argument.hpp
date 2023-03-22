#pragma once

#include <string>

#include "ArgumentType.hpp"

class Argument
{
public:
  virtual ArgumentType getType() const = 0;
};