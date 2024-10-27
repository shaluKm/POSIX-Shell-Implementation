#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>


using namespace std;

string getUsername() {
  char* username = getlogin();
  if (username == nullptr) {
    return "UnknownUser";
  }
  return username;
}

string getSystemName() {
  char hostname[256];
  gethostname(hostname, sizeof(hostname));
  return hostname;
}

string getCurrentDirectory(string home) {
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  string currentDir(cwd);

  int homeDirPos = currentDir.find(home);
  if (home.length() && homeDirPos == 0) {
    int len = home.length();
    currentDir.replace(0, len, "~");
  }
  return currentDir;
}

void displayPrompt(string home) {
  string username = getUsername();
  string systemName = getSystemName();
  string currentDir = getCurrentDirectory(home);

  cout << username << "@" << systemName << ":"  << currentDir << " > ";
}