#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

bool searchFileOrFolder(const string& filename, const string& currentDirectory) {
  DIR* dir = opendir(currentDirectory.c_str());
  if (!dir) {
    cerr << "Error opening directory: " << currentDirectory << endl;
    return false;

  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    string name = entry->d_name;

    if (name == "." || name == "..") {
      continue;
    }

    string path = currentDirectory + "/" + name;

    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0) {
      if (name == filename) {
        closedir(dir);
        return true;
      }
      if (S_ISDIR(fileStat.st_mode)) {
        if (searchFileOrFolder(filename, path)) {
          closedir(dir);
          return true;
        }
      }
    }
  }

  closedir(dir);
  return false;

}

