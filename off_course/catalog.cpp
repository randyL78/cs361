#include "catalog.h"

#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;


CourseCatalog::CourseCatalog()
{

}

void CourseCatalog::read (istream& input)
{
  string line;
  getline(input, line);
  while (input) {
    istringstream in(line);
    string word;
    in >> word;
    CourseName c1 = parseCourseName(word);
    coursesOffered.insert(c1);
    while (in >> word)
    {
      CourseName c2 = parseCourseName(word);
      addCourses(c1, c2);
    }
    getline(input, line);
  }
}


/**
 * Adds a pair of courses to the catalog if they have not previously been
 * encountered, and records that one course is an immediate pre-requisite
 * of the other.
 *
 * @param course1  a course, possibly never seen before
 * @param prereqOfC1  another course that is an immediate pre-requisite
 *                    of this one.
 */
void CourseCatalog::addCourses (
        const CourseName& course1,
        const CourseName& prereqOfCourse1)
{
  coursesOffered.insert({prereqOfCourse1, course1});
  prereqs.insert(make_pair(course1, prereqOfCourse1));
}


/**
 * Remove a course from the catalog, including any
 * relationships in which it enables other courses.
 */
void CourseCatalog::removeCourse (const CourseName& c)
{
  // Erase prereqs by value. Would be simple if they were
  // the keys, but by value not so much.
  // Iterate through the prereqs, if the value matches c
  // then erase it.
  // based on solution by @Scrontch in https://stackoverflow.com/questions/2115640/stl-multimap-remove-erase-values
  for (auto i = prereqs.begin(); i != prereqs.end();)
  {
    if(i->second == c)
      // i becomes invalid after erase so we have to use
      // the return value of erase() to make it valid again.
      i = prereqs.erase(i);
    else
      ++i;
  }

  coursesOffered.erase(c);
}


std::pair<CourseCatalog::CourseMap::const_iterator, CourseCatalog::CourseMap::const_iterator>
CourseCatalog::getPrereqsOf(const CourseName &cname) const
{
  return prereqs.equal_range(cname);
}

bool CourseCatalog::containsCourse (const CourseName& cname) const
{
	return coursesOffered.find(cname) != coursesOffered.end();
}

CourseName CourseCatalog::parseCourseName (string combined)
{
  int i = 0;
  while (combined[i] >= 'a')
    ++i;
  string dept = combined.substr(0, i);
  istringstream numIn (combined.substr(i));
  int num;
  numIn >> num;
  return CourseName(dept, num);
}

std::size_t CourseCatalog::courseNameHash(const CourseName &c)
{
  size_t dept_hash = hash<string>{}(c.dept);
  size_t num_hash = hash<int>{}(c.num);
  return dept_hash + 31 * num_hash;
}

bool CourseCatalog::operator== (const CourseCatalog& right) const
{
	return right.coursesOffered == coursesOffered;
}

std::ostream& operator<< (std::ostream& out, const CourseCatalog& cat)
{
  vector<CourseName> sorted_courses(cat.begin(), cat.end());
  sort(sorted_courses.begin(), sorted_courses.end());
  for (auto c : sorted_courses)
  {
    out << c << endl;
  }
	return out;
}

