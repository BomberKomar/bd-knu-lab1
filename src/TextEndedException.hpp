#pragma once

#include <exception>
#include <string>

class TextEndedException : public std::exception
{
public:
  const char *what() const noexcept
  {
    return this->message.c_str();
  }

private:
  std::string message = "The text has been ended.";
};