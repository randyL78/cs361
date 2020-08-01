#include "packets.h"

#include <vector>

#include <algorithm>
#include "backtrack.h"

using namespace std;


// Sets up the minimumCollectionSize function as a backtracking problem.
// # of backtracking variables = # of packets
// Each variable takes on two possible values:
//    0 = packet is not in the collection
//    1 = packet is in the collection




//
// Compute the number of cards in a collection.
//
int numberOfCardsInCollection (const Collection& purchasedpackets)
{
  Packet collection;
  for (unsigned i = 0; i < purchasedpackets.size(); ++i)
  {
    Packet theUnion;

    set_union (collection.begin(), collection.end(),
               purchasedpackets[i].begin(), purchasedpackets[i].end(),
               inserter(theUnion, theUnion.end()));
    theUnion.swap (collection);
  }

  // How many cards did we end up with?
  return collection.size();
}



int minimumCollectionSize (const Collection& allPackets)
{
  int nPackets = allPackets.size();
  int totalNumberOfCards = numberOfCardsInCollection(allPackets);

  BackTrack backtrack (nPackets, 2);
  int smallestSolutionSoFar = nPackets;

  while (backtrack.more())
  {
    Collection solution;
    int nPacketsInSolution = 0;
    for (int i = 0; i < nPackets; ++i)
    {
      if (backtrack[i] == 1)
      {
        solution.push_back (allPackets[i]);
        ++nPacketsInSolution;
      }
    }
    int nCards = numberOfCardsInCollection(solution);
    if (nCards == totalNumberOfCards)
    {
      smallestSolutionSoFar = min(smallestSolutionSoFar,
                                  nPacketsInSolution);
    }

    // To speed things up, if the number of packets in our solution
    // is already as large as smallestSolutionSoFar, then there's no
    // point to trying any solutions that add still more packets, so
    // we prune at the highest numerbered packet in the collection.
    if (nPacketsInSolution >= smallestSolutionSoFar)
    {
      int maxPacket = 0;
      for (int i = 0; i < nPackets; ++i)
        if (backtrack[i] == 1)
          maxPacket = i;
      backtrack.prune(maxPacket);
    }
    else
      ++backtrack;
  }
  return smallestSolutionSoFar;
}