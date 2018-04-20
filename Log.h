#ifndef LOG_H
#define LOG_H

#include <ctime>
#include <cstring>
#include <iostream>

struct Log
{
      int id;
      char project[50];
      time_t start_time;
      time_t end_time;

      bool operator==(const Log &other)
      {
            if (id == other.id) return true;
            if (strcmp(project, other.project) == 0) return true;
            if (!end_time && !other.end_time) return true;

            return false;
      }

      bool within_n_days(int n_days)
      {
            time_t current_time;
            time(&current_time);

            time_t n_days_ms = n_days * 100 * 60 * 60 * 24;
            time_t n_days_ago = current_time - n_days_ms;
            return start_time >= n_days_ago;
      }

      time_t time_spent()
      {
            time_t current_time;
            time(&current_time);

            if (end_time)
                  return end_time - start_time;
            return current_time - start_time;
      }

      void print()
      {
            std::cout << id << " : "
                      << project << " "
                      << start_time << " - "
                      << end_time << std::endl;
      }

      void fill(const Log &other)
      {
            if (other.id) id = other.id;
            if (other.project[0]) strcpy(project, other.project);
            if (other.start_time) start_time = other.start_time;
            if (other.end_time) end_time = other.end_time;
      }

};

#endif // LOG_H
