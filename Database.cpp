#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#include "Database.h"

using namespace std;

DatabaseSimulation::DatabaseSimulation()
{
	BST<Student> studentTable;
	BST<Faculty> facultyTable;
}

DatabaseSimulation::~DatabaseSimulation()
{
	//do nothing. No memory dynamically allocated in this class
}

void DatabaseSimulation::runSimulation()
{
	cout << endl; //formatting
	cout << "Welcome to the Chapman University student-faculty database" << endl
	     << "Checking for the existence of pre-existing student and faculty tables. Stand-by" << endl;
	cout << endl;

	ifstream inputStreamCheckerFaculty;
	ifstream inputStreamCheckerStudent;

	try
	{

		inputStreamCheckerFaculty.open("masterFaculty.txt");
		inputStreamCheckerStudent.open("masterStudent.txt");
		if(!inputStreamCheckerFaculty.good() && inputStreamCheckerStudent.good())
			throw 1;
	}

	catch(int e)
	{
		cout << "Cannot have student database without faculty database. Ending program" << endl;
		exit(1);
	}


	inputStreamCheckerFaculty.close(); //close the inputstream. It's only purpose was to check to see if the requested files exist
	inputStreamCheckerStudent.close(); //close the inputstream. It's only purpose was to check to see if the requested files exist

	setUpFacultyDatabase();
	setUpStudentDatabase();

	displayMenu();

	while(true)
	{
		cout << endl; //make the format look nice
		cout << "Type the number of the option you would like to perform" << endl;
		int userInput;
		cin >> userInput;

		switch(userInput)
		{
			case 1:
				cout << endl;
				studentTable.printTree();
				break;
			case 2:
				cout << endl;
				facultyTable.printTree();
				break;
			case 3:
				displayStudentInformationGivenID();
				break;
			case 4:
				displayFacultyInformationGivenID();
				break;
			case 5:
				displayAdvisorInformationGivenStudentID();
				break;
			case 6:
				displayAdviseeInformationGivenFacultyID();
				break;
			case 7:
				addNewStudent();
				typeOfAction = "Added student";
				break;
			case 8:
				DeleteStudentGivenID();
				typeOfAction = "Deleted student";
				break;
			case 9:
				addNewFacultyMember();
				typeOfAction = "Added faculty";
				break;
			case 10:
				DeleteFacultyMemberGivenID();
				typeOfAction = "Deleted faculty";
				break;
			case 11:
				changeStudentAdvisor();
				break;
			case 12:
				removeAdviseeFromFacultyMember();
				break;
			case 13:
				//fill in later
				performRollBack();
				break;
			case 14:
				clearStudentFile(); //clear the student file once we have what we need from it so we don't write redundant material to it
				clearFacultyFile(); //clear the faculty file once we have what we need so we don't write redundant material to it

				cout << "Thank You!" << endl;

				studentTable.printTreeToFile("masterStudent.txt");
				facultyTable.printTreeToFile("masterFaculty.txt");

				cout << "Contents written to disk" << endl;
				exit(0);
			default:
				cerr << "Input not recognized. Ending program" << endl;
				exit(1);
		}
	}
}

