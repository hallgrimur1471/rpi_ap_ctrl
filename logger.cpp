#include "logger.h"

using namespace std;

Logger::
Logger(const string folder)
{
	logFolder = folder;
	make_logfile_directory();
	logFile = determine_next_logfile_path();
	logPath = logFolder + "/" + logFile;
}

Logger::
~Logger()
{}

void
Logger::
log(string toLog)
{
	time_t rawtime;
  	struct tm * timeinfo;
  	time ( &rawtime );
 	timeinfo = localtime ( &rawtime );

	std::ofstream file(logPath.c_str(), std::ios_base::app);
	file << "========================================================\n"
	     << "Date: " << asctime(timeinfo)
	     << "\nLog Message:\n" << toLog
	     << "\n========================================================\n\n"
	     << std::flush; 
}

void
Logger::
make_logfile_directory()
{
	struct stat st;
	struct stat *stp = &st;
	stat(logFolder.c_str(), stp);
	bool directoryExists = S_ISDIR(stp->st_mode);
	if (!directoryExists)
	{
		int results = mkdir(logFolder.c_str(), 0777);
		if (results == -1)
		{
			int errsv = errno;
			cout << "Did not manage to make directory: " + logFolder << endl;
			cout << "errno: " + SSTR(errsv) << endl;
		}
		else
		{
			cout << "Made directory: " + logFolder << endl;
		}
	}
}

string
Logger::
determine_next_logfile_path()
{
	time_t rawtime;
  	struct tm * t;
  	time ( &rawtime );
 	t = localtime ( &rawtime );

 	const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
 							"Jul", "Aug", "Sep", "Okt", "Nov", "Dec"};
 	const char * weekdays[] = {"Sun", "Mon", "Tue",
 							  "Wed", "Thu", "Fri", "Sat"};

 	char timeString[100];
 	sprintf(timeString, "%s%04d%3s%02d%3s%02d%02d%02d%s", LOGFILENAME_BASE,
 										t->tm_year+1900, months[t->tm_mon],
 										t->tm_mday, weekdays[t->tm_wday],
 										t->tm_hour, t->tm_min, t->tm_sec,
 										LOGFILENAME_EXTENSION);

	cout << timeString << endl;

	return timeString;
}



/*
	// determine next logfile name
	int counter = 1;
	//string c = int_to_string(counter);
	//cout << c << endl;
	string path = logFolder + "/" + LOGFILENAME_BASE + SSTR(counter) + LOGFILENAME_EXTENSION;
	cout << path << endl;
	stat(path.c_str(), stp);
	cout << stp->st_mode << endl;
	while (S_ISREG(stp->st_mode) && counter < 5)
	{
		new(stp) struct stat();
		counter++;
		path = logFolder + "/" + LOGFILENAME_BASE + SSTR(counter) + LOGFILENAME_EXTENSION;
		cout << path << endl;
		stat(path.c_str(), stp);
		cout << stp->st_mode << endl;
	}

	return path;
	*/

	/*

	file << "========================================================\n"
	     << "Date: " << asctime(timeinfo)
	     << "\nLog Message:\n" << toLog
	     << "\n========================================================\n\n"
	     << std::flush; 

	*/