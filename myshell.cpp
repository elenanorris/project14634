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
        cout << "myshell >>>";
        if (!getline(cin, inputLine)) {
            break; //error or end of file
        }

        if (inputLine == "exit") { //exits the shell if input is "exit"
            break; //leaves the shell
        }

        Param param; //makes a param object
        parseInput(inputLine.c_str(), param);
        if (inDebug) {
            param.printParams(); //prints using printParams in param.cpp
        }
    }

    return 0;
}