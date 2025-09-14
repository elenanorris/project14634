/*
Elena Norris, COP4634
Project 1 - Part 1
Zolfghari
*/
#include <iostream>
#include <cstring> //this allows you to use strcmp and strtok
#include <cstdlib>
#include "parse.hpp" //include header file
#include "param.hpp" //include param header file

using namespace std;

//main function to parse the input and put it into the Parameter objects
void parseInput(const char *input, Param &param) {
    char *inputSave = strdup(input);
    if (!inputSave) { //if you can't save the input, it sends an error
        cerr << "Memory allocation failed for input" << endl;
        return;
    }

    param.setInputRedirect(nullptr); //clears input file redirection
    param.setOutputRedirect(nullptr); //clears output file redirection
    param.setBackground(0); //reseting the background to make it 0
    param.setArgumentCount(0); //reseting the argument count to make it 0

    int argumentCount = 0;
    char *tokenForInput = strtok(inputSave, " \t\n"); //makes the input a token

    while (tokenForInput != nullptr && argumentCount < MAXARGS) {
        if (tokenForInput[0] == '<') { //allows for a space between > and whatever the filename is
            if (strlen(tokenForInput) > 1) {
                param.setInputRedirect(tokenForInput + 1);
            }
            else {
                tokenForInput = strtok(nullptr, " \t\n");
                if (tokenForInput == nullptr) {
                    cerr << "Error, there is not an input file after the '<'" << endl;
                break;
                }
                param.setInputRedirect(tokenForInput);
            }
            
        }
        else if (tokenForInput[0] == '>') {
            if (strlen(tokenForInput) > 1) { //allows for a space between > and whatever the filename is
                param.setOutputRedirect(tokenForInput + 1);
            }
            else {
                tokenForInput = strtok(nullptr, " \t\n");
                if (tokenForInput == nullptr) {
                    cerr << "Error, there is not an output file after the '>'" << endl;
                    break;
                }
                param.setOutputRedirect(tokenForInput); //sets the redirection for after <
            }
            
        }
        else if (strcmp(tokenForInput, "&") == 0) { //if the token is &, it makes the background 1
            param.setBackground(1);
        }

        else {
            param.setArgument(argumentCount, tokenForInput); //sets the parameter arguments
            argumentCount++;
        }

        tokenForInput = strtok(nullptr, " \t\n"); //goes and gets the next token
    }

    param.setArgumentCount(argumentCount);
    free(inputSave); //gets rid of the saved input
}

//Source, understand strcmp https://www.geeksforgeeks.org/c/strcmp-in-c/
//Source, understand cerr more clearly  https://www.programiz.com/cpp-programming/library-function/iostream/cerr