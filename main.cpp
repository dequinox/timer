#include <iostream>
#include "Timer.h"
#include "Tracker.h"
using namespace std;


int main(int argc, char *argv[])
{
      string operation = argv[1];
      string argv2 = argv[2] == NULL ? "" : argv[2];
      string argv3 = argv[3] == NULL ? "" : argv[3];

      if (operation == "start")    Timer::start(argv2);
      if (operation == "status")   Timer::status(argv2, 7);
      if (operation == "stop")     Timer::stop();
      if (operation == "modify")   Timer::modify(argv2, argv3);
      if (operation == "projects") Timer::projects();
      if (operation == "log")      Timer::logs();
      if (operation == "reset")    Timer::reset();
      if (operation == "delete")   Timer::clear(argv2);

      if (operation == "add")      Tracker::add(argv2);
      if (operation == "habits")   Tracker::habits(7);

      return 0;
}
