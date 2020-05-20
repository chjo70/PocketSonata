#ifndef MYSOCKET_H
#define MYSOCKET_H


#include "_system.h"
#include "cthread.h"

#define MAX_CLIENTS     (30)
#define PORT            (8888)

typedef struct {
    unsigned int opCode;
    unsigned int uiLength;

} STR_LAN_HEADER ;

class CMySocket : public CThread
{
public:
    CMySocket( int iKeyId );
    void Run();
    virtual void _routine();
    
};

#endif // MYSOCKET_H
