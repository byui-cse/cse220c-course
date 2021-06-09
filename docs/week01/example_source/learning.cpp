//
//  main.cpp
//  learning_debugging
//
//  Created by Lee Barney on 4/16/20.
//  This work is licensed under a Creative Commons Attribution 4.0 International License.
//

// Libraries and directives for Windows/Linux-based machines necessary to compile this program
#if (defined(_WIN32) || defined(__linux__))
  #ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
  #endif /* _WIN32 */
  #include <cstdarg>
  #include <ctime>
#endif


#include <iostream>

using namespace std;

int total(int count, ...) {

  va_list theNumbers;

  va_start(theNumbers, count); // Set up the list of numbers.

  int sum = 0;
  for (int i = 0; i < count; i++) { //similar to using for..in with a range in Python
    int anInt = va_arg(theNumbers, int); //Get the next int from the list of ints
    sum += anInt;
  }
  va_end(theNumbers); // Clean up.
  return sum;
}

int main(int argc, const char* argv[]) {

  // current date/time based on current system
  time_t now = time(0);

  // convert now to string form
  string currentDateAndTime = ctime(&now);

  cout << "It is now " << currentDateAndTime << endl;


  int theTotal = total(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

  cout << "The total is " << theTotal << endl;
  return 0;
}

