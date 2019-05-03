#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

class Student
{
  public:
    Student();
    Student(int id, string theName, string studentLevel, string studentMajor, double theGPA, int theAdvisorField);
    Student(int id); //an overloaded constructor to initialize a Student object with only an ID number (used to find a student given his/her ID number)
    ~Student();
    void setStudentID(int id);
    void setName(string theName);
    void setLevel(string theLevel);
    void setMajor(string theMajor);
    void setGPA(int theGPA);
    void setAdvisor(int advisorID);
    int getAdvisor();
    int getStudentByID();
    void getInformation();
    void writeInformationToDisk(string fileToWrite);

    //overloaded operators
    friend const bool operator <(const Student& student1, const Student& student2);
    friend const bool operator >(const Student& student1, const Student& student2);
    friend const bool operator ==(const Student& student1, const Student& student2);
	friend const bool operator !=(const Student& student1, const Student& student2);


  private:
    int studentID;
    string name;
    string level;
    string major;
    double GPA;
    int AdvisorField;
};
