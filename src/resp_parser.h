#ifndef RESP_PARSER_H
#define RESP_PARSER_H

#include "datastore.h"
#include <string_view>

inline constexpr char RESP_SIMPLE_STR = '+';
inline constexpr char RESP_BULK_STR = '$';
inline constexpr char RESP_ARRAY = '*';
inline constexpr char RESP_ERROR = '-';
inline constexpr char RESP_INTEGER = ':';

struct respInput {
  std::string type;
  std::string str;
  std::vector<respInput> array;
};

struct ParsedCommand {
  std::string type;
  std::vector<std::string> details;
};

respInput readInput(std::istringstream& message);
respInput parse_bulk_string(std::istringstream& stream);
respInput parse_resp_array(std::istringstream& message);

ParsedCommand parse_command_details(std::vector<std::string>& command_details);

#endif