#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include "datastore.h"
#include "resp_parser.h"

std::string parse_bulk_string(const std::string& message)
{
  std::istringstream stream(message);

  char prefix;
  if (!stream.get(prefix) || prefix != '$')
    throw std::runtime_error{"Invlaid type, expecting bulk strings only"};

  int length {};
  if (!(stream >> length))
    throw std::runtime_error{"Failed to parse bulk string length"};

  std::string payload {};

  //consume /r/n
  stream.get();
  stream.get();

  for (size_t i {}; i < length; i++) {
    payload.push_back(stream.get());
  }

  return payload;
}

ParsedCommand parse_command_details(std::vector<std::string>& command_details)
{
  ParsedCommand newCommand;
  std::string command_type = command_details[2];
  std::transform(command_type.begin(), command_type.end(), command_type.begin(), [](unsigned char c){
    return std::tolower(c);
  });

  newCommand.type = command_type;

  for (size_t detail_idx {4}; detail_idx < command_details.size(); detail_idx += 2)
  {
      newCommand.details.push_back(command_details[detail_idx]);
  }

  return newCommand;
}
