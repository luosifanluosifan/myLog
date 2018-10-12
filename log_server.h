#pragma once
#include<stdarg.h>
#include<string>
#include<sys/utime.h>
#include<time.h>
using namespace std;
typedef unsigned int u32;
#define MAX_LOG_LENGTH 4096
#define MAX_FILEPATH_LEN   128
#define MAX_TIME_LEN   128
#define LOG_RECORD(logLev,fmt,...) log_server::get_instance()->Log_Recordlog(__FILE__,(u32)__LINE__,__FUNCTION__,(u32)logLev,fmt,__VA_ARGS__)

typedef enum
{
	LOG_DEBUG = 0,
	LOG_INFO,
	LOG_WARN,
    LOG_ERROR,
	LOG_FATAL,
	OTHER
}LOG_LEVEL;

class log_server
{
public:
	log_server();
	~log_server();

	static log_server* get_instance();

public:
	void Log_Recordlog(const char* _file,u32 _line,const char* _function,u32 logLev,const char* _fmt,...);
	string GetSystemTime();
	void OpenFile(string _file);
private:
	FILE *mfd;
	string m_fileName;
	bool m_logelvel_flag[OTHER];
	string m_logLevel_Info[OTHER];
};

