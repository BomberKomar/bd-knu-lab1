#include <iostream>
#include <string>

#include "Shell.hpp"
#include "Expression.hpp"
#include "MusicRecordRepository.hpp"
#include "Command.hpp"

void Shell::run()
{
  std::string expressionText = "";

  while (true)
  {
    std::cout << SHELL_PROMPT;
    std::getline(std::cin, expressionText);

    try
    {
      Expression expression(expressionText);

      Command *foundCommand = NULL;

      for (auto &command : this->commands)
      {
        if (command->getText() == expression.getCommandText())
        {
          foundCommand = command;
        }
      }

      if (foundCommand == NULL)
      {
        std::cout << "Unknown command\n";
      }
      else
      {
        std::cout << foundCommand->execute(expression.getArguments());
      }
    }
    catch (const std::exception &exc)
    {
      std::cout << exc.what() << '\n';
    }
  }
}
