#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>


using namespace std;

void handleInputRedirection(const string& inputFilename) {
  int inputFileDescriptor = open(inputFilename.c_str(), O_RDONLY);
  if (inputFileDescriptor == -1) {
    cerr << "Error: Input file '" << inputFilename << "' not found." << endl;
  } else {
    // Redirect standard input to the specified file
    dup2(inputFileDescriptor, 0);
    close(inputFileDescriptor);
  }
}

void handleOutputRedirection(const string inputText, const string outputFileName, bool append) {
  int openMode = O_WRONLY;
  if (append) {
    openMode |= O_APPEND; // Append mode
  } else {
    openMode |= O_TRUNC; // Truncate mode (overwrite)
  }

  int outputFileDescriptor = open(outputFileName.c_str(), openMode | O_CREAT, 0644);

  if (outputFileDescriptor == -1) {
    std::cerr << "Error: Failed to open output file '" << outputFileName << "'." << std::endl;
  } else {
    write(outputFileDescriptor, inputText.c_str(), inputText.size());
    close(outputFileDescriptor);
  }
}