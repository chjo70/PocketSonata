#include "cthread.h"
#include <errno.h>

#ifndef S_DEFFILEMODE
#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#endif

CThread::CThread( int iMsgKey )
{
    // 메시지큐 생성
    memset( & m_Msg, 0, sizeof(STR_MessageData) );

    m_MsgKeyID = msgget( IPC_PRIVATE, 0666 | IPC_CREAT);
    if (m_MsgKeyID == -1 )
    {
        perror("msgget error : ");
        exit(0);
    }
}

/**
 * @brief CThread::Run
 */
void CThread::Run( void *(*Func)(void*) )
{
    printf( "\n Run..." );

    pthread_create( & m_MainThread, NULL, Func, this );

}

/**
 * @brief CThread::Pend
 * @return
 */
int CThread::Pend()
{
    void *pStatus;
    //int iStatus[100];
    int iStatus;

    pStatus = ( void *) malloc( 100 );
    iStatus = pthread_join( m_MainThread, /* (void **) & iStatus[0] */ NULL );
    free( pStatus );

    return iStatus;
}

/**
 * @brief CThread::Stop
 */
void CThread::Stop()
{
    // pthread_exit();
}
