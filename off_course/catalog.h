#ifndef CATALOG_H
#define CATALOG_H

#include "courseName.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <iterator>

namespace std {
    template<>
    struct hash<CourseName>
    {
        size_t operator() (const CourseName& courseName) const
        {
          hash<string> str_hash;
          hash<int> int_hash;
          return (size_t)str_hash(courseName.dept) + 31 * int_hash(courseName.num);
        }
    };
}

/**
 * A University Dept course catalog, with information
 * on courses offered and their pre-requisite structure.
 */
class CourseCatalog {
	using CourseSet = std::unordered_set<CourseName>;
	using CourseMap = std::unordered_multimap<CourseName, CourseName>;
public:

	typedef CourseSet::iterator iterator;
	typedef CourseSet::const_iterator const_iterator;


    /**
     *  Create a new course catalog.
     */
	CourseCatalog();


	/**
	 * Provide access to the courses in the catalog.
	 */
	iterator begin() {return coursesOffered.begin();}
	iterator end() {return coursesOffered.end();}

	const_iterator begin() const {return coursesOffered.begin();}
	const_iterator end() const {return coursesOffered.end();}


	/**
	 * Adds a pair of courses to the catalog if they have not previously been
	 * encountered, and records that one course is an immediate pre-requisite
	 * of the other.
	 *
	 * @param course1  a course, possibly never seen before
	 * @param prereqOfC1  another course that is an immediate pre-requisite
	 *                    of this one.
	 */
	void addCourses (
			const CourseName& course1,
			const CourseName& prereqOfCourse1);

	/**
	 * Remove a course from the catalog, including any
	 * relationships in which it enables other courses.
	 */
	void removeCourse (const CourseName& c);

	/**
	 * See if a course is already in the catalog.
	 *
	 * @param cname name of a course
	 * @return true iff cname is in the catalog
	 */
	bool containsCourse (const CourseName& cname) const;

	/**
	 * Fetch all known prerequisites of a given course.
	 * @param cname a course name
	 * @return a pair of iterators denoting a begin-end range of course names,
	 *      each of which is an immediate prerequisite of cname.
	 */
	std::pair<CourseMap::const_iterator, CourseMap::const_iterator>
	    getPrereqsOf (const CourseName& cname) const;


	/**
	 * Read a catalog from an input stream.
	 *
	 * Input is repeated lines of
	 *
	 *   course prereq1OfCourse prereq2OfCourse ...
	 *
	 * @param input the input stream
	 */
	void read (istream& input);


	bool operator== (const CourseCatalog& right) const;

private:
  /**
   * Creates the hashing function to use in the unordered set
   * @param c
   * @return
   */
  static std::size_t courseNameHash(const CourseName& c);

	/**
	 * All of the courses offered by this Dept or
	 * required as part of their degree program.
	 */
	CourseSet coursesOffered;

	/**
	 * Prerequisites of each course
	 */
	CourseMap prereqs;


	CourseName parseCourseName (string combined);


};

std::ostream& operator<< (std::ostream& out, const CourseCatalog& cat);

#endif
