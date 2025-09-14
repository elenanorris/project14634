/*
Author: Elijah Kenning
Course: COP4634
Assignment: Project 1 - Part 1
Professor: Prof. Zolfghari
*/

#include "param.hpp"
#include <iostream>
#include <cstring>
using namespace std;

Param::Param() {
	inputRedirect = nullptr;
	outputRedirect = nullptr;
	background = 0;
	argumentCount = 0;
	for (int i = 0; i < MAXARGS; i++) {
		argumentVector[i] = nullptr;
	}
}

Param::Param(char* inRedir, char* outRedir, int bkGr, int argCount) {
	inputRedirect = inRedir ? strdup(inRedir) : nullptr ;
	if (inputRedirect) {
		strcpy(inputRedirect, inRedir);
	} 

	outputRedirect = outRedir ? strdup(outRedir) : nullptr;
	if (outputRedirect) {
		strcpy(outputRedirect, outRedir);
	}

	background = bkGr;
	argumentCount = argCount;

	for (int i = 0; i < MAXARGS; i++) {
		argumentVector[i] = nullptr;
	}
}

Param::~Param() { // [3]
	delete[] inputRedirect;
	delete[] outputRedirect;

	for (int i = 0; i < MAXARGS; i++) {
		delete[] argumentVector[i];
	}
}

// Deep Copy Constructor
Param::Param(const Param &object) {
	
	// Copying the inputRedirect
	if (object.inputRedirect) {
		inputRedirect = new char[strlen(object.inputRedirect) + 1]; // [1]
		strcpy(inputRedirect, object.inputRedirect); // [2]
	}
	else {
		inputRedirect = nullptr;
	}

	// Copying the outputRedirect
	if (object.outputRedirect) {
		outputRedirect = new char[strlen(object.outputRedirect) + 1];
		strcpy(outputRedirect, object.outputRedirect);
	}
	else {
		outputRedirect = nullptr;
	}

	// Copying the integer arguments
	background = object.background;
	argumentCount = object.argumentCount;

	// Copying the argumentVector
	for (int i = 0; i < MAXARGS; i++) {
		if (object.argumentVector[i]) {
			argumentVector[i] = new char[strlen(object.argumentVector[i]) + 1];
			strcpy(argumentVector[i], object.argumentVector[i]);
		}
		else {
			argumentVector[i] = nullptr;
		}
	}
}

// Copy Assignment Operator
Param & Param::operator=(const Param &object) { // [4]
	// cleans up old memory
	if (this != &object) { // avoids having a Param object accidentally delete its own attributes when we do not want it to
		delete[] inputRedirect;
		delete[] outputRedirect;
		for (int i = 0; i < MAXARGS; i++) {
			delete[] argumentVector[i];
		}
	}
	
	// Deep copy
	
	if (object.inputRedirect) {
		inputRedirect = new char[strlen(object.inputRedirect) + 1];
		strcpy(inputRedirect, object.inputRedirect);
	}
	else {
		inputRedirect = nullptr;
	}

	if (object.outputRedirect) {
		outputRedirect = new char[strlen(object.outputRedirect) + 1];
		strcpy(outputRedirect, object.outputRedirect);
	}
	else {
		outputRedirect = nullptr;
	}

	background = object.background;
	argumentCount = object.argumentCount;

	for (int i = 0; i < MAXARGS; i++) {
		if (object.argumentVector[i]) {
			argumentVector[i] = new char[strlen(object.argumentVector[i]) + 1];
			strcpy(argumentVector[i], object.argumentVector[i]);
		}
		else {
			argumentVector[i] = nullptr;
		}
	}

	return *this;
}



char* Param::getInputRedirect() {
	return inputRedirect; // returns the inputRedirect pointer
}

void Param::setInputRedirect(const char* newInput) {
	delete[] inputRedirect; // need to deallocate memory before adding new content to the memory address the pointer is pointing to
	if (newInput) { // if the newInput is not a nullptr
		inputRedirect = new char[strlen(newInput) + 1]; // assign a new char array
		strcpy(inputRedirect, newInput);
	}
	else {
		inputRedirect = nullptr;
	}
}

char* Param::getOutputRedirect() {
	return outputRedirect; 
}

void Param::setOutputRedirect(const char* newOutput) {
	delete[] outputRedirect;
	if (newOutput) {
		outputRedirect = new char[strlen(newOutput) + 1];
		strcpy(outputRedirect, newOutput);
	}
	else {
		outputRedirect = nullptr;
	}
}

int Param::getBackground() {
	return background;
}

void Param::setBackground(int bkGrVal) {
	if (bkGrVal == 0 || bkGrVal == 1) { // background is boolean (0 or 1) only
		background = bkGrVal;
	}
	return;
}

int Param::getArgumentCount() {
	return argumentCount;
}

void Param::setArgumentCount(int argCountVal) {
	argumentCount = argCountVal;
}

char* Param::getArgument(int index) {
	if (index >= 0 && index < MAXARGS) {
		return argumentVector[index]; 
	}
	return nullptr; // if index is invalid
}

void Param::setArgument(int index, const char* arg) {
	if (index >= 0 && index < MAXARGS) {
		delete[] argumentVector[index]; // need to delete or else overwrites any old strings -> memory leaks
		if (arg) {
			argumentVector[index] = new char[strlen(arg) + 1];
			strcpy(argumentVector[index], arg);
		}
		else {
			argumentVector[index] = nullptr;
		}
	}
}

void Param::printParams() {
	cout << "Input: " << (inputRedirect ? inputRedirect : "NULL") << endl; // [6]
	cout << "Output: " << (outputRedirect ? outputRedirect : "NULL") << endl;
	cout << "Background: " << background << endl;
	cout << "Arg count: " << argumentCount << endl;
	cout << "Arguments: ";
	for (int i = 0; i < argumentCount; i++) {
		if (argumentVector[i]) { // avoids printing null pointers
			cout << argumentVector[i] << endl;
		}
	}
}

/*
Sources:
[1] strlen(): https://www.geeksforgeeks.org/cpp/sizeof-vs-strlen-vs-size-in-cpp/

		strleng(array)

			- use strlen() since it accepts a pointer to an array 
			  as an argument.
			- Used in case of char array where the elements are not separated by a comma.
			- Is the predefined function of the char array.

[2] strcpy(): https://www.geeksforgeeks.org/cpp/cpp-strcpy/

		char* strcpy(char* dest, const char* src);

			dest = Pointer to the destination array where the content is to be copied
			src = string that will be copied

			- Used to copy one string to another string.
			- Return value: after copying the src string to dest string, 
			- returns a ptr to dest string

[3] Dynamic Array (De)Allocation: https://cppscripts.com/cpp-dynamic-allocation-array
[4] Copy Assignment Operator proper syntax: https://www.geeksforgeeks.org/cpp/assignment-operator-overloading-in-c/
[5] strdup(): https://www.geeksforgeeks.org/cpp/strdup-strdndup-functions-c/

		char *strdup(const char *s); 

			- used to duplicate a string
			- returns a pointer to a null-terminated byte string, which is a duplicate
			of the string pointed to by s.

			(eg)
			 char source[] = "GeeksForGeeks";

			// A copy of source is created dynamically
			// and pointer to copy is returned.
			char* target = strdup(source);

[6] Ternary Operators: https://www.w3schools.com/cpp/cpp_conditions_shorthand.asp

		variable = (condition) ? expressionTrue : expressionFalse;

			- Simplifies printing/value assignment since do not need if-else if-else chains
*/