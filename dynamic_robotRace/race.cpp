#include "checkpoint.h"
#include <cmath>
#include <vector>

using namespace std;


double distanceBetween (const Checkpoint& cp1, const Checkpoint& cp2)
{
  double dx = cp1.x - cp2.x;
  double dy = cp1.y - cp2.y;
  return sqrt(dx*dx + dy*dy);
}


double minRaceTime (const vector<Checkpoint>& raceCourse)
{
  /** your solution here **/
}

