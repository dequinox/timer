#include <iostream>
#include "Timer.h"
using namespace std;


int main(int argc, char *argv[])
{
      string operation = argv[1];

      if (operation == "start")    Timer::start(argv[2]);
      if (operation == "status")   Timer::status(argv[2], 7);
      if (operation == "stop")     Timer::stop();
      if (operation == "projects") Timer::projects();
      if (operation == "log")      Timer::logs();
      if (operation == "delete")   Timer::clear();

      return 0;
}
