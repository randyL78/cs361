#include "section.h"

using namespace std;




Section::Section ()
  : theCallNumber(0), firstStudent(0), numStudents(0)
{
}

Section::Section (Course course, int callNumber)
  : theCourse(course), theCallNumber(callNumber), 
    firstStudent(0), numStudents(0)
{
}


Section::Section (const Section& sect)
  : theCourse(sect.theCourse), theCallNumber(sect.theCallNumber), 
    firstStudent(0), numStudents(0)
{
  for (ListNode* current = sect.firstStudent; 
       current != 0; current=current->next)
    addStudent (current->data);
}

Section& Section::operator= (const Section& sect)
{
  if (this != &sect)
    {
      ListNode* next;
      for (ListNode* current = firstStudent; current != 0; current=next)
	{
	  next = current->next;
	  delete current;
	}
      theCourse = sect.theCourse;
      theCallNumber = sect.theCallNumber;
      firstStudent = 0;
      numStudents = 0;
      for (ListNode* current = sect.firstStudent; current != 0; 
	   current=current->next)
	addStudent (current->data);
    }
  return *this;
}

Section::~Section()
{
  ListNode* next;
  for (ListNode* current = firstStudent; current != 0; current=next)
    {
      next = current->next;
      delete current;
    }
}


void Section::addStudent(Student s)
{
  ListNode* prev = 0;
  ListNode* current = firstStudent;
  while (current != 0 && current->data.getName() < s.getName())
    {
      prev = current;
      current = current->next;
    }
  ListNode* newNode = new ListNode (s, current);
  if (prev != 0)
    prev->next = newNode;
  else
    firstStudent = newNode;
  ++numStudents;
}

bool Section::operator== (const Section& right) const
{
  return (theCourse == right.theCourse)
    && (theCallNumber == right.theCallNumber);
}


bool Section::operator< (const Section& right) const
{
  if (theCourse < right.theCourse)
    return true;
  else if (theCourse == right.theCourse)
    return (theCallNumber < right.theCallNumber);
  else
    return false;
}
