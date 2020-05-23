#include "faculty.h"

#include <cassert>

using namespace std;


Faculty::Faculty (int maxSections)
  : theMaxSections(10000), numSections(0)
{
}

Faculty::Faculty (Name name, int maxSections)
  : theName(name), theMaxSections(10000), numSections(0)
{
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
