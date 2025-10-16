#pragma once
#include <iostream>
#include <mutex>

namespace redis
{
    class Logger
    {
        inline static std::mutex mtx_;

    public:
        template <typename... Args>
        static void info(Args &&...args)
        {
            std::lock_guard<std::mutex> l(mtx_);
            (std::cout << ... << args) << std::endl;
        }
    };
}