#pragma once

#include "RepositoryException.hpp"

class IdViolationException : public RepositoryException
{
public:
  IdViolationException() : RepositoryException("This id has already been used.") {}
};