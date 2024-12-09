#include "core/cmd/cmd.h"

#include <boost/process.hpp>
#include <future>
#include <sstream>

namespace bp = boost::process;

Cmd::Cmd(const std::string& command) : command_(command), result_({0, command, "", ""}) {}

std::future<const CmdResult&> Cmd::execute() {
    return std::async(std::launch::async, [this]() -> const CmdResult& {
        std::ostringstream output;
        std::ostringstream error;

        try {
            bp::ipstream pipe_stream;
            bp::ipstream err_stream;
            bp::child process(command_, bp::std_out > pipe_stream, bp::std_err > err_stream);

            std::string line;
            while (std::getline(pipe_stream, line)) output << line << '\n';
            while (std::getline(err_stream, line)) error << line << '\n';

            process.wait();
            result_.exit_code = process.exit_code();
            result_.output = output.str();
            result_.error = error.str();
        } catch (const std::exception& ex) {
            result_.exit_code = -1;
            result_.error = ex.what();
        }

        return result_;
    });
}
