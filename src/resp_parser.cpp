#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include "datastore.h"
#include "resp_parser.h"

respInput readInput(std::istringstream& message)
{
  char prefix;

  if (!message.get(prefix))
    throw std::runtime_error{"Could not parse input"};

  switch (prefix)
  {
  case RESP_ARRAY:
    return parse_resp_array(message);
    break;

  case RESP_BULK_STR:
    return parse_bulk_string(message);
    break;

  default:
    throw std::runtime_error{"Unknown type message type"};
    break;
  }
}

respInput parse_bulk_string(std::istringstream& stream)
{

  int length;
  if (!(stream >> length))
    throw std::runtime_error{"Failed to parse bulk string length"};
  if (length < 0)
  {
    respInput nullInput {.type = RESP_BULK_STR, .str = ""};
    return nullInput;
  }

  //consume /r/n
  stream.get();
  stream.get();

  std::string payload(length, '\0');
  if (!stream.read(payload.data(), length))
    throw std::runtime_error{"Malformed bulk string"};

  //consume trailing /r/n
  stream.get();
  stream.get();

  respInput value;
  value.str = payload;
  value.type = RESP_BULK_STR;

  return value;
}

respInput parse_resp_array(std::istringstream& message)
{

  int length;
  if (!(message >> length))
    throw std::runtime_error{"Failed to parse RESP array length"};

  if (length < 0)
  {
    respInput nullArray{.type = RESP_ARRAY, .array = {}};
    return nullArray;
  }

  //consume \r\n
  message.get();
  message.get();

  respInput value;
  value.type = RESP_ARRAY;

  for (size_t i {}; i < length; i++)
  {
    respInput array_value = readInput(message);
    value.array.push_back(array_value);
  }

  return value;

}
