#pragma once

#include "constants.hpp"
#include "set"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <fstream>
#include <spdlog/sinks/basic_file_sink.h>
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

#define NC_LOG(category, level) Logger::getInstance()->logStream(category, level)

#define NC_LEVEL_TRACE 0
#define NC_LEVEL_DEBUG 1
#define NC_LEVEL_INFO 2
#define NC_LEVEL_WARN 3
#define NC_LEVEL_ERROR 4
#define NC_LEVEL_CRITICAL 5
#define NC_LEVEL_OFF 6

    // Log levels enum
    enum LogLevels : int
    {
        TRACE    = NC_LEVEL_TRACE,
        DEBUG    = NC_LEVEL_DEBUG,
        INFO     = NC_LEVEL_INFO,
        WARN     = NC_LEVEL_WARN,
        ERR      = NC_LEVEL_ERROR,
        CRITICAL = NC_LEVEL_CRITICAL,
        OFF      = NC_LEVEL_OFF,
        log_levels
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
        ~Logger() { spdlog::drop_all(); }

        Logger(Logger&&)      = delete;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        void operator<<(std::string msg);

        void    setLogLevel(int);
        void    addVisibleCategories(std::string);
        void    log(std::string category, LogLevels level, std::string msg);
        Logger& logStream(std::string category, LogLevels level);

    private:
        std::set<std::string> m_visibleCategories;
        LogLevels             m_logLevel;

        std::string m_currentCategoty;
        LogLevels   m_currentLevel;
    };

}
