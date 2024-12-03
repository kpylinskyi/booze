#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <ctime>

class Log {
public:
    Log(std::string message);
    
    virtual std::string to_string() const;
    virtual void print() const = 0;

protected:
    std::string _message;
    std::time_t _timestamp;

    const std::string _reset_color_code;
};

#endif