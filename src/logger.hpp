#pragma once

#include "set"
#include "spdlog/spdlog.h"
// #define DEBUG
namespace nc {
#ifndef DEBUG

#define NC_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define NC_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define NC_LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define NC_LOG_CRIT(...) spdlog::critical(__VA_ARGS__)
#else
#define NC_LOG_INFO(...)
#define NC_LOG_WARN(...)
#define NC_LOG_ERROR(...)
#define NC_LOG_CRIT(...)
#endif // !DEBUG

    enum class LogLevels
    {
        DEBUG,
        INFO,
        WARNING,
        ERR,
        CRITICAL
    };

    class Logger
    {
    private:
        Logger();

    public:
        static std::shared_ptr<Logger> getInstance()
        {
            static std::shared_ptr<Logger> loggerPtr{ new Logger() };
            return loggerPtr;
        }
        ~Logger() {}

        Logger(Logger&&)      = delete;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        void setLogLevel(int);
        void addVisibleCategories(std::string);

    private:
        std::set<std::string> m_visibleCategories;
        LogLevels             m_logLevel;
    };

}
