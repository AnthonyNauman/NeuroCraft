#include "logger.hpp"

namespace nc {

    Logger::Logger() {}

    void Logger::setLogLevel(int level) { m_logLevel = static_cast<LogLevels>(level); }

    void Logger::addVisibleCategories(std::string category) { m_visibleCategories.insert(category); }
}