#ifndef MYSOCKET_H
#define MYSOCKET_H


#include "_system.h"
#include "cthread.h"

#define MAX_CLIENTS     (30)
#define PORT            (8888)

#define MAX_LAN_DATA    (1024)

class CMySocket : public CThread
{
private:
    static char m_szClassName[LENGTH_OF_CLASSNAME];

private:
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

public:
    CMySocket( int iKeyId );
    void Run();
    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }
    
};

#endif // MYSOCKET_H
