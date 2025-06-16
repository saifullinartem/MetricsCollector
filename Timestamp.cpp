#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

inline std::string ToTimeStampForFile(std::chrono::system_clock::time_point tp) {
    auto sec = std::chrono::floor<std::chrono::seconds>(tp);
    auto ms  = std::chrono::duration_cast<std::chrono::milliseconds>(tp - sec).count();
    std::time_t t = std::chrono::system_clock::to_time_t(sec);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d_%H.%M.%S") << '.' << std::setw(3) << std::setfill('0') << ms;
    return oss.str();
}

inline std::string ToTimeStamp(std::chrono::system_clock::time_point tp) {
    auto sec = std::chrono::floor<std::chrono::seconds>(tp);
    auto ms  = std::chrono::duration_cast<std::chrono::milliseconds>(tp - sec).count();
    std::time_t t = std::chrono::system_clock::to_time_t(sec);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%F %T") << '.' << std::setw(3) << std::setfill('0') << ms;
    return oss.str();
}
