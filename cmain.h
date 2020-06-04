#ifndef CMAIN_H
#define CMAIN_H

#include "_system.h"
#include "cthread.h"




class CMain : public CThread
{
private:
    static CMain *pInstance;
    //static char m_szClassName[LENGTH_OF_CLASSNAME];

private:
    void Init();

public:
    CMain( int iKeyId, char *pClassName=NULL );
    void Run();
    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CMain* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CMain( g_iKeyId++, (char *)"CMain" );
        }
        return pInstance;
    }
};

#define MAIN     CMain::GetInstance()

#endif // CMAIN_H
