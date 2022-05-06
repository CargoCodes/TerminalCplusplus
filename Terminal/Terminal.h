#ifndef TERMINALCPP_TERMINAL_H
#define TERMINALCPP_TERMINAL_H

#include <iostream>
#include <vector>
#include "strList.h"

using namespace std;

class Terminal {
public:

    explicit TerminalCpp(bool output=false) : output_(output) {}

    string type(const string& command);

    void clear() {
        this->oldCds_.clear();
    }

    void setOutpt(bool state) {
        this->output_ = state;
    }

private:

    bool output_;

    strList oldCds_;

    bool checkStore(const string& command) {
        strList cmdList = adjustCommand(command);
        if (cmdList[0] == "cd") {
            this->oldCds_.append(command);
            return true;
        }
        return false;
    }

    static strList split(string str, char separator) {
        strList list;
        while(str.find(separator) < str.length()){
            list.append(str.substr(0, str.find(separator)));
            str = str.substr(str.find(separator)+1, str.length());
        }
        list.append(str);
        return list;
    }

    static strList adjustCommand(const string& command) {
        strList commandList = split(command, ' ');
        for(int i = 0; i < commandList.len(); i++){
            if(commandList[i] == " " or commandList[i].empty())
                commandList.pop(i);
        }
        return commandList;
    }

    static string exec(const char* cmd);

};

#endif //TERMINALCPP_TERMINAL_H
