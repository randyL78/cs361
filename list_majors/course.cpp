#include "course.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;


/**
 * Create a new course and set cname to null
 */
Course::Course()
  : name(), prereqs()
{}

/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
  : name(cname), prereqs()
{}


/**
 * Create a new course named cname that does have known prerequisites
 */
Course::Course (const CourseName& cname,
                const std::initializer_list<CourseName> prereqsList)
  : name(cname), prereqs(prereqsList)
{}

/**
* @return the number of known prerequisites to this course.
*/
int Course::getNumberOfPrereqs() const
{
  return prereqs.size();
}

/**
 * Adds cname to the list of prerequisites for this course.
 * If this name is already in the list, this has no effect.
 */
void Course::addPrereq(const CourseName& cname)
{
  // guard clause to make sure course doesn't already exist
  for (CourseName p_name: prereqs)
    if (p_name == cname)
      return;

  prereqs.push_back(cname);
}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 */
void Course::removePrereq(const CourseName& cname)
{
  for (const_iterator it = begin(); it != end(); it++)
    if (*it == cname)
    {
      prereqs.erase(it);
      break;
    }
}

bool Course::operator==(const Course &rhs)
{
  return name    == rhs.name &&
         prereqs == rhs.prereqs;
}

// Using Dr Zeil's example code method
// from: https://www.cs.odu.edu/~zeil/submit/websubmit.cgi?asstinfo=/home/zeil/courses/cs361/sum20/Assts/iter_majors/iter_majors.ini&bogus=foo.txt
bool Course::operator<(const Course &rhs) {
  using namespace std::rel_ops;

  if (name != rhs.name)
    return false;

  return prereqs < rhs.prereqs;
}

std::ostream &operator<<(ostream &out, const Course &c) {
  // based on operator of the same name inside of catalog.cpp
  // of assignment 1 written by Dr Zeil, just updated to use
  // iterator loop. Updated using example solution code.
  out << c.name << " (";
  bool first = true;

  for (const CourseName &cname : c)
  {
    if (!first)
      out << ',';

    out << cname;
    first = false;
  }
  out << ')';
  return out;
}
