#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <map>
#include <memory>
#include "log_factory.hpp"
#include "logger/log_level.hpp"

/**
 * @class Logger
 * @brief Provides logging functionality with thread-safe file and console output, supporting multiple log levels.
 */
class Logger
{
public:
    static Logger &getInstance(const std::string &filename = "default.log");

    void log(LOG_LVL log_lvl, const std::string &message);

    std::string log_lvl_to_string(LOG_LVL log_lvl);

private:
    std::ofstream _log_file; /**< The file stream used for writing log messages to a file. */
    std::mutex _mutex;       /**< Mutex to ensure thread-safe access to the log file. */
    LogFactory _log_factory; /**< Factory to create appropriate log objects based on log level. */

    /**
     * @brief Constructs a Logger that writes to a specified file.
     * @param filename The name of the file where logs will be stored.
     */
    Logger(const std::string &filename);

    /**
     * @brief Destroys the Logger, closing the log file.
     */
    ~Logger();

    // Prevent copy and assignment
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

#endif // LOGGER_HPP
