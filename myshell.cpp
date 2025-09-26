#include <iostream>
#include <string>
#include <cstring>
#include "param.hpp"
#include "parse.hpp"

using namespace std; //This is a simple myshell that takes the input and parses it and prints it
int main(int argumentCount, char *arguments[]) {
    bool inDebug = false;
    if (argumentCount > 1 && string(arguments[1]) == "-Debug") { //checks for the flag -Debug
        inDebug = true;
    }

    string inputLine;
    while(true) {
        cout << "myshell >>>"; //gets the input
        if (!getline(cin, inputLine)) {
            break; //error or end of file
        }

        if (inputLine == "exit") { //exits the shell if input is "exit"
            while (waitpid(-1, nullptr, WNOHANG) >0);
            break;
        }

        Param param; //makes a param object
        parseInput(inputLine.c_str(), param);
        if (inDebug) {
            param.printParams(); //prints using printParams in param.cpp
        }

        if (param.getArgumentCount() == 0) {
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            cerr << "Fork failure" << endl;
            continue;
        }

        else if (pid == 0) {
            if (param.getInputRedirect()) {
                if (!freopen(param.getInputRedirect(), "r", stdin)) {
                    cerr << "Input redirect failure" << endl;
                    exit(1);
                }
            }

            if (param.getOutputRedirect()) {
                if (!freopen(param.getOutputRedirect(), "r", stdin)) {
                    cerr << "Output redirect failure" << endl;
                    exit(1);
                }
            }

            //space for executing the commands
        }

        else {
            if (!param.getBackground()) {
                waitpid(pid, nullptr, 0);
            }
            else {
                cout << "Background process pid " << pid << endl;
            }

            while (waitpid(-1, nullptr, WNOHANG) > 0);
        }
 
    }    
    
    return 0;
}