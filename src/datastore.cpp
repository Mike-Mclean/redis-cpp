#include <iostream>
#include <string>
#include <unordered_map>

class Datastore
{
    public:

    Datastore() = default;

    void set(const std::string& key, const std::string& value) {datastore.emplace(key, value);}
    std::string get(const std::string& key)
    {
        if (m_datastore.find(key) != m_datastore.end())
            return datastore[key];

        return "Key not found";
    }

    private:

    std::unordered_map<std::string, std::string> m_datastore;
};
