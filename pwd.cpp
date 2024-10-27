string getExecutableDirectory(const char* path) {
	char* executablePath = realpath(path, NULL);

	if (executablePath == NULL) {
		perror("realpath error");
		return "";
	}

	char* dirPath = dirname(executablePath);
	string directory = dirPath.c_str();

	free(executablePath);

	return directory;
}

void CurrentDirectory() {
	string executableDir = getExecutableDirectory("/proc/self/exe");
	cout << executableDir;
}