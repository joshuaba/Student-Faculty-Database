#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "FileIO.h"
#include "Student.h"

using namespace std;

class Faculty
{
	public:
		Faculty();
		Faculty(int id, string facultyName, string facultyLevel, string facultyDepartment);
		Faculty(int id); //overloaded constructor to initialize a faculty person object with only an id# (used to find/delete a faculty member by his/her ID)
		~Faculty();
		void setFacultyID(int facultyID);
		void setName(string theName);
		void setLevel(string theLevel);
		void setDepartment(string theDepartment);
		int getFacultyID();
		string getName();
		string getLevel();
		string getDepartment();
		int getAdvisee(int position);
		int getNumberOfAdvisees();
		void removeAdvisee(int studentID);//remove an advisee from the list of the faculty member's student advisees
		void assignStudent(int id);
		void getInformation();
		int getAdviseeByID(int ID);
		bool containsStudent(int studentID); //returns true if the faculty member has a student with studentID number assigned as an advisee. Returns false if not
		void writeInformationToDisk(string fileToWrite); //serialize the faculty objects of the BST

		friend const bool operator <(const Faculty& faculty1, const Faculty& faculty2);
		friend const bool operator >(const Faculty& faculty1, const Faculty& faculty2);
		friend const bool operator ==(const Faculty& faculty1, const Faculty& faculty2);
		friend const bool operator !=(const Faculty& faculty1, const Faculty& faculty2);

	private:
	  int FacultyID;
	  string name;
	  string level;
	  string department;
	  vector<int> studentIDS;
};
