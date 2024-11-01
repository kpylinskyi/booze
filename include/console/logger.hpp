#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <map>

enum Levels { INFO, WARNING, ERROR };

struct LogLevel {
    std::string Name;
    std::string Color;
};

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void info(const std::string& message) const;
    void warning(const std::string& message) const;
    void error(const std::string& message) const;
private:
    std::ofstream _log_file;
    std::mutex _mutex;
    std::map<Levels, LogLevel> _levels;

    std::string getCurrentTime() const;
};