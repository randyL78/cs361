#include "section.h"
#include "faculty.h"


#include <fstream>
#include <cassert>
#include <algorithm>


using namespace std;


const int MaxFaculty = 250;



void loadFacultyAndSections (Faculty* fac, int& nFaculty, 
		const char* fileName)
{
	Section section;

	ifstream in (fileName);
	while (in >> section)
	{
		Name nm;
		in >> nm;

		// Look for this faculty name to see if the faculty
		//   member already exists. If not, add to the array.
		int foundAt = nFaculty;
		for (int i = 0; i < nFaculty && foundAt == nFaculty; ++i)
			if (fac[i].getName() == nm)
				foundAt = i;

		if (foundAt == nFaculty)
		{
			assert (nFaculty < MaxFaculty);
			fac[nFaculty] = Faculty(nm);
			++nFaculty;
		}

		// Add this section to the faculty member
		fac[foundAt].addSection (section);
	}
}



void loadEnrollment (Faculty* fac, int nFaculty, const char* fileName)
{
	Student student;
	int callNumber;

	ifstream in (fileName);
	while (in >> callNumber)
	{
		in >> student;

		// Find the faculty member who teaches this section
		// Look for this faculty name to see if the faculty
		//   member already exists. If not, add to the array.
		int facNum = nFaculty;
		for (int i = 0; i < nFaculty && facNum == nFaculty; ++i)
		{
			if (fac[i].containsSection(callNumber))
			{
				facNum = i;
			}
		}

		// Add this student to the section
		if (facNum < nFaculty)
		{
			Section& section = fac[facNum].getSection(callNumber);
			section.addStudent (student);
		}
	}
}




void report (const Faculty* fac, int nFaculty)
{
	for (int i = 0; i < nFaculty; ++i)
	{
		cout << fac[i] << endl;
	}
}




int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cerr << "Usage: \n";
		cerr << "   " << argv[0] << "sectionsFile enrollmentFile" << endl;
		return 1;
	}


	Faculty faculty[MaxFaculty];
	int numFaculty = 0;

	loadFacultyAndSections (faculty, numFaculty, argv[1]);
	loadEnrollment (faculty, numFaculty, argv[2]);

	sort (faculty, faculty+numFaculty);    // Sorts faculty using
	// operator < to compare them

	report (faculty, numFaculty);

	return 0;
}

