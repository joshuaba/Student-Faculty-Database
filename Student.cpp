#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "Student.h"

using namespace std;

Student::Student()
{
	studentID = 0;
	name = "";
	level = "";
	major = "";
	GPA = 0.00;
	AdvisorField = 0;
}

Student::Student(int id, string theName, string studentLevel, string studentMajor, double theGPA, int theAdvisorField)
{
	studentID = id;
	name = theName;
	level = studentLevel;
	major = studentMajor;
	GPA = theGPA;
	AdvisorField = theAdvisorField;
}

Student::Student(int id)
{
	studentID = id; //set the studentID number to the id number argument passed in
	name = "";
	level = "";
	major = "";
	GPA = 0.00;
	AdvisorField = 0;
}

Student::~Student()
{
	//do nothing. No dynamically allocated memory
}

void Student::setStudentID(int id)
{
	studentID = id;
}

void Student::setName(string theName)
{
	name = theName;
}

void Student::setLevel(string theLevel)
{
	level = theLevel;
}

void Student::setMajor(string theMajor)
{
	major = theMajor;
}

void Student::setGPA(int theGPA)
{
	GPA = theGPA;
}

void Student::setAdvisor(int advisorID)
{
	AdvisorField = advisorID;
}

int Student::getAdvisor()
{
	return AdvisorField;
}

int Student::getStudentByID()
{
	return studentID;
}

void Student::getInformation()
{
	cout << endl
		 << "Name: " << name << endl
		 << "Student ID: " << studentID << endl
		 << "Level: " << level << endl
		 << "Major: " << major << endl
		 << "GPA: " << GPA << endl
		 << "Advisor Faculty ID: " << AdvisorField << endl;
	cout << endl;
}

void Student::writeInformationToDisk(string fileToWrite)
{
	ofstream fileOutput; //the output stream so we can write the information out to disk

	fileOutput.open(fileToWrite, ios::app);

	fileOutput << name <<',' << studentID << ',' << level << ',' << major << ',' << GPA << ',' << AdvisorField << ','; //output the faculty information
	fileOutput << endl; //return to the next line

	/*
	FileIO fileOutput(fileToWrite);
	fileOutput.writeToFile(name);
	fileOutput.writeToFile(studentID);
	fileOutput.writeToFile(level);
	fileOutput.writeToFile(major);
	fileOutput.writeToFile(GPA);
	fileOutput.writeToFile(AdvisorField);
	*/
	fileOutput.close();
}

const bool operator <(const Student& student1, const Student& student2)
{
	return (student1.studentID < student2.studentID);
}

const bool operator >(const Student& student1, const Student& student2)
{
	return (student1.studentID > student2.studentID);
}

const bool operator ==(const Student& student1, const Student& student2)
{
	return (student1.studentID == student2.studentID);
}

const bool operator !=(const Student& student1, const Student& student2)
{
	return(student1.studentID != student2.studentID);
}
