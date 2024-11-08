#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <map>

/**
 * @enum Levels
 * @brief Defines different logging levels.
 */
enum Levels { INFO, WARNING, ERROR };

/**
 * @struct LogLevel
 * @brief Represents a log level with a name and color for output formatting.
 */
struct LogLevel {
    std::string Name;   /**< The name of the log level (e.g., "INFO", "WARNING", "ERROR"). */
    std::string Color;  /**< The color code associated with the log level for console output. */
};

/**
 * @class Logger
 * @brief Provides logging functionality with thread-safe file and console output, supporting multiple log levels.
 */
class Logger {
public:
    /**
     * @brief Constructs a Logger that writes to a specified file.
     * @param filename The name of the file where logs will be stored.
     */
    Logger(const std::string& filename);

    /**
     * @brief Destroys the Logger, closing the log file.
     */
    ~Logger();

    /**
     * @brief Logs an informational message.
     * @param message The message to log at the INFO level.
     */
    void info(const std::string& message) const;

    /**
     * @brief Logs a warning message.
     * @param message The message to log at the WARNING level.
     */
    void warning(const std::string& message) const;

    /**
     * @brief Logs an error message.
     * @param message The message to log at the ERROR level.
     */
    void error(const std::string& message) const;

private:
    std::ofstream _log_file;                   /**< The file stream used for writing log messages to a file. */
    std::mutex _mutex;                         /**< Mutex to ensure thread-safe access to the log file. */
    std::map<Levels, LogLevel> _levels;        /**< Mapping of log levels to their respective LogLevel structures. */

    /**
     * @brief Retrieves the current date and time as a string.
     * @return A string representing the current date and time.
     */
    std::string getCurrentTime() const;
};
