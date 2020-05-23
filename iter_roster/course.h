#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

/**
 * A course at the university. Courses are identified by
 * department and number, although the course "number"
 * can actually include non-numeric elements.
 */
class Course {
  std::string theDept;
  std::string theNumber;
public:
  /**
   * Create a course with an empty dept and number.
   */
  Course();

  /**
   * Create a course with the given name and number.
   */
  Course (std::string dept, std::string number);

  /**
   * Get the department string for a course.
   * @return the dept
   */
  std::string getDept() const  {return theDept;}

  /**
   * Get the number for a course.
   * @return the number
   */
  std::string getNumber() const {return theNumber;}

  /**
   * Compare two courses to see if they have the same dept and number.
   *
   * @param right the other course to compare to this one
   * @return true iff the dept and number are equal.
   */
  bool operator== (const Course& right) const;


  /**
   * Compare two courses to see what order they should appear
   * in a sorted listing
   *
   * @param right the other course to compare to this one
   * @return true iff this course should be lsited before the other.
   */
  bool operator< (const Course& right) const;

};


/**
 * Read a course in the form "DEPT NUMBER"
 * The dept is terminated by a blank space or by a numeric digit,
 * (the first digit of the number). Leading ' ' are ignored.
 *
 * @param in the stream from which to read
 * @param course the variable in which to place the read-in data
 * */
std::istream& operator>> (std::istream& in, Course& course);

/**
 * Write a Course in the form "DEPT NUMBER" with no intervening space.
 *
 * @param out the output stream on which to write
 * @param course the course to be written
 */
std::ostream& operator<< (std::ostream& out, const Course& course);






#endif
