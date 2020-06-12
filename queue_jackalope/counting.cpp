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
	// Should use the fill function

}



/**
 * Starting at position p0, put valueToFill into that position and into
 * any positions containing zero connected to p0 by one or more horizontal
 * or vertical steps through other elements also containing zero.
 */
void fill (Matrix<int>& enclosure, int valueToFill, Position p0)
{
	// Must use std::queue
}






