#ifndef _SYSTEM_H
#define _SYSTEM_H



#define PROGRAM_NAME        "PocketSonata"
#define PROGRAM_VERSION     "Ver 0.1a"

// 로그 디렉토리
#define LOG_DIRECTORY       ("/LOG")





typedef unsigned int UINT;





#ifdef _MAIN_GLOBALS_

int g_iKeyId=1;
int g_iMode;

#else
extern int g_iKeyId;
extern int g_iMode;

#endif




#endif // _SYSTEM_H
