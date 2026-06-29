#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <unordered_map>
#include <string_view>

class Datastore
{
    public:

        Datastore() = default;

        void set(std::string_view key, std::string_view value) {m_datastore.emplace(key, value);}

        std::string get(const std::string& key)
        {
            if (m_datastore.find(key) != m_datastore.end())
                return m_datastore[key];

            return "Key not found";
        }

        bool has_key(const std::string& key)
        {
            if (m_datastore.find(key) != m_datastore.end())
                return true;

            return false;
        }

    private:

        std::unordered_map<std::string, std::string> m_datastore;
};

#endif
