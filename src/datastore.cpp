#include "datastore.h"
#include <string>
#include <unordered_map>
#include <string_view>
#include <mutex>
#include <chrono>
#include <optional>

void Datastore::set(std::string_view key, std::string_view value, std::optional<int> expiry){
    MapValue data;
    data.value = value;
    if (expiry.has_value())
        data.expiry = std::chrono::steady_clock::now() + std::chrono::milliseconds(expiry.value());
    m_datastore.emplace(key, data);
}

std::string Datastore::get(const std::string& key){
    MapValue val {m_datastore[key]};
    return val.value;
}

bool Datastore::has_key(const std::string& key){
    if (m_datastore.find(key) != m_datastore.end()){
        MapValue val {m_datastore[key]};
        if (val.expiry.has_value() && std::chrono::steady_clock::now() >= val.expiry.value()){
                return false;
        }
        return true;
    }
    return false;
}