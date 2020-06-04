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

#define LENGTH_OF_CLASSNAME (20)

struct STR_MessageData {
    long mtype;

    unsigned int opCode;
    int iSocket;
    char msg[256];

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

protected:
    char m_szClassName[LENGTH_OF_CLASSNAME];

public:
    CThread( int iMsgKey, char *pClassName );
    ~CThread();

    void Run();
    void Run( void *(*Func)(void*) );
    int Pend();
    void Stop();
    int QMsgRcv();

    inline key_t GetKeyId() { return m_MsgKeyID; }
    inline STR_MessageData *GetDataMessage() { return & m_Msg; }

    static void *CallBack( void *pArg );

    virtual void _routine() { }
    virtual const char *ChildClassName() { return NULL; }

    //pthread_create(&thread,NULL,thread_routine, NULL);
};

#endif // CTHREAD_H
