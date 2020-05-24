
#include "creclan.h"
#include "clog.h"


// 클래스 내의 정적 멤버변수 값 정의
char CRecLan::m_szClassName[LENGTH_OF_CLASSNAME] = { "CRecLan" };
CRecLan* CRecLan::pInstance = nullptr;


/**
 * @brief CRecLan::CRecLan
 * @param iKeyId
 */
CRecLan::CRecLan( int iKeyId ) : CThread( iKeyId )
{
   LOGENTRY;
}

/**
 * @brief CRecLan::Run
 */
void CRecLan::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CRecLan::_routine
 */
void CRecLan::_routine()
{
    LOGENTRY;
    STR_MessageData *pMsg = GetDataMessage();

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( pMsg->x.opCode ) {
            case enREQ_DUMP_LIST :
                DumpList();
                break;
            default:
                //Log( enNormal, "AAA" );
                break;
        }
    }

}

/**
 * @brief CRecLan::DumpList
 */
void CRecLan::DumpList()
{

}
