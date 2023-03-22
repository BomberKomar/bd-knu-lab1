#include "ArgumentType.hpp";

std::string argumentTypeToString(ArgumentType type)
{
  switch (type)
  {
  case ArgumentType::String:
    return "string";

  case ArgumentType::Number:
    return "number";
  }
}
