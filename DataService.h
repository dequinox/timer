#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

struct Project
{
      std::string name;
      int id;
};


namespace DataService
{
      std::string GetOurPath(const bool append_seperator = false)
      {
            std::string homedir;

            homedir.assign(getpwuid(getuid())->pw_dir);
            std::string full = homedir + "/Documents/Projects/Timer/";
            return full + (append_seperator ? "/" : "");
      }

      template <class T>
      bool Add(const T &data, const std::string file_name)
      {
            std::string path = GetOurPath(true);
            std::ofstream file(path + file_name, std::ios::binary);

            if (file.is_open())
            {
                  file.write(reinterpret_cast<const char *>(&data), sizeof(T));
                  file.close();
                  return true;
            }

            file.close();
            return false;
      }

      template <class T>
      bool Modify(const T &old_data, const T &new_data, const std::string &file_name)
      {
            std::string path = GetOurPath(true);
            std::fstream file(path + file_name, std::ios::binary);

            T data;
            while (file.good())
            {
                  file.read(reinterpret_cast<char *>(&data), sizeof(T));
                  if (data == old_data)
                  {
                        file.seekp(file.tellg() - sizeof(T));
                        file.write(reinterpret_cast<const char *>(&new_data), sizeof(T));
                        file.close();
                        return true;
                  }
            }
            file.close();
            return false;
      }


      template <class T>
      bool Remove(const T &old_data, const std::string file_name)
      {
            std::string path = GetOurPath(true);
            std::fstream file(path + file_name, std::ios::binary);

            T data;
            while(file.good())
            {
                  file.read(reinterpret_cast<char *>(&data), sizeof(T));
                  if (data != old_data)
                  {
                        file.write(reinterpret_cast<char *>(&data), sizeof(T));
                  }
            }
            file.close();
            return true;
      }

      template <class T>
      std::vector <T> Get(const std::string &file_name)
      {
            std::string path = GetOurPath(true);
            std::ifstream file(path + file_name, std::ios::binary);

            std::vector <T> data;
            T d;
            while (file.good())
            {
                  file.read(reinterpret_cast<char *>(&d), sizeof(T));
                  data.push_back(d);
            }

            file.close();
            return data;
      }

      int GetID(std::string key, std::string file_name)
      {
            std::string path = GetOurPath(true);
            std::fstream file(path + file_name, std::ios::binary);

            Project project = {};
            int maxID = 0;

            if (file.is_open())
            {
                  while (file.good())
                  {
                        file.read(reinterpret_cast<char *>(&project), sizeof(Project));
                        if (project.name == key || std::to_string(project.id) == key)
                        {
                              file.close();
                              return project.id;
                        }

                        if (maxID < project.id)
                              maxID = project.id;
                  }

                  project = {key, maxID + 1};
                  file.write(reinterpret_cast<char *>(&project), sizeof(Project));

                  file.close();
                  return project.id;
            }
      }
}

#endif // DATASERVICE_H
