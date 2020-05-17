#ifndef CLOG_H
#define CLOG_H

#include <stdio.h>

#include "_system.h"

#define LOG_DIR_SIZE        (1024)

// 로그 타입 사용자가 원하는 대로 정의
enum LogType {
    enDebug=0,
    enNormal,
    enLineFeed,
    enError,
    enEnd,
};

#define LOGMSG( A, B )      LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B )
#define LOGMSG2( A, B )     LOG->LogMsg( A, NULL, NULL, NULL, B )
#define LOGENTRY            LOG->LogMsg( enNormal, __FUNCTION__, __FILE__, __LINE__, NULL )

class CLog
{
private:
    static CLog *pInstance;

    char m_szPresentDirectory[LOG_DIR_SIZE];
    char m_szLogDir[LOG_DIR_SIZE*2];

    char m_szLog[LOG_DIR_SIZE*5];

public:
    CLog();

    static CLog* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CLog();
        }
        return pInstance;
    }

    void LogMsg( int nType, char *pMsg );
    void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *pStr );


};



#define LOG     CLog::GetInstance()

#endif // CLOG_H
