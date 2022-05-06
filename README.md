# TerminalCplusplus

Library that allows you to call terminal commands in C++ whithout discarding director changes (unlike system() command does).

`Usage:`

    #include "Terminal.h"
    
Create a terminal object. Pass true or false sa argument if you want (or not) to have back the output.
  
    Terminal term = Terminal(true);
    
Only one straight-forward method: type. Pass inside it the command you want to be executed.  

    string output = term.type("pwd");
    
    // in this case, it stores the current path in "output"
    
    
To clear the memory of directory changes, returning back to the project folder:

    term.clear()
    
To change the output return state (if false, there will be an empty string as return value):

    term.setOutput()
