The purpose of project I is to accept input from the user and parse the string into tokens. After the tokens are created, it will then store them in the appropriate attributes of the Param class. It should print the contents of the fields only when shell is started with debug. You enter the shell using ./myshell -Debug. Inside the shell you provide information and commands as the user

parse.hpp and param.hpp are the header files for parse.cpp and param.cpp

The makefile has what is necessary to run the program.

Parse.cpp takes in user provided information and parses it into the tokens in the param class. It also increments argumentCount and resets it as needed.

Param.cpp copies the information that is tokenized and sets them as arguments in order to print in printParams().

MyShell.cpp allows for input of information and uses Param.cpp and Parse.cpp to take it and save it. The execvp() and execv() functions takes in the arguments passed into them as UNIX commands that can execute in the Linux environment the myshell executable is executed in. 