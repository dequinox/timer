#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <map>
#include <set>
#include <vector>
#include "Log.h"
#include "DataService.h"

namespace Timer
{
      const std::string project_file = "Project.txt";
      const std::string log_file = "Log.txt";

      void start(std::string project)
      {
            Log newLog;

            time_t current_time;
            time(&current_time);
            time_t end_time = 0;

            newLog.id = current_time;
            strcpy(newLog.project, project.c_str());
            newLog.start_time = current_time;
            newLog.end_time = end_time;

            DataService::Add(newLog, log_file);
      }

      void stop()
      {
            Log oldLog = {};
            Log newLog = {};
            time_t current_time;

            time(&current_time);
            newLog.end_time = current_time;
            DataService::Modify(oldLog, newLog, log_file);
      }

      void status(std::string project_name, const int n_days)
      {
            std::map<std::string, int> project_time;
            std::vector<Log> logs;

            logs = DataService::Get<Log>(log_file);
            for (auto log : logs)
            {
                  std::string project = log.project;
                  std::string category = "";
                  for (int i = 0; i < project.length(); i++)
                  {
                        if (project[i] == '.')
                        {
                              project_time[category] += log.time_spent();
                        }
                        category += project[i];
                  }
                  project_time[category] += log.time_spent();
            }

            if (project_name.empty())
            {
                  for (auto project : project_time)
                  {
                        std::cout << project.first << " "
                                  << project.second
                                  << std::endl;
                  }
            }
            else
            {
                  std::cout << project_name << " "
                            << project_time[project_name]
                            << std::endl;
            }

      }

      void clear()
      {
            DataService::remove(log_file);
      }

      void projects()
      {
            std::set<std::string> projects;
            std::vector<Log> logs;

            logs = DataService::Get<Log>(log_file);
            for (auto log : logs)
            {
                  projects.insert(log.project);
            }

            for (auto project : projects)
            {
                  std::cout << project << std::endl;
            }
      }

      void logs()
      {
            std::vector<Log> logs;

            logs = DataService::Get<Log>(log_file);
            for (auto log : logs)
            {
                  log.print();
            }
      }
}

#endif // TIMER_H
