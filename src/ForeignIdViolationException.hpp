#pragma once

#include "RepositoryException.hpp"

class ForeignIdViolationException : public RepositoryException
{
public:
  ForeignIdViolationException() : RepositoryException("Foreign id violation.") {}
};