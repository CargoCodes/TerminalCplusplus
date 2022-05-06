#ifndef TERMINALCPP_STRLIST_H
#define TERMINALCPP_STRLIST_H
#include <iostream>
#include <vector>

using namespace std;

class strList {
public:
    strList() = default;

    void append(const string& element) {
        this->mainVector.push_back(element);
    }

    const string& pop(int index){
        if (index < this->mainVector.size()) {
            string element = mainVector[index];
            vector<string> tmpVec;
            for (int i = 0; i < this->mainVector.size(); i++) {
                if (i != index)
                    tmpVec.push_back(this->mainVector[i]);
            }
            this->mainVector.clear();
            for(int i = 0; i < tmpVec.size(); i++)
                this->mainVector.push_back(tmpVec[i]);
            return element;
        } else {
            cerr << "Error: List index out of range. pop" << endl;
            throw IndexOutOfRange;
        }
    }

    const string& operator[](int index) const {
        if(index < this->mainVector.size())
            return this->mainVector[index];
        else {
            cerr << "Error: List index out of range. []" << endl;
            throw IndexOutOfRange;
    }

    int len() const {
        return this->mainVector.size();
    }

    string join(const string& separator) {
        string joinedString;
        for(int i = 0; i<this->mainVector.size(); i++) {
            joinedString += this->mainVector[i];
            joinedString += separator;
        }
        joinedString += this->mainVector[this->mainVector.size()];
        return joinedString;
    }

    void print() {
        for(int i = 0; i < this->mainVector.size(); i++)
            cout << mainVector[i];
        cout << endl;
    }

    void clear() {
      this->mainVector.clear();
    }

private:
    vector<string> mainVector;

    std::exception IndexOutOfRange;
};

#endif //TERMINALCPP_STRLIST_H
