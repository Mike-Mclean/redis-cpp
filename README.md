# redis-cpp

A Redis server implementation in C++20, built as part of CodeCrafters'
["Build Your Own Redis"](https://codecrafters.io/challenges/redis) challenge.
It speaks the RESP protocol, handles concurrent clients over TCP, and
implements a subset of the Redis command set backed by an in-memory
key/value store.

## Features

- Custom RESP (REdis Serialization Protocol) parser
- TCP server accepting multiple concurrent clients (one thread per connection)
- In-memory datastore with optional per-key expiry
- Commands: `PING`, `ECHO`, `SET` (with `EX`/`PX` expiry), `GET`

## Project layout

```
src/
  main.cpp              # TCP server / connection handling entry point
  resp_parser.{h,cpp}    # RESP wire format parsing
  command_handlers.{h,cpp} # Command dispatch and execution
  datastore.{h,cpp}      # In-memory key/value store
tests/
  redis_test.cpp         # Catch2 unit tests
```

## Requirements

- CMake >= 3.13
- A C++23-capable compiler
- [vcpkg](https://vcpkg.io) with `VCPKG_ROOT` set in your environment

Dependencies (`asio`, `pthreads`, `catch2`) are managed via vcpkg — see
[vcpkg.json](vcpkg.json).

## Building and running

```sh
./your_program.sh
```

This configures the project with CMake (using the vcpkg toolchain file),
builds it, and runs the resulting `redis` server on port `6379`.

Equivalently, you can drive CMake directly:

```sh
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake --build build
./build/redis
```

Once running, interact with it using `redis-cli` or `nc`:

```sh
redis-cli -p 6379 PING
redis-cli -p 6379 SET foo bar EX 10
redis-cli -p 6379 GET foo
```

## Testing

Unit tests are written with [Catch2](https://github.com/catchorg/Catch2) and
built as a separate `tests` target.

```sh
./build/tests                                # run directly, verbose output
ctest --test-dir build --output-on-failure   # via CTest, pass/fail summary
```

## Submitting to CodeCrafters

```sh
codecrafters submit
```

Test output streams to your terminal. See [codecrafters.yml](codecrafters.yml)
for build configuration.
