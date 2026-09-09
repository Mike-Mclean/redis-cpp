#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <unordered_map>
#include <string_view>
#include <mutex>
#include <shared_mutex>
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

        void set(std::string key, std::string value, std::optional<int> expiry = std::nullopt);
        std::optional<std::string> get_map_value(const std::string& key) const;

    private:
        std::unordered_map<std::string, MapValue> m_datastore;
        mutable std::shared_mutex map_mutex;
};

#endif
