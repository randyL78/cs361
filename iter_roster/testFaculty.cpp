/*
 * testFaculty.cpp
 *
 * Unit tests for Faculty class
 *
 *  Created on: April 28, 2019
 *      Author: zeil
 */

#include "faculty.h"

#include <array>
#include <string>
#include <sstream>

#include "unittest.h"


using namespace std;


const int Section1ID = 21011;
const Course Course1 ("CS", "100");
const Section Section1 (Course1, Section1ID);

const int Section2ID = 21002;
const Course Course2 ("CS", "200");
const Section Section2 (Course2, Section2ID);

const int Section3ID = 21000;
const Course Course3 ("CS", "300");
const Section Section3 (Course3, Section3ID);

std::array<Section, 3> orderedSections = {Section1, Section2, Section3};
std::array<Section, 3> sections = {Section2, Section3, Section1};

// #define DEFAULT_UNIT_TEST_TIME_LIMIT -1L  // Uncomment for debugging


UnitTest (FacultyDefaultConstructor) {
	Faculty fac;
	assertThat (fac.getName(), is(Name()));
	assertThat (fac.getNumberOfSections(), is(0));
	assertFalse (fac.containsSection(Section1ID));
	assertThat (fac, is(Faculty()));
	assertFalse (fac < Faculty());
	assertFalse (Faculty() < fac);

	assertThat(fac.begin(), is(fac.end()));

	ostringstream out;
	out << fac;
	assertThat(out.str(), contains("0"));
}





UnitTest (FacultyNameIterIterConstructor) {
	Name jdoe ("Doe", "John");
	Faculty fac (jdoe, sections.begin(), sections.end());
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(3));
	assertTrue (fac.containsSection(Section1ID));
	assertTrue (fac.containsSection(Section2ID));
	assertTrue (fac.containsSection(Section3ID));
	assertThat (fac, isNot(Faculty()));
	if (fac < Faculty())
		assertFalse (Faculty() < fac);
	else
		assertTrue (Faculty() < fac);

	int ctr = 0;
	for (const Section& section: fac)
	{
		assertThat(section, is(orderedSections[ctr]));
		++ctr;
	}

	ostringstream out;
	out << fac;
	assertThat(out.str(), contains("Doe"));
	assertThat(out.str(), contains("21011"));

	Faculty fac2 (jdoe, orderedSections.begin(), orderedSections.end());
	assertThat (fac, is(fac2));
}







UnitTest (FacultyCopy) {
	Name jdoe ("Doe", "John");
	Faculty fac0 (jdoe);
	fac0.addSection(Section2);
	fac0.addSection(Section3);

	Faculty fac = fac0;

	assertThat (fac.getName(), is(fac0.getName()));
	assertThat (fac.getNumberOfSections(), is(fac0.getNumberOfSections()));


	assertTrue (fac.containsSection(Section3ID));
	assertTrue (fac.containsSection(Section2ID));

	auto it0 = fac0.begin();
	auto it = fac.begin();

	while (it0 != fac0.end() && it != fac.end())
	{
		assertThat (*it, is(*it0));
		++it0;
		++it;
	}
	assertThat (it0, is(fac0.end()));
	assertThat (it, is(fac.end()));

	assertThat(fac.getSection(Section3ID), is(fac0.getSection(Section3ID)));
	assertThat(fac.getSection(Section2ID), is(fac0.getSection(Section2ID)));

	assertThat(fac, is(fac0));
	assertFalse(fac < fac0);
	assertFalse(fac0 < fac);

	ostringstream out;
	out << fac0;
	ostringstream out2;
	out2 << fac;

	assertThat(out.str(), is(out2.str()));

	// Verify that changes to the copy do not affect the original
	fac.addSection(Section1);
	assertThat(fac.getNumberOfSections(), is(fac0.getNumberOfSections()+1));
	assertTrue(fac.containsSection(Section1ID));
	assertFalse(fac0.containsSection(Section1ID));

}

UnitTest (FacultyAssignBasic) {
	Name jdoe ("Doe", "John");
	Faculty fac0 (jdoe);
	fac0.addSection(Section2);
	fac0.addSection(Section3);

	Faculty fac;
	fac = fac0;

	assertThat (fac.getName(), is(fac0.getName()));
	assertThat (fac.getNumberOfSections(), is(fac0.getNumberOfSections()));


	assertTrue (fac.containsSection(Section3ID));
	assertTrue (fac.containsSection(Section2ID));

	assertThat(fac.getSection(Section3ID), is(fac0.getSection(Section3ID)));
	assertThat(fac.getSection(Section2ID), is(fac0.getSection(Section2ID)));

	auto it0 = fac0.begin();
	auto it = fac.begin();

	while (it0 != fac0.end() && it != fac.end())
	{
		assertThat (*it, is(*it0));
		++it0;
		++it;
	}
	assertThat (it0, is(fac0.end()));
	assertThat (it, is(fac.end()));



	assertThat(fac, is(fac0));
	assertFalse(fac < fac0);
	assertFalse(fac0 < fac);

	ostringstream out;
	out << fac0;
	ostringstream out2;
	out2 << fac;

	assertThat(out.str(), is(out2.str()));

	// Verify that changes to the copy do not affect the original
	fac.addSection(Section1);
	assertThat(fac.getNumberOfSections(), is(fac0.getNumberOfSections()+1));
	assertTrue(fac.containsSection(Section1ID));
	assertFalse(fac0.containsSection(Section1ID));
}

