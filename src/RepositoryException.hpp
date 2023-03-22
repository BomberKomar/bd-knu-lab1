#pragma once

#include <exception>
#include <string>

class RepositoryException : public std::exception
{
public:
  RepositoryException(const std::string &message) : message(message)
  {
  }

  virtual const char *
  what() const noexcept override
  {
    return this->message.c_str();
  }

protected:
  std::string message;
};