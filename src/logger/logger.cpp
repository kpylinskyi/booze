#include "logger/logger.hpp"

Logger &Logger::getInstance(const std::string &filename)
{
    static Logger instance(filename);
    return instance;
}

Logger::Logger(const std::string &filename)
{
    _log_file.open(filename, std::ios::app);
    if (!_log_file.is_open())
    {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
}

Logger::~Logger()
{
    if (_log_file.is_open())
    {
        _log_file.close();
    }
}

void Logger::log(LOG_LVL log_lvl, const std::string &message)
{
    std::lock_guard<std::mutex> lock(_mutex);

    auto log_entry = _log_factory.createLog(log_lvl, message);
    log_entry->print();

    if (_log_file.is_open())
    {
        _log_file << "[" << LogLevel::to_string(log_lvl) << "] " << log_entry->to_string() << std::endl;
    }
}