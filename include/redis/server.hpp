#pragma once

#include <string>

namespace redis
{
    class Server
    {
    public:
        Server(const std::string &address, int port);
        void start();
        void stop();

    private:
        std::string address_;
        int port_;
        bool running_;
    };
}