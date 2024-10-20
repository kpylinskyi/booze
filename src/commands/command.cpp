#include "commands/command.hpp"

std::string Command::execute(){
    std::ostringstream output;
    
    try{
        bp::ipstream pipe_stream;
        bp::ipstream err_stream;
        bp::child process(cmd, bp::std_out > pipe_stream, bp::std_err > err_stream);

        std::string line;

        while (pipe_stream && std::getline(pipe_stream, line)) {
            output << line << std::endl;
        }

        while (err_stream && std::getline(err_stream, line )) {
            output << "stderr: " << line << std::endl;
        }

        process.wait();
        if (process.exit_code() != 0){
            output << "Command failed with exit code: " << process.exit_code() << std::endl;
        }
    } catch (const std::exception& ex) {
        output << "Errorr executing process " << ex.what() << std::endl; 
    }
    return output.str();
}