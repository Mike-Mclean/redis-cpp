#include "datastore.h"

struct ParsedCommand {
  std::string type;
  std::vector<std::string> details;
};

std::vector<std::string> parse_bulk_string(const std::string& message);

ParsedCommand parse_command_details(const std::vector<std::string>& command_details);

std::string handle_echo(const std::string& echo_message);

std::string handle_set(const std::vector<std::string>& pair_details, Datastore& data);

std::string handle_get(const std::vector<std::string>& key_details, Datastore& data);

std::string handle_received(const std::vector<std::string>& parsed_received_message, Datastore& data);