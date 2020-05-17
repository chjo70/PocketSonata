#include <iostream>

#include "cthread.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

extern void usrAppStart();

/**
 * @brief thread_routine
 * @param pArg
 * @return
 */
void *thread_routine( void *pArg )
{
        pthread_t tid;

        key_t keyId;
        STR_MessageData *pMessageData;

        keyId = ( ( CThread * ) pArg )->GetKeyId();
        pMessageData = ( ( CThread * ) pArg )->GetDataMessage();

        tid = pthread_self();

        int i=0;
        printf("\ttid:%lx, keyId=%d\n",tid, keyId );

        while( true ) {
            printf( "\n\tmsgrcv[%d]...", keyId );
            if( msgrcv( keyId, (void *) pMessageData, sizeof(STR_MessageData)-sizeof(long), (1 >> 1), 0)	== -1) {

            }
            printf("\tnew thread:%d, opCode:%x\n",i, pMessageData->x.opCode );
            i++;
            sleep(1);
        }

        printf( "\n Thread 종료");

        pthread_exit( 0 );

        return NULL;
}

int main()
{
    usrAppStart();
    return 0;
}
