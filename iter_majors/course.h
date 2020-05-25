#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include "courseName.h"

using namespace std;

class Course {
    CourseName name;           ///< Name of the course
    std::vector<CourseName> prereqs;

public:
    // aliases for iterator support piggy backing off of standard vector
    using iterator = std::vector<CourseName>::iterator;
    using const_iterator = std::vector<CourseName>::const_iterator;
    // end iterator aliases


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
    Course (const CourseName& cname, const std::initializer_list<CourseName> prereqsList);

    /**
     * Create a deep copy of a course
     * @param course - the course to copy
     */
    Course(const Course &course);

    /**
     * Move constructor
     * @param course
     */
    Course(Course &&course);

    /**
     * Creates a Course with a range of prerequisites
     * @param cname Name of the course
     * @param firstCourse First course in the list of prerequisites
     * @param lastCourse Last course in the list of prerequisites
     */
    template<typename Iterator>
    Course( const CourseName& cname, Iterator firstCourse, Iterator lastCourse);

    /**
     * Just your run of the mill destructor
     */
    ~Course() = default;  // vector handles its own deallocation

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
     * No longer needed with use of vector or other iterators
     *
     * @deprecated
     * @precondition 0 <= i && i < getNumberofPrereqs()
     * @param i index of the prerequisite to retrieve
     * @return name of the prerequisite course
     */
    // CourseName getPrereq(int i) const;

    /**
     * Assigns one Course to another (Copy Assignment)
     * @param rhs the Course to be assigned
     * @return
     */
    const Course& operator=(const Course &rhs);

    /**
     * Assigns one Course to another (Move Assignment)
     * @param rhs
     * @return
     */
    Course& operator=(Course &&rhs);



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

/**
 * Compares the CourseName of 2 Courses
 * @param lhs
 * @param rhs
 * @return true if lhs CourseName is less thant rhs CourseName
 */
bool operator<(const Course &lhs, const Course &rhs);



std::ostream& operator<< (std::ostream& out, const Course& c);


#endif
