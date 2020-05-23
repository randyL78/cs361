#include "name.h"

using namespace std;


bool operator< (const Name& left, const Name& right)
{
  if (left.lastName != right.lastName)
    return (left.lastName < right.lastName);
  else
    return (left.firstName < right.firstName);
}

bool operator== (const Name& left, const Name& right)
{
  return (left.lastName == right.lastName)
    && (left.firstName == right.firstName);
}


// Read a name in the form "lastname, firstname"
// E.g.,   "Smith, John Q"
// The name is terminated by end of input or by any character < ' '
// (tab and newline characters being most likely)
istream& operator>> (istream& in, Name& name)
{
  name.lastName = name.firstName = "";

  // Skip leading blanks, if any
  char c = ' ';
  while ((c == ' ') && (in.get(c))) {}
  if (c != ' ')
    in.putback(c);

  // Read last name (up to ',')
  while ((c >= ' ') && (c != ',') && (in.get(c)))
    {
      if ((c >= ' ') && (c != ','))
	name.lastName += c;
    }
  
  if (c == ',')
    {
      // Skip blanks after the ','
      c = ' ';
      while ((c == ' ') && (in.get(c))) {}
      if (c != ' ')
	in.putback(c);

      // Read the remainder of the name
      c = ' ';
      while ((c >= ' ') && (in.get(c)))
	{
	  if (c >= ' ')
	    name.firstName += c;
	}
    }
  
  if (c < ' ')
    in.putback(c);
  return in;
}


// Write a name in the form "lastname, firstname"
// E.g.,   "Smith, John Q"
ostream& operator<< (ostream& out, const Name& name)
{
  out << name.lastName << ", " << name.firstName;
  return out;
}


