#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <map>
#include <vector>
#include "Log.h"
#include "Project.h"
#include "DataService.h"

namespace Timer
{
      const std::string project_file = "Project.txt";
      const std::string log_file = "Log.txt";

      void start(std::string key)
      {
            Project newProject;
            Log newLog;
            int project_id;
            char project_name[50];

            strcpy(project_name, key.c_str());
            newProject.setName(project_name);

            project_id = DataService::GetID(newProject, project_file);


            time_t current_time;
            time(&current_time);
            time_t end_time = 0;

            newLog = {current_time, project_id, current_time, end_time};
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
            std::vector<Log> logs;
            std::map<int, int> total_project_time;

            logs = DataService::Get<Log>(log_file);
            for (auto l : logs)
            {
                  if (l.within_n_days(n_days))
                        total_project_time[l.project_id] += l.time_spent();
            }

            for (auto p : total_project_time)
            {
                  std::cout << p.first << " : " << p.second << std::endl;
            }

      }

      void clear()
      {
            DataService::remove(log_file);
            DataService::remove(project_file);
      }

      template<class T>
      void print(std::string file_name)
      {
            std::vector<T> data;

            data = DataService::Get<T>(file_name);
            for (auto instance : data)
            {
                  instance.print();
            }
      }

      void projects()
      {
            print<Project>(project_file);
      }

      void logs()
      {
            print<Log>(log_file);
      }
}

#endif // TIMER_H
