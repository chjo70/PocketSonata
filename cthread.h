#ifndef CTHREAD_H
#define CTHREAD_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <regex.h>

struct STR_MessageData {
    long mtype;

    union {
        unsigned int opCode;
        char msg[256];
    } x ;

} ;

/**
 * @brief The CThread class
 */
class CThread
{
private:
    pthread_t m_MainThread;
    key_t m_MsgKeyID;
    STR_MessageData m_Msg;

public:
    CThread( int iMsgKey );
    ~CThread();

    void Run();
    void Run( void *(*Func)(void*) );
    int Pend();
    void Stop();
    int QMsgRcv();

    inline key_t GetKeyId() { return m_MsgKeyID; }
    inline STR_MessageData *GetDataMessage() { return & m_Msg; }

    static void *CallBack( void *pArg ) {
        CThread *pThhread = static_cast<CThread*> (pArg);

        pThhread->_routine();

        return NULL;
    }

    virtual void _routine() { }

    //pthread_create(&thread,NULL,thread_routine, NULL);
};

#endif // CTHREAD_H