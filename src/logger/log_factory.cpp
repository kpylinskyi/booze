#include "logger/log_factory.hpp"
#include "logger/log/info_log.hpp"
#include "logger/log/warning_log.hpp"
#include "logger/log/error_log.hpp"

std::shared_ptr<Log> LogFactory::createLog(LOG_LVL log_lvl, std::string message)
{
    switch (log_lvl)
    {
    case LOG_LVL::INF:
        return std::make_shared<InfoLog>(message);
    case LOG_LVL::WRN:
        return std::make_shared<WarningLog>(message);
    case LOG_LVL::ERR:
        return std::make_shared<ErrorLog>(message);
    default:
        throw std::invalid_argument("Unsupported log level");
    }
}
