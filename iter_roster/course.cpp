#include "course.h"

using namespace std;


Course::Course()
{
}

Course::Course (std::string dept, std::string number)
  : theDept(dept), theNumber(number)
{
}



bool Course::operator== (const Course& right) const
{
  return theDept == right.theDept && theNumber == right.theNumber;
}



bool Course::operator< (const Course& right) const
{
  if (theDept < right.theDept)
    return true;
  else if (theDept == right.theDept)
    return (theNumber < right.theNumber);
  else
    return false;
}




// Read a course in the form "DEPT NUMBER"
// The dept is terminated by a blank space or by a numeric digit,
// (the first digit of the number).
// Leading ' ' are ignored.
istream& operator>> (istream& in, Course& course)
{
  string dept;
  string number;

  char c = ' ';
  while ((c <= ' ') && (in.get(c))) {}

  dept = c;
  while ((c > '9') && (in.get(c)))
    {
      if (c > '9')
	dept += c;
    }

  while ((c <= ' ') && (in.get(c))) {}

  number = c;
  while ((c > ' ') && (in.get(c)))
    {
      if (c > ' ')
	number += c;
    }

  course = Course(dept, number);

  return in;
}


// Write a Course in the form "DEPT NUMBER" with no intervening space.
std::ostream& operator<< (std::ostream& out, const Course& course)
{
  string cname = course.getDept() + course.getNumber();
  out << cname;
  return out;
}
	   
