#include "cthread.h"
#include <errno.h>
#include "clog.h"

#ifndef S_DEFFILEMODE
#define S_DEFFILEMODE   (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#endif

CThread::CThread( int iMsgKey )
{
    m_MainThread = -1;

    // 메시지큐 생성
    memset( & m_Msg, 0, sizeof(STR_MessageData) );

    m_MsgKeyID = msgget( IPC_PRIVATE, 0666 | IPC_CREAT);
    if (m_MsgKeyID == -1 )
    {
        perror("msgget error : ");
        exit(0);
    }
}

CThread::~CThread()
{
    pthread_join( m_MainThread, NULL);
}

/**
 * @brief CThread::Create
 */
void CThread::Run( void *(*Func)(void*) )
{
    LOGMSG( enNormal, "\n Running thread..." );

    pthread_create( & m_MainThread, NULL, Func, this );

}

/**
 * @brief CThread::Run
 */
void CThread::Run()
{
    LOGMSG1( enNormal, " Running thread...%s", ChildClassName() );

    pthread_create( & m_MainThread, NULL, CallBack, this );

}

//static void *CThread::CallBack( void *pArg )
//{
//    CThread *pThhread = static_cast<CThread*> (pArg);

//    pThhread->_routine();
//}

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

void *CThread::CallBack( void *pArg )
{
    CThread *pThhread = static_cast<CThread*> (pArg);

    pThhread->_routine();

    return NULL;
}


/**
 * @brief CThread::QMsgRcv
 * @return
 */
int CThread::QMsgRcv()
{
    LOGENTRY;

    int iMsgRcv = msgrcv( m_MsgKeyID, (void *) & m_Msg, sizeof(STR_MessageData)-sizeof(long), (1 >> 1), 0);

    return iMsgRcv;

}
