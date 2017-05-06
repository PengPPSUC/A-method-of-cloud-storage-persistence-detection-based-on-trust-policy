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
	SOCKET sockClient= socket(AF_INET,SOCK_DGRAM,0);//创建套接字
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr =inet_addr("127.0.0.1");
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	char *FileRead(const char *textPath,char *textBuff);
	string int_to_String(int n);
	CMD5 md5;
	void permutation(int n,int *z_arry,char *sendBuffer);
	char recvBuf[100];
	char sendBuf[20];
	char tempBuf[100];
	int TheTotalNumOfBlocl=20;
	int InitialSequence[20];
	int TheCurrentSequenceNum=0;
	permutation(TheTotalNumOfBlocl,InitialSequence,sendBuf);
	printf("%d,%d,%d",sendBuf[9],strlen(sendBuf),sizeof(sendBuf));
	string theTXTmessage[100];
	int len = sizeof(SOCKADDR);
	while (1)
	{
		TheCurrentSequenceNum=TheCurrentSequenceNum+rand()%4;
		//printf("Please input data:\n");
		//gets(sendBuf);
		sendto(sockClient,sendBuf,sizeof(sendBuf)+1,0,(SOCKADDR*)&addrSrv,len);
		recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrSrv,&len);
		if ('q'==recvBuf[0])
		{
			sendto(sockClient,"q",strlen("q")+1,0,(SOCKADDR*)&addrSrv,len);
			printf("Chat end!\n");
			break;
		}
		//sprintf(tempBuf,"%s say : %s",inet_ntoa(addrSrv.sin_addr),recvBuf);
		//printf("%s\n",tempBuf);
	}
	closesocket(sockClient);
	WSACleanup();
}

void permutation(int n,int *z_arry,char *sendBuffer)
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
		sendBuffer[i]=z_arry[i];
	}
	return;
}
char *FileRead(const char *textPath,char *textBuff)
{
	FILE *pFile;
	if (NULL==(pFile=fopen(textPath,"r")))
	{
		printf("Error,can't open file!");
	} 
	else
	{
		fseek(pFile,0,SEEK_END);
		int len=ftell(pFile);
		textBuff=new char[len+1];
		rewind(pFile);
		fread(textBuff,1,len,pFile);
		textBuff[len]=0;
		fclose(pFile);
	}
	return textBuff;
}

string int_to_String(int n)
{
	string fileName="";
	fileName+=to_string((long double)n);
	return fileName;
}
