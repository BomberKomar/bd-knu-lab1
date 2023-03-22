#pragma once

#include <string>
#include <vector>

#include "MusicRecordRepository.hpp"
#include "Command.hpp"

const std::string SHELL_PROMPT = "~> ";

class Shell
{
public:
  Shell(const std::vector<Command *> &commands) : commands(commands) {}
  void run();

private:
  std::vector<Command *> commands;
};
