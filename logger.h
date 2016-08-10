// sudo apt-get install libboost-dev
#include <fstream>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <errno.h>
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

#define MAXLOGFILES = 100
#define LOGFILENAME_BASE ""
#define LOGFILENAME_EXTENSION ".log"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


class Logger
{

public:

	Logger(const std::string folder);
	~Logger();

	void log(std::string toLog);

private:

	std::string logFolder;
	std::string logFile;
	std::string logPath;

	void make_logfile_directory();
	std::string determine_next_logfile_path();

};