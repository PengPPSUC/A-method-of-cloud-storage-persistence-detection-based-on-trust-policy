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
	void GenerrateTheChallengeSequenceNum(int *InitialSequence,int TheTotalNumOfBlocl,int TheMaxMixNum,int *TheChallengeSequence);
	char recvBuf[100];
	char sendBuf[50];
	char tempBuf[100];
	int TheTotalNumOfBlocl=20;
	int InitialSequence[20];
	int TheChallengeSequence[50];
	int TheCurrentSequenceNum=0;
	permutation(TheTotalNumOfBlocl,InitialSequence,sendBuf);
	GenerrateTheChallengeSequenceNum(InitialSequence,TheTotalNumOfBlocl,4,TheChallengeSequence);
	for (int i=0;i<sizeof(TheChallengeSequence);i++)
		{
			if (TheChallengeSequence[i]==127)
			{
				printf("%d,",TheChallengeSequence[i]);
				sendBuf[i]=TheChallengeSequence[i];
				break;
			}
			else
			{
				printf("%d,",TheChallengeSequence[i]);
				sendBuf[i]=TheChallengeSequence[i];
			}
			
		}
	printf("\n");
	string theTXTmessage[100];
	int len = sizeof(SOCKADDR);
	while (1)
	{
		//printf("Please input data:\n");
		//gets(sendBuf);
		sendto(sockClient,sendBuf,sizeof(sendBuf)+1,0,(SOCKADDR*)&addrSrv,len);
		recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrSrv,&len);
		for (int i=0;i<33;i++)
		{
			printf("%c",recvBuf[i]);
		}
		printf("\n");
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

void GenerrateTheChallengeSequenceNum(int *InitialSequence,int TheTotalNumOfBlocl,int TheMaxMixNum,int *TheChallengeSequence)
{
	int TheRemainNum=0;
	int i=0;
	int j=0;
	
	while (1)
	{
		TheRemainNum=TheRemainNum+(1+rand()%(TheMaxMixNum));
		if (TheRemainNum>=(TheTotalNumOfBlocl-TheMaxMixNum))
		{
			for (i;i<TheRemainNum;i++)
			{
				TheChallengeSequence[i+j]=InitialSequence[i];
			}
			TheChallengeSequence[TheRemainNum+j]=100;
			i=TheRemainNum;
			j++;
			for (TheRemainNum;TheRemainNum<TheTotalNumOfBlocl;TheRemainNum++)
			{
				TheChallengeSequence[TheRemainNum+j]=InitialSequence[TheRemainNum];

			}
			TheChallengeSequence[TheTotalNumOfBlocl+j]=127;
			break;
		}
		else
		{
			for (i;i<TheRemainNum;i++)
			{
				TheChallengeSequence[i+j]=InitialSequence[i];
			}
			TheChallengeSequence[TheRemainNum+j]=100;
			i=TheRemainNum;
			j++;
		}

	}

}
