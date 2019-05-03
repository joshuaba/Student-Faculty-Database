#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include "Faculty.h"

using namespace std;

Faculty::Faculty()
{
	FacultyID = 0;
	name = "";
	level = "";
	department = "";
}

Faculty::Faculty(int id, string facultyName, string facultyLevel, string facultyDepartment)
{
	name = facultyName;
	FacultyID = id;
	level = facultyLevel;
	department = facultyDepartment;
}

Faculty::Faculty(int id)
{
	name = "";
	FacultyID = id;
	level = "";
	department = "";
}

Faculty::~Faculty()
{
	FacultyID = 0;
	name = "";
	level = "";
	department = "";
}

void Faculty::setFacultyID(int facultyID)
{
	FacultyID = facultyID;
}

int Faculty::getFacultyID()
{
	return FacultyID;
}

void Faculty::setName(string theName)
{
	name = theName;
}

string Faculty::getName()
{
	return name;
}

void Faculty::setLevel(string theLevel)
{
	level = theLevel;
}

string Faculty::getLevel()
{
	return level;
}

void Faculty::setDepartment(string theDepartment)
{
	department = theDepartment;
}

string Faculty::getDepartment()
{
	return department;
}

void Faculty::assignStudent(int id)
{
	studentIDS.push_back(id);
	cout << "Added student" << endl;
}

int Faculty::getAdviseeByID(int ID)
{
	return studentIDS[ID];
}

void Faculty::getInformation()
{
	cout << endl; //make output look nice
	cout << "Faculty name: " << name << endl;
	cout << "Faculty department: " << department << endl;
	cout << "Faculty level: " << level << endl;
	cout << "Faculty ID#: " << FacultyID << endl;
	cout << "Number of advisees: " << studentIDS.size() << endl;
	cout << endl; //make the output look nicer
}

void Faculty::removeAdvisee(int studentID)
{
	for (int i = 0; i < studentIDS.size(); ++i)
	{
		if(studentIDS[i] == studentID)
			studentIDS.erase(studentIDS.begin() + i); //delete the student with student ID# studentID from the list of student advisees
	}
}

int Faculty::getAdvisee(int position)
{
	return studentIDS[position];
}

int Faculty::getNumberOfAdvisees()
{
	return studentIDS.size();
}

bool Faculty::containsStudent(int studentID)
{
	for (int i = 0; i < studentIDS.size(); ++i)
	{
		if(studentIDS[i] == studentID)
			return true;
	}

	return false;
}

void Faculty::writeInformationToDisk(string fileToWrite)
{
	ofstream fileOutput; //the output stream so we can write the information out to disk

	fileOutput.open(fileToWrite, ios::app);

	fileOutput << name <<',' << FacultyID << ',' << level << ',' << department << ','; //output the faculty information
	for (int i = 0; i < studentIDS.size(); ++i)
		fileOutput << studentIDS[i] << ','; //output the advisee IDs of the faculty member
	fileOutput << endl; //return to the next line

	/*
	fileOutput.writeToFile(name);
	fileOutput.writeToFile(level);
	fileOutput.writeToFile(department);
	fileOutput.writeToFile(FacultyID);
	for (int i = 0; i < studentIDS.size(); ++i)
		fileOutput.writeToFile(studentIDS[i]);
	*/

	fileOutput.close();
}

const bool operator <(const Faculty& faculty1, const Faculty& faculty2)
{
	return (faculty1.FacultyID < faculty2.FacultyID);
}

const bool operator >(const Faculty& faculty1, const Faculty& faculty2)
{
	return (faculty1.FacultyID > faculty2.FacultyID);
}

const bool operator ==(const Faculty& faculty1, const Faculty& faculty2)
{
	return (faculty1.FacultyID == faculty2.FacultyID);
}

const bool operator !=(const Faculty& faculty1, const Faculty& faculty2)
{
	return (faculty1.FacultyID != faculty2.FacultyID);
}
