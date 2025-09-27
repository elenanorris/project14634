#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h> // for fork(), getpid(), _Exit() - can only be executed on UNIX systems
#include <sys/types.h> // for pid_t
#include <sys/wait.h> // for waitpid()
#include <cstdio> // for freopen()
#include <vector>
#include "param.hpp"
#include "parse.hpp"
using namespace std;

/*
This is a simple myshell that takes the input and
parses it and prints it.
*/

int main(int argumentCount, char* arguments[]) {
    bool inDebug = false;
    if (argumentCount > 1 && string(arguments[1]) == "-Debug") { //checks for the flag -Debug, used for outputting values in Param object
        inDebug = true;
    }

    string inputLine;
    while (true) {
        cout << "myshell >>>"; //gets the input
        if (!getline(cin, inputLine)) {
            break; //error or end of file, program exits
        }

        if (inputLine == "exit") { //exits the shell if input is "exit"
            while (waitpid(-1, nullptr, WNOHANG) > 0); // reaps any finished child processes to avoid zombies
            break; // breaks while loop to exit shell
        }

        Param param; //makes a param object
        parseInput(inputLine.c_str(), param); // parses input from command line to store in the Param object's argumentVector vector
        if (inDebug) {
            param.printParams(); //prints using printParams in param.cpp
        }

        if (param.getArgumentCount() == 0) { // no command is ran, so continues the loop
            continue;
        }

        pid_t pid = fork(); // creates a child process

        if (pid < 0) { // fork() fails to create a child process
            cerr << "Fork failure" << endl;
            continue;
        }


        if (pid == 0) { // child process branch

            if (param.getInputRedirect()) {
                if (!freopen(param.getInputRedirect(), "r", stdin)) { // if the process cannot read the file, it cannot redirect input  
                    cerr << "Input redirect failure" << endl;
                    _Exit(1); // program is terminated immediately without performing any cleanup tasks [2]
                }
            }

            if (param.getOutputRedirect()) {
                if (!freopen(param.getOutputRedirect(), "w", stdout)) { // sees if it can write the file to another file as an output
                    cerr << "Output redirect failure" << endl;
                    _Exit(1); // _Exit() avoids flushing parent's stdio buffers [2]
                }
            }

            //space for the child process to execute the commands baesd on "param"'s "argumentVector"'s elements

               // building argv for execvp() [1]
            int argc = param.getArgumentCount();
            if (argc == 0) {
                _Exit(0); // nothing to do [2]
            }

            // "argv" vector holds pointers to the "argumentVector" vector's elements,
            // in addition to ending the "argv" vector with a final nullptr terminator
            vector<char*> argv;
            argv.reserve(argc + 1); // [3] used for reserving space for a dynamic vector if know the maximum number of elements
            for (int i = 0; i < argc; i++) {
                char* arg = param.getArgument(i); // "param" object owns the memory
                argv.push_back(arg);
            }
            argv.push_back(nullptr); // "argv" MUST BE NULL-TERMINATED

            // ensures argv[0] exists
            if (!argv[0]) {
                cerr << "argv[0] does not exist" << endl;
                _Exit(0);
            }

            // executing the UNIX command
            if (execvp(argv[0], argv.data()) == -1) { // [4] .data() returns a pointer to the memory array used internally by the "argv" vector to store its owned elements
                cerr << "execvp failed" < endl;
                _Exit(1); // execvp() failed, so immediately kill child made by "fork()" with error code
            }
            // otherwise, execvp() executes the UNIX command, replaces child node, and code below never runs

        }

        else {
            if (!param.getBackground()) { // if the command is not a background command, then the parent waits for children to finish
                waitpid(pid, nullptr, 0);
            }
            else {
                cout << "Background process pid " << pid << endl;
            }

            while (waitpid(-1, nullptr, WNOHANG) > 0); // parent processes loops this to reap any other finished children processes
        }

    }

    return 0;
}
/*
Sources:
[1] execvp() in C/C++: https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus
[2] exit() vs. _exit(): https://www.geeksforgeeks.org/cpp/exit-vs-_exit-c-cpp/
                        https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/exit-exit-exit?view=msvc-170
    * call _exit() after fork() and before execvp() if exiting due to an error
        - _exit() does not execute

 [3] .reserve() method for C++ vectors: https://www.geeksforgeeks.org/cpp/using-stdvectorreserve-whenever-possible/
 [4] vector.data() method for C++ vector: https://cplusplus.com/reference/vector/vector/data/
 */