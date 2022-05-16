# TerminalCplusplus

### Library that allows to call terminal commands in C++ whithout discarding directory changes (unlike built-in system() method does).

## `Usage:`

    #include "Terminal.h"
    
Create a terminal object. Pass true or false sa argument if you want (or not) to have back the output.
  
    Terminal term = Terminal(true);
    
One straight-forward method: type. Pass inside it the command you want to be executed.  

    std::string output = term.type("pwd");
    
    // in this case, it stores the current path in "output" variable
    
    
To clear the memory of directory changes, returning back to the project folder:

    term.clear();
    
To change the output return state (if false, there will be an empty string as return value):

    term.setOutput(false);

To remove the last directory change (useful in case of mistake, or in case the directory gets removed):
    
    term.removeLastCD();

## `Example:`

Imagine a basic directory tree:

    - home
        - c++
            - project1
                - main.cpp
            - project2
                - main2.cpp
        - python
            - project3
            
This is the difference between TerminalCplusplus and system(), receiving the same exact instructions:

    // /home/c++/project1/main.cpp
    #include <iostream>
    #include "Terminal.h"
    
    Terminal term = Terminal(true);
    
    string path = term.type("pwd");
    std::cout << path << std::endl;
    // output: /home/c++/project1
    
    term.type("cd ..");
    std::cout << term.type("ls") << std::endl;
    /* output:  project1
                project2 */
                
    term.type("cd ..");
    term.type("cd python");
    std::cout << term.type("pwd") << std::endl;
    // output: /home/python
    
    term.clear();
    std::cout << term.type("pwd") << std::endl;
    
    -------------------------------------------
    // /home/c++/project2/main2.cpp
    #include <iostream>
    
    system("pwd"); // automatically prints the output
    // output: /home/c++/project2
    
    system("cd ..");
    system("ls");
    // output: main2.cpp
    
    system("cd ..");
    system("cd python"); //Error--> cd: python: No such file or directory
    system("pwd");
    // output: /home/c++/project2
    
The main differences between TerminalCplusplus and system(): \
    - Terminal allows multiple direcotry changes \
    - Terminal allows to store the output in a variable \
    - Terminal lets you chose if return the output or not \
    - system() prints its output always, in any case \
    - system() doesn't allow to store the output \
    - system() doesn't allow multiple directory change