bool DatabaseSimulation::setUpStudentDatabase() //the method to initialize the studentTable with appropriate values read in from masterStudent.txt
{
	try
	{
		ifstream inputStream;
		inputStream.open("masterStudent.txt");

		if(!inputStream.good())
			throw 10;

		while(!inputStream.eof()) //continue to loop while we have not reached the end of the file
		{
			string studentInformation;
			getline(inputStream, studentInformation);

			if(studentInformation == "")
				return false;

			char delimeter = ',';
			string studentName, studentLevel, studentMajor;
			int studentID, studentAdvisorID;
			double studentGPA;


			studentName = studentInformation.substr(0, studentInformation.find(delimeter));
			studentInformation.erase(0, studentInformation.find(delimeter)+1);

			studentID = stoi(studentInformation.substr(0, studentInformation.find(delimeter)));
			studentInformation.erase(0, studentInformation.find(delimeter)+1);

			studentLevel = studentInformation.substr(0, studentInformation.find(delimeter));
			studentInformation.erase(0, studentInformation.find(delimeter)+1);

			studentMajor = studentInformation.substr(0, studentInformation.find(delimeter));
			studentInformation.erase(0, studentInformation.find(delimeter)+1);

			studentGPA = stod(studentInformation.substr(0, studentInformation.find(delimeter)));
			studentInformation.erase(0, studentInformation.find(delimeter)+1);

			studentAdvisorID = stoi(studentInformation.substr(0, studentInformation.find(delimeter)));
			studentInformation.erase(0, studentInformation.find(delimeter)+1);

			cout << studentName << " "
				 << studentID << " "
				 << studentLevel << " "
				 << studentMajor << " "
				 << studentGPA   << " "
				 << studentAdvisorID << " " << endl;

			Student studentToAdd(studentID, studentName, studentLevel, studentMajor, studentGPA, studentAdvisorID);
			studentTable.insert(studentToAdd);
		}
		inputStream.close();
	}
	catch(int e)
	{
		cout << "No student input file found. Establishing brand new database" << endl;
		return false;
	}
	return true;
}

bool DatabaseSimulation::setUpFacultyDatabase()
{
	try
	{
		ifstream inputStream;
		inputStream.open("masterFaculty.txt"); //connect the inputStream to masterFaculty.txt
		if(!inputStream.good())
			throw 10;
		if(inputStream.eof())
			return false;
		while(!inputStream.eof()) //continue to loop while we have not reached the end of the file
		{
			string facultyInformation;
			getline(inputStream, facultyInformation);

			if (facultyInformation == "")
				return false;

			char delimeter = ',';
			string facultyName, facultyLevel, facultyDepartment;
			int facultyID;

			facultyName = facultyInformation.substr(0, facultyInformation.find(delimeter));
			facultyInformation.erase(0, facultyInformation.find(delimeter)+1);

			facultyID = stoi(facultyInformation.substr(0, facultyInformation.find(delimeter)));
			facultyInformation.erase(0, facultyInformation.find(delimeter)+1);

			facultyLevel = facultyInformation.substr(0, facultyInformation.find(delimeter));
			facultyInformation.erase(0, facultyInformation.find(delimeter)+1);

			facultyDepartment = facultyInformation.substr(0, facultyInformation.find(delimeter));
			facultyInformation.erase(0, facultyInformation.find(delimeter)+1);

			Faculty facultyToAdd(facultyID, facultyName, facultyLevel, facultyDepartment); //create a faculty person object to add to the facultyTable

			while(!facultyInformation.empty()) //while the string is not empty
			{
				int studentAdviseeID = stoi(facultyInformation.substr(0, facultyInformation.find(delimeter))); //find the studentAdviseeIDs for this faculty member. Note that they will be the last elements in the line
				facultyInformation.erase(0, facultyInformation.find(delimeter)+1);
				facultyToAdd.assignStudent(studentAdviseeID); //assign these students as advisees of the faculty member
			}

			facultyTable.insert(facultyToAdd); //insert the initialized faculty member into the facultyTable
		}
		inputStream.close();
	}
	catch(int e)
	{
		cout << "No faculty input file found. Establishing brand new database" << endl;
		return false; //just exit the function, since there was no inputFile found
	}

	return true;

}

void DatabaseSimulation::clearFacultyFile()
{
	ofstream outputStream;
	outputStream.open("masterFaculty.txt");

	outputStream.close();
}

void DatabaseSimulation::clearStudentFile()
{
	ofstream outputStream;
	outputStream.open("masterStudent.txt");

	outputStream.close();
}

