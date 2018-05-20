#pragma once


#define LOG_CODE_MAP_BEGIN typedef enum _LOG_TYPE_CODE{ LOG_BEGIN,

#define Reg_Log_Type_Code(x) x,

#define LOG_TYPE_MAN_END LOG_END } LOG_TYPE_CODE, * PLOG_TYPE_CODE;

#define Reg_Log_Name(x,y) m_LogDir[x] = y;

LOG_CODE_MAP_BEGIN
// here You can reg log
Reg_Log_Type_Code(LOG_NORMAL)
Reg_Log_Type_Code(LOG_ONLINE)
Reg_Log_Type_Code(LOG_OFFLINE)
Reg_Log_Type_Code(LOG_DISCONNECT)
Reg_Log_Type_Code(LOG_ERROR)
LOG_TYPE_MAN_END


#include <assert.h>


class CMyLog
{
	char * m_LogDir[LOG_END - LOG_BEGIN - 1];
public:
	CMyLog(){
		// here You can bind log with string
		Reg_Log_Name(LOG_NORMAL, "Normal")
		Reg_Log_Name(LOG_ONLINE, "Online")
		Reg_Log_Name(LOG_OFFLINE, "Offline")
		Reg_Log_Name(LOG_DISCONNECT, "Disconnect")
		Reg_Log_Name(LOG_ERROR, "Error")
			for (int i = LOG_BEGIN + 1;
				i < LOG_END;
				++i){
			assert(m_LogDir[i]);
		}
	};
	char * GetLogName(LOG_TYPE_CODE i){ return m_LogDir[i]; }
	~CMyLog(){};
};

extern CMyLog MyLog;
