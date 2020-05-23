#include "student.h"

using namespace std;



Student::Student()
{
}


Student::Student (Name name)
  : theName(name)
{
}



bool Student::operator== (const Student& right) const
{
  return theName == right.theName;
}

bool Student::operator< (const Student& right) const
{
  return theName < right.theName;
}


