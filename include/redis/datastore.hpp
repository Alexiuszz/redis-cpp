#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <variant>
#include <optional>
#include <chrono>

namespace redis
{
    struct ValueObject
    {
        enum class Type
        {
            STRING,
            LIST,
            SET,
            HASH
        };
        Type type;
        std::variant<std::string, std::list<std::string>,
                     std::unordered_set<std::string>,
                     std::unordered_map<std::string, std::string>>
            data;
        std::optional<std::chrono::steady_clock::time_point> expiry;
    };

    class DataStore
    {
    public:
        std::optional<ValueObject> get(const std::string &key) const;
        void set(const std::string &key, ValueObject value);
        void del(const std::string &key);
        void expire(const std::string &key, int seconds);

    private:
        mutable std::unordered_map<std::string, ValueObject> store_;
    };

}
