/*
Author: Elijah Kenning
Course: COP4634
Assignment: Project 1 - Part 1
Professor: Prof. Zolfghari
*/

#ifndef PARAM_HPP
#define PARAM_HPP 

// max number of tokens that can be parsed on the command line
const int MAXARGS = 32;        // runtime constant


/*
The purpose of the Param class is to serve as a structure for parsed input strings from the 
command line that can then later be processed by myshell.cpp to be used for executing commands for
process management.
*/

class Param
{
private:
	char *inputRedirect; /* file name or NULL */
	char *outputRedirect; /* file name or NULL */
	int background; /* either 0 (false) or 1 (true) */
	int argumentCount; /* number of tokens in argument vector */
	char *argumentVector[MAXARGS]; /* array of strings */
		
public :
	Param(); // [1]
	Param(char* inRedir, char* outRedir, int bkGr, int argCount);
	~Param();

	Param(const Param &object);// Copy Constructor, takes the address of the object as its argument
	Param& operator=(const Param &object);// Copy Assignment Operator, takes content of object's ptr as its argument

	// Write down in notes why each one is needed
	char* getInputRedirect();
	void setInputRedirect(const char* newInput);

	char* getOutputRedirect();
	void setOutputRedirect(const char* newOutput);

	int getBackground();
	void setBackground(int bckGrVal);

	int getArgumentCount();
	void setArgumentCount(int argCountVal);

	char *getArgument(int index); 
	void setArgument(int index, const char* arg); 

	void printParams();
};

#endif 

/*
Sources:
[1] Rule of 3: https://www.geeksforgeeks.org/cpp/rule-of-three-in-cpp/
[2] Returning a pointer from a function: https://www.geeksforgeeks.org/cpp/how-to-return-a-pointer-from-a-function-in-cpp/
*/