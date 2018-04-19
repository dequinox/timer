#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <map>
#include <vector>
#include "Log.h"
#include "DataService.h"

namespace Timer
{
      const std::string project_file = "Project.txt";
      const std::string log_file = "Log.txt";

      void start(std::string project)
      {
            int project_id;
            time_t current_time;

            project_id = DataService::GetID(project, project_file);
            time(&current_time);

            time_t end_time = 0;
            Log newLog = {current_time, project_id, current_time, end_time};
            DataService::Add(newLog, log_file);
      }

      void stop()
      {
            Log oldLog = {};
            Log newLog;
            time_t current_time;

            time(&current_time);
            newLog.end_time = current_time;

            DataService::Modify(oldLog, newLog, log_file);
      }

      void status(const int n_days)
      {
            std::vector<Log> logs;
            int total_project_time[10000];

            logs = DataService::Get<Log>(log_file);
            for (auto l : logs)
            {
                  if (l.within_n_days(n_days))
                        total_project_time[l.project_id] += l.time_spent();
            }


      }
}

#endif // TIMER_H
