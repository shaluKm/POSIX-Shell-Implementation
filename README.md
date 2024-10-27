# AOS Assignment 2 - POSIX Shell Implementation

## How to run the program?
- `g++ main.cpp` => `a.out`
- `./a.out` => this runs the POSIX shell

## Input handling logic
- Keep track of all the commands in `commandHistory` array (storing recent 20 commands)
- Use 'strtok' to tokenize the command and separate `;` separated commands 
- After that for each command we push each space separated words into `args` array
	- while doing that we keep quoted string as single word.
- Using `args` array to figure out the entered command further the specfic command based on it's input parameter

## Terminal Prompt Implementation
- This function invoked before at the start of each new line after the previous command implementation
- Considering the current directory where the program is executed as `HOME`.
- The path is rendered as relative to `HOME`.

## Change Directory
- Under the hood `chdir` is used.
- **Special Handling**
	- `cd ..`: In case we are at `HOME` => just printing out the `HOME` path. 

## Echo
-`echo_string` function is called with the text to be printed as argument
the function prints the output on terminal using standard output

## PWD
- prints present working directory
- calls the `getCurrentDirectory` function prints the path

## ls
- The ls command allows listing files and directories in the current working directory
- It supports various options, including -a, -l, and combinations like -al and -la.
- To list files and directories in the current working directory: ls
- To list hidden files and directories (those starting with a dot): ls -a
- To display detailed information about files and directories (permissions, owner, size, and modification time): ls -l
- To combine options, e.g., list hidden files with details: ls -al or ls -la Listing Specific Directories
- The ls command relies on system calls and directory traversal to fetch file and directory information.
It formats file permissions, owner, group, size, and modification time in a human-readable format.
- Hidden files and directories (those starting with a dot) are omitted by default unless the -a flag is used.
- The -l flag displays detailed information for each file and directory.

## Background Process
- search the command for the presence of '&'
- use 'fork' system call to make child process which execute teh command in background.The command to be executed id implemented with system() call

## Process Information
- For finding the process status info I am utilising the process stats store in `/proc/{pid}/status`
- For memory => `/proc/{pid}/statm`
- For executable path => `/proc/{pid}/exe`

## Search
- Search for a given file or folder under the current directory recursively
- searchFileOrFolder take filename to be searched and current directory as argument

## Output Redirection
- output of the command is written in the file taken as input.'>' for overwriting and '>>' for appending
- currently implemented for echo command only

## History
- store commands in vector of strings
- maximum capacity is 20 as defined in question
- calculates the start and end index of commands in the vectors and print them using loop