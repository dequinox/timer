#ifndef TIMER_H
#define TIMER_H

#include <>
#include "DataService.h"

namespace Timer
{
      void start(string project)
      {
            int project_id;

            project_id = DataService::getId(project);
            DataService::addLog(project_id);
      }

      void getCurrentTime()
      {
      }
}

#endif // TIMER_H
