#include "redis/server.hpp"
#include <utility>
#include "redis/logger.hpp"

namespace redis
{
    Server::Server(const std::string &address, int port)
        : address_(address), port_(port), running_(false) {}

    Server::Server(int port) : Server("127.0.0.1", port) {}

    void Server::start()
    {
        if (running_)
        {
            return;
        }
        running_ = true;
        Logger::info("Server started on ", address_, ":", port_);
    }

    void Server::stop()
    {
        if (!running_)
        {
            return;
        }
        running_ = false;
        Logger::info("Server stopped");
    }

} // namespace redis
