#include <iostream>
#include <string>
#include <cstdlib>
#include "FileIO.h"

using namespace std;

FileIO::FileIO()
{
	//do nothing
}

FileIO::FileIO(string fileToBeProcessed) //overloaded constructor. Connects the output stream to the file passed in as the argument
{
	outputStream.open(fileToBeProcessed);
}

FileIO::~FileIO()
{
	inputStream.close();
	outputStream.close();
	//no memory dynamically allocated
}

void FileIO::writeToFile(string whatToWrite)
{
	outputStream << whatToWrite << ",";
}

void FileIO::writeToFile(int whatToWrite)
{
	outputStream<< whatToWrite << ",";
}

void FileIO::writeToFile(double whatToWrite)
{
	outputStream << whatToWrite << ",";
}

void FileIO::readFromFile(string fileFromWhichToRead)
{
	inputStream.open(fileFromWhichToRead);
}




