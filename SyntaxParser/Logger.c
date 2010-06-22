#include "Logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

static FILE *logFile = NULL;
static LogSeverity requestedLogSevirity = lNone;

#define LINE_SIZE 512

void InitLogger(const char *filename,LogSeverity severity)
{
	requestedLogSevirity = severity;
	fopen_s(&logFile,filename,"a");
}

void LogToFile(LogSeverity level,const char *file,unsigned int lineNum,const char *format,...)
{
	char sTime[100];
	char sLevel[10];
	char line[LINE_SIZE] = {0};
	time_t	cTime;
	struct tm currentTime;
	va_list argList;

	if(requestedLogSevirity > level)
		return;

	time(&cTime);
	localtime_s(&currentTime,&cTime);
	asctime_s(sTime,100,&currentTime);
	//remove the \n at the end of the string
	sTime[strlen(sTime) - 1] = '\0';
	
	//gets the log level
	switch(level)
	{
	case lNone:
		strcpy_s(sLevel,10,"NONE");
		break;
	case lError:
		strcpy_s(sLevel,10,"ERROR");
		break;
	case lWarn:
		strcpy_s(sLevel,10,"WARN");
		break;
	case lDebug:
		strcpy_s(sLevel,10,"DEBUG");
		break;
	}

	//Converts the formating string and args to 
	//one string
	va_start (argList, format);
		vsprintf_s(line,LINE_SIZE -1,format,argList);
	va_end(argList);
	
	//write the line to log
	fprintf(logFile,"%s [%s] %s(%d) %s\n",sTime,sLevel,file,lineNum,line);
	fflush(logFile);

}

void TerminateLog()
{
	fclose(logFile );
}