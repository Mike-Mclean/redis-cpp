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

std::string handle_echo(const std::string& echo_message)
{
  std::string padding {"\r\n"};
  size_t message_size {echo_message.length()};

  std::string response {"$" + std::to_string(message_size) + padding + echo_message + padding};

  return response;
}

std::string handle_set(const std::vector<std::string>& pair_details, Datastore& data)
{
  std::string key {pair_details[0]};
  std::string value {pair_details[1]};
  data.set(key, value);
  return "+OK\r\n"
}

std:string handle_get(const std::vector<std::string>& key_details, Datastore& data)
{
  std::string full_key {key_details[0]};
  for (size_t kd_idx {1}; kd_idx < key_details.size(); kd_details++)
    full_key += " " + key_details[kd_idx]

  if (data.has_key(full_key)){
    
  }
}

std::string handle_received(const std::vector<std::string>& parsed_received_message, Datastore& data)
{

  std::string response {};
  ParsedCommand command {parse_command_details(parsed_received_message)};

  switch (command.type){
    case "ECHO":
      //if the command is an echo, there's only one element of .details
      //Maybe need to fix this; an echo command can have multiple elements
      response = handle_echo(command.details[0])
      break;
    case "SET":
      response = handle_set(command.details, data)
      break;
    case "GET":
      response = handle_get(command.details, data)
      break;
    default:
      // Response for a PING
      response = "+PONG\r\n";
      break;
  }

  return response;
}
