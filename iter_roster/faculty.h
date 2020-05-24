#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <iostream>
#include <iterator>

#include "name.h"
#include "section.h"

/**
 * A faculty member at the university.
 *
 * Faculty have names, and are responsible for teaching sections
 * of courses.
 */
class Faculty
{
  Name theName;

  int theMaxSections;
  int numSections;
  Section* sections;


  // Iterator types
  typedef Section*          iterator;
  typedef const Section*    const_iterator;


public:
  /**
   * Create a faculty member with empty/default name.
   *
   * @param maxSection maximum number of sections that we can later add
   *           to this faculty member
   */
  Faculty (int maxSections = 100);

  /**
   * Create a faculty member with the given name, to which we can
   * later add up to maxSections course sections.
   *
   * @param name name for this faculty member
   * @param maxSection maximum number of sections that we can later add
   *           to this faculty member
   */
  Faculty (Name name, int maxSections = 100);

  /**
   * Create a faculty member with given name and add sections from a range
   * of sections
   * @param name name for this faculty member
   * @param startSection
   * @param stopSection
   */
  Faculty (Name name, iterator startSection, iterator stopSection);

  /**
   * Copy constructor. Creates a deep copy of the Faculty given
   * @param faculty
   */
  Faculty (const Faculty &faculty);

  /**
   * Get the faculty member's name.
   * @return the name
   */
  Name getName() const {return theName;}

  /**
   * Get the number of sections currently assigned to this
   * faculty member.   Initially zero when the Faculty object
   * is created, this increases with every addSection call.
   *
   * @return number of sections
   */
  int getNumberOfSections() const {return numSections;}

  /**
   * Get the section stored with the indicated call number.
   *
   * @param callNumber identifier for the section we are looking for.
   *
   * @pre containsSection(callNumber)
   */
  const Section& getSection (int callNumber) const;
  Section& getSection (int callNumber);


  /**
   * Determine if the faculty member teaches this section.
   *
   * @param callNumber identifier for the section we are looking for.
   * @return true iff that section has previsouly been added to this faculty
   *     member
   */
  bool containsSection (int callNumber) const;

  /**
   * Add a section to this faculty member.
   *
   * @param sect a course section
   * @pre getNumberOfSections() < mx where mx is the maxSections value
   *       used when the object was created.
   */
  void addSection(Section sect);

  /**
   * Two faculty objects are equal if their names are equal and if they contain
   * equal sections, even if those sections were added in different orders.
   *
   * @param right  the other faculty member to be compared to this one
   * @return true iff the names are equal, the number of sections are equal,
   *    and if each section in one faculty is equal to a section in the other.
   */
  bool operator== (const Faculty& right) const;

  /**
   * One faculty member is < the other if its name is < than the other's.
   * If the names are equal, then the sections may be ordered in any fashion
   * such for for any two faculty f1 and f2, exactly one of the following
   * conditions folds:
   *
   * - f1 == f2
   * - f1 < f2
   * - f2 < f1
   *
   * @param right  the other faculty member to be compared to this one
   * @return true iff this faculty member should be listed before the other
   */
  bool operator< (const Faculty& right) const;

  // Iterator functions
  // Begin
  // End
  // Size
  // TODO:Type will need to change from an int to an iterator once I get more into the function
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  /**
   * Assigns the Faculty on the right to the faculty on the left
   * @param rhs the Faculty to copy
   * @return a copy of Faculty to assign
   */
  const Faculty& operator=(const Faculty &rhs);



private:
  friend std::ostream& operator<< (std::ostream& out, const Faculty& fac);
};

/**
 * Writes out the faculty member's name and sections, with sections
 * displayed in sorted (increasing) order according to the Section::operator<
 * relation.
 *
 * @param out the stream to which to write
 * @param fac the faculty member to be written
 */
std::ostream& operator<< (std::ostream& out, const Faculty& fac);



#endif
