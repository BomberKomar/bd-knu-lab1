#pragma once

#include <string>
#include "RepositoryException.hpp"

class UnexpectedCharacterException : public RepositoryException
{
public:
  UnexpectedCharacterException(std::string expression, int position) : RepositoryException("")
  {
    this->message = "Unexpected symbol.";

    this->message += '\n' + expression;

    this->message += '\n';
    for (int i = 0; i < position; i++)
    {
      this->message += ' ';
    }
    this->message += '^';
  }
};