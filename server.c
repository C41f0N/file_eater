#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// A function to display an error and stop the program
void error(const char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main()
{

    // Declaring Socket File Descriptors (Pre and Post Connection)
    int sockFdPreConn, sockFdPostConn;

    // awamiErrorCode to store error codes for any function we run so that we can show an error if needed
    int awamiErrorCode;

    // Setting the port to run the process on..
    int port = 5055;

    // Declaring buffer of size 1024, needed for sending messages
    char buffer[1024];

    // Declaring object to carry addresses for server and client
    struct sockaddr_in serverAddress, clientAddress;

    // A variable to store the length of the address of the client we will connect to
    socklen_t clientLength;

    // Initiliazing socket before connection
    sockFdPreConn = socket(AF_INET, SOCK_STREAM, 0);

    // Checking if initialization returned with any errors...
    if (sockFdPreConn < 0)
    {
        error("[!] Error while Pre connection socket initialization.");
    }

    // Cleaning/Emptying the server address variable before use
    bzero((char *)&serverAddress, sizeof(serverAddress));

    // Initializing the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port); // Setting port from int to required datatype before setting it

    // Binding the address to the preConnection socket and checking if it goes wrong
    if (bind(sockFdPreConn, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        error("[!] Error while binding.");
    }

    // Listen for connections
    listen(sockFdPreConn, 1);

    // Initializing clientLength
    clientLength = sizeof(clientAddress);

    // Initializing post-connection socket once the connection is made by the client
    sockFdPostConn = accept(sockFdPreConn, (struct sockaddr *)&clientAddress, &clientLength);

    // Checking if the initialization was successful
    if (sockFdPostConn < 0)
    {
        error("[!] Error while accepting connection.");
    }

    printf("[+] Connection made successfully with %s.", inet_ntoa(clientAddress.sin_addr));

    return 0;
}