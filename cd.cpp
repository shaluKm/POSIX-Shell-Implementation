#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>

void changeDirectory(string target, string home, string &previousDirectory) {
	const string currentDir = getCurrentDirectory(home);
	if (target[0] == '~') {
		target = home + target.substr(1);
	}
	if (previousDirectory[0] == '~') {
		previousDirectory = home + previousDirectory.substr(1);
	}

	if (target == ".") {
		return ;
	} else if (target == "..") {
		if (currentDir == "~") {
			cout << home << "\n";
			return;
		}
		chdir("..");
		cout << getCurrentDirectory(home) << endl;
	} else if (target == "~") {
		chdir(home.c_str());
		cout << getCurrentDirectory(home) << endl;
	} else if (target == "-") {
		chdir(previousDirectory.c_str());
		cout << getCurrentDirectory(home) << endl;
	} else {
		if (chdir(target.c_str()) == 0) {
			cout << getCurrentDirectory(home) << endl;
		} else {
			cout << "cd: " << strerror(errno) << endl;
			return;
		}
	}
	previousDirectory = currentDir;
}
