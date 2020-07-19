#include "packets.h"

#include <vector>
#include <set>

#include <algorithm>
#include <iostream>
#include "backtrack.h"

using namespace std;


// Returns the maximum packet value in the collection
int findMax(const Collection& allPackets)
{
  int max = 0;
  // quadratic time... not the model of efficiency I know.
  for (Packet packet: allPackets)
    for (int card : packet)
      if(card > max)
        max = card;

  return max;
}

// Returns the number of packets in the solution, or 0 if not a solution
int checkSolution(BackTrack bt, const Collection& all_packets, int size, int max_card)
{
  // Using a set here since it automatically filters out duplicates
  std::set<int> cards;
  int number_of_cards = 0;

  for(int i = 0; i < size; ++i) {
    if(bt[i] == 1) {
      cards.insert(all_packets[i].begin(), all_packets[i].end());
      ++number_of_cards;
    }
  }

  return cards.size() == max_card ? number_of_cards : 0;
}

// Sets up the minimumCollectionSize function as a backtracking problem.
// # of backtracking variables = # of packets
// Each variable takes on two possible values:
//    0 = packet is not in the collection
//    1 = packet is in the collection
int minimumCollectionSize (const Collection& allPackets)
{
  // Vector to keep track of all the solutions. The minimum value in
  // the solution set is the one we want to return.
  vector<int> solutions;

  // Find the number of possible answers by finding unique packet values in the
  // collection. Since these are aliases for integers and are contiguous, then this
  // amounts to finding the max value.
  int max_card = findMax(allPackets);

  // Since we are dealing with a vector that isn't changing, we only want to check
  // the size once!
  int all_packets_count = allPackets.size();

  BackTrack bt(all_packets_count, 2);

  // Since there could be multiple solutions, and we want the minimum one, we
  // don't need to check for solved in the condition.
  while (bt.more())
  {
    // check current bt to see if it is a solution, if it is push the number of cards in
    // the solution to the solutions vector.
    int solved = checkSolution(bt, allPackets, all_packets_count, max_card);
    if(solved > 0)
      solutions.push_back(solved);

    // Since we are storing the solutions in a vector, no need to check for solution
    // before incrementing.
    ++bt;
  }

  // make sure solutions isn't empty and then return the minimum number in it.
  return solutions.begin() == solutions.end() ? 0 : *min_element(solutions.begin(), solutions.end());
}
