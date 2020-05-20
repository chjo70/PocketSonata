
#define _MAIN_GLOBALS_

#include "cmain.h"
#include "clog.h"
#include "mysocket.h"

extern void usrAppStart();

CMySocket g_theMySocket( g_iKeyId );

void usrAppStart()
{

    LOGMSG( enNormal, "쓰레드를 구동합니다." );

    //
    MAIN->Run();
    g_theMySocket.Run();

    while( true ) {
        sleep( 10000000 );
    }

}

CMain* CMain::pInstance = nullptr;

/**
 * @brief CMain::CMain
 */
CMain::CMain( int iKeyId ) : CThread( iKeyId )
{
    LOGENTRY;

    //Init();
    //Run( );
}

/**
 * @brief CMain::Init
 */
void CMain::Init()
{
    LOGENTRY;

    STR_MessageData sndMsg;

    CThread theThread1(10), theThread2(11);

    /*

    theThread1.Run( thread_routine );
    theThread2.Run( thread_routine );

    sndMsg.mtype = 1;
    sndMsg.x.opCode = 0x1234;

    int i=0;

    printf("\ntid:%lx\n",pthread_self());
    while( true ){
        printf("main:%d\n",i);
        i++;
        sleep(1);

        if(msgsnd( theThread1.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread1.GetKeyId() );

        }
        if(msgsnd( theThread2.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread2.GetKeyId() );
        }

        //theThread1.Pend();
        //theThread1.Stop();

    }

    */

}

/**
 * @brief CMain::Run
 */
void CMain::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CMain::_routine
 */
void CMain::_routine()
{
    LOGENTRY;

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }
    }

}
