
myshell: myshell.cpp param.cpp parse.cpp
	g++ -std=c++14 -Wall -o myshell myshell.cpp param.cpp parse.cpp
clean:
	$(RM) a.out *.o *.gch *.dSYM myshell