#ifndef PACKETS_H
#define PACKETS_H

#include <vector>

typedef std::vector<int> Packet;
 
typedef std::vector<Packet> Collection;

int minimumCollectionSize (const Collection& allPackets);


#endif
