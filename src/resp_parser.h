#ifndef RESP_PARSER_H
#define RESP_PARSER_H

#include "datastore.h"

struct ParsedCommand {
  std::string type;
  std::vector<std::string> details;
};

std::vector<std::string> parse_bulk_string(const std::string& message);

ParsedCommand parse_command_details(const std::vector<std::string>& command_details);

#endif