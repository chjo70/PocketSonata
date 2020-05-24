#ifndef CRECLAN_H
#define CRECLAN_H

#include "_sysmsg.h"
#include "cthread.h"

class CRecLan : public CThread
{
private:
    static CRecLan *pInstance;
    static char m_szClassName[LENGTH_OF_CLASSNAME];

private:


public:
    CRecLan( int iKeyId );
    void Run();

    // 명령에 대한 처리 함수 정의
    void DumpList();


    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CRecLan* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CRecLan( g_iKeyId++ );
        }
        return pInstance;
    }
};

#define RECLAN     CRecLan::GetInstance()

#endif // CRECLAN_H
