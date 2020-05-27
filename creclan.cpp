
#include <sys/types.h>
#include <sys/socket.h>


#include "creclan.h"
#include "clog.h"

#define _DEBUG_


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
    m_pMsg = GetDataMessage();

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->opCode ) {
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
    UINT uiStartAddress;

    STR_LAN_HEADER strLanHeader;
    UNI_LAN_DATA uniLanData;

    STR_REQ_DUMP_LIST *pData= ( STR_REQ_DUMP_LIST * ) m_pMsg->msg;

    int iRet;
    char *pAddress;

#ifdef _DEBUG_
    char *pBuffer;
    pBuffer = pAddress = (char *) malloc( 16 * 1000 );
#else
    pAddress = (char *) uiStartAddress;
#endif

    // 랜 헤더 송신
    strLanHeader.opCode = enRES_DUMP_LIST;
    strLanHeader.uiLength = DUMP_DATA_SIZE;

    iRet = send( m_pMsg->iSocket, (char *) & strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );

    // 랜 데이터 송신
    memcpy( uniLanData.cData, pBuffer, DUMP_DATA_SIZE );

    iRet = send( m_pMsg->iSocket, (char *) & uniLanData, strLanHeader.uiLength, MSG_DONTWAIT );

#ifdef _DEBUG_
    free( pBuffer );
#endif
}
