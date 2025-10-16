#include "redis/datastore.hpp"
#include <chrono>

namespace redis
{

    std::optional<ValueObject> DataStore::get(const std::string &key) const
    {
        auto it = store_.find(key);
        if (it == store_.end())
        {
            return std::nullopt;
        }

        if (it->second.expiry)
        {
            const auto now = std::chrono::steady_clock::now();
            if (now >= *(it->second.expiry))
            {
                store_.erase(it); // purge expired entries on access
                return std::nullopt;
            }
        }

        return it->second;
    }

    void DataStore::set(const std::string &key, ValueObject value)
    {
        store_.insert_or_assign(key, std::move(value));
    }

    void DataStore::del(const std::string &key)
    {
        store_.erase(key);
    }

    void DataStore::expire(const std::string &key, int seconds)
    {
        auto it = store_.find(key);
        if (it == store_.end())
        {
            return;
        }

        // Remove already expired entries or handle non-positive TTLs by deleting.
        const auto now = std::chrono::steady_clock::now();
        if ((it->second.expiry && now >= *(it->second.expiry)) || seconds <= 0)
        {
            store_.erase(it);
            return;
        }

        it->second.expiry = now + std::chrono::seconds(seconds);
    }

}
