#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "datastore.h"
#include "resp_parser.h"

std::vector<std::string> parse_bulk_string(const std::string& message)
{
  std::string crlf {"\r\n"};
  std::vector<std::string> message_details;

  size_t start {0};
  std::string token {};
  size_t pos {message.find(crlf, start)};

  while (pos != std::string::npos)
  {
    token = message.substr(start, (pos - start));
    message_details.push_back(token);
    start = pos + crlf.length();
    pos = message.find(crlf, start);
  }

  return message_details;
}

ParsedCommand parse_command_details(const std::vector<std::string>& command_details)
{
  ParsedCommand newCommand;
  std::for_each(command_details.begin(), command_details.end(), [](std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){
      return std::tolower(c);
    });
  });

  std::string command_type { command_details[2] };

  newCommand.type = command_type;

  for (size_t detail_idx {4}; detail_idx < command_details.size(); detail_idx += 2)
  {
      newCommand.details.push_back(command_details[detail_idx]);
  }

  return newCommand;
}
