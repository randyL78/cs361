#ifndef NAME_H
#define NAME_H

#include <iostream>
#include <string>

/**
 * A name, consisting of a first name and last name.
 */
struct Name 
{
  std::string lastName; //!< Last name
  std::string firstName; //!< First name (actually, first plus initial, if any)

  /**
   * Create a name.
   *
   * @param ln last name
   * @param fn first name
   */
  Name (const std::string& ln, const std::string& fn)
    : lastName(ln), firstName(fn)
    {}

  /**
   * Create a name with empty first and last names.
   */
  Name() {}
};

/**
 * Compare two names for conventional alphabetic ordering.
 *
 * @param left one name
 * @param right second named
 * @return true iff left should appear before right in a sorted listing
 */
bool operator< (const Name& left, const Name& right);

/**
 * Compare two names for euqality
 * @param left one name
 * @param right second named
 * @return true iff they have the same first and last name components
 */
bool operator== (const Name& left, const Name& right);

/**
 * Read a name in the form "lastname, firstname"
 *
 * E.g.,   "Smith, John Q"
 *
 * The name is terminated by end of input or by any character < ' '
 * (tab and newline characters being most likely)
 *
 * Leading ' ' are, however, ignored.
 *
 * @param in input stream
 * @param name place to put the read-in data
 **/
std::istream& operator>> (std::istream& in, Name& name);

/**
 * Write a name in the form "lastname, firstname"
 *
 * E.g.,   "Smith, John Q"
 *
 * @param out the output stream
 * @param name the name to write
 **/
std::ostream& operator<< (std::ostream& out, const Name& name);







#endif
