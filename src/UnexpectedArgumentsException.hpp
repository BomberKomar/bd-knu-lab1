#pragma once

#include "RepositoryException.hpp"

class UnexpectedArgumentsException : public RepositoryException
{
public:
  UnexpectedArgumentsException() : RepositoryException("Unexpected arguments for this command.") {}
};