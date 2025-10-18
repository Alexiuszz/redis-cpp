#include "redis/server.hpp"
#include "redis/logger.hpp"

int main() {
    redis::Logger::info("Starting redis-cpp...");
    redis::Server server(6379);
    server.start();
    return 0;
}