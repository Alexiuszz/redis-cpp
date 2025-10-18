#include <gtest/gtest.h>
#include "redis/datastore.hpp"

TEST(DataStoreTest, BasicSetGet) {
    redis::DataStore ds;
    redis::ValueObject v{redis::ValueObject::Type::STRING, "hello"};
    ds.set("key", v);
    auto out = ds.get("key");
    ASSERT_TRUE(out.has_value());
}