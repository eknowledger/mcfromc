#pragma once

typedef enum {lDebug,lWarn,lError,lNone} LogSeverity;

void InitLogger(const char *filename,LogSeverity severity);
void TerminateLog();
void LogToFile(LogSeverity level,const char *file,unsigned int lineNum,const char *format,...);

#define WRITE_TO_LOG(sevirity,text) \
{\
	LogToFile(sevirity,__FILE__,__LINE__,__FUNCTION__ ": " text); \
}

#define WRITE_TO_LOG_1(sevirity,text,p1) \
{\
	LogToFile(sevirity,__FILE__,__LINE__,__FUNCTION__ ": " text,p1); \
}