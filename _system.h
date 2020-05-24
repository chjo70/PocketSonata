#ifndef _SYSTEM_H
#define _SYSTEM_H

// 로그 디렉토리
#define LOG_DIRECTORY       ("/LOG")
#define LENGTH_OF_CLASSNAME (20)



typedef unsigned int UINT;





#ifdef _MAIN_GLOBALS_

int g_iKeyId=1;
int g_iMode;

#else
extern int g_iKeyId;
extern int g_iMode;

#endif




#endif // _SYSTEM_H