void DatabaseSimulation::displayMenu()
{
	cout << endl; //formatting
	cout << "You have the following options: " << endl
		 << endl
		 << "1 -------------> Print all students and their information (students will be printed by ascending ID#)" << endl
		 << "2 -------------> Print all faculty and their information (faculty members will be printed by ascending ID#)" << endl
		 << "3 -------------> Find and display student information by the student's ID#" << endl
		 << "4 -------------> Find and display faculty information by the faculty member's ID#" << endl
		 << "5 -------------> Use a student's ID# to print the name and information of the student's faculty advisor" << endl
		 << "6 -------------> Use a faculty's ID# to print all the names and information of the faculty member's advisees" << endl
		 << "7 -------------> Add a new student to the student database" << endl
		 << "8 -------------> Delete a student from the student database by the student's ID#" << endl
		 << "9 -------------> Add a new faculty member" << endl
		 << "10 ------------> Delete a faculty member from the faculty database by the faculty member's ID#" << endl
		 << "11 ------------> Change a student's advisor given the student ID (will prompt for the new faculty advisor's ID#)" << endl
		 << "12 ------------> Remove a student advisee by their ID# from a faculty member" << endl
		 << "13 ------------> Rollback -- undo the previous 5 actions" << endl
		 << "14 ------------> Exit" << endl;
}

void DatabaseSimulation::addNewStudent()
{
	string studentName;
	string majorOfStudent;
	string levelOfStudent;
	int studentID;
	double studentGPA;
	int advisorID;

	cout << "Input the following attributes for the new student: " << endl;
	cout << "Name: ";
	string blank;
	getline(cin, blank);
	getline(cin, studentName);
	cout << endl;
	cin.clear();

	cout << "Major of student: ";
	getline(cin, majorOfStudent);
	cout << endl;
	cin.clear();


	cout << "Level of student (Freshman, Sophomore, Junior, Senior): ";
	getline(cin, levelOfStudent);
	cout << endl;
	cin.clear();

	cout << "Student ID#: ";
	cin >> studentID;
	cout << endl;
	cin.clear();

	cout << "Student GPA: ";
	cin >> studentGPA;
	cout << endl;
	cin.clear();

	cout << "ID of the student's faculty advisor: ";
	cin >> advisorID;
	cout << endl;
	cin.clear();

	Faculty facultyAdvisor(advisorID);

	//the program will end if the requested faculty advisor is not in the database
	if(!facultyTable.contains(facultyAdvisor))
	{
		cerr << "The requested advisor is not in the database. Ending program " << endl;
		exit(1);
	}

	Student studentToAdd(studentID, studentName, levelOfStudent, majorOfStudent, studentGPA, advisorID); //create a student object initialized with the values the user typed in
	studentTable.insert(studentToAdd); //add the student person to the studentTable (the student BST)

	Faculty facultyAdvisorUpdated = facultyTable.find(facultyAdvisor); //instantiate a new faculty member with all the same values as the one already in the table. This is because we are going to update the faculty member's information
	if(!facultyAdvisorUpdated.containsStudent(studentID))
		facultyAdvisorUpdated.assignStudent(studentID); //update the faculty advisor's assigned advisees
	else
	{
		cerr << "Faculty member already has the requested student as an advisee! Ending program!" << endl;
		exit(1);
	}
	facultyTable.deleteR(facultyAdvisor); //delete the old version of the faculty member from the database
	facultyTable.insert(facultyAdvisorUpdated); //add in the new version of the faculty member

	studentMembersChanged.push(studentToAdd); //push this student to our studentMembers Changed stack so we can undo this action if needed
}

void DatabaseSimulation::addNewStudentAsRollback(Student theStudent)
{
	Faculty facultyAdvisor(theStudent.getAdvisor());

	//the program will end if the requested faculty advisor is not in the database
	if(!facultyTable.contains(facultyAdvisor))
	{
		cerr << "The requested advisor is not in the database. Ending program " << endl;
		exit(1);
	}

	studentTable.insert(theStudent); //add the student person to the studentTable (the student BST)

	Faculty facultyAdvisorUpdated = facultyTable.find(facultyAdvisor); //instantiate a new faculty member with all the same values as the one already in the table. This is because we are going to update the faculty member's information
	if(!facultyAdvisorUpdated.containsStudent(theStudent.getStudentByID()))
		facultyAdvisorUpdated.assignStudent(theStudent.getStudentByID()); //update the faculty advisor's assigned advisees
	else
	{
		cerr << "Faculty member already has the requested student as an advisee! Ending program!" << endl;
		exit(1);
	}
	facultyTable.deleteR(facultyAdvisor); //delete the old version of the faculty member from the database
	facultyTable.insert(facultyAdvisorUpdated); //add in the new version of the faculty member
}

