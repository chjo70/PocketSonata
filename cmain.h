#ifndef CMAIN_H
#define CMAIN_H

#include "cthread.h"


class CMain
{
private:
    static CMain *pInstance;

private:
    void Init();

public:
    CMain();
    void Run();

    static CMain* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CMain();
        }
        return pInstance;
    }
};

#define MAIN     CMain::GetInstance()

#endif // CMAIN_H
