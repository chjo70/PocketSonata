#include "curbit.h"
#include "clog.h"


#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CUrBit* CUrBit::pInstance = nullptr;

/**
 * @brief CUrBit::CUrBit
 * @param iKeyId
 */
CUrBit::CUrBit( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
{
   LOGENTRY;
}

/**
 * @brief CUrBit::Run
 */
void CUrBit::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CUrBit::_routine
 */
void CUrBit::_routine()
{
    LOGENTRY;
    m_pMsg = GetDataMessage();

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->opCode ) {

            default:
                //Log( enNormal, "AAA" );
                break;
        }
    }

}
