#ifndef _SYSTEM_H
#define _SYSTEM_H

// 로그 디렉토리
#define LOG_DIRECTORY       ("/LOG")


#ifdef _MAIN_GLOBALS_

int g_iKeyId=1;

#else
extern int g_iKeyId;

#endif

#endif // _SYSTEM_H
