#ifndef SECTION_H
#define SECTION_H

#include <string>
#include <iostream>


#include "course.h"
#include "student.h"

/**
 * A section of a course. Sections are identified by call number,
 * have a course that they are an instance of, and have zero or more
 * enrolled students.
 */
class Section
{
  Course theCourse;
  int theCallNumber;
  
  struct ListNode {
    Student data;
    ListNode* next;

    ListNode (const Student& stu, ListNode* nxt)
      : data(stu), next(nxt)
      {}
  };

  ListNode* firstStudent;  // linked list: Must be kept in order by name
  int numStudents;


public:
  /**
   * Create an empty section with a default course and no students.
   */
  Section ();

  /**
   * Create a section with the given call number and course, and no students.
   *
   * @param course the course that this is a section of
   * @param callNumber the indetifying number for this section.
   */
  Section (Course course, int callNumber);

  /**
   * Copy a section.
   */
  Section (const Section&);

  /**
   * Assign one section to another.
   */
  Section& operator= (const Section&);

  /**
   * Recover storage held by this section.
   */
  ~Section();

  /**
   * Get the course that thyis is a section of.
   *
   * @return the course
   */
  const Course& getCourse() const {return theCourse;}
  int getCallNumber() const       {return theCallNumber;}

  /**
   * How many students are enrolled in this section?
   *
   * @return the number of enrolled students
   */
  int getNumberOfStudents() const {return numStudents;}

  /**
   * Add a student to the section.
   *
   * Students are ordered by name.
   *
   * @param s a student
   */
  void addStudent(Student s);

  /**
   * Compare two sections to see if they are equal.
   *
   * @param right the section to be compared with this one
   * @return true iff the sections have the same course and call number.
   *
   */
  bool operator== (const Section& right) const;

  /**
   * Compare two courses to see which should occur first in a sorted listing.
   * Comparison is on course, with ties broken buy call number.
   *
   * @param right the section to be compared with this one
   * @return true iff this section should be listed before the other.
   */
  bool operator< (const Section& right) const;

private:
  friend std::ostream& operator<< (std::ostream& out, 
				   const Section& section);

};

/**
 * Read a section from an input stream.
 *
 * @param in the input stream
 * @param section the place to receive the read-in data
 */
std::istream& operator>> (std::istream& in, Section& section);

/**
 * Write a section to an output stream
 *
 * @param out the output stream
 * @param section the section to be written
 */
std::ostream& operator<< (std::ostream& out, const Section& section);



#endif
