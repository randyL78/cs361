#include "faculty.h"

#include <cassert>

using namespace std;


Faculty::Faculty (int maxSections)
  : theMaxSections(10000), numSections(0), sections(new Section[theMaxSections])
{
}

Faculty::Faculty (Name name, int maxSections)
  : theName(name), theMaxSections(10000), numSections(0), sections(new Section[theMaxSections])
{
}

Faculty::Faculty (Name name, iterator startSection, iterator stopSection)
  : theName(name), theMaxSections(10000), numSections(0), sections(new Section[theMaxSections])
{
    for (auto it = startSection; it < stopSection; it++)
    {
      addSection(*it);
    }
}

Faculty::Faculty(const Faculty &faculty)
  : theName(faculty.theName), theMaxSections(10000), numSections(0)
  , sections(new Section[theMaxSections])
{
  for (auto it = faculty.begin(); it < faculty.end(); it++)
  {
    addSection(*it);
  }
}

Faculty::Faculty(Faculty &&faculty)
  : theName(faculty.theName), theMaxSections(10000), numSections(faculty.numSections)
  , sections(faculty.sections)
{
  // release the memory pointing to the faculty that is moving's pointer variables
  faculty.sections = nullptr;
}

const Section& Faculty::getSection (int callNumber) const
{
  int i = 0;
  while (i < numSections && sections[i].getCallNumber() != callNumber)
    ++i;

  assert (i < numSections);
  return sections[i];
}

Section& Faculty::getSection (int callNumber)
{
  int i = 0;
  while (i < numSections && sections[i].getCallNumber() != callNumber)
    ++i;

  assert (i < numSections);
  return sections[i];
}


bool Faculty::containsSection (int callNumber) const
{
  int i = 0;
  while (i < numSections && sections[i].getCallNumber() != callNumber)
    ++i;

  return (i < numSections);
}


void Faculty::addSection(Section s)
{
  assert (numSections < theMaxSections);
  ++numSections;
  int k = numSections -1;
  while (k > 0 && s < sections[k-1])
  {
	  sections[k] = sections[k-1];
	  --k;
  }
  sections[k] = s;
}

// Iterator functions
Faculty::iterator Faculty::begin()
{
  return sections; // TODO: make this more generic and not reliant on array type
}

Faculty::const_iterator Faculty::end() const
{
  return sections + numSections;  // TODO: make this more generic and not reliant on array type
}

Faculty::const_iterator Faculty::begin() const
{
  return sections; // TODO: make this more generic and not reliant on array type
}

Faculty::iterator Faculty::end()
{
  return sections + numSections;  // TODO: make this more generic and not reliant on array type
}

bool Faculty::operator== (const Faculty& right) const
{
  if (!(getName() == right.getName())
		  || getNumberOfSections() != right.getNumberOfSections())
		return false;
  for (int i = 0; i < getNumberOfSections(); ++i)
  {
	  if (!(sections[i] == right.sections[i]))
		  return false;
  }
  return true;
}


bool Faculty::operator< (const Faculty& right) const
{
  if (getName() == right.getName())
  {
  	  int limit = min(getNumberOfSections(), right.getNumberOfSections());

  	  for (int i = 0; i < limit; ++i)
  	  {
  		  const Section& lft = sections[i];
  		  const Section& rght = right.sections[i];
  		  if (lft < rght)
  			  return true;
  		  else if (rght < lft)
  			  return false;
  	  }
  	  return getNumberOfSections() < right.getNumberOfSections();
  }
  else
	  return getName() < right.getName();
}

const Faculty& Faculty::operator=(const Faculty &rhs)
{
  theName = rhs.getName();

  for (auto it = rhs.begin(); it < rhs.end(); it++)
  {
    addSection(*it);
  }

  return *this;
}