#include <cstdlib>
#include <iostream>
#include <sstream>
#include <time.h>

#include "kthLargest.h"

using namespace std;

void generate (int* a, int n)
{
  for (int i = 0; i < n; ++i)
	{
	  a[i] = rand();
	}
}

int main(int argc, char** argv)
{
  if (argc != 3)
    {
      cerr << "When you run this program, you must supply two parameters.\n" 
           << "The first is the size of the arrays you want to generate.\n"
           << "The second is the number of trials you want to perform.\n"
           << "\n"
           << "For example, if you called this program driver, you\n"
           << "might invoke it as:\n"
           << "   driver 100 10 \n"
           << "to generate 10 random trials on arrays of 100 elements each."
	     << endl;
      return 1;
    }

  int N;
  int trials;

  {
    istringstream arg1 (argv[1]);
    arg1 >> N;

    istringstream arg2 (argv[2]);
    arg2 >> trials;
  }
  

  srand(time(0));

  int *array = new int[N]; // O(1)

  for (int t = 0; t < trials; t++) // total: O(trials*f(N))
    {                              // where f(N) is the complexity of randSearch
	  if (t % N == 0) {
		  // Once every N trials, generate a new array.
		  // This amortizes to O(1) per trial, so array generation
		  // should not be slow enough to significantly affect the
		  // timing reulsts.
		  //
		  generate (array, N);  // O(N), but amortizes
	  }
	  int k = rand() % N;  // randomly select a value to search for
	  int value = kthLargest (array, N, k);
    }

  return 0;
}


   