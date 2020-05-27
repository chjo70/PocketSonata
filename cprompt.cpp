#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

#include<readline/readline.h>
#include<readline/history.h>

#include "cprompt.h"
#include "clog.h"

#define _DEBUG_

#define MAX_LIST        (100)
#define MAX_KETLINE     (1000)


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

char CPrompt::m_szListOfOwnCmds[NOOFOWNCMDS][50] = { "md",
                                                     "mm",
                                                     "help",
                                                     "hello" } ;


// 클래스 내의 정적 멤버변수 값 정의
char CPrompt::m_szClassName[LENGTH_OF_CLASSNAME] = { "CPrompt" };
CPrompt* CPrompt::pInstance = nullptr;

CPrompt::CPrompt( int iKeyId ) : CThread( iKeyId )
{
   LOGENTRY;

   m_uiDumpAddress = 0;
   m_uiModifyAddress = 0;
}



/**
 * @brief CRecLan::_routine
 */
void CPrompt::_routine()
{
    int execFlag = 0;
    char inputString[MAX_KETLINE];
    char *parsedArgs[MAX_LIST], *parsedArgsPiped[MAX_LIST];

    LOGENTRY;
    //STR_MessageData *pMsg = GetDataMessage();

    while( true ) {
        if( takeInput( inputString ) )
            continue;

        execFlag = processString( inputString, parsedArgs, parsedArgsPiped );

    }

}


/**
 * @brief CPrompt::takeInput Function to take input
 * @param str
 * @return
 */
int CPrompt::takeInput(char* str)
{
    char* buf;

    buf = readline( "\n $> " );
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

// Help command builtin
void CPrompt::openHelp( int iArg )
{
    switch( iArg ) {
        case 1 :
            puts( "\n md 시작_어드레스_값 [종료_어드레스_값], [데이터_크기] 형식으로 입력하여 시작 어드레스 값을 시작으로 메모리 값을 16진수로 표시합니다.");
            puts( "\n\t\t 시작_어드레스_값 : 시작 어드레스를 나타낸다.");
            puts( "\n\t\t 종료_어드레스_값 : 종료 어드레스를 나타낸다.");
            puts( "\n\t\t 데이터_크기 : 전시할 비트를 표시하며 1, 2, 4, 8 등으로 정할 수 있다.");
            break;

        case 2 :
            puts( "\n mm 시작_어드레스_값, [데이터_크기] 형식으로 입력하여 시작 어드레스 값을 시작으로 메모리 값을 16진수로 표시합니다.");
            puts( "\n\t\t 시작_어드레스_값 : 시작 어드레스를 나타낸다.");
            puts( "\n\t\t 데이터_크기 : 전시할 비트를 표시하며 1, 2, 4, 8 등으로 정할 수 있다.");
            break;

        default :
            puts("\n 디버깅용 프로그램 쉘 입니다. 백 그라운드에서는 다른 프로세스가 실행되어 정상 운용이 되며 이 쉘을 통해서 간단 명령을 수행할 수 있습니다."
                "\n 2020년 Copyright(c) @ 조철희"
                "\nList of Commands supported:"
                "\n>md"
                "\n>mm"
                "\n>exit"
                "\n>improper space handling");
                break;

    }

    return;
}

// Function to execute builtin commands
int CPrompt::ownCmdHandler(char** parsed)
{
    int i, switchOwnArg = 0;
    char* username;

    UINT uiData, uiData2;

    for (i = 0; i < NOOFOWNCMDS; i++) {
        if (strcmp(parsed[0], m_szListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case 1:
        if( parsed[1] == 0 && m_uiDumpAddress == 0 ) {
            openHelp( switchOwnArg );
        }
        else {
            if( parsed[1] != NULL ) {
                uiData = atoi( parsed[1] );
            }
            else {
                uiData = m_uiDumpAddress;
            }
            MemoryDump( uiData );
        }
        break;
    case 2:
        if( parsed[1] == 0 ) {
            openHelp( switchOwnArg );
        }
        else {
            if( parsed[1] != NULL ) {
                uiData = atoi( parsed[1] );
            }
            else {
                uiData = m_uiModifyAddress;
            }

            if( parsed[2] != NULL ) {
                uiData2 = atoi( parsed[2] );
            }
            else {
                uiData2 = 1;
            }
            MemoryModify( uiData, uiData2 );
        }
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;
    default:
        break;
    }

    return 0;
}

// function for finding pipe
int CPrompt::parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}

// function for parsing command words
void CPrompt::parseSpace(char* str, char** parsed)
{
    int i;

    for (i = 0; i < MAX_LIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int CPrompt::processString(char* str, char** parsed, char** parsedpipe)
{
    char* strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);

    } else {

        parseSpace(str, parsed);
    }

    if (ownCmdHandler(parsed))
        return 0;
    else
        return 1 + piped;
}

/**
 * @brief CPrompt::MemoryDump
 * @param uiAddress
 */
void CPrompt::MemoryDump( UINT uiStartAddress, UINT uiEndAddress )
{
    int i, j;
    char *pAddress, *pData;

    int iLines;

#ifdef _DEBUG_
    char *pBuffer;
    pBuffer = pAddress = (char *) malloc( 16 * 1000 );
#else
    pAddress = (char *) uiStartAddress;
#endif

    if( uiEndAddress == 0 ) {
        uiEndAddress = uiStartAddress + ( 16 * 10 );
    }

    iLines = ( uiEndAddress - uiStartAddress ) / 16;
    printf( "\n Address\tData\t\t\t\t\tASCII" );
    for( i=0 ; i < iLines ; ++i ) {
        printf( "\n %08p" , (void *) pAddress );
        pData = pAddress;
        for( j=0 ; j < 16 ; ++j ) {
            printf( "%02x ", *pData++ );
        }
        pData = pAddress;
        for( j=0 ; j < 16 ; ++j ) {
            if( isprint( *pData ) )
                printf( "%1c", *pData++ );
            else
                printf( " " );
        }

        pAddress += 16;
    }

    m_uiDumpAddress = uiEndAddress + 1;

#ifdef _DEBUG_
    free( pBuffer );
#endif

}

/**
 * @brief CPrompt::MemoryModify
 * @param uiStartAddress
 * @param uiDataType
 */
void CPrompt::MemoryModify( UINT uiStartAddress, UINT uiDataType )
{
    char *pBuf;
    char *pAddress, *pData;

#ifdef _DEBUG_
    char *pBuffer;
    pBuffer = pAddress = (char *) malloc( 16 * 1000 );
#else
    pAddress = (char *) uiStartAddress;
#endif

    do {
        printf( "%08p %02x" , pAddress, *pAddress );
        pBuf = readline( " " );

        if( *pBuf != 0 && *pBuf == '.' ) {
            // *pAddress = atoi( *pBuf );
            ++ pAddress;
            //printf( "\n" );
        }
        else {
            break;
        }
    }
    while( true );

#ifdef _DEBUG_
    free( pBuffer );
#endif

}
