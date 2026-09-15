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

std::string handle_echo(const std::string& echo_message);
std::string handle_set(const std::vector<std::string>& pair_details, Datastore& data);
std::string handle_get(const std::vector<std::string>& key_details, Datastore& data);
std::string handle_received(std::vector<std::string>& parsed_received_message, Datastore& data);


redisCommand extract_command(respInput& parsed_input);
SetOptions parse_set_args(const std::vector<std::string>& args);

#endif