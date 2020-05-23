#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

#include "name.h"


/**
 * A minimal class for describing students.
*/

class Student {
  Name theName;
public:
  /**
   * Create a student with an empty/default name
   */
  Student();

  /**
   * Create a student with the indicated name.
   *
   * @param name the student's name
   */
  Student (Name name);

  /**
   * Get the student's name.
   *
   * @return the name
   */
  Name getName() const  {return theName;}

  /**
   * Compare two students for equality
   */
  bool operator== (const Student& right) const;

  /**
   * Compare two students to see which should be listed first.
   */
  bool operator< (const Student& right) const;

};

/**
 * Read a student from an input stream.
 */
std::istream& operator>> (std::istream& in, Student&);

/**
 * Write a student to an output stream.
 */
std::ostream& operator<< (std::ostream& out, const Student&);





#endif
