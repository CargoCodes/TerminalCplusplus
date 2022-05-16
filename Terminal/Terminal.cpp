#include "Terminal.h"

string TerminalCpp::type(const string& command) {
    bool check = checkStore(command); // checks if the cuurent command is "cd"
    string output;

    if(check){
        string commands = this->oldCds_.join("; "); // joins all the stored commands, separating the with "; "

        output = exec(commands.c_str()); // executes the command and stores the output in the return variable
    } else {
        if(oldCds_.len() >= 1) { // if there is any stored command
            string commands = oldCds_.join("; "); // joins all the stored commands, separating the with "; "
            strList cmdList = adjustCommand(command); // splits the current command to check if it's "clear"

            if(cmdList[0] == "clear")  // if it's "clear", executes it normally
                system("clear");
            else { // otherwise adds the current command to the saved directory changes
                commands += command;
                output = exec(commands.c_str()); // executes the commands and stores the output in the return variable
            }
        } else {
            strList cmdList = adjustCommand(command);
            if(cmdList[0] == "clear") // if it's "clear", executes it normally
                system("clear");
            else // otherwise adds the current command to the saved directory changes
                output = exec(command.c_str()); // executes the commands and stores the output in the return variable
        }
    }
    if(this->output_) // if the user requires the output
        return output;
    else
        return "";
}

string TerminalCpp::exec(const char* cmd) {
    char buffer[2048];
    string output;

    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL)
            output += buffer;
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return output;
}
