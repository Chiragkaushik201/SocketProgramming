#include<iostream>

using namespace std;

int main()
{
	struct sock_addrin srv;
	WSAData ws;
	if(WSAStartup(MAKEWORD(2,2),&ws)<0)
	{
		cout<<"Client WSA Sartup failed"<<endl;
		WSACleanup();
		return (EXIT_FAILURE)
	}

	int nSocket = socket(AF_INET,SOCK_STREAM,IPPROT_TCP);
	srv.sin_family = AF_INET;
	srv.sin_port =htons();
	srv.sin_addr.s_addr = inet_add("127.0.0.1");
	memset(&srv.sin_zero,0,8);

	//Connecting
	int retVal = connect(nSocket,(struct sockadd*)&srv,sizeof(srv));

	if(retVal>0)
	{
		char bff[255];
		recv(nSocket,buff,255,0);

		getchar();
		cout<<buff<<endl;
	}



	return 0;
}
