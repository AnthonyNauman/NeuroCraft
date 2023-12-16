#include "logger.hpp"
#include <iostream>
namespace nc {

    void LogStream::flush()
    {
        if (m_buffer.str().empty()) {
            return;
        }

        if (m_currentLevel < LOGSTRCT.logLevel || m_currentLevel >= LogLevels::log_levels) {
            return;
        }

        if (!LOGSTRCT.visibleCategories.empty()) {
            if (LOGSTRCT.visibleCategories.find(m_currentCategoty) == LOGSTRCT.visibleCategories.end()) {
                return;
            }
        }

        switch (m_currentLevel) {
            case LogLevels::TRACE: std::cout << termcolor::white; break;
            case LogLevels::DEBUG: std::cout << termcolor::blue; break;
            case LogLevels::INFO: std::cout << termcolor::green; break;
            case LogLevels::WARN: std::cout << termcolor::bright_magenta; break;
            case LogLevels::ERR: std::cout << termcolor::yellow; break;
            case LogLevels::CRITICAL: std::cout << termcolor::red; break;
            case LogLevels::OFF: std::cout << termcolor::dark; break;

            default: break;
        };

        std::cout << nowTimeStr() + " [" + m_currentCategoty + "] " + "[" << logLevelStr() + "] ";
        std::cout << termcolor::reset << m_buffer.str() << std::endl;
        logToFile();
        m_buffer = std::ostringstream();
    }
    void LogStream::logToFile()
    {
        std::string logPath = "logs/log.log";
        if (!std::filesystem::exists(std::filesystem::path("logs"))) {
            std::filesystem::create_directory(std::filesystem::path("logs"));
        }

        std::ofstream logs;
        logs.open(logPath, std::ios::app);
        if (logs.is_open()) {
            logs << nowTimeStr() + " [" + m_currentCategoty + "] " + "[" + logLevelStr() + "] " + m_buffer.str() << std::endl;
            logs.flush();
            logs.close();
        }
    }

    std::string LogStream::logLevelStr()
    {
        std::string lvl;
        switch (m_currentLevel) {
            case LogLevels::TRACE: lvl = "TRACE"; break;
            case LogLevels::DEBUG: lvl = "DEBUG"; break;
            case LogLevels::INFO: lvl = "INFO"; break;
            case LogLevels::WARN: lvl = "WARN"; break;
            case LogLevels::ERR: lvl = "ERR"; break;
            case LogLevels::CRITICAL: lvl = "CRITICAL"; break;
            case LogLevels::OFF: lvl = "OFF"; break;

            default: lvl = ""; break;
        };

        return lvl;
    }

    std::string LogStream::nowTimeStr()
    {
        auto t  = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "[%d-%m-%Y %H-%M-%S]");
        return oss.str();
    }

    LogStream Logger::GetLogStream(std::string category, LogLevels level) { return LogStream(category, level); }
}