#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

string getCurrentDirectory() {
  char buffer[PATH_MAX];
  if (getcwd(buffer, sizeof(buffer)) != nullptr) {
    return buffer;
  } else {
    return "Error getting current directory.";
  }
}

string formatPermissions(mode_t mode) {
  const char *perms = "rwxrwxrwx";
  static char permissions[10];
  strcpy(permissions, "---------");
  for (int i = 0; i < 9; i++) {
    if (mode & (1 << i)) {
      permissions[i] = perms[i];
    }
  }
  return permissions;
}

void listFiles(const char *path, bool showHidden, bool showDetails) {
  DIR *dir = opendir(path);
  if (!dir) {
    std::cerr << "Error opening directory" << std::endl;
    return;
  }

  dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    if (!showHidden && entry->d_name[0] == '.') {
      continue;
    }

    struct stat fileStat;
    stat((std::string(path) + "/" + entry->d_name).c_str(), &fileStat);

    if (showDetails) {
      struct passwd *user = getpwuid(fileStat.st_uid);
      struct group *group = getgrgid(fileStat.st_gid);

      cout << formatPermissions(fileStat.st_mode) << " ";
      cout << fileStat.st_nlink << " ";
      cout << (user ? user->pw_name : "") << " ";
      cout << (group ? group->gr_name : "") << " ";
      cout << std::setw(6) << fileStat.st_size << " ";

      struct tm *timeinfo = localtime(&fileStat.st_mtime);
      char timeStr[80];
      strftime(timeStr, sizeof(timeStr), "%b %d %H:%M", timeinfo);
      cout << timeStr << " ";
    }

    cout << entry->d_name << std::endl;
  }
  closedir(dir);
}

void echo_string(const vector<string>& tokens) {
  for (size_t i = 1; i < tokens.size(); ++i) {
    cout << tokens[i] << " ";
  }
  std::cout << std::endl;
}

void changeDirectory(const vector<string>& tokens) {
  if (tokens.size() != 2) {
    cerr << "Usage: cd <directory>" << endl;
    return;
  }
  if (chdir(tokens[1].c_str()) != 0) {
    cerr << "Error changing directory." << endl;
  }
}