void DatabaseSimulation::addNewFacultyMember()
{
	string facultyName;
	string facultyLevel;
	string facultyDepartment;
	int facultyIDNumber;

	cout << "Input the following attributes for the new faculty member: " << endl
		 << "Name: ";
	string blank; //placeholder so that we can clear out the buffer
	getline(cin, blank); //clear out the input buffer
	getline(cin, facultyName);
	cout << endl;

	cout << "Level (Lecturer, Instructor, Assistant Professor, Associate Professor, Professor): ";
	getline(cin, facultyLevel);
	cout << endl;

	cout << "Department faculty member belongs to: ";
	getline(cin, facultyDepartment);
	cout << endl;

	cout << "Faculty ID Number: ";
	cin >> facultyIDNumber;
	cout << endl;

	Faculty facultyToAdd(facultyIDNumber, facultyName, facultyLevel, facultyDepartment);
	facultyTable.insert(facultyToAdd);

	facultyMembersChanged.push(facultyToAdd); //push this newly created faculty member to the facultyMembersChanged stack so we can undo this action if needed
}

void DatabaseSimulation::addNewFacultyMemberAsRollback(Faculty theFaculty)
{
	facultyTable.insert(theFaculty);
}

void DatabaseSimulation::displayStudentInformationGivenID()
{
	int studentID;
	cout << "Student ID#: ";
	cin >> studentID;

	Student studentToFind(studentID);

	(studentTable.find(studentToFind)).getInformation();
}

void DatabaseSimulation::displayFacultyInformationGivenID()
{
	int facultyID;
	cout << "Faculty ID#: ";
	cin >> facultyID;

	Faculty facultyToFind(facultyID);

	(facultyTable.find(facultyToFind)).getInformation();
}

void DatabaseSimulation::displayAdvisorInformationGivenStudentID()
{
	cout << "Student ID#: ";
	int studentID;
	cin >> studentID;

	Student studentToFind(studentID); //create a student object to locate in the student database. If that student exists, we will then get his/her faculty advisor's ID# and search the faculty database for the faculty member's information

	int facultyID = (studentTable.find(studentToFind)).getAdvisor(); //returns the ID# of the student's faculty advisor

	Faculty facultyToFind(facultyID); //create a faculty object initialized with the facultyID obtained from above

	(facultyTable.find(facultyToFind)).getInformation(); //print out the information of the faculty member
}

void DatabaseSimulation::DeleteStudentGivenID()
{
	int studentID;
	cout << "Student ID#: ";
	cin  >> studentID;

	Student studentToDelete(studentID);

	//first unassign whoever the student had as an advisor
	int facultyID = (studentTable.find(studentToDelete)).getAdvisor(); //returns the ID# of the student's faculty advisor

	Faculty facultyToFind(facultyID); //create a faculty object initialized with the facultyID obtained from above. We will use this to search for the correct faculty member in the DB
	Faculty facultyMemberUpdated = facultyTable.find(facultyToFind); //instantiate a new faculty person object with the same values as the faculty member we just found in the DB. We will then delete the old faculty person and insert the updated one
	facultyMemberUpdated.removeAdvisee(studentID); //update the faculty member by removing the student we want to delete from his/her list of advisees
	facultyTable.deleteR(facultyToFind); //delete the original version of the faculty member
	facultyTable.insert(facultyMemberUpdated); //insert the updated faculty member into the table

	studentTable.deleteR(studentToDelete);
	cout << "Student deleted" << endl;

	studentMembersChanged.push(studentToDelete); //push the studentToDelete person onto our stack so we can undo this delete if needed (when rollback is called)
}

