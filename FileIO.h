#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

class FileIO
{
	public:
		FileIO(); //no-arg constructor
		FileIO(string fileToBeProcessed); //overloaded constructor
		~FileIO(); //destructor
		void writeToFile(string whatToWrite);
		void writeToFile(int whatToWrite);
		void writeToFile(double whatToWrite);
		void readFromFile(string fileFromWhichToRead);

	private:
		ofstream outputStream;
		ifstream inputStream;
		//fill in later
};
