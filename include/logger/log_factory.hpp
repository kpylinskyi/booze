#ifndef LOG_FACTORY_HPP
#define LOG_FACTORY_HPP

#include "logger/log_level.hpp"
#include "logger/log/log.hpp"
#include <memory>

class LogFactory {
public:
    LogFactory() = default;

    std::shared_ptr<Log> createLog(LOG_LVL level, std::string message);
};

#endif // LOG_FACTORY_HPP
