#include <iostream>
#include <iomanip>
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;
using namespace boost;

int main(){
  const unsigned int n=1000000;
  bitset< n > bs;
  dynamic_bitset< > dynbs(n);
   bs.reset();
   dynbs.reset();

  unsigned int i,r,R=10000;
  high_resolution_clock::time_point tick,tock;


  ////////////////////////////////////////////////////////////
  // Method: set

  std::cout << "set" << std::endl;

  tick=high_resolution_clock::now();

  for(r=0; r<R; r++)
    for(i=0; i<n; i++)
      bs.set(i);

  tock=high_resolution_clock::now();
  cout << setw(16) << "bitset: " 
       << setw(16) << duration_cast<nanoseconds>(tock-tick).count() << " nsecs" 
       << std::endl;

  tick=high_resolution_clock::now();

  for(r=0; r<R; r++)
    for(i=0; i<n; i++)
      dynbs.set(i);

  tock=high_resolution_clock::now();
  cout << setw(16) << "dyn bitset: " 
       << setw(16) << duration_cast<nanoseconds>(tock-tick).count() << " nsecs"
       << std::endl << std::endl;


  ////////////////////////////////////////////////////////////
  // Method: flip

  std::cout << "flip" << std::endl;

  tick=high_resolution_clock::now();

  for(r=0; r<R; r++)
    for(i=0; i<n; i++)
      bs.flip(i);

  tock=high_resolution_clock::now();
  cout << setw(16) << "bitset: " 
       << setw(16) << duration_cast<nanoseconds>(tock-tick).count() << " nsecs"
       << std::endl;

  tick=high_resolution_clock::now();

  for(r=0; r<R; r++)
    for(i=0; i<n; i++)
      dynbs.flip(i);

  tock=high_resolution_clock::now();
  cout << setw(16) << "dyn bitset: " 
       << setw(16) << duration_cast<nanoseconds>(tock-tick).count() << " nsecs"
       << std::endl << std::endl;


  ////////////////////////////////////////////////////////////
  // Method: count

  std::cout << "count" << std::endl;

  tick=high_resolution_clock::now();

  for(r=0; r<R; r++)
    for(i=0; i<n; i++)
      bs.count();

  tock=high_resolution_clock::now();
  cout << setw(16) << "bitset: " 
       << setw(16) << duration_cast<nanoseconds>(tock-tick).count() << " nsecs"
       << std::endl;

  tick=high_resolution_clock::now();

  for(r=0; r<R; r++)
    for(i=0; i<n; i++)
      dynbs.count();

  tock=high_resolution_clock::now();
  cout << setw(16) << "dyn bitset: " 
       << setw(16) << duration_cast<nanoseconds>(tock-tick).count() << " nsecs"
       << std::endl;


  return 0;
}

