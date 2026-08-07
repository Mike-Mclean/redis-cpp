#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <unordered_map>
#include <string_view>
#include <mutex>
#include <chrono>
#include <optional>

struct MapValue {
    std::string value;
    std::optional<std::chrono::steady_clock::time_point> expiry;
};

class Datastore
{
    public:

        Datastore() = default;

        void set(std::string_view key, std::string_view value, std::optional<int> expiry = std::nullopt);
        std::string get(const std::string& key);
        bool has_key(const std::string& key);

    private:

        std::unordered_map<std::string, MapValue> m_datastore;
};

#endif
