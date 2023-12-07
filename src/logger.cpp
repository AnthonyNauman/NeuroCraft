#include "logger.hpp"
#include <iostream>
namespace nc {

    Logger::Logger()
    {
        std::string logPath = "logs/log";
        if (std::filesystem::exists(std::filesystem::path("logs"))) {
            if (std::filesystem::exists(std::filesystem::path(logPath))) {
                std::filesystem::remove(std::filesystem::path(logPath));
            }
        } else {
            std::filesystem::create_directory(std::filesystem::path("logs"));
        }

        std::ofstream logs;
        logs.open(logPath);
        if (logs.is_open()) {
            logs << "";
            logs.flush();
            logs.close();
        }

        auto logger = spdlog::basic_logger_mt("logger", logPath);
    }

    void Logger::setLogLevel(int level) { m_logLevel = static_cast<LogLevels>(level); }

    void Logger::addVisibleCategories(std::string category) { m_visibleCategories.insert(category); }

    Logger& Logger::logStream(std::string category, LogLevels level)
    {
        m_currentCategoty = category;
        m_currentLevel    = level;
        return *this;
    }

    Logger& Logger::operator<<(std::string msg)
    {
        std::string logPath = "logs/log";
        if (!std::filesystem::exists(std::filesystem::path("logs"))) {
            std::filesystem::create_directory(std::filesystem::path("logs"));
        }
        if (!std::filesystem::exists(std::filesystem::path(logPath))) {
            std::ofstream logs;
            logs.open(logPath);
            if (logs.is_open()) {
                logs << "";
                logs.flush();
                logs.close();
            }
        }

        if (!m_visibleCategories.empty()) {
            if (m_visibleCategories.find(m_currentCategoty) == m_visibleCategories.end()) {
                return *this;
            }
        }

        std::string spdMsg = "[" + m_currentCategoty + "] " + msg;

        //!\todo перенести set_pattern и set_level в конструктор (тупой перенос вызовов не сработал)
        auto logger = spdlog::get("logger");
        logger->log(static_cast<spdlog::level::level_enum>(m_currentLevel), spdMsg);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
        logger->set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
        logger->flush();

        spdlog::set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
        spdlog::log(static_cast<spdlog::level::level_enum>(m_currentLevel), spdMsg);

        return *this;
    }
}