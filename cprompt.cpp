#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

#include<readline/readline.h>
#include<readline/history.h>

#include "cprompt.h"
#include "clog.h"

#define MAX_LIST        (100)
#define MAX_KETLINE     (1000)

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

char CPrompt::m_szListOfOwnCmds[NOOFOWNCMDS][50] = { "md",
                                         "cd",
                                         "help",
                                         "hello" } ;


// 클래스 내의 정적 멤버변수 값 정의
char CPrompt::m_szClassName[LENGTH_OF_CLASSNAME] = { "CPrompt" };
CPrompt* CPrompt::pInstance = nullptr;

CPrompt::CPrompt( int iKeyId ) : CThread( iKeyId )
{
   LOGENTRY;
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

    buf = readline( "\n $>" );
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

// Help command builtin
void CPrompt::openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Suprotik Dey"
        "\n-Use the shell at your own risk..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");

    return;
}

// Function to execute builtin commands
int CPrompt::ownCmdHandler(char** parsed)
{
    int i, switchOwnArg = 0;
    char* username;

    for (i = 0; i < NOOFOWNCMDS; i++) {
        if (strcmp(parsed[0], m_szListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
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
