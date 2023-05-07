#makefile

CC = g++

all: server

server: server.o ExpressionTree.o BinaryTree.o
	g++ -o server server.o ExpressionTree.o BinaryTree.o

server.o: server.cpp ExpressionTree.h
	g++ -c -o server.o server.cpp

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	g++ -c -o BinaryTree.o BinaryTree.cpp

ExpressionTree.o: ExpressionTree.cpp BinaryTree.h
	g++ -c -o ExpressionTree.o ExpressionTree.cpp

clean:
	rm *.o server client
