#include "course.h"
#include "unittest.h"
#include <array>
#include <list>
#include <sstream>

using namespace std;

/**
 * A "test fixture" is a mechanism for providing common access to test
 * data that may be used in multiple tests.
 *
 *
 */
class CNFixture {
public:
	const CourseName cs150;
	const CourseName cs250;
	const CourseName cs361;
	const CourseName cs330;
	const CourseName cs350;

	std::array<CourseName, 2> courses2;
	std::array<CourseName, 3> courses3;
	std::array<CourseName, 4> courses4;
	std::array<CourseName, 5> courses5;


	CNFixture();

};

CNFixture::CNFixture()
: cs150 ("CS", 150),
  cs250 ("CS", 250),
  cs361 ("CS", 361),
  cs330 ("CS", 330),
  cs350 ("CS", 350),
  courses2{cs361, cs330},
  courses3{cs150, cs250, cs361},
  courses4{cs150, cs250, cs361, cs330},
  courses5{cs150, cs250, cs361, cs330, cs350}
{

}



UnitTest(CourseDefaultConstructor) {
	Course c;
	assertThat (c.getName(), isEqualTo(CourseName()));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(0));
	assertThat (c, isEqualTo(Course()));
	assertThat (c, not(isLessThan(Course())));
	assertThat (c, not(isGreaterThan(Course())));
}

UnitTest(CourseConstructor) {
	CourseName cs150 ("CS", 150);
	CourseName math150 ("MATH", 150);
	CourseName cs250 ("CS", 250);
	Course c (cs150);

	assertThat (c.getName(), isEqualTo(cs150));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(0));
	assertThat (c, isNotEqualTo(Course()));
	assertThat (c, isLessThan(Course(math150)));
	assertThat (c, isLessThan(Course(cs250)));

	assertThat (c.begin(), isEqualTo(c.end()));

	ostringstream out;
	out << c;
	assertThat (out.str(), contains("CS150"));
}

UnitTest(CourseConsInitList0) {
	CNFixture fix;
	Course c (fix.cs350, {fix.cs150, fix.cs361, fix.cs330});

	assertThat (c.getName(), isEqualTo(fix.cs350));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (c, isNotEqualTo(Course()));
	assertThat (c, isLessThan(Course(fix.cs361)));
	assertThat (c, isGreaterThan(Course(fix.cs250)));

	ostringstream out;
	out << c;
	assertThat (out.str(), contains("CS350 (CS150,CS361,CS330)"));
}

UnitTest(CourseConsInitListSingle) {
	CNFixture fix;
	Course c (fix.cs350, {fix.cs330});

	assertThat (c.getName(), isEqualTo(fix.cs350));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c, isNotEqualTo(Course()));
	assertThat (c, isLessThan(Course(fix.cs361)));
	assertThat (c, isGreaterThan(Course(fix.cs250)));

	ostringstream out;
	out << c;
	assertThat (out.str(), contains("CS350 (CS330)"));
}

UnitTest(CourseConsInitListEmpty) {
	CNFixture fix;
	Course c (fix.cs350, {});

	assertThat (c.getName(), isEqualTo(fix.cs350));
	assertThat (c.getNumberOfPrereqs(), isEqualTo(0));
	assertThat (c, isNotEqualTo(Course()));
	assertThat (c, isLessThan(Course(fix.cs361)));
	assertThat (c, isGreaterThan(Course(fix.cs250)));

	ostringstream out;
	out << c;
	assertThat (out.str(), contains("CS350 ()"));
}

