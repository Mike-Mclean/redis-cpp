#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "datastore"

struct ParsedCommand {
  std::string type;
  std::vector<std::string> details;
};

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
    newCommand.type = command_details[2]

    for (size_t detail_idx {4}; detail_idx < command_details.size(); detail_idx += 2)
    {
        newCommand.details.push_back(command_details[detail_idx]);
    }

    return newCommand;
}

std::string handle_echo(std::string echo_message)
{
  std::string padding {"\r\n"};
  std::string response {};

  for (index; index < parsed_message.size(); index++)
  {
    response += parsed_message[index] + padding;
  }

  return response;
}

std::string handle_set(const std::vector<std::string>& parsed_message, Datastore& data)
{

  data.set()
  return "+OK\r\n"
}

std:string handle_get(const std::vector<std::string>& parsed_message, size_t index)
{

}

std::string handle_received(const std::vector<std::string>& parsed_received_message, Datastore& data)
{

  std::string response {};
  ParsedCommand command {parse_command_details(parsed_received_message)};

  switch (command.type){
    case "ECHO":
      //if the command is an echo, there's only one element of .details
      response = handle_echo(command.details[0])
      break;
    case "SET":
      response = handle_set()
      break;
    case "GET":
      response = handle_get()
      break;
    default:
      // Response for a PING
      response = "+PONG\r\n";
      break;
  }

  return response;
}
