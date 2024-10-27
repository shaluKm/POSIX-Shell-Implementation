#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

void executeBackgroundCommand(const string& command) {
	pid_t pid = fork();

	if (pid == 0) {
		system(command.c_str());
		exit(0);
	} else if (pid < 0) {
		cerr << "Failed to fork process." << endl;
	} else {
		cout << pid << endl;
	}
}

void executeForegroundCommand(const string& command) {
	system(command.c_str());
}