void DatabaseSimulation::DeleteStudentAsRollback(Student theStudent)
{
	//first unassign whoever the student had as an advisor
	int facultyID = (studentTable.find(theStudent)).getAdvisor(); //returns the ID# of the student's faculty advisor

	Faculty facultyToFind(facultyID); //create a faculty object initialized with the facultyID obtained from above. We will use this to search for the correct faculty member in the DB
	Faculty facultyMemberUpdated = facultyTable.find(facultyToFind); //instantiate a new faculty person object with the same values as the faculty member we just found in the DB. We will then delete the old faculty person and insert the updated one
	facultyMemberUpdated.removeAdvisee(theStudent.getStudentByID()); //update the faculty member by removing the student we want to delete from his/her list of advisees
	facultyTable.deleteR(facultyToFind); //delete the original version of the faculty member
	facultyTable.insert(facultyMemberUpdated); //insert the updated faculty member into the table

	studentTable.deleteR(theStudent);
	cout << "Student deleted" << endl;
}

void DatabaseSimulation::DeleteFacultyMemberGivenID()
{
	cout << "Faculty ID#: ";
	int facultyID;
	cin  >> facultyID; //read in the ID# of the faculty member to delete
	Faculty facultyMemberToDelete(facultyID); //instantiate a faculty member person object with the ID passed in by the user as the constructor. We create this faculty person object so that we can use it as the argument for our delete function

	//before we delete the faculty member, we must reassign all the faculty member's advisees to new faculty members
	Faculty facultyMemberToDeleteModified = facultyTable.find(facultyMemberToDelete);

	for (int i = 0; i < facultyMemberToDeleteModified.getNumberOfAdvisees(); ++i)
	{
		Student studentToBeReassigned(facultyMemberToDeleteModified.getAdvisee(i));
		Student studentToBeReassignedModified = studentTable.find(studentToBeReassigned);
		int studentID = studentToBeReassignedModified.getStudentByID();

		cout << "Faculty ID# of the new faculty advisor to assign to student with ID of " << studentID << ": ";
		int newFacultyID;
		cin  >> newFacultyID;

		studentToBeReassignedModified.setAdvisor(newFacultyID); //reassign the student person to the faculty member with ID of newFacultyID

		Faculty facultyToAssignStudentTo(newFacultyID); //create a faculty person object instantiated with the ID of newFacultyID. We will use this object to search for the faculty member whose ID matches that of the faculty person object we created
		Faculty facultyToAssignStudentToModified = facultyTable.find(facultyToAssignStudentTo); //find and return the faculty person in the faculty table whose ID matches the one the user typed in (if the faculty member even exists)
		facultyToAssignStudentToModified.assignStudent(studentID); //assign the student to the faculty member found from the line above
		facultyTable.deleteR(facultyToAssignStudentTo); //delete the old version of the faculty member who we just assigned the student to
		facultyTable.insert(facultyToAssignStudentToModified); //insert the updated version of the faculty member
		studentTable.deleteR(studentToBeReassigned); //delete the old version of the student (with the advisor we are deleting) from the studentTable
		studentTable.insert(studentToBeReassignedModified); //insert the newly updated version of the student into the studentTable
	}

	facultyTable.deleteR(facultyMemberToDelete); //traverse the facultyTable/database and delete the facultyMemberToDelete
	cout << "Faculty member deleted" << endl;

	facultyMembersChanged.push(facultyMemberToDelete); //push this faculty member onto our stack so we can undo this change if needed
}

