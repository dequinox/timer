#ifndef LOG_H
#define LOG_H

#include <ctime>
#include <iostream>

struct Log
{
      int id;
      int project_id;
      time_t start_time;
      time_t end_time;

      bool operator==(const Log &other)
      {
            if (id == other.id) return true;
            if (project_id == other.project_id) return true;
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
            return end_time - start_time;
      }

      void setNew(const Log &other)
      {
            if (other.id) id = other.id;
            if (other.project_id) project_id = other.project_id;
            if (other.start_time) start_time = other.start_time;
            if (other.end_time) end_time = other.end_time;
      }

      void print()
      {
            std::cout << id << " : "
                      << project_id << " "
                      << start_time << " - "
                      << end_time << std::endl;
      }

};

#endif // LOG_H
