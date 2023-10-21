/*
	Initialise Winsock
*/

#include<stdio.h>
#include<Windows.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char buffer[2048];
	int recv_size, awaamiErrorCode;
	
	// Repetitive code declared as functions here...

	void error() {
		exit(1);
	}

	void initWinSock() {
		fprintf(stderr, "\nInitialising Winsock...");
		if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
		{
			fprintf(stderr, "\nFailed. Error Code : %d",WSAGetLastError());
			error();
		}
		
		fprintf(stderr, "\nInitialised.");
	}

	void createPrepSock() {

		if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
		{
			fprintf(stderr, "\nCould not create socket : %d" , WSAGetLastError());
			error();
		}

		// fprintf(stderr, "\nSocket Created.");

	}
	
	int makeConnToServer() {

		server.sin_addr.s_addr = inet_addr("127.0.0.1");
		server.sin_family = AF_INET;
		server.sin_port = htons(8888);
		
		if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
		{
			return 0;
		}

		return 1;
	}

	int reliableRecieve() {

		// Cleaning buffer before data comes.
		memset(buffer,0,strlen(buffer));

		if ((recv_size = recv(s, buffer, sizeof(buffer), 0)) == SOCKET_ERROR) {
			return -1;
		}



		buffer[recv_size] = '\0';
		if (recv_size > 0) {
			return 1;
		} else {
			return 0;
		}
	}

	void reliableSend() {
		//Sending message to client
		send(s , buffer , strlen(buffer) , 0);
	}



	// Main Code
	initWinSock();

	int connected = 0;

	while (1) {
		while (!connected) {
			Sleep(1000);
			fprintf(stderr, "\n[+] Trying to connect...");
			createPrepSock();
			connected = makeConnToServer();
		}

		fprintf(stderr, "\n[+] Connected\n\n");
		while (connected) {
			
			awaamiErrorCode = reliableRecieve();

			if (awaamiErrorCode == 1) { // Success with some data.
				fprintf(stderr, "\n[RECIEVED]: %s", buffer);
			} else if (awaamiErrorCode == 0) { // Success without any data.
				continue;
			} else { // Connection was broken
				connected = 0;
				break;
			}
		}

		fprintf(stderr, "\n\n[+] Disconnected...");
	}


	fprintf(stderr, "\nServer said: %s", buffer);

	strcpy(buffer, "Okay! geez.");
	fprintf(stderr, "\nReplying to server: %s", buffer);
	reliableSend();

	closesocket(s);

	return 0;
}