void DatabaseSimulation::DeleteFacultyMemberAsRollback(Faculty theFaculty)
{
	//before we delete the faculty member, we must reassign all the faculty member's advisees to new faculty members
	Faculty facultyMemberToDeleteModified = facultyTable.find(theFaculty);

	for (int i = 0; i < facultyMemberToDeleteModified.getNumberOfAdvisees(); ++i)
	{
		Student studentToBeReassigned(facultyMemberToDeleteModified.getAdvisee(i));
		Student studentToBeReassignedModified = studentTable.find(studentToBeReassigned);
		int studentID = studentToBeReassignedModified.getStudentByID();

		cout << "Faculty ID# of the new faculty advisor to assign to student with ID of " << studentID << ": ";
		int newFacultyID;
		cin  >> newFacultyID;

		studentToBeReassignedModified.setAdvisor(newFacultyID); //reassign the student person to the faculty member with ID of newFacultyID

		Faculty facultyToAssignStudentTo(newFacultyID); //create a faculty person object instantiated with the ID of newFacultyID. We will use this object to search for the faculty member whose ID matches that of the faculty person object we created
		Faculty facultyToAssignStudentToModified = facultyTable.find(facultyToAssignStudentTo); //find and return the faculty person in the faculty table whose ID matches the one the user typed in (if the faculty member even exists)
		facultyToAssignStudentToModified.assignStudent(studentID); //assign the student to the faculty member found from the line above
		facultyTable.deleteR(facultyToAssignStudentTo); //delete the old version of the faculty member who we just assigned the student to
		facultyTable.insert(facultyToAssignStudentToModified); //insert the updated version of the faculty member
		studentTable.deleteR(studentToBeReassigned); //delete the old version of the student (with the advisor we are deleting) from the studentTable
		studentTable.insert(studentToBeReassignedModified); //insert the newly updated version of the student into the studentTable
	}

	facultyTable.deleteR(theFaculty); //traverse the facultyTable/database and delete the facultyMemberToDelete
	cout << "Faculty member deleted" << endl;
}

void DatabaseSimulation::changeStudentAdvisor()
{
	int studentID;
	cout << "Student ID#: ";
	cin  >> studentID;

	int newFacultyID;
	cout << "New faculty member advisor ID#: ";
	cin  >> newFacultyID;

	//the following code assigns the faculty member with the faculty ID specified by the user to the student with the student ID#
	Faculty originalFacultyMemberVersion(newFacultyID); //create a faculty person object to make sure they exist in the faculty database and so that we will be able to change the faculty member's advisee list
	Faculty updatedFacultyMemberVersion = facultyTable.find(originalFacultyMemberVersion);
	updatedFacultyMemberVersion.assignStudent(studentID); //assign the student to the faculty member
	facultyTable.deleteR(originalFacultyMemberVersion);
	facultyTable.insert(updatedFacultyMemberVersion);
	//end code block

	//the following code updates the facultyAdvisor for the student person
	Student originalStudentVersion(studentID);
	int idOfOriginalFacultyAdvisor = (studentTable.find(originalStudentVersion)).getAdvisor(); //we need to get the ID of the student's original faculty advisor so we can unassign this student from that faculty member
	Student updatedStudentVersion = studentTable.find(originalStudentVersion);
	studentTable.deleteR(originalStudentVersion); //delete the original version of this student so we can add the updated student to the tree
	updatedStudentVersion.setAdvisor(newFacultyID); //since we already searched for the new faculty member we want to assign to this student above, we can just perform this operation. If the requested faculty member does not exist in the DB, line 284 will throw an error and exit
	studentTable.insert(updatedStudentVersion);
	//end code block

	//the following code unassigns the student from the original faculty advisor
	Faculty facultyMemberToUnassignFromStudent(idOfOriginalFacultyAdvisor); //create an instance of a faculty person object so we can use it to search for the faculty member we are wanting to unassign from the student
	Faculty facultyMemberToUnassignFromStudentUpdated = facultyTable.find(facultyMemberToUnassignFromStudent); //the find method returns, in this case, a faculty object
	facultyMemberToUnassignFromStudentUpdated.removeAdvisee(studentID); //update the faculty member we found in line 296
	facultyTable.deleteR(facultyMemberToUnassignFromStudent); //delete the original version of the original faculty advisor from the tree
	facultyTable.insert(facultyMemberToUnassignFromStudentUpdated); //insert the updated version of the original faculty member onto the tree
	//end code block
}

