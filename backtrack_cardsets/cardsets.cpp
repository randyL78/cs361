#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <iterator>
#include <functional>


#include "packets.h"

using namespace std;

void run(istream& input)
{
  // Reads a set of packet descriptions, one packet per line.
  // Each line consists of 1 or more integers
  // Prints the minimum number of packets required to cover all
  //   the integers occurring in any packet.

  vector<Packet> packets;
  
  string line;
  while (getline(input, line))
    {
      Packet packet;
      
      istringstream in (line);
      copy (istream_iterator<int>(in), 
			istream_iterator<int>(),
			inserter(packet, packet.end()));
	  
      if (!packet.empty())
		{
		  if (*(packet.begin()) >= 0)
			packets.push_back (packet);
		  else
			break;
		}
    }
  
  cout << minimumCollectionSize(packets)
       << " packets required for a full collection."
       << endl;
}


int main (int argc, char** argv)
{
  if (argc > 1)
	{
	  ifstream in (argv[1]);
	  run (in);
	}
  else
	{
	  run (cin);
	}
  return 0;
}
