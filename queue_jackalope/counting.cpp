#include "counting.h"
#include "matrix.h"

#include <list>
#include <queue>

using namespace std;

/**
 * Count the number of islands (areas composed entirely of
 * non-negative values connected either horizontally or
 * vertically.
 *
 * @param enclosure a rectangular area of represented with -1 for water
 *        and zeros for land.
 * @return the number of unconnected islands
 */
int countTheIslands (const Matrix<int>& enclosure)
{
  // create an enclosure copy to pass to fill
  // that we can change
  Matrix<int> copy_enclosure = enclosure;

	// Should use the fill function
	int island_num = 0;
	for(int i = 0; i < enclosure.length1(); ++i)
	  for(int j = 0; j < enclosure.length2(); ++j)
      if (copy_enclosure(i, j) == 0)
        fill(copy_enclosure, ++island_num, {i , j});

  return island_num;
}


bool shouldChange(Position posToCheck, const Matrix<int> enclosure)
{
  return posToCheck.x < enclosure.length1()
      && posToCheck.y < enclosure.length2()
      && posToCheck.x >= 0
      && posToCheck.y >= 0
      && enclosure(posToCheck.x, posToCheck.y) == 0;
}

void addIfNeeded(Position pos, int value, Matrix<int> &enclosure, std::queue<Position> &queue)
{
  if (shouldChange(pos, enclosure))
  {
    enclosure(pos.x, pos.y) = value;
    queue.push(pos);
  }
}


/**
 * Starting at position p0, put valueToFill into that position and into
 * any positions containing zero connected to p0 by one or more horizontal
 * or vertical steps through other elements also containing zero.
 */
void fill (Matrix<int>& enclosure, int valueToFill, Position p0)
{
	std::queue<Position> island_queue {};

  island_queue.push(p0);
  enclosure(p0.x, p0.y) = valueToFill;

	while (!island_queue.empty())
  {
	  Position current_pos = island_queue.front();

    Position left = {current_pos.x - 1, current_pos.y};
    addIfNeeded(left, valueToFill, enclosure, island_queue);

    Position right = {current_pos.x + 1, current_pos.y};
    addIfNeeded(right, valueToFill, enclosure, island_queue);

    Position top = {current_pos.x, current_pos.y - 1};
    addIfNeeded(top, valueToFill, enclosure, island_queue);

    Position bottom = {current_pos.x, current_pos.y + 1};
    addIfNeeded(bottom, valueToFill, enclosure, island_queue);

    island_queue.pop();
  }
}






