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
        : name()
{

}

/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
        : name(cname)
{

}


/**
 * Create a new course named cname that does have known prerequisites
 */
Course::Course (const CourseName& cname, const std::initializer_list<CourseName> prereqsList)
    : name(cname)
{
  for (CourseName cname: prereqsList)
    prereqs.push_back(cname);
}


/**
* Create a deep copy of a course
*/
Course::Course(const Course &course)
        : name(course.getName())
{
  for (CourseName cname: course.prereqs)
    prereqs.push_back(cname);
}

/**
 * Move constructor
 */
Course::Course(Course &&course)
        : name(course.name), prereqs(course.prereqs)
{

}


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
  const_iterator temp = end();

  // ensures the prereq exists before trying to remove it
  for (const_iterator it = begin(); it != end(); it++)
    if (*it == cname)
      temp = it;

  if (temp != end())
    prereqs.erase(temp);
}

const Course &Course::operator=(const Course &rhs)
{
  // adapted from "Data Structures and Algorithm Analysis" 4th edition
  // by Mark Weiss figure 1.18.
  Course copy = rhs;
  std::swap(*this, copy);

  return *this;
}

Course &Course::operator=(Course &&rhs)
{
  // adapted from "Data Structures and Algorithm Analysis" 4th edition
  // by Mark Weiss figure 1.18
  std::swap(name, rhs.name);
  std::swap(prereqs, rhs.prereqs);

  return *this;
}

bool operator==(const Course &lhs, const Course &rhs)
{
  return lhs.getName() == rhs.getName() &&
         lhs.getNumberOfPrereqs() == rhs.getNumberOfPrereqs();
}

bool operator<(const Course &lhs, const Course &rhs) {
  if (lhs.getName() == rhs.getName() &&
      lhs.getNumberOfPrereqs() < rhs.getNumberOfPrereqs()) {
    return true;
  }
  if (lhs.getName() < rhs.getName()) {
    return true;
  }
  return false;
}

std::ostream &operator<<(ostream &out, const Course &c) {
  // based on operator of the same name inside of catalog.cpp
  // of assignment 1 written by Dr Zeil, just updated to use
  // iterator loop
  out << c.name << " (";

  for (Course::const_iterator it = c.begin(); it != c.end(); it++)
  {
    if (it != c.begin())
      out << ',';

    out << *it;
  }
  out << ')';
  return out;
}
