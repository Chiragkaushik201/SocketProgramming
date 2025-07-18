#include<iostream>
#include<string.h>
#ifdef _WIN32
#include<winsock2.h>
#else
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#endif

//Note: File descriptor and socket descriptor is same

using namespace std;
fd_set fr,fw,fe; //fd_count,fd_array[64] stores file descriptor handling socket and can handle maximum 64


int main()	
{

	struct sockaddr_in srv;

#ifdef _WIN32
	//1. Initialise WSA variables: settingup environment for Socket Programming
	WSADATA ws;

	if(WSAStartup(MAKEWORD(2,2),&ws)<0) //setting up version of winsock 2,2
	{
		cout<<"Failed to setup WSA"<<endl;
	}
#endif
	

	//2. Intitialise the socket
	int nSocket = socket(AF_INET //Address family
			,SOCK_STREAM //Socket type
			,IPPROTO_TCP);//0:underlying protocol; //IPPROTO_TCP:for tcp protocol
	int maxsock=nSocket;
	if(nSocket<0)
	{
		cout<<"Unable to setup socket"<<endl;
	}
	else
	{
		cout<<"Socket Opened!! Socket Descriptor ID:"<<nSocket<<endl;
	}

	//3. Intitialise the enviroment for sockaddr structure
	srv.sin_family= AF_INET;
	srv.sin_port = htons(25667);
	srv.sin_addr.s_addr =INADDR_ANY;
	memset(&(srv.sin_zero),0,8);

	//Before binding we can set if the socket is blocking or non blocking
	//by default it is blocking but for non blocking this functionlality is used
	//blockstate = 0 means blocking and 1 means non blocking
	//retval =0 in sucess
	//unsigned long block_state=1;
	//auto retVal = ioctlsocket(nSocket,FIOBIO, &block_state);

	//4. Bind the socket to local port: Number of services running , client needs a specific port to go to a specfic program
	
	retVal = bind(nSocket,(sockaddr*)&srv,sizeof(sockaddr));
	
	//5. Listen the request from the client
	retVal=listen(nSocket,5);//maximum 5 queues

	if(retVal<0)
	{
		cout<<"Failed to listen to local port";
	}
	
	//6. Keep waiting for the requests and proceed as per requests
	//keeping the socket descriptor into fd_set
	//Socket descriptor points to a kernel object , that kernal object is opaque i.e. it is abstracted
	
	FD_SET(nSocket,&fr);//nSocket is getting attached to fr fd_set
	struct timeval tv;
	tv.tv_sec=1;
	tv.tv_usec=0;

	//select function handles multiple sockets through fd_set structure which handle maximum of 64 sockets
	//returns: -1 : some error has been encountered
	//	 :  0 : timed out and no socket descriptor is ready
	//	 : >0 : Number of file descriptor is ready
	retVal = select(maxsock+1,&fr,&fw,fe,tv);//tells us how many socket descrptors are ready to read/write or execute

	if(retVal>0)
	{
		//Connected state
	}
	else if(retVal ==0)
	{
		//No connection or communication made
	}
	else
	{
		//failed
	}


	WSACleanup(); //Must call before closing /returning


	return 0;
}



