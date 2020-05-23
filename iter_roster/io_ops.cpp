// Normally, these operations would appear in the same .cpp file as the
// rest of the corresponding ADT operations, but in this assignment 
// it seemed appropriate to separate out the bulk of the code I
// was providing from the files that students would be editing. 
// Among other things, this prevents tampering, inadvertant or 
// intentional, with the basic data structures and with the I/O formats.

#include "course.h"
#include "faculty.h"
#include "section.h"
#include "student.h"

#include <iomanip>
#include <algorithm>

using namespace std;


std::ostream& operator<< (std::ostream& out, const Faculty& fac)
{
  // 1. print the faculty header 
  out << fac.getName() << ": ";
  out << fac.getNumberOfSections() << " sections, ";

  //  Collect all sections and add up total enrollment
  int totalEnrollment = 0;
  for (const Section& section: fac)
    {
      totalEnrollment += section.getNumberOfStudents();
    }
  out << totalEnrollment << ", students\n";

  // 2. print the sections

  for (Faculty::const_iterator it = fac.begin(); it != fac.end(); ++it)
    {
      out << "  " << *it;
    }

  // 3. Finish up with an empty line
  out << endl;
  return out;
}



std::istream& operator>> (std::istream& in, Section& section)
{
  int callNumber;
  Course course;
  in >> callNumber >> course;
  section = Section(course, callNumber);
  return in;
}

std::ostream& operator<< (std::ostream& out, const Section& section)
{
  // 1. print the section header
  out << setw(8) << left << section.getCourse() 
      << setw(6) << left << section.getCallNumber();
  out << ": " << section.getNumberOfStudents() << " students\n";

  // 2. collect the students, sort, and print
  Student* students = new Student[section.getNumberOfStudents()];
  {
    int i = 0;
    for (Section::ListNode* current = section.firstStudent; 
	 current != 0; current=current->next)
      {
	students[i] = current->data;
	++i;
      }
  }
  
  sort (students, students+section.getNumberOfStudents());

  for (int i = 0; i < section.getNumberOfStudents(); ++i)
    out << "    " << students[i] << "\n";

  delete[] students;

  out << flush;
  return out;
}


std::istream& operator>> (std::istream& in, Student& s)
{
  Name nm;
  in >> nm;
  s = Student(nm);
  return in;
}

std::ostream& operator<< (std::ostream& out, const Student& s)
{
  out << s.getName();
  return out;
}

