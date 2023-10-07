#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

// A function to display an error and stop the program
void error(const char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char const *argv[])
{

    printf("=========================================================");
    printf("\n               WELCOME TO FILE EATER");
    printf("\n=========================================================");

    printf("\n\n[+] Preparing for connections...");

    // Declaring Socket File Descriptors (Pre and Post Connection)
    int sockFdPreConn, sockFdPostConn;

    // awamiErrorCode to store error codes for any function we run so that we can show an error if needed
    int awamiErrorCode;

    // Setting the port to run the process on..
    int port = 4053;

    // Declaring buffer of size 1024, needed for sending messages
    char buffer[1024];

    // Declaring object to carry addresses for server and client
    struct sockaddr_in serverAddress, clientAddress;

    // A variable to store the length of the address of the client we will connect to
    socklen_t clientLength;

    // Initiliazing socket before connection
    sockFdPreConn = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;
    if (setsockopt(sockFdPreConn, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0)
    {
        error("\n[!] Error while setting sock option.");
    }

    // Checking if initialization returned with any errors...
    if (sockFdPreConn < 0)
    {
        error("\n[!] Error while Pre connection socket initialization.");
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
        error("\n[!] Error while binding.");
    }

    printf("\n[+] Done preparing.");

    // Listen for connections
    printf("\n\n[+] Listening for connections...");
    listen(sockFdPreConn, 5);

    // Initializing clientLength
    clientLength = sizeof(clientAddress);
    sleep(1);

    // Initializing post-connection socket once the connection is made by the client
    sockFdPostConn = accept(sockFdPreConn, (struct sockaddr *)&clientAddress, &clientLength);

    // Checking if the initialization was successful
    if (sockFdPostConn < 0)
    {
        error("\n[!] Error while accepting connection.");
    }

    printf("\n[+] Connected successfully.");

    // Closing both sockets
    close(sockFdPostConn);
    close(sockFdPreConn);

    printf("\n");
    return 0;
}