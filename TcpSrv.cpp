
#ifdef _DEBUG
#pragma warning( disable : 4786)
#endif
#include <WinSock2.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include "md5class.h"
#include <vector>
#include <time.inl>
#include <iostream>
#include <cassert>
#include <atlstr.h>
#include <iosfwd>
#include <sstream>
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
	
	char *FileRead(const char *textPath,char *textBuff);
	string int_to_String(int n);
	CMD5 md5;

	//SOCKET sockSrv = socket(AF_INET,SOCK_STREAM,0);//TCP
	SOCKET sockSrv = socket(AF_INET,SOCK_DGRAM,0);//UDP
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);

	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));


	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[20];
	char sendBuf[100];
	char tempBuf[100];
	char *tempTextBuff="";
	char *textBuff="";
	string fileMainPath = "C:/Users/Hasee/Desktop/";
	int textBloclNum=1;
	string textName="";
	textName=int_to_String(textBloclNum);
	//printf("%s\n",textName.c_str());
	string textform=".txt";
	string TrueTextPath=fileMainPath+textName+textform;
	const char *textPath=TrueTextPath.c_str();
	printf("The path is %s \n",textPath);
	textBuff=FileRead(TrueTextPath.c_str(),tempTextBuff);
	printf("the text is :%s.\n",textBuff);
	//printf("The text is:%s\n",readLineTemp);
	//const char *readLineChar =readLine.c_str();
	//md5.setPlainText(readLineChar);
	//printf("The text's md5 is : %s\n",md5.getMD5Digest());
	while (1)
	{
		recvfrom(sockSrv,recvBuf,sizeof(recvBuf)+1,0,(SOCKADDR*)&addrClient,&len);
		if('q'==recvBuf[0])
		{
			sendto(sockSrv,"q",strlen("q")+1,0,(SOCKADDR*)&addrClient,len);
			printf("Chat end!\n");
			break;
		}
		//sprintf(tempBuf,"%s say : %s",inet_ntoa(addrClient.sin_addr),recvBuf);
		printf("client say: %d\n",recvBuf[9]);
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
		//printf("the text's len is :%d \n",len);
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