void DatabaseSimulation::removeAdviseeFromFacultyMember()
{
	int facultyID; //the id number of the faculty member from whom we want to remove the student
	cout << "Faculty ID#: ";
	cin  >> facultyID;

	int studentID;
	cout << "Student ID#: ";
	cin  >> studentID;

	int facultyIDOfNewAdvisor;
	cout << "ID# of new faculty advisor for the student: ";
	cin  >> facultyIDOfNewAdvisor;

	Faculty facultyToRemoveStudentFrom(facultyID); //create a new faculty person object. We will use this object to see if the requested faculty member is stored in the faculty database
	Faculty facultyToRemoveStudentFromUpdated = facultyTable.find(facultyToRemoveStudentFrom); //create a new faculty person object and set it equal to the faculty member found in the tree

	Faculty facultyToAssignStudentTo(facultyIDOfNewAdvisor); //create a new faculty person object. We will assign the student to this new advisor
	Faculty facultyToAssignStudentToUpdated = facultyTable.find(facultyToAssignStudentTo);

	Student studentToProcess(studentID);
	Student updatedStudent = studentTable.find(studentToProcess);

	if(facultyToRemoveStudentFromUpdated.containsStudent(studentID) && updatedStudent.getAdvisor() == facultyID) //checks to see if the faculty member requested even has the student requested as an advisee
	{
		facultyToRemoveStudentFromUpdated.removeAdvisee(studentID); //remove the advisee student from the faculty member
		updatedStudent.setAdvisor(facultyIDOfNewAdvisor); //assign a different advisor to the student who we just removed as an advisee from the faculty member
		facultyToAssignStudentToUpdated.assignStudent(studentID);

		studentTable.deleteR(studentToProcess); //delete the old version of the student
		studentTable.insert(updatedStudent); //insert the new version of the student
		facultyTable.deleteR(facultyToRemoveStudentFrom); //delete the original faculty member
		facultyTable.insert(facultyToRemoveStudentFromUpdated); //insert the updated version of the faculty member (with the student removed as an advisee)
		facultyTable.deleteR(facultyToAssignStudentTo); //delete the old version of the faculty member who we are assigning the student to
		facultyTable.insert(facultyToAssignStudentToUpdated); //insert the new version of the faculty member who we are assigning the studen to
	}
	else
	{
		cerr << "The requested faculty member does not have the requested student as an advisee! Ending program" << endl;
		exit(1); //exit the program
	}
}

void DatabaseSimulation::displayAdviseeInformationGivenFacultyID()
{
	int facultyID;
	cout << "Faculty ID#: ";
	cin  >> facultyID;

	Faculty memberToProcess(facultyID); //create a faculty person. We will search for this faculty member's student advisees

	//Faculty facultyMemberFound(facultyTable.find(memberToProcess)); //find the faculty member in our faculty database

	int numAdvisees = (facultyTable.find(memberToProcess)).getNumberOfAdvisees();
	if(numAdvisees == 0)
		cout << "No advisees assigned to the faculty member" << endl;

	for (int i = 0; i < numAdvisees; ++i)
	{
		Student theStudent((facultyTable.find(memberToProcess)).getAdvisee(i)); //this will instantiate a new student person to be searched for in the student database (the constructor argument returns an int value)
		(studentTable.find(theStudent)).getInformation(); //obtain the information for the faculty member's advisee
	}
}

void DatabaseSimulation::performRollBack()
{
	if(typeOfAction == "Added faculty" && !facultyMembersChanged.empty()) //the facultyMembersChanged stack cannot be empty
	{
		DeleteFacultyMemberAsRollback(facultyMembersChanged.top());
		facultyMembersChanged.pop(); //pop off the top faculty person in the facultyMembersChanged stack since we already processed them
	}

	else if(typeOfAction == "Deleted faculty" && !facultyMembersChanged.empty())
	{
		addNewFacultyMemberAsRollback(facultyMembersChanged.top());
		facultyMembersChanged.pop(); //pop off the top faculty person in the facultyMembersChanged stack since we already processed them
	}

	else if(typeOfAction == "Added student" && !studentMembersChanged.empty())
	{
		DeleteStudentAsRollback(studentMembersChanged.top()); //delete the recently added student
		studentMembersChanged.pop(); //pop off the top student person in the studentMembersChanged stack since we already processed them
	}

	else if(typeOfAction == "Deleted student" && !studentMembersChanged.empty())
	{
		addNewStudentAsRollback(studentMembersChanged.top()); //add back the recently deleted student
		studentMembersChanged.pop(); //pop off the top student person in the studentMembersChanged stack since we already processed them
	}

	else
	{
		cout << "No recent changes were made." << endl;
		return;
	}
}
