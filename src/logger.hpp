#pragma once

#include "spdlog/spdlog.h"
// #define DEBUG
namespace nc {
#ifndef DEBUG
#define __logInfo(...) spdlog::info(__VA_ARGS__)
#define __logWarn(...) spdlog::warn(__VA_ARGS__)
#define __logError(...) spdlog::error(__VA_ARGS__)
#define __logCritical(...) spdlog::critical(__VA_ARGS__)
#else
#define __logInfo(...) 
#define __logWarn(...) 
#define __logError(...) 
#define __logCritical(...)
#endif // !DEBUG
}
