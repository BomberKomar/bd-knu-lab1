#pragma once

#include <string>
#include <vector>

#include "Argument.hpp"
#include "NumberArgument.hpp"
#include "StringArgument.hpp"

class Expression
{
public:
  Expression(std::string text);
  ~Expression();
  std::string getCommandText();
  const std::vector<Argument *> getArguments() const;

private:
  std::string readCommandText();
  Argument *readArgument();
  StringArgument *readStringArgument();
  NumberArgument *readNumberArgument();
  void skipSpaces(bool spaceIsRequired);
  bool textIsEnded();
  char getCursorCharacter();

  size_t textCursorIndex = 0;
  std::string text;
  std::string commandText;
  std::vector<Argument *> arguments;
};