UnitTest (FacultyAssignRetVal) {
	Name jdoe ("Doe", "John");
	Faculty fac0 (jdoe);
	fac0.addSection(Section2);
	fac0.addSection(Section3);

	Faculty fac00;

	Faculty fac (fac00 = fac0);

	assertThat (fac.getName(), is(fac0.getName()));
	assertThat (fac.getNumberOfSections(), is(fac0.getNumberOfSections()));


	assertTrue (fac.containsSection(Section3ID));
	assertTrue (fac.containsSection(Section2ID));

	assertThat(fac.getSection(Section3ID), is(fac0.getSection(Section3ID)));
	assertThat(fac.getSection(Section2ID), is(fac0.getSection(Section2ID)));


	assertThat(fac, is(fac0));
	assertFalse(fac < fac0);
	assertFalse(fac0 < fac);

	ostringstream out;
	out << fac0;
	ostringstream out2;
	out2 << fac;

	assertThat(out.str(), is(out2.str()));

	// Verify that changes to the copy do not affect the original
	fac.addSection(Section1);
	assertThat(fac.getNumberOfSections(), is(fac0.getNumberOfSections()+1));
	assertTrue(fac.containsSection(Section1ID));
	assertFalse(fac0.containsSection(Section1ID));
}


UnitTest (FacultyAdd1) {
	Name jdoe ("Doe", "John");
	Faculty fac0(jdoe);
	Faculty fac (jdoe);
	fac.addSection(Section1);
	assertThat (fac, isNot(fac0));
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(1));
	assertTrue (fac.containsSection(Section1ID));
	assertFalse (fac.containsSection(Section2ID));
	assertFalse (fac.containsSection(Section3ID));

	fac.addSection(Section2);
	assertThat (fac, isNot(fac0));
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(2));
	assertTrue (fac.containsSection(Section1ID));
	assertTrue (fac.containsSection(Section2ID));
	assertFalse (fac.containsSection(Section3ID));

	fac.addSection(Section3);
	assertThat (fac, isNot(fac0));
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(3));
	assertTrue (fac.containsSection(Section1ID));
	assertTrue (fac.containsSection(Section2ID));
	assertTrue (fac.containsSection(Section3ID));

	int ctr = 0;
	for (const Section& section: fac)
	{
		assertThat(section, is(orderedSections[ctr]));
		++ctr;
	}

}


UnitTest (FacultyAdd2) {
	Name jdoe ("Doe", "John");
	Faculty fac0(jdoe);
	Faculty fac (jdoe);
	fac.addSection(Section2);
	assertThat (fac, isNot(fac0));
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(1));
	assertTrue (fac.containsSection(Section2ID));
	assertFalse (fac.containsSection(Section3ID));
	assertFalse (fac.containsSection(Section1ID));

	fac.addSection(Section3);
	assertThat (fac, isNot(fac0));
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(2));
	assertTrue (fac.containsSection(Section2ID));
	assertTrue (fac.containsSection(Section3ID));
	assertFalse (fac.containsSection(Section1ID));

	fac.addSection(Section1);
	assertThat (fac, isNot(fac0));
	assertThat (fac.getName(), is(jdoe));
	assertThat (fac.getNumberOfSections(), is(3));
	assertTrue (fac.containsSection(Section2ID));
	assertTrue (fac.containsSection(Section3ID));
	assertTrue (fac.containsSection(Section1ID));

	Faculty fac2 (jdoe, orderedSections.begin(), orderedSections.end());
	assertThat (fac2, is(fac));

	int ctr = 0;
	for (const Section& section: fac)
	{
		assertThat(section, is(orderedSections[ctr]));
		++ctr;
	}


}

UnitTestTimed (FacultyAdd3, 2000) {
	Name jdoe ("Doe", "John");
	int testLimit = 400;
	Faculty fac (jdoe);
	for (int i = 0; i < testLimit; ++i) {
		char j = 33 + (i % 60);
		Course c ("CS", string("00") + j);
		Section s (c, 100 + (int)i);
		Faculty fac0(fac);
		fac.addSection(s);
		assertThat(fac, isNot(fac0));
		assertThat(fac.getNumberOfSections(), is(i+1));
	}

	for (int i = 0; i < testLimit; ++i) {
		assertTrue(fac.containsSection(100+i));
	}

	// Check the ordering of sections
	auto it = fac.begin();
	auto prev = it;
	int cnt = 1;
	++it;
	while (it != fac.end())
	{
		assertThat (*it, isGreaterThanOrEqualTo(*prev));
		prev = it;
		++it;
		++cnt;
	}
	assertThat (cnt, is(testLimit));

}


