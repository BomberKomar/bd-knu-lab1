#include "Expression.hpp"
#include "TextEndedException.hpp"
#include "UnexpectedCharacterException.hpp"

Expression::Expression(std::string text) : text(text)
{
  this->skipSpaces(false);

  this->commandText = this->readCommandText();

  while (!this->textIsEnded())
  {
    try
    {
      this->arguments.push_back(this->readArgument());
    }
    catch (const TextEndedException &e)
    {
      break;
    }
  }
}

Expression::~Expression()
{
  for (auto argument : this->arguments)
  {
    delete argument;
  }
}

bool Expression::textIsEnded()
{
  return this->textCursorIndex >= this->text.length();
}

Argument *Expression::readArgument()
{
  this->skipSpaces(true);

  if (this->textIsEnded())
  {
    throw TextEndedException();
  }

  auto cursorCharacter = this->text[this->textCursorIndex];

  if (isdigit(cursorCharacter))
  {
    return this->readNumberArgument();
  }
  else if (cursorCharacter == '\'')
  {
    return this->readStringArgument();
  }
  else
  {
    throw UnexpectedCharacterException(this->text, this->textCursorIndex);
  }
}

char Expression::getCursorCharacter()
{
  return this->text[this->textCursorIndex];
}

void Expression::skipSpaces(bool spaceIsRequired)
{
  if (spaceIsRequired && (this->textIsEnded() || this->getCursorCharacter() != ' '))
  {
    throw UnexpectedCharacterException(this->text, this->textCursorIndex);
  }

  while (!this->textIsEnded() &&
         this->text[this->textCursorIndex] == ' ')
  {

    this->textCursorIndex++;
  }
}

NumberArgument *Expression::readNumberArgument()
{
  std::string resultString = "";
  bool resultIsContainingPeriod = false;

  while (this->textCursorIndex < this->text.length())
  {
    auto cursorCharacter = this->getCursorCharacter();

    if (cursorCharacter == ' ')
    {
      break;
    }

    if (cursorCharacter == '.')
    {
      if (resultIsContainingPeriod)
      {
        throw UnexpectedCharacterException(this->text, this->textCursorIndex);
      }

      resultIsContainingPeriod = true;
    }
    else if (!isdigit(cursorCharacter))
    {
      throw UnexpectedCharacterException(this->text, this->textCursorIndex);
    }

    resultString += cursorCharacter;
    this->textCursorIndex++;
  }

  return new NumberArgument(std::stod(resultString));
}

StringArgument *Expression::readStringArgument()
{
  this->textCursorIndex++;

  std::string result = "";

  while (!this->textIsEnded())
  {
    char cursorCharacter = this->getCursorCharacter();

    this->textCursorIndex++;

    if (cursorCharacter == '\'')
    {
      return new StringArgument(result);
    }

    result += cursorCharacter;
  }

  throw UnexpectedCharacterException(this->text, this->textCursorIndex);
}

std::string Expression::readCommandText()
{
  std::string result = "";

  while (!this->textIsEnded())
  {
    char cursorCharacter = this->getCursorCharacter();

    if (cursorCharacter == ' ')
    {
      break;
    }

    result += cursorCharacter;

    this->textCursorIndex++;
  }

  if (result.empty())
  {
    throw UnexpectedCharacterException(this->text, this->textCursorIndex);
  }

  return result;
}

const std::vector<Argument *> Expression::getArguments() const
{
  return this->arguments;
}

std::string Expression::getCommandText()
{
  return this->commandText;
}