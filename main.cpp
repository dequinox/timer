#include <iostream>
#include "Timer.h"
using namespace std;


int main(int argc, char *argv[])
{
      string operation = argv[1];
      string argv2 = argv[2] == NULL ? "" : argv[2];

      if (operation == "start")    Timer::start(argv2);
      if (operation == "status")   Timer::status(argv2, 7);
      if (operation == "stop")     Timer::stop();
      if (operation == "projects") Timer::projects();
      if (operation == "log")      Timer::logs();
      if (operation == "delete")   Timer::clear();

      return 0;
}
