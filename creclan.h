#ifndef CRECLAN_H
#define CRECLAN_H

#include "_sysmsg.h"
#include "cthread.h"

class CRecLan : public CThread
{
private:
    static CRecLan *pInstance;

    STR_MessageData *m_pMsg;

private:
    void SendQMessage();

public:
    CRecLan( int iKeyId, char *pClassName=NULL );
    void Run();

    // 명령에 대한 처리 함수 정의
    void DumpList();


    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CRecLan* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CRecLan( g_iKeyId++, (char*)"CRecLan" );
        }
        return pInstance;
    }
};

#define RECLAN     CRecLan::GetInstance()

#endif // CRECLAN_H
