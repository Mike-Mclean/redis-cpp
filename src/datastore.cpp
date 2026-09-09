#include "datastore.h"
#include <string>
#include <unordered_map>
#include <string_view>
#include <mutex>
#include <chrono>
#include <optional>

void Datastore::set(std::string key, std::string value, std::optional<int> expiry){
    std::unique_lock<std::shared_mutex> lock(map_mutex);
    MapValue data;
    data.value = std::move(value);
    if (expiry.has_value())
        data.expiry = std::chrono::steady_clock::now() + std::chrono::milliseconds(expiry.value());
    m_datastore.insert_or_assign(std::move(key), std::move(data));
}

std::optional<std::string> Datastore::get_map_value(const std::string& key) const {
    std::shared_lock<std::shared_mutex> lock(map_mutex);
    auto it = m_datastore.find(key);
    if (it != m_datastore.end()){
        return it->second.value;
    }
    return std::nullopt;
}
