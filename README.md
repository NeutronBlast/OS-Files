## File and Signal Management

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [Project's goal](#project's-goal)
* [About the Project](#about-the-project)
* [Implementation Details](#implementation-details)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
* [Usage](#usage)

## Project's Goal
To familiarize with system calls for creation and access to file system structure in UNIX.

<!-- ABOUT THE PROJECT -->
## About The Project
This repository contains an application that goes through a tree of directories recursively, generating a report with the most important information for each directory in the tree, in this way, the user will be able to know exactly in which directory he's wasting the most space.

## Implementation Details
1. If the output file name isn't specified in the command line the report will be generated on the screen
2. From the root directory (where the program is executed) and for each directory contained in that root the report should contain the following information:

__Absolute Path__

__Permissions__: As they are showed in the `ls -l` command 

__user-id__: User id of the owner of the directory

__group-id__: Group id assigned to the directory

__Last modified date__

__Last access date__

__Total number of files contained__ (counting sub-directories)

__Total of bytes of files contained__ (not counting sub-directories)

3. The name of every report file made by children processes will have as name its PID.txt
4. In case of finding a `.dmp` file this will be deleted and its information will be added to the report, the information that is needed for each `.dmp` file deleted is the following: *directory*, *last modified date*, *size*
5. Main process has to create a child process for each subdirectory that it is in the root directory
6. Each child process should generate the report as it was specified before
7. The parent process will generate a final report with the information of its directory and the global information for each subdirectory, considering the data retrieved by its children
8. The parent process will read its children information through their respective PID.txt files
9. The parent process should install a signal management to avoid to kill the process with CTRL-C

### Built With

* [C]()

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* [Ubuntu](https://ubuntu.com/download/desktop)

* gcc

```sh
sudo apt update
sudo apt install build-essential
sudo apt-get install manpages-dev
```

To make sure gcc was installed execute

```sh
gcc --version
```

<!-- USAGE EXAMPLES -->
## Usage

1. Command line
```sh
els OutputFileName
```