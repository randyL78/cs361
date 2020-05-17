#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "courseName.h"

using namespace std;

class Course {
    //** You may not change the declarations in this private: area.
    CourseName name;           ///< Name of the course
    int numberOfPrerequisites; ///< How many prereqs are currently in the array?
    int maxPrerequisites;      ///< How many prereqs will fit into the array?
    CourseName * prereqs;      ///< Pointer to an array of course names.
public:

    /**
     * Create a new course and set cname to null
     */
     Course();

	/**
	 * Create a new course named cname and having no
	 * known prerequisites;
	 */
	Course (const CourseName& cname);

	/**
	 * Create a deep copy of a course
	 * @param course - the course to copy
	 */
	Course(const Course &course);

	/**
	 * Just your run of the mill destructor
	 */
	~Course();

	/**
	 * @return the name of the course
	 */
	CourseName getName() const {return name;}

	/**
	 * @return the number of known prerequisites to this course.
	 */
	int getNumberOfPrereqs() const;

	/**
	 * Adds cname to the list of prerequisites for this course.
	 * If this name is already in the list, this has no effect.
	 *
	 * @param cname name of a prerequisite course
	 */
	void addPrereq(const CourseName& cname);

	/**
	 * Removes cname from the list of prerequisites for this course.
	 * If this name is not in the list, this has no effect.
	 *
	 * @param cname name of a prerequisite course
	 */
	void removePrereq(const CourseName& cname);

	/**
	 * Get the name of the i_th prerequisite.
	 *
	 * @precondition 0 <= i && i < getNumberofPrereqs()
	 * @param i index of the prerequisite to retrieve
	 * @return name of the prerequisite course
	 */
	CourseName getPrereq(int i) const;


private:
	friend std::ostream& operator<< (std::ostream& out, const Course& c);
};

/**
 * Compares two courses for equality
 * @param lhs
 * @param rhs
 * @return
 */
bool operator==(const Course &lhs, const Course &rhs);

bool operator<(const Course &lhs, const Course &rhs);

std::ostream& operator<< (std::ostream& out, const Course& c);


#endif
