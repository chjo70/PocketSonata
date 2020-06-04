#ifndef CURBIT_H
#define CURBIT_H


#include "_sysmsg.h"
#include "cthread.h"

class CUrBit : public CThread
{
public:
    static CUrBit *pInstance;

    STR_MessageData *m_pMsg;

public:
    CUrBit( int iKeyId, char *pClassName=NULL );
    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CUrBit* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CUrBit( g_iKeyId++, (char*)"CUrBit" );
        }
        return pInstance;
    }
};

#define URBIT     CUrBit::GetInstance()

#endif // CURBIT_H
