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
  : name(cname), prereqs(), numberOfPrerequisites(0)
{}


/**
 * Create a new course named cname that does have known prerequisites
 */
Course::Course (const CourseName& cname,
                const std::initializer_list<CourseName> prereqsList)
  : name(cname), numberOfPrerequisites(0)
{
  for(auto it = prereqsList.begin(); it != prereqsList.end(); ++it)
    addPrereq(*it);
}

/**
* @return the number of known prerequisites to this course.
*/
int Course::getNumberOfPrereqs() const
{
  return numberOfPrerequisites;
}

/**
 * Adds cname to the list of prerequisites for this course.
 * If this name is already in the list, this has no effect.
 */
void Course::addPrereq(const CourseName& cname)
{

  // handles if list is empty or if the first course name is larger
  // than the one being added
  if(numberOfPrerequisites == 0 || cname < *prereqs.begin()) {
    prereqs.push_front(cname);
    ++numberOfPrerequisites;
    return;
  }

  // handles if the course name is larger than the last element of the list
  if(*--(prereqs.end()) < cname)
  {
    prereqs.push_back(cname);
    ++numberOfPrerequisites;
    return;
  }

  // tried to use a reverse iterator and base() to simplify things,
  // but kept having runtime errors in unitest when I did
  for(const_iterator it = prereqs.begin(); it != prereqs.end(); ++it)
  {
    // early return if duplicate
    if(*it == cname)
      return;

    if(cname < *it)
    {
      prereqs.insert(it, cname);
      ++numberOfPrerequisites;
      return;
    }
  }
}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 */
void Course::removePrereq(const CourseName& cname)
{
  // std::list.remove() has O(N) runtime where N is the number of elements in
  // the list as long as comparisons are O(1)
  // (http://www.cplusplus.com/reference/list/list/remove/), but
  // assuming you want us to build the loop ourselves since remove isn't
  // mentioned in the lecture notes
  // prereqs.remove(cname);
  for(const_iterator it = prereqs.begin(); it != prereqs.end(); ++it)
  {
    if(cname == *it)
    {
      prereqs.erase(it);
      --numberOfPrerequisites;
      return;
    }
  }
}

bool Course::operator==(const Course &rhs) const
{
  return name    == rhs.name &&
         prereqs == rhs.prereqs;
}

// Using Dr Zeil's example code method
// from: https://www.cs.odu.edu/~zeil/submit/websubmit.cgi?asstinfo=/home/zeil/courses/cs361/sum20/Assts/iter_majors/iter_majors.ini&bogus=foo.txt
bool Course::operator< (const Course &rhs) const {
  using namespace std::rel_ops;

	if (name != rhs.name)
		return name < rhs.name;

	return prereqs < rhs.prereqs;
}

std::ostream &operator<<(ostream &out, const Course &c) {
  // based on operator of the same name inside of catalog.cpp
  // of assignment 1 written by Dr Zeil, just updated to use
  // iterator loop. Updated using example solution code.
  out << c.name << " (";
  bool first = true;

  for (const CourseName& cname : c)
  {
    if (!first)
      out << ',';

    out << cname;
    first = false;
  }
  out << ')';
  return out;
}
