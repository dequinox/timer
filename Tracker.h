#ifndef TRACKER_H
#define TRACKER_H

#include <cstring>
#include <vector>
#include <map>
#include "Habit.h"
#include "DataService.h"

namespace Tracker
{
      const std::string habit_file = "Habit.txt";

      void add(std::string habit_name)
      {
            Habit newHabit;

            time_t current_time;
            time(&current_time);

            newHabit.date = current_time;
            strcpy(newHabit.name, habit_name.c_str());

            DataService::Add(newHabit, habit_file);
      }

      void habits(const int n_days)
      {
            std::map<std::string, int> habit_cnt;
            std::vector<Habit> habits;

            habits = DataService::Get<Habit>(habit_file);
            for (auto habit : habits)
            {
                  if (habit.within_n_days(n_days))
                  {
                        std::string habit_name = habit.name;
                        habit_cnt[habit_name]++;
                  }
            }

            for (auto habit : habit_cnt)
            {
                  std::cout << habit.first << " "
                            << "[" << habit.second
                            << "]" << std::endl;
            }
      }
}

#endif // TRACKER_H
