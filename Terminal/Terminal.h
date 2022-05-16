#ifndef TERMINALCPP_TERMINAL_H
#define TERMINALCPP_TERMINAL_H

#include <iostream>
#include <vector>

using namespace std;

class TerminalCpp {
public:

    explicit TerminalCpp(bool output=false) : output_(output) {}

    string type(const string& command);

    void clear() {
        this->oldCds_.clear();
    }

    void setOutpt(bool state) {
        this->output_ = state;
    }

    void removeLastCD(){
        this->oldCds_.pop(this->oldCds_.len()-1);
    }

private:

    class strList { // nested class for string list
    public:
        strList() = default;

        void append(const string& element) { // adds the element at teh bottom of the list
            this->mainVector.push_back(element);
        }

        const string& pop(int index) { // removes the element at the given index and returns it
            if (index < this->mainVector.size()) { // validity index check
                string element = mainVector[index]; // gets the element at the given index
                vector<string> tmpVec;

                for (int i = 0; i < this->mainVector.size(); i++) { // scans the element in the list
                    if (i != index) // if teh index is different froom the given one
                        tmpVec.push_back(this->mainVector[i]); // stores the element in the temporary list
                }

                this->mainVector.clear(); // clears the list

                for(const auto & i : tmpVec) // puts back the elements in the list
                    this->mainVector.push_back(i);

                return element;
            } else {
                cerr << "Error: List index out of range." << endl;
                throw IndexOutOfRange;
            }
        }

        const string& operator[](int index) const { // gets back the element at the given index, if not out of range
            if(index < this->mainVector.size())
                return this->mainVector[index];
            else {
                cerr << "Error: List index out of range. []" << endl;
                throw IndexOutOfRange;
            }
        }

        int len() const { // returns the length of the list
            return this->mainVector.size();
        }

        string join(const string& separator) { // joins the elements in the list, separated by the specified separator
            string joinedString;
            for(auto & i : this->mainVector) {
                joinedString += i + separator;
            }
            joinedString += this->mainVector[this->mainVector.size()];
            return joinedString;
        }

        void clear() { // clears the list
            this->mainVector.clear();
        }

    private:
        vector<string> mainVector;

        std::exception IndexOutOfRange;
    };

    bool output_;

    strList oldCds_;

    bool checkStore(const string& command) {
        strList cmdList = adjustCommand(command); // adjusts the command
        if (cmdList[0] == "cd") { // if the command is "cd"
            this->oldCds_.append(command); // adds to the list the command
            return true;
        }
        return false;
    }

    static strList split(string str, char separator) { // splits the string into a list, basing on the given separator
        strList list;
        while(str.find(separator) < str.length()){ // while the separator is still in the string
            list.append(str.substr(0, str.find(separator))); // add to the list an element
            str = str.substr(str.find(separator)+1, str.length()); // changes the string, removing the processed parts
        }
        list.append(str); // adds the final part
        return list;
    }

    static strList adjustCommand(const string& command) {
        strList commandList = split(command, ' '); // splits the command in a list
        for(int i = 0; i < commandList.len(); i++){ // scans the list
            if(commandList[i] == " " or commandList[i].empty()) // if the command is empty
                commandList.pop(i); // removes the empty element from the list
        }
        return commandList;
    }

    static string exec(const char* cmd);
};

#endif //TERMINALCPP_TERMINAL_H
