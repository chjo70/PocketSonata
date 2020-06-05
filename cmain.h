#ifndef CMAIN_H
#define CMAIN_H

using namespace std;

#include "_system.h"
#include "cthread.h"

#include "dev/minIni.h"


// INI 파일 정의
#define INI_FILE    "packetSonata.ini"

class CMain : public CThread
{
private:
    static CMain *pInstance;

    minIni m_theIni;

private:
    void Init();
    void ReadIni();

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
