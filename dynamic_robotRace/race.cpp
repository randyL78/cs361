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
  // store the result
  double result = 0.0;

  // store the best result of previous checkpoint
  int last_checkpoint_hit = 0;

  // store size of vector so we aren't repeatedly calling .size()
  int num_of_checkpoints = raceCourse.size();


  // loop through each checkpoint. Since we need to access 2 checkpoints
  // at a time stop 2 short from the number of checkpoints
  for(int i = 1; i < num_of_checkpoints; ++i)
  {
    double time_for_checkpoint = distanceBetween(raceCourse[last_checkpoint_hit], raceCourse[i]);

    // account for 1 second wait time at each checkpoint except finish line
    if (i + 1 != num_of_checkpoints)
      time_for_checkpoint += 1;

    if (i + 1 == num_of_checkpoints || time_for_checkpoint < raceCourse[i].penalty) {
      result += time_for_checkpoint;
      last_checkpoint_hit = i;
    }
    else {
      result += raceCourse[i].penalty;
    }
  }

  return  result;
}

