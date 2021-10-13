#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// const int MaxNameSize = 32;
class Student {
  // Functions
 public:
  void display() const;
  void init(string name, int id, float gpa);
  int getId() const { return m_id; }
  float getGPA() const { return m_gpa; }
  string getName() const { return m_name; }
  void readStudentInfo();
  void printStudentVec(vector<Student> &sV);

 private:
  // Data
  int m_id;
  string m_name;
  float m_gpa;
};

std::ostream &operator<<(std::ostream &out, Student &s);
bool operator==(Student &lhs, Student &rhs);
bool operator<(const Student &lhs, const Student &rhs);

#endif  // STUDENT_H