UnitTest(CourseConsIter0) {
	CNFixture fix;
	Course c1 (fix.cs350, fix.courses3.begin(), fix.courses3.end());

	vector<CourseName> v(fix.courses3.begin(), fix.courses3.end());
	Course c2 (fix.cs350, v.begin(), v.end());

	assertThat (c1.getName(), isEqualTo(fix.cs350));
	assertThat (c1.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (c1, isEqualTo(c2));

	list<CourseName> list(fix.courses4.begin(), fix.courses4.end());
	Course c3 (fix.cs350, list.begin(), list.end());

	assertThat(c1, isNotEqualTo(c3));

	ostringstream out;
	out << c1;
	assertThat (out.str(), contains("CS350 (CS150,CS250,CS361)"));
}

/**
 * Generate an always empty iterator range
 */
class BogusContainer {
	CourseName x;
public:
	typedef CourseName* iterator;
	typedef const CourseName* const_iterator;

	iterator begin() {return &x;}
	iterator end() {return &x;}

	const_iterator begin() const {return &x;}
	const_iterator end() const {return &x;}
};

UnitTest(CourseConsIterEmpty) {
	CNFixture fix;
	Course c1 (fix.cs350, fix.courses3.begin(), fix.courses3.begin());

	vector<CourseName> v(fix.courses3.begin(), fix.courses3.end());
	Course c2 (fix.cs350, v.begin()+1, v.begin()+1);

	assertThat (c1.getName(), isEqualTo(fix.cs350));
	assertThat (c1.getNumberOfPrereqs(), isEqualTo(0));
	assertThat (c1, isEqualTo(c2));

	BogusContainer bc;
	Course c3 (fix.cs350, bc.begin(), bc.end());

	assertThat(c1, isEqualTo(c3));

	ostringstream out;
	out << c1;
	assertThat (out.str(), contains("CS350 ()"));
}






UnitTest(CourseAddPrereq) {
	CNFixture fix;

	Course c0(fix.cs350);
	Course c (fix.cs350);
	assertThat (c, isEqualTo(c0));

	c.addPrereq(fix.cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c, isNotEqualTo(c0));
	assertThat (*(c.begin()), isEqualTo(fix.cs361));

	c.addPrereq(fix.cs330);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertTrue (equal(c.begin(), c.end(),
			    fix.courses2.begin(), fix.courses2.end()));

	c.addPrereq(fix.cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertTrue (equal(c.begin(), c.end(),
			    fix.courses2.begin(), fix.courses2.end()));

	ostringstream out;
	out << c;
	string outStr = out.str();
	assertThat (outStr, contains("CS350"));
	assertThat (outStr, contains("CS330"));
	assertThat (outStr, contains("CS361"));

}

UnitTest(CourseRemovePrereq) {
	CNFixture fix;

	Course c0(fix.cs350);
	Course c (fix.cs350);
	assertThat (c, isEqualTo(c0));

	c.addPrereq(fix.cs361);
	c.addPrereq(fix.cs330);

	c.removePrereq(fix.cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (*(c.begin()), isEqualTo(fix.cs330));

	ostringstream out;
	out << c;
	string outStr = out.str();
	assertThat (outStr, contains("CS350"));
	assertThat (outStr, contains("CS330"));
	assertThat (outStr, not(contains("CS361")));

}




UnitTest(CourseCopy) {
	CNFixture fix;

	Course c(fix.cs350);
	c.addPrereq(fix.cs361);
	c.addPrereq(fix.cs330);

	Course c2 (c);
	assertThat(c2, isEqualTo(c));

	c2.addPrereq(fix.cs150);
	assertThat(c2, isNotEqualTo(c));

	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertTrue (equal(c.begin(), c.end(),
			fix.courses2.begin(), fix.courses2.end()));

	std::array<CourseName, 3> c2prereqs {fix.cs361, fix.cs330, fix.cs150};
	assertTrue (equal(c2.begin(), c2.end(),
				c2prereqs.begin(), c2prereqs.end()));

	c.removePrereq(fix.cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (*(c.begin()), isEqualTo(fix.cs330));
	assertTrue (equal(c2.begin(), c2.end(),
					c2prereqs.begin(), c2prereqs.end()));
}

UnitTest(CourseAssign) {
	CNFixture fix;

	Course c(fix.cs350);
	c.addPrereq(fix.cs361);
	c.addPrereq(fix.cs330);

	Course c2;
	Course c3(c2 = c);
	assertThat(c2, isEqualTo(c));
	assertThat(c3, isEqualTo(c));

	c2.addPrereq(fix.cs150);
	assertThat(c2, isNotEqualTo(c));

	assertThat (c.getNumberOfPrereqs(), isEqualTo(2));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertTrue (equal(c.begin(), c.end(),
			fix.courses2.begin(), fix.courses2.end()));

	std::array<CourseName, 3> c2prereqs {fix.cs361, fix.cs330, fix.cs150};
	assertTrue (equal(c2.begin(), c2.end(),
				c2prereqs.begin(), c2prereqs.end()));

	c.removePrereq(fix.cs361);
	assertThat (c.getNumberOfPrereqs(), isEqualTo(1));
	assertThat (c2.getNumberOfPrereqs(), isEqualTo(3));
	assertThat (*(c.begin()), isEqualTo(fix.cs330));
	assertTrue (equal(c2.begin(), c2.end(),
					c2prereqs.begin(), c2prereqs.end()));
}


UnitTest(zzCheckForMemoryLeaks) {
	assertThat(MemoryChecked::getCurrentCount(), isEqualTo(0));
}


