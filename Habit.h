#ifndef HABIT_H
#define HABIT_H

#include <ctime>

struct Habit
{
      time_t date;
      char name[50];

      bool within_n_days(const int n_days)
      {
            time_t current_time;
            time(&current_time);

            time_t n_days_ms = n_days * 100 * 60 * 60 * 24;
            time_t n_days_ago = current_time - n_days_ms;
            return date >= n_days_ago;
      }
};

#endif // HABIT_H
