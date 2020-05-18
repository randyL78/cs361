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
: name(), numberOfPrerequisites(0), maxPrerequisites(10),
  prereqs(new CourseName[maxPrerequisites])
{

}

/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
: name(cname), numberOfPrerequisites(0), maxPrerequisites(10),
  prereqs(new CourseName[maxPrerequisites])
{

}

/**
 * Create a deep copy of a course
 * @param course - the course to copy
 */
Course::Course(const Course &course)
: name(course.getName()), numberOfPrerequisites(course.getNumberOfPrereqs()),
  maxPrerequisites(10), prereqs(new CourseName[maxPrerequisites])
{
    for (int i = 0; i < numberOfPrerequisites; i++) {
        prereqs[i] = course.getPrereq(i);
    }
}

/**
 * Move constructor
 * @param course
 */
Course::Course(Course &&course)
: name(course.name), numberOfPrerequisites(course.numberOfPrerequisites),
  maxPrerequisites(10), prereqs(course.prereqs)
{
    course.prereqs = nullptr;
}

Course::~Course() {
   delete [] prereqs;
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
 *
 * @param cname name of a prerequisite course
 */
void Course::addPrereq(const CourseName& cname)
{
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] == cname)
			return;
	assert (numberOfPrerequisites < maxPrerequisites);
	prereqs[numberOfPrerequisites] = cname;
	++numberOfPrerequisites;
}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::removePrereq(const CourseName& cname)
{
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] == cname)
		{
			for (int j = i+1; j < numberOfPrerequisites; ++j)
				prereqs[j-1] = prereqs[j];
			--numberOfPrerequisites;
			break;
		}
}

/**
 * Get the name of the i_th prerequisite.
 *
 * @precondition 0 <= i && i < getNumberofPrereqs()
 * @param i index of the prerequisite to retrieve
 * @return name of the prerequisite course
 */
CourseName Course::getPrereq(int i) const
{
	assert (i >= 0 && i < numberOfPrerequisites);
	return prereqs[i];
}

const Course &Course::operator=(const Course &rhs)
{
    Course copy = rhs;
    std::swap(*this, copy);

    return *this;
}

Course &Course::operator=(Course &&rhs)
{
    std::swap(name, rhs.name);
    std::swap(numberOfPrerequisites, rhs.numberOfPrerequisites);
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
