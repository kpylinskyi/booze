#ifndef CMD_H
#define CMD_H

#include <string>
#include <future>

/**
 * @struct CommandResult
 * @brief Represents the result of a system command execution.
 */
struct CmdResult {
    int exit_code;        /**< The exit code returned by the command. */
    std::string command;  /**< The command that was executed. */
    std::string output;   /**< Standard output of the command. */
    std::string error;    /**< Standard error output of the command, if any. */
};

class Cmd {
  public:
    Cmd(const std::string& command);

    virtual std::future<const CmdResult&> execute();

  protected:
    std::string command_;
    CmdResult result_;
};


#endif //CMD_H
