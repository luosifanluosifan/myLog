#include "log_server.h"


log_server::log_server()
{
	m_logelvel_flag[LOG_DEBUG] = true;
	m_logelvel_flag[LOG_INFO] = true;
	m_logelvel_flag[LOG_WARN] = true;
	m_logelvel_flag[LOG_ERROR] = true;
	m_logelvel_flag[LOG_FATAL] = true;

	m_logLevel_Info[LOG_DEBUG] = "LOG_DEBUG";
	m_logLevel_Info[LOG_INFO] = "LOG_INFO";
	m_logLevel_Info[LOG_WARN] = "LOG_WARN";
	m_logLevel_Info[LOG_ERROR] = "LOG_ERROR";
	m_logLevel_Info[LOG_FATAL] = "LOG_FATAL";

	mfd = NULL;
#ifndef WIN32
	m_fileName = "/home/luosi/log/";
#endif // !WIN32

	m_fileName = "./log_running.txt";
}

log_server* log_server::get_instance()
{
	static log_server logger;
	return &logger;
}

void log_server::Log_Recordlog(const char* _file, u32 _line, const char* _function, u32 logLev, const char* _fmt, ...)
{
	string timeNow = GetSystemTime();
	char log_Content[MAX_LOG_LENGTH] = {};
	if (m_logelvel_flag[logLev])
	{
		OpenFile(m_fileName);
		va_list ArgList;

		(void)va_start(ArgList, _fmt);
		sprintf_s(log_Content, "\n[%s]-[%s]-[%s]-[%s]-[line in %d]! ", timeNow.c_str(), m_logLevel_Info[logLev].c_str(), _file, _function, _line);

		if (mfd)
		{
			fputs(log_Content, mfd);
		}

		vsnprintf_s(log_Content, MAX_LOG_LENGTH, MAX_LOG_LENGTH, _fmt, ArgList);

		fputs(log_Content, mfd);

		fflush(mfd);

		fclose(mfd);
	}
}

void log_server::OpenFile(string _file)
{
	mfd = fopen(_file.c_str(), "a+");
}
string log_server::GetSystemTime()
{
	char timeLocal[MAX_TIME_LEN] = {};
	time_t rawtime;
	struct tm *ptminfo;
	time(&rawtime);
	ptminfo = localtime(&rawtime);

	sprintf_s(timeLocal, MAX_TIME_LEN, "%02d%02d%02d-%02d:%02d:%02d", ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

	return timeLocal;
}
log_server::~log_server()
{
}
