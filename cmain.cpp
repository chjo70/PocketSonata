#include "cmain.h"
#include "clog.h"

extern void usrAppStart();



void usrAppStart()
{

    //pTheMain = new CMain;
    //delete pTheMain;

    LOGMSG( enNormal, "프로그램을 시작합니다." );

    MAIN->Run();

}

CMain* CMain::pInstance = nullptr;

/**
 * @brief CMain::CMain
 */
CMain::CMain()
{
    LOGENTRY;

    Init();
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

}
