#ifndef COMMAND_HANDLERS
#define COMMAND_HANDLERS

#include <vector>
#include <string>
#include "datastore.h"

struct redisCommand {
    std::string type;
    std::vector<std::string> args;
};

struct SetOptions {
    std::string key;
    std::string value;
    std::optional<int> expiry;
};

std::string handle_echo(const std::vector<std::string>& echo_args);
std::string handle_set(const std::vector<std::string>& set_args, Datastore& data);
std::string handle_get(const std::vector<std::string>& get_args, Datastore& data);
std::string handle_received(respInput parsed_command, Datastore& data);


redisCommand extract_command(respInput& parsed_input);
SetOptions parse_set_args(const std::vector<std::string>& args);

#endif