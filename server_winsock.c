#include<stdio.h>
#include<winsock2.h>
#include<string.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{

	// Declaring needed variables

	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;
    int c, recv_size;
    char buffer[2048];


	// Repetitive code declared as functions here...

	void error() {
		exit(1);
	}

	void initWinSock() {
		printf("\nInitialising Winsock...");
		if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
		{
			printf("\nFailed. Error Code : %d",WSAGetLastError());
			error();
		}
		
		printf("\nInitialised.");
	}
	
	void createAndBindSock() {

	if((s = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP )) == INVALID_SOCKET)
	{
		printf("\nCould not create socket : %d" , WSAGetLastError());
		error();
	}

	fprintf(stderr, "\nSocket Created.");

    //Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
		
		//Bind
		if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
		{
			printf("\nBind failed with error code : %d" , WSAGetLastError());
			error();
		}
		
		puts("\nBind done");
	}

	void listenAndAcceptConn() {
		listen(s , 3);

		c = sizeof(struct sockaddr_in);
		new_socket = accept(s , (struct sockaddr *)&client, &c);
		if (new_socket == INVALID_SOCKET)
		{
			printf("\naccept failed with error code : %d" , WSAGetLastError());
		}

		printf("\nConnection Accepted.");
	
	}

	void reliableRecieve() {

		// Cleaning buffer before data comes.
		memset(buffer,0,strlen(buffer));

		if ((recv_size = recv(new_socket, buffer, sizeof(buffer), 0)) == SOCKET_ERROR) {
			printf("\n[!] Recieve Failed.");
		}

		buffer[recv_size] = '\0';
	}

	void reliableSend() {
		//Sending message to client
		send(new_socket , buffer , strlen(buffer) , 0);

	}


	// Main Code

	initWinSock();
	createAndBindSock();
	listenAndAcceptConn();


	int quit = 0;

	while (!quit) {
		fprintf(stderr, "\nEnter your message: ");
		fgets (buffer, sizeof(buffer), stdin);
		
		fprintf(stderr, "\n[SENDING]: %s", buffer);
		reliableSend();

		fprintf(stderr, "\nEnter 1 if you want to quit: ");
		scanf("%d", &quit);
		
		Sleep(100);
	}
	
	// Not closing properly on purpose
	// closesocket(s);
	// closesocket(new_socket);

	return 0;
}