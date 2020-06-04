
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "mysocket.h"
#include "clog.h"
#include "creclan.h"


// 클래스 내의 정적 멤버변수 값 정의
//char CMySocket::m_szClassName[LENGTH_OF_CLASSNAME] = { "CMySocket" };

/**
 * @brief CMySocket::CMySocket
 */
CMySocket::CMySocket( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
{
    LOGENTRY;

}

/**
 * @brief CMySocket::Run
 */
void CMySocket::Run()
{
    
    CThread::Run();
}

/**
 * @brief CMySocket::_routine
 */
void CMySocket::_routine()
{
    LOGENTRY;

    bool bHeader[MAX_CLIENTS];
    UINT uiTotalRead[MAX_CLIENTS];

    STR_LAN_HEADER strLanHeader[MAX_CLIENTS];
    char szLanData[MAX_CLIENTS][MAX_LAN_DATA];

    int opt = true, addrlen, i, iActivity, iRead;
    int iClientSocket[MAX_CLIENTS];
    int iMasterSocket, iMaxSocket, iSocket, iNewSocket;

    struct sockaddr_in address;

    char *pLanData;

    //set of socket descriptors
    fd_set readfds;

    STR_MessageData sndMsg;

    //initialise all client_socket[] to 0 so not checked
    for( i=0 ; i < MAX_CLIENTS ; i++) {
        iClientSocket[i] = 0;
    }

    //create a master socket
    if( ( iMasterSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) {
        perror( "Master Socket 실패" );
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(iMasterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) {
        perror( "Master Socket 소켓 옵션");
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if( bind( iMasterSocket, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        perror( "Bind 실패");
    }
    printf( " Listener on port %d\n", PORT );

    //try to specify maximum of 3 pending connections for the master socket
    if( listen( iMasterSocket, 3 ) < 0 ) {
        perror( "Listen 실패" );
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts( " Waiting for connections ..." );

    while( true ) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET( iMasterSocket, &readfds);
        iMaxSocket = iMasterSocket;

        //add child sockets to set
        for( i=0 ; i < MAX_CLIENTS ; i++ ) {
            //socket descriptor
            iSocket = iClientSocket[i];

            //if valid socket descriptor then add to read list
            if( iSocket > 0) {
                FD_SET( iSocket , &readfds);
            }

            //highest file descriptor number, need it for the select function
            if(iSocket > iMaxSocket) {
                iMaxSocket = iSocket;
            }
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        iActivity = select( iMaxSocket + 1 , &readfds , NULL , NULL , NULL);

        if ((iActivity < 0) && (errno!=EINTR) ) {
            perror( "select 에러" );
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(iMasterSocket, &readfds)) {
            if ((iNewSocket = accept(iMasterSocket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0 ) {
                perror( "Accept 실패" );
            }

            //add new socket to array of sockets
            for (i = 0; i < MAX_CLIENTS; i++) {
                //if position is empty
                if( iClientSocket[i] == 0 ) {
                    iClientSocket[i] = iNewSocket;
                    bHeader[i] = true;
                    uiTotalRead[i] = 0;
                    LOGMSG1( enNormal, " Adding to list of sockets as %d\n" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for ( i = 0; i < MAX_CLIENTS; i++ ) {
            iSocket = iClientSocket[i];

            //Check if it was for closing , and also read the
            //incoming message
            if (FD_ISSET( iSocket , &readfds)) {
                if( bHeader[i] == true ) {
                    pLanData = (char *) & strLanHeader[i];
                    if (( iRead = recv( iSocket , & pLanData[uiTotalRead[i]], sizeof(STR_LAN_HEADER)-uiTotalRead[i], MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( iSocket, & address, & iClientSocket[i] );
                    }
                    //Echo back the message that came in
                    else {
                        uiTotalRead[i] += iRead;
                        if( uiTotalRead[i] == sizeof(STR_LAN_HEADER) ) {
                            bHeader[i] = false;
                            uiTotalRead[i] = 0;
                        }
                    }
                }
                else {
                    pLanData = (char *) & szLanData[i];
                    if (( iRead = recv( iSocket , & pLanData[uiTotalRead[i]], strLanHeader[i].uiLength-uiTotalRead[i], MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( iSocket, & address, & iClientSocket[i] );
                    }
                    else {
                        uiTotalRead[i] += iRead;
                        if( uiTotalRead[i] == strLanHeader[i].uiLength ) {
                            bHeader[i] = true;
                            uiTotalRead[i] = 0;

                            sndMsg.mtype = 1;
                            sndMsg.opCode = strLanHeader[i].opCode;
                            sndMsg.iSocket = iSocket;

                            memcpy( & sndMsg.msg[0], pLanData, strLanHeader[i].uiLength );

                            if( msgsnd( RECLAN->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
                                perror( "msgsnd 실패" );
                            }
                            else {
                                // DisplayMsg( & sndMsg );

                            }

                        }
                    }
                }
            }
        }
    }

}

/**
 * @brief CMySocket::CloseSocket
 * @param iSocket
 * @param pAddress
 * @param pClientSocket
 */
void CMySocket::CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket )
{
    int addrlen;

    addrlen = sizeof(sockaddr_in);
    //Somebody disconnected , get his details and print
    getpeername(iSocket , (struct sockaddr*) pAddress , (socklen_t*)&addrlen);
    LOGMSG2( enNormal, "Host disconnected , ip %s , port %d \n" , inet_ntoa(pAddress->sin_addr) , ntohs(pAddress->sin_port));

    //Close the socket and mark as 0 in list for reuse
    close( iSocket );
    *pClientSocket = 0;

}
