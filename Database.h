#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <stack>
#include "Faculty.h"
#include "BSTGeneric.h"

using namespace std;

class DatabaseSimulation
{
	public:
		DatabaseSimulation(); //no-arg constructor
		~DatabaseSimulation(); //destructor
		void runSimulation();
		void displayMenu();
		void addNewStudent();
		void addNewStudentAsRollback(Student theStudent);//overloaded method. This is primarily used when doing the roll-back as a counter to the addNewStudent method
		void addNewFacultyMember();
		void addNewFacultyMemberAsRollback(Faculty theFaculty);//overloaded method. This is primarily used when doing the roll-back as a counter to the addNewStudent method
		void displayStudentInformationGivenID();
		void displayFacultyInformationGivenID();
		void displayAdvisorInformationGivenStudentID();
		void displayAdviseeInformationGivenFacultyID();
		void DeleteStudentGivenID();
		void DeleteStudentAsRollback(Student theStudent); //overloaded method. This is primarily used when doing the roll-back as a counter to the addNewStudent method
		void DeleteFacultyMemberGivenID();
		void DeleteFacultyMemberAsRollback(Faculty theFaculty); //overloaded method. This is primarily used when doing the roll-back as a counter to the addNewStudent method
		void changeStudentAdvisor();
		void removeAdviseeFromFacultyMember();
		//void writeTreesToDisk();
		bool setUpStudentDatabase();
		bool setUpFacultyDatabase();
		void clearStudentFile();
		void clearFacultyFile();
		void performRollBack();

	private:
		BST<Student> studentTable;
		BST<Faculty> facultyTable;
		string typeOfAction; //this variable is used to keep track of what kind of a change the user made to the database. It will be used in the rollback fuction.
		stack<Faculty> facultyMembersChanged;
		stack<Student> studentMembersChanged;
};

