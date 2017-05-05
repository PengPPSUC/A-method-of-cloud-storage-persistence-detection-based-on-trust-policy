
#ifdef _DEBUG
#pragma warning( disable : 4786)
#endif
#include <WinSock2.h>
#include <stdio.h>
#include "md5class.h"
#include <vector>
#include <string>
#include <time.inl>

using namespace std;

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
                               
		return;
	}


	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) {

			WSACleanup( );
			return; 
	}

	CMD5 md5;

	//SOCKET sockSrv = socket(AF_INET,SOCK_STREAM,0);//TCP
	SOCKET sockSrv = socket(AF_INET,SOCK_DGRAM,0);//UDP
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[100];

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
		if('q'==recvBuf[0])
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);
			printf("Chat end!\n");
			break;
		}
		sprintf(tempBuf,"%s say : %s",inet_ntoa(addrClient.sin_addr),recvBuf);
		printf("%s\n",tempBuf);
		printf("Please input data:\n");
		gets(sendBuf);
		md5.setPlainText(sendBuf);
		sendto(sockSrv,md5.getMD5Digest(),strlen(md5.getMD5Digest())+1,0,(SOCKADDR*)&addrClient,len);
	}
	closesocket(sockSrv);
	WSACleanup();
	/*TCP
	listen(sockSrv,5);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		SOCKET sockConn = accept(sockSrv,(SOCKADDR*)&addrClient,&len);
		
		char sendBuf[100];
		sprintf(sendBuf,"Welcome %s to my home",
			inet_ntoa(addrClient.sin_addr));
		send(sockConn,sendBuf,strlen(sendBuf)+1,0);

		char recvBuf[100];
		recv(sockConn,recvBuf,100,0);
		printf("%s\n",recvBuf);
		closesocket(sockConn);

	}
	*/
}

