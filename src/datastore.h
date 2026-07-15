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

        void set(std::string_view key, std::string_view value, std::optional<int> expiry = std::nullopt)
        {
            MapValue data;
            data.value = value;
            if (expiry.has_value())
                data.expiry = std::chrono::steady_clock::now() + std::chrono::milliseconds(expiry.value());
            m_datastore.emplace(key, data);
        }

        std::string get(const std::string& key)
        {
            MapValue val {m_datastore[key]};
            return val.value;
        }

        bool has_key(const std::string& key)
        {
            if (m_datastore.find(key) != m_datastore.end()){
                MapValue val {m_datastore[key]};
                if (val.expiry.has_value() && std::chrono::steady_clock::now() >= val.expiry.value()){
                        return false;
                }
                return true;
            }
            return false;
        }

    private:

        std::unordered_map<std::string, MapValue> m_datastore;
};

#endif
