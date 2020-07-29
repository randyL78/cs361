#include "checkpoint.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

double distanceBetween (const Checkpoint& cp1, const Checkpoint& cp2)
{
  double dx = cp1.x - cp2.x;
  double dy = cp1.y - cp2.y;
  return sqrt(dx*dx + dy*dy);
}

double accumulated_penalties(const vector<Checkpoint>& raceCourse, int start, int stop)
{
  double temp = 0.0;

  for (int i = start; i < stop; ++i)
    temp += raceCourse[i].penalty;

  return temp;
}

double recursiveMinRaceTime (const vector<Checkpoint>& raceCourse, int current_checkpoint, int finish_line) {
  // Base cases
  if (current_checkpoint == 0)
    return 0.0;

  double best_so_far = -1;
  // run through starting at different checkpoints
  for (int i = 0; i < current_checkpoint; ++i)
  {
    double temp_distance = distanceBetween(raceCourse[i], raceCourse[current_checkpoint]);
    double temp_route = recursiveMinRaceTime(raceCourse, i, finish_line);
    double penalties = accumulated_penalties(raceCourse, i + 1, current_checkpoint);
    temp_route += temp_distance + (current_checkpoint == finish_line ? 0.0 : 1.0) + penalties;

    if (best_so_far == -1 || temp_route < best_so_far)
      best_so_far = temp_route;
  }


  if (current_checkpoint == finish_line)
  {
    return best_so_far;
  }

  double penalty_route = recursiveMinRaceTime(raceCourse, current_checkpoint - 1, finish_line);
  penalty_route += raceCourse[current_checkpoint].penalty;

  return (best_so_far < penalty_route) ? best_so_far : penalty_route;
}

double tableMinRaceTime(const vector<Checkpoint>& raceCourse)
{
  // store size of vector so we aren't repeatedly calling .size()
  int num_of_checkpoints = raceCourse.size();
  /**
   * ***** Penalties Table *****
   */
  // table to store the different penalty combinations
  int penalties[num_of_checkpoints][num_of_checkpoints];

  // build out diagonal of penalty table
  for(int i = 0; i < num_of_checkpoints; ++i)
    penalties[i][i] = raceCourse[i].penalty;

  // build upper triangle of penalty table
  for(int i = 0; i < num_of_checkpoints; ++i)
  {
    for(int j = i + 1; j < num_of_checkpoints; ++j)
    {
      penalties[i][j] = raceCourse[j].penalty + penalties[i][j-1];
    }
  }

  /**
   * ***** Main Table *****
   */
  // table to store the different distance combinations
  double distances[num_of_checkpoints + 1][num_of_checkpoints + 1];
  int current_checkpoint = 0;

  for (int i = 0; i < num_of_checkpoints; ++i)
    distances[i][0] = distanceBetween(raceCourse[0], raceCourse[i]) + penalties[0][i];
  for(int i = 1; i < num_of_checkpoints; ++i) {
    double distance = distanceBetween(raceCourse[current_checkpoint], raceCourse[i]);
    if (i == num_of_checkpoints - 1) {
      distances[0][i] = distance + distances[0][i - 1];
    } else {
      ++distance;


      double current_penalty = penalties[current_checkpoint + 1][i + 1];


      if (distance < current_penalty) {
        distances[0][i] = distance + distances[0][i - 1];
        current_checkpoint = i;
      } else {
        distances[0][i] = current_penalty + distances[0][i - 1];
      }
    }
  }

  current_checkpoint = 0;
  for(int i = 1; i < num_of_checkpoints; ++i) {
    double distance = distanceBetween(raceCourse[current_checkpoint], raceCourse[i]);
    if (i == num_of_checkpoints - 1) {
      distances[1][i] = distance + distances[1][i - 1];
    } else {
      ++distance;


      double current_penalty = penalties[current_checkpoint + 1][i + 1];


      if (distance < current_penalty) {
        distances[1][i] = distance + distances[1][i - 1];
        current_checkpoint = i;
      } else {
        distances[1][i] = current_penalty + distances[1][i - 1];
      }
    }
  }

  for (int j = 0; j < num_of_checkpoints; ++j)
  {
    for(int i = 0; i < num_of_checkpoints; ++i)
      cout << setw(8) << setprecision(3) << distances[j][i];

    cout << endl;
  }

  return  distances[0][num_of_checkpoints - 1];
}


double minRaceTime (const vector<Checkpoint>& raceCourse)
{
  int num_of_checkpoints = raceCourse.size();
//  return recursiveMinRaceTime(raceCourse, num_of_checkpoints - 1, num_of_checkpoints - 1);
  return tableMinRaceTime(raceCourse);

  double distances[num_of_checkpoints][num_of_checkpoints];
  distances[0][0] = 0.0;

  for (int i = 1; i < num_of_checkpoints; ++i)
  {
    distances[0][i] = distanceBetween(raceCourse[i-1], raceCourse[i]) + (i == num_of_checkpoints - 1 ? 0 : 1);
    distances[i][0] = raceCourse[i].penalty;
  }

  for (int i = 1; i < num_of_checkpoints; ++i)
  {
    for (int j = 1; j < num_of_checkpoints; ++j)
    {
      double cost_to_travel = distances[i - 1][j - 1] + distances[i - 1][j];
      double cost_to_skip = distances[i - 1][j - 1] + distances[i][j - 1];
      cout << cost_to_travel << " " << cost_to_skip << endl;
      distances[i][j] = min(cost_to_travel, cost_to_skip);
    }
  }

  for (int i = 0; i < num_of_checkpoints; ++i) {
    for (int j = 0; j < num_of_checkpoints; ++j) {
      cout << setw(8) << setprecision(3) << distances[i][j];
    }
    cout << endl;
  }
  return distances[num_of_checkpoints - 1][num_of_checkpoints - 1];
}

