#pragma once

#include "../constants.hpp"
#include "set"
#include "../../libs/termcolor/include/termcolor/termcolor.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#define NC_LOG(...) nc::LogStream(__VA_ARGS__)

namespace nc {
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

    struct LogStruct {
        std::set<std::string> visibleCategories;
        LogLevels             logLevel;
        void addVisibleCategories(std::string cat)
        {
            if(!cat.empty())
                visibleCategories.insert(cat);
        }
    };


    extern LogStruct LOGSTRCT;

    class LogStream
    {
        public:
            LogStream(std::string category, LogLevels level)
            : m_currentCategoty(category)
            , m_currentLevel(level)
            {
               operator<<("");
            }

            ~LogStream()
            {
                flush();
            }

            template<class T>
            LogStream& operator<<(const T& msg)
            {
                buffer() << msg;
                return *this;
            }
        
    private:
        std::ostringstream& buffer() {return m_buffer;}
        void log();
        void flush();
        void logToFile();
        std::string logLevelStr();
        std::string nowTimeStr();
    private:
       
        std::ostringstream    m_buffer;
        std::string m_currentCategoty;
        LogLevels   m_currentLevel;
    };
}