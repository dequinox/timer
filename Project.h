#ifndef PROJECT_H
#define PROJECT_H

#include <cstring>
#include <iostream>

struct Project
{
      int id;
      char name[50];

      void setName(const char other_name[50])
      {
            strcpy(name, other_name);
      }

      bool operator==(const Project &other)
      {
            return strcmp(name, other.name) == 0;
      }

      void setNew(const Project &other)
      {
            strcpy(name, other.name);
      }

      void print() const
      {
            std::cout << id << " : "
                      << name << std::endl;
      }
};

#endif // PROJECT_H
