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
    // 타겟 명령어 정의
    enREQ_URBIT = 0x1000,

    // 디버깅 용
    enREQ_DUMP_LIST = 0xF000,

} ;

// 각각의 명령어에 대한 데이터 구조체 정의
struct STR_REQ_DUMP_LIST {
    UINT uiAddress;
    UINT uiDataSize;
    UINT uiDataLength;
};



//////////////////////////////////////////////////////////////
// 송신 메시지 정의

#define     DUMP_DATA_SIZE              (16*10)

enum enRES_MESSAGE {
    enRES_DUMP_LIST = enREQ_DUMP_LIST,


} ;


struct STR_RES_DUMP_LIST {
    STR_REQ_DUMP_LIST strReqDumpList;

    char cData[500];
} ;



// 랜 메시지 구조체
union UNI_LAN_DATA {
    UINT uiResult;

    // 수신 메시지 구조체 정의
    STR_REQ_DUMP_LIST strReqDumpList;
    UINT uiUnit;

    // 송신 메시지 구조체 정의
    STR_RES_DUMP_LIST strResDumpList;

};



#endif // _SYSMSG_H
