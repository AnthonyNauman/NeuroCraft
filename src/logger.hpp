#pragma once

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
}
