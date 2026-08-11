#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <optional>
#include "datastore.h"
#include "resp_parser.h"

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


  if (pair_details.size() > 2)
  {
    int expiry;
    std::string expiry_type {pair_details[2]};
    try {
      expiry = std::stoi(pair_details[3]);
    } catch (const std::exception&) {
      std::cerr << "Error: Not a valid number.\n";
      return "-ERR value is not an integer or out of range\r\n";
    }
    if (expiry_type == "ex")
    {
      expiry *= 1000;
    }
    data.set(key, value, expiry);
  } else {
    data.set(key, value);
  }

  return "+OK\r\n";
}

std::string handle_get(const std::vector<std::string>& key_details, Datastore& data)
{
  std::string full_key {key_details[0]};
  for (size_t kd_idx {1}; kd_idx < key_details.size(); kd_idx++)
    full_key += " " + key_details[kd_idx];

  if (auto map_value = data.get_map_value(full_key)){
    std::string response { "$" };
    response += std::to_string(map_value->length()) + "\r\n" + map_value.value() + "\r\n";
    return response;
  } else {
    return "$-1\r\n";
  }
}

std::string handle_received(std::vector<std::string>& parsed_received_message, Datastore& data)
{

  std::string response {};
  ParsedCommand command {parse_command_details(parsed_received_message)};

  if (command.type == "echo"){
    response = handle_echo(command.details[0]);
  } else if (command.type == "set"){
    response = handle_set(command.details, data);
  } else if (command.type == "get"){
    response = handle_get(command.details, data);
  } else{
    // Response for a PING
    response = "+PONG\r\n";
  }

  return response;
}
