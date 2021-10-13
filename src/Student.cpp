#include "Student.h"

#include <cstring>
#include <iostream>

using namespace std;

void Student::display() const {
  cout << m_name << " " << m_id << " " << m_gpa << endl;
}

void Student::init(string name, int id, float gpa) {
  m_id = id;
  m_gpa = gpa;
  // strcpy(this->name, name);
  m_name = name;
}

ostream &operator<<(ostream &out, Student &s) {
  s.display();
  return out;
}

bool operator==(Student &lhs, Student &rhs) {
  return (lhs.getId() == rhs.getId());
}

bool operator<(const Student &lhs, const Student &rhs) {
  return (lhs.getGPA() < rhs.getGPA());
}

void printStudentVec(vector<Student> &sV) {
  for (int i = 0; i < sV.size(); i++) {
    cout << sV[i];
  }
}

void Student::readStudentInfo() {
  cout << "Please enter student info..." << endl;
  string name;
  cout << "Name: ";
  cin >> name;
  int id;
  cout << "ID: ";
  cin >> id;
  float gpa;
  cout << "GPA: ";
  cin >> gpa;
  init(name, id, gpa);
}

bool sortById(const Student &lhs, const Student &rhs) {
  return lhs.getId() < rhs.getId();
}
