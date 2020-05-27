#ifndef CPROMPT_H
#define CPROMPT_H

#include "_system.h"
#include "cthread.h"

#define NOOFOWNCMDS             (4)



class CPrompt : public CThread
{
private:
    static CPrompt *pInstance;
    static char m_szClassName[LENGTH_OF_CLASSNAME];

    static char m_szListOfOwnCmds[NOOFOWNCMDS][50];

    UINT m_uiDumpAddress;
    UINT m_uiModifyAddress;


private:
    int takeInput(char* str);
    void openHelp( int iArg=-1 );
    int ownCmdHandler(char** parsed);
    void parseSpace(char* str, char** parsed);
    int parsePipe(char* str, char** strpiped);
    int processString(char* str, char** parsed, char** parsedpipe);
    int CPromptparsePipe(char* str, char** strpiped);


    void MemoryDump( UINT uiStartAddress, UINT uiEndAddress=0 );
    void MemoryModify( UINT uiStartAddress, UINT uiDataType=1 );

public:
    CPrompt( int iKeyId );

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CPrompt* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CPrompt( g_iKeyId++ );
        }
        return pInstance;
    }


};


#define PROMPT     CPrompt::GetInstance()

#endif // CPROMPT_H
