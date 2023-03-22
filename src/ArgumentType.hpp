#pragma once

#include <string>

enum ArgumentType
{
  String,
  Number
};

std::string argumentTypeToString(ArgumentType type);
