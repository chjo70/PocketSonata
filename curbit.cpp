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
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->msg[0];

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->opCode ) {
            case enREQ_URBIT :
                LOGMSG1( enNormal, "URBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                break;

            default:
                //Log( enNormal, "AAA" );
                break;
        }
    }

}
