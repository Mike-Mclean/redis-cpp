#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <optional>
#include "datastore.h"
#include "resp_parser.h"
#include "command_handlers.h"

std::string handle_received(respInput& parsed_command, Datastore& data)
{

  std::string response {};
  redisCommand command {extract_command(parsed_command)};

  if (command.type == "ECHO") {
    response = handle_echo(command.args);
  } else if (command.type == "SET") {
    response = handle_set(command.args, data);
  } else if (command.type == "GET") {
    response = handle_get(command.args, data);
  } else if (command.type == "PING"){
    response = handle_ping();
  } else {
    throw std::runtime_error{"Unknown command"};
  }

  return response;
}

std::string handle_echo(const std::vector<std::string>& echo_args)
{
  if (echo_args.size() > 1){
    throw std::runtime_error{"Too many arguments to ECHO command"};
  }
  return "$" + std::to_string(echo_args[0].size()) + "\r\n" + echo_args[0] + "\r\n";
}

std::string handle_set(const std::vector<std::string>& set_args, Datastore& data)
{
  SetOptions set_details {parse_set_args(set_args)};

  if (set_details.expiry)
  {

    data.set(set_details.key, set_details.value, set_details.expiry);

  } else {

    data.set(set_details.key, set_details.value);

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

redisCommand extract_command(respInput& parsed_input)
{
  redisCommand command;
  command.type = parsed_input.array[0].str;

  //Arguments start at i = 1 in the array
  for (size_t i {1}; i < parsed_input.array.size(); i++)
  {
    command.args.push_back(parsed_input.array[i].str);
  }

  return command;
}

SetOptions parse_set_args(const std::vector<std::string>& args)
{

  if (args.size() > 4)
    throw std::runtime_error{"Invalid number of arguments for set command"};
  if (args.size() < 2)
    throw std::runtime_error{"Too few arguments for set command"};
  if (args.size() == 3)
    throw std::runtime_error{"Missing expiry time for EX or PX option"};

  SetOptions set {.key = args[0], .value = args[1]};

  if (args.size() > 2)
  {
    std::string expiry_type {args[2]};

    try {

      int expiry {std::stoi(args[3])};
      if (expiry_type == "EX")
        expiry *= 1000;

      set.expiry = expiry;

    } catch (const std::exception&) {

      throw std::runtime_error{"expiry value is not an integer or is out of range"};

    }
  }

  return set;

}
