#ifndef COMMAND_HANDLERS
#define COMMAND_HANDLERS

#include <vector>
#include <string>
#include "datastore.h"

std::string handle_echo(const std::string& echo_message);

std::string handle_set(const std::vector<std::string>& pair_details, Datastore& data);

std::string handle_get(const std::vector<std::string>& key_details, Datastore& data);

std::string handle_received(const std::vector<std::string>& parsed_received_message, Datastore& data);


#endif