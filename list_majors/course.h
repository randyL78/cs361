#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <list>
#include <initializer_list>
#include "courseName.h"
#include <iterator>

using namespace std;

class Course {
    CourseName name;           ///< Name of the course
    list<CourseName> prereqs;  ///< List of course names
    int numberOfPrerequisites; ///< How many prereqs are currently in the list?

public:
    using iterator       = list<CourseName>::iterator;
    using const_iterator = list<CourseName>::const_iterator;

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
     * Create a new course named cname that does have known prerequisites
     * @param cname
     * @param prereqsList
     */
    Course (const CourseName& cname, const initializer_list<CourseName> prereqList);

    /**
     * Creates a Course with a range of prerequisites
     *
     * @param cname Name of the course
     * @param firstCourse First course in the list of prerequisites
     * @param lastCourse Last course in the list of prerequisites
     */
    template<typename Iterator>
    // Note: use of template requires definition to be here in the header
    Course( const CourseName& cname, Iterator firstCourse, Iterator lastCourse);

    iterator begin() { return prereqs.begin(); }
    const_iterator begin() const { return prereqs.cbegin(); }

    iterator end() { return prereqs.end(); }
    const_iterator end() const { return prereqs.cend(); }


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
     * Compares two courses for equality
     * @param lhs
     * @param rhs
     * @return
     */
    bool operator==(const Course &rhs) const;

    /**
     * Compares the CourseName of 2 Courses
     * @param lhs
     * @param rhs
     * @return true if lhs CourseName is less thant rhs CourseName
     */
    bool operator<(const Course &rhs) const;

private:
    friend std::ostream& operator<< (std::ostream& out, const Course& c);
};

std::ostream& operator<< (std::ostream& out, const Course& c);

// Note: use of template requires definition to be here in the header
template<typename Iterator>
Course::Course( const CourseName& cname, Iterator firstCourse, Iterator lastCourse)
  : name(cname), prereqs(), numberOfPrerequisites(0)
{
    for(auto it = firstCourse; it != lastCourse; ++it)
      addPrereq(*it);
}

#endif
