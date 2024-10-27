#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "display.cpp"
#include "echo.cpp"
#include "cd.cpp"
#include"search.cpp"
#include"pinfo.cpp"
#include"process.cpp"
#include "IO.cpp"
#include "ls.cpp"

using namespace std;

int main() {
	string input;
	vector<string> commandHistory;
	string homePath = getCurrentDirectory("");
	string previousDir = "~";

	while (true) {
		displayPrompt(homePath);


		if (!getline(cin, input)) {
			break;
		}

		commandHistory.push_back(input);
		if (commandHistory.size() > 20) {
			commandHistory.erase(commandHistory.begin());
		}


		char* token = strtok(const_cast<char*>(input.c_str()), ";");

		while (token != nullptr) {
			string command = token;

			if (!command.empty()) {
				int redirectionMode = 0;
				istringstream iss(command);
				vector<string> args;
				string arg;
				while (iss >> quoted(arg)) {
					args.push_back(arg);

					if (arg == ">") {
						redirectionMode = 1;
					} else if (arg == ">>") {
						redirectionMode = 2;
					} else if (arg == "<") {
						redirectionMode = 3;
					}
				}

				if (args[0] == "cd") {
					if (args.size() == 1) {
						changeDirectory(homePath, homePath, previousDir);
					} else {
						changeDirectory(args[1], homePath, previousDir);
					}
				} else if (command == "pwd") {
					cout << getCurrentDirectory(homePath) << endl;
				} else if (args[0] == "echo") {
					if (redirectionMode == 0) {
						string text = args[1];
						echo_string(text);
					} else if (redirectionMode == 1) {
						// 1. output redirection
						handleOutputRedirection(args[1], args[3], false);
					} else if (redirectionMode == 2) {
						// 2. output redirection append
						handleOutputRedirection(args[1], args[3], true);
					}
					// 3. TODO input redirection
				} else if (args[0] == "ls") {
					bool showHidden = false;
					bool showDetails = false;
					vector<string> directories;

					for (int i = 1; i < args.size(); ++i) {
						const string& arg = args[i];
						if (arg == "-a" || arg == "-la" || arg == "-al") {
							showHidden = true;
							showDetails = true;
						} else if (arg == "-l") {
							showDetails = true;
						} else if (arg == "~") {
							directories.push_back(homePath);
						} else if (arg == "-") {
							std::cerr << "Invalid option: " << arg << std::endl;
						} else {
							string directory = arg;
							if (directory.size() && directory[0] == '~') {
								directory = homePath + arg.substr(1);
							}
							directories.push_back(directory);
						}
					}

					if (!directories.empty()) {
						for (const string& dir : directories) {
							cout << "Directory: " << dir << endl;
							listFiles(dir.c_str(), showHidden, showDetails);
							cout << std::endl;
						}
					} else {
						listFiles(".", showHidden, showDetails);
					}
				} else if (args[0] == "search") {
					string name = args[1];
					char cwd[1024];
					getcwd(cwd, sizeof(cwd));
					string currentDir(cwd);

					if (searchFileOrFolder(name, currentDir)) cout << "true" << endl;
					else cout << "false" << endl;
				}
				else if (command == "pinfo") {
					// assuming the current shell process as default
					displayProcessInfo(getpid());
				} else if (args[0] == "pinfo ") {
					int pid = stoi(args[1]);
					displayProcessInfo(pid);
				} else if (command.back() == '&') {
					command.pop_back();
					executeBackgroundCommand(command);
				} else if (args[0] == "history") {
					int num = 10; // Default: Display 10 latest commands
					if (args.size() > 1) {
						num = stoi(args[1]);
					}

					int startIndex = max(0, static_cast<int>(commandHistory.size()) - num);
					for (int i = startIndex; i < commandHistory.size(); ++i) {
						cout << commandHistory[i] << endl;
					}
				}
			}


			token = strtok(nullptr, ";");
		}
	}

	return 0;
}

