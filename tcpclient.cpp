#ifdef _DEBUG
#pragma warning( disable : 4786)
#endif

#include <WinSock2.h>
#include <stdio.h>
#include "md5class.h"
#include <vector>
#include <time.inl>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
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
	/*TCP
	SOCKET sockClient= socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr =inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	char recvBuf[100];
	recv(sockClient,recvBuf,100,0);
	printf("%s/n",recvBuf);

	send(sockClient,"This is Xu",strlen("This is Xu")+1,0);

	closesocket(sockClient);
	WSACleanup();

	getchar();
	*/
	CMD5 md5;
	void permutation(int n,int *z_arry);
	int TheNumOfTheBlock=30;
	int InitialSequence[30];
	permutation(TheNumOfTheBlock,InitialSequence);
	for (int i=0;i<30;i++)
	{
		printf("%d,",InitialSequence[i]);
	}
	SOCKET sockClient= socket(AF_INET,SOCK_DGRAM,0);//�����׽���
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr =inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[100];
	string theTXTmessage[100];
	int len = sizeof(SOCKADDR);
	while (1)
	{
		printf("Please input data:\n");
		gets(sendBuf);
		sendto(sockClient,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR*)&addrSrv,len);
		recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrSrv,&len);
		if ('q'==recvBuf[0])
		{
			sendto(sockClient,"q",strlen("q")+1,0,(SOCKADDR*)&addrSrv,len);
			printf("Chat end!\n");
			break;
		}
		sprintf(tempBuf,"%s say : %s",inet_ntoa(addrSrv.sin_addr),recvBuf);
		printf("%s\n",tempBuf);

	}
	closesocket(sockClient);
	WSACleanup();
}

void permutation(int n,int *z_arry)
{
	int i,j,k,z;
	int buffer[100];
	for (i=0; i<n; i++)
		buffer[i]=0;
	srand((unsigned)time((time_t *)0));
	for (i=0; i<n; i++){
		z=rand()%(n-i);
		j=0;
		k=0;
		while(j<=z)
		{
			if(buffer[j+k]==0) j++;
			else k++;
		}
		buffer[j+k-1]=1;
		z_arry[i]=j+k-1;
	}
	return;
}



string readText(string readLine,string filePath)
{
	ifstream ifs(filePath);
	getline(ifs,readLine);
	return readLine;
}