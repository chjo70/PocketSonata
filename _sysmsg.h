#ifndef _SYSMSG_H
#define _SYSMSG_H

#include "_system.h"

struct STR_LAN_HEADER {
    unsigned int opCode;
    unsigned int uiLength;

} ;

//////////////////////////////////////////////////////////////
// 수신 메시지 정의
enum enREQ_MESSAGE {
    enREQ_DUMP_LIST = 0x1000,


} ;

// 각각의 명령어에 대한 데이터 구조체 정의
struct STR_REQ_DUMP_LIST {
    UINT uiAddress;
    UINT uiDataSize;
    UINT uiDataLength;
};


//////////////////////////////////////////////////////////////
// 송신 메시지 정의
enum enRES_MESSAGE {
    enRES_DUMP_LIST = enREQ_DUMP_LIST,


} ;


// 랜 메시지 구조체
struct STR_LAN_DATA {
    UINT uiLength;

    union UNI_DATA {
        UINT uiResult;

        // 수신 메시지 구조체 정의
        STR_REQ_DUMP_LIST strReqDumpList;
    } x ;

};



#endif // _SYSMSG_H
