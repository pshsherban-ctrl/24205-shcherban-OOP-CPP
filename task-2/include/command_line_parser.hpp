#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <string>

class CommandLineParser {
public:
    struct Options {
        std::string input_file;
        std::string output_file;
        int iterations = 0;
        bool offline_mode = false;
        bool help_requested = false;
        bool error = false;
        std::string error_message;
    };
    
    static Options parse(int argc, char* argv[]);
    static void show_usage(const std::string& program_name);
    
private:
    static std::pair<std::string, std::string> split_option(const std::string& option);
};

#endif 