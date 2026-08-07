#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include "../src/datastore.h"
#include "../src/command_handlers.h"
#include "../src/resp_parser.h"
#include <string>

TEST_CASE("bulk strings parse correctly", "[parse_bulk_string]"){
    std::string ping {"*1\r\n$4\r\nPING\r\n"};
    std::vector<std::string> expected {"*1", "$4", "PING"};
    REQUIRE(parse_bulk_string(ping) == expected);
}

TEST_CASE("command details are parsed correctly", "[parse_command_details]"){

    SECTION("ping commands are parsed correctly") {
        std::vector<std::string> ping {"*1", "$4", "PING"};
        ParsedCommand expected {"ping", {}};
        ParsedCommand details {parse_command_details(ping)};
        REQUIRE(expected.type == details.type);
        REQUIRE_THAT(expected.details, Catch::Matchers::RangeEquals(details.details));
    }

    SECTION("echo commands are parsed correctly"){
        std::vector<std::string> hey {"*2", "$4", "ECHO", "$3", "hey"};
        ParsedCommand expected {"echo", {"hey"}};
        ParsedCommand details {parse_command_details(hey)};
        REQUIRE(expected.type == details.type);
        REQUIRE_THAT(expected.details, Catch::Matchers::RangeEquals(details.details));
    }

    SECTION("set commands are parsed correctly") {
        std::vector<std::string> ds_set {"*3", "$3", "SET", "$3", "foo", "$3", "bar"};
        ParsedCommand expected {"set", {"foo", "bar"}};
        ParsedCommand details {parse_command_details(ds_set)};
        REQUIRE(expected.type == details.type);
        REQUIRE_THAT(expected.details, Catch::Matchers::RangeEquals(details.details));
    }

}

TEST_CASE("echo is handled correctly", "[handle_echo]"){
    std::string hey {"HEY"};
    std::string expected {"$3\r\nHEY\r\n"};
    std::string echo {handle_echo(hey)};
    REQUIRE(echo == expected);
}

TEST_CASE("Handler returns PONG from PING request", "[handle_received]") {
    Datastore ds;
    std::vector<std::string> ping {"*1", "$4", "PING"};
    std::string expected {"+PONG\r\n"};
    std::string response {handle_received(ping, ds)};
    REQUIRE(response == expected);
}

TEST_CASE("datastore stores and retrieves a value", "[datastore]") {
    Datastore ds;
    ds.set("key", "value");
    REQUIRE(ds.get("key") == "value");
}

TEST_CASE("set command is handled correctly", "[handle_set]"){
    Datastore ds;
    std::vector<std::string> ds_set {"*3", "$3", "SET", "$3", "foo", "$3", "bar"};
    std::string expected {"+OK\r\n"};
    std::string handle_set {handle_received(ds_set, ds)};
    REQUIRE(handle_set == expected);
}

TEST_CASE("get command is handled correctly", "[handle_get]"){
    Datastore ds;
    ds.set("foo", "bar");
    std::vector<std::string> ds_get {"*2", "$3", "GET", "$3", "foo"};
    std::string expected {"+OK\r\n"};
    std::string handle_get {handle_received(ds_get, ds)};
    REQUIRE(handle_get == expected);
}

TEST_CASE("get command is handled correctly when key doesn't exist", "[handle_get]"){
    Datastore ds;
    ds.set("foo", "bar");
    std::vector<std::string> ds_get {"*2", "$3", "GET", "$3", "fee"};
    std::string expected {"$-1\r\n"};
    std::string handle_get {handle_received(ds_get, ds)};
    REQUIRE(handle_get == expected);
}
