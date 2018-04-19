#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


namespace DataService
{
      std::string GetOurPath(const bool append_seperator = false)
      {
            std::string homedir;

            homedir.assign(getpwuid(getuid())->pw_dir);
            std::string full = homedir + "/Documents/Projects/Timer";
            return full + (append_seperator ? "/" : "");
      }

      template <class T>
      bool Add(const T &data, const std::string &file_name)
      {
            std::string path = GetOurPath(true);
            std::ofstream file(path + file_name, std::ios::app | std::ios::binary);

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
            std::fstream file(path + file_name, std::ios::in | std::ios::out | std::ios::binary);

            T data;
            if (!file)
            std::cout << path + file_name << std::endl;
            while (file.read(reinterpret_cast<char *>(&data), sizeof(T)))
            {
                  if (data == old_data)
                  {
                        data.setNew(new_data);
                        file.seekp(file.tellg() - sizeof(T));
                        file.write(reinterpret_cast<const char *>(&data), sizeof(T));
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
            while (file.read(reinterpret_cast<char *>(&d), sizeof(T)))
            {
                  data.push_back(d);
            }

            file.close();
            return data;
      }

      template <class T>
      int GetID(const T &key, const std::string &file_name)
      {
            std::string path = GetOurPath(true);
            std::ifstream file(path + file_name, std::ios::binary);

            int maxID = 0;
            T data;
            while (file.read(reinterpret_cast<char *>(&data), sizeof(T)))
            {
                  data.print();
                  key.print();
                  if (data == key)
                  {
                        file.close();
                        return data.id;
                  }
                  if (maxID < data.id)
                        maxID = data.id;
            }

            data.setNew(key);
            data.id = maxID + 1;
            file.close();

            Add(data, file_name);
            return maxID + 1;
      }

      void remove(std::string file_name)
      {
            std::remove(file_name.c_str());
      }
}

#endif // DATASERVICE_H
