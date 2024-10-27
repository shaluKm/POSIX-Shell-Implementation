#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

string getStatusFromLine(const string& line) {
  istringstream iss(line);
  string state;
  // "State: {state}"
  iss >> state;
  iss >> state;
  // R+ || R => Running
  // S+ || S => Sleeping interruptible wait
  // Z => Zombie
  // T => Stopped on a signal
  return state;
}

string getCurrentProcessStatus(const string& pid_str) {
  string statusFilePath = "/proc/" + pid_str + "/status";
  ifstream statusFile(statusFilePath);

  if (!statusFile) {
    return "Process not found.";
  }

  string line;
  while (getline(statusFile, line)) {
    if (line.find("State:") != string::npos) {
      return getStatusFromLine(line);
    }
  }

  return "Unknown";
}

string getCurrentMemoryUsage(const string& pid_str) {
  string statmFilePath = "/proc/" + pid_str + "/statm";
  ifstream statmFile(statmFilePath);

  if (!statmFile) {
    return "Memory information not available.";
  }

  unsigned long virtualMemorySize;
  statmFile >> virtualMemorySize;

  return to_string(virtualMemorySize) + " {Virtual Memory}";
}

string getExecutablePath(const string& pid_str) {
  string exeFilePath = "/proc/" + pid_str + "/exe";
  char link[PATH_MAX];
  ssize_t len = readlink(exeFilePath.c_str(), link, sizeof(link) - 1);

  if (len != -1) {
    link[len] = '\0';
    return string(link);
  }

  return "Executable path not found.";
}

void displayProcessInfo(int pid) {
  string pid_str = to_string(pid);

  cout << "pid -- " << pid_str << endl;
  string processStatus = getCurrentProcessStatus(pid_str);
  cout << "Process Status -- {" << processStatus << "}" << endl;
  string memoryUsage = getCurrentMemoryUsage(pid_str);
  cout << "memory -- " << memoryUsage << endl;
  string executablePath = getExecutablePath(pid_str);
  cout << "Executable Path -- " << executablePath << endl;
}


