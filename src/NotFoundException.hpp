#pragma once

#include "RepositoryException.hpp"

class NotFoundException : public RepositoryException
{
public:
  NotFoundException() : RepositoryException("Failed to find the record.") {}
};