#ifndef CMAIN_H
#define CMAIN_H

#include "_system.h"
#include "cthread.h"


class CMain : public CThread
{
private:
    static CMain *pInstance;

private:
    void Init();

public:
    CMain( int iKeyId );
    void Run();
    virtual void _routine();

    static CMain* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CMain( g_iKeyId );
        }
        return pInstance;
    }
};

#define MAIN     CMain::GetInstance()

#endif // CMAIN_H
