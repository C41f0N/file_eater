#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char const *argv[])
{

    // Initializing socket file descriptor and the awaami error code
    int sockFd, awaamiErrorCode;

    // Setting the server IP and checking if it is valid
    int port = 4053;

    // Declaring server address object
    struct sockaddr_in serverAddress;

    // Cleaning/Emptying the server address variable before use
    bzero((char *)&serverAddress, sizeof(serverAddress));

    // Declaring buffer needed for data transfer
    char buffer[1024];

    // Initialising socket file descriptor
    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    // Checking if there was an error
    if (sockFd < 0)
    {
        error("\n[!] Error opening socket.");
    }

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        error("\n[!] Invalid IP");
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    // Connecting to host while checking for errors
    if (connect(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        error("\n[!] Error while trying to connect");
    }

    printf("[+] Successfully Connected.\n");

    close(sockFd);
    return 0;
}
