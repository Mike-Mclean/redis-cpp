#ifndef COMMAND_HANDLERS
#define COMMAND_HANDLERS

#include <vector>
#include <string>
#include "datastore.h"

enum class Commands{
    PING, ECHO, GET, SET
};

struct redisCommand {
    Commands type;
    std::vector<std::string> args;
};


std::string handle_echo(const std::string& echo_message);

std::string handle_set(const std::vector<std::string>& pair_details, Datastore& data);

std::string handle_get(const std::vector<std::string>& key_details, Datastore& data);

std::string handle_received(std::vector<std::string>& parsed_received_message, Datastore& data);

std::string handle_ping();

redisCommand extract_command(respInput& parsed_input);


#endif