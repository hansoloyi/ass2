/* main.cpp */

#include "Scene.h"

using namespace std;

/*
 * Used for miscellaneous testing and debugging purposes.
 */

int main(int argc, char *argv[])
{
  ifstream file(argv[1]);
  Scene sc = Scene(file);
  sc.setUp();
  cout << "run 'open test' to view image\n";
}

