#include "clog.h"

#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

CLog* CLog::pInstance = nullptr;

CLog::CLog()
{

}

/**
 * @brief CLog::LogMsg
 * @param nType
 * @param pszFunction
 * @param pszFile
 * @param iLine
 * @param pStr
 */
void CLog::LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *pStr )
{
    int fid;

    char szDate[LOG_DIR_SIZE];
    char szFileLine[LOG_DIR_SIZE];

    getcwd( m_szPresentDirectory, sizeof(m_szPresentDirectory) );

    strcpy( m_szLogDir, m_szPresentDirectory );
    strcat( m_szLogDir, LOG_DIRECTORY );

    if( 0 == mkdir( m_szLogDir, 0776 ) || errno == EEXIST ) {
        time_t timer;
        struct tm* t;
        struct timeval tv;

        gettimeofday( &tv,NULL);
        timer = time( & tv.tv_sec );
        t = localtime(&timer);

        sprintf( szDate, "/%d_%d_%d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );
        strcat( m_szLogDir, szDate );

        fid = open(m_szLogDir, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
        if( fid != 0 ) {
            sprintf( m_szLog, "\n%d-%02d-%02d %02d:%02d:%02d.%3d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, (int)( tv.tv_usec / 1000. ) );

            switch( nType ) {
            case enNormal :
                strcat( m_szLog, "[NORMAL]\t" );
                break;
            case enDebug :
                strcat( m_szLog, "[DEBUG ]\t" );
                break;
            case enEnd :
                strcat( m_szLog, "[END   ]\t" );
                break;

            case enLineFeed :
                m_szLog[0] = 0;
                break;

            case enError :
                strcat( m_szLog, "[ERROR ]\t" );
                break;

            default :
                break;
            }

            sprintf( szFileLine, "[%s:%d{%s}]\t\t" , pszFile, iLine, pszFunction );

            if( szFileLine[0] != 0 ) {
                strcat( m_szLog, szFileLine );
            }
            if( pStr != NULL ) {
                strcat( m_szLog, pStr );
            }

            write( fid, m_szLog, strlen(m_szLog) );

            close( fid );
        }
    }

}

/**
 * @brief Log
 * @param nType
 * @param fmt
 */
void Log( int nType, const char *fmt, ... )
{


}
