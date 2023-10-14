#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>

void error(const char *errorMessage)
{
    perror(errorMessage);
    fprintf(stderr, "\n\n");
    exit(1);
}

int main(int argc, char const *argv[])
{

    fprintf(stderr, "\n[+] Preparing to connect to backdoor.");

    // Where the extracted direcories will be stored
    char directoryList[2048];

    // Function to pull directories and store them in directoryList
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
            filetype[0] = entry->d_type + '0';

            strcpy(filename, entry->d_name);
            strcat(filename, "\n");
            strcat(filename, filetype);
            strcat(filename, "\n\n");
            strcat(directoryList, filename);
        }

        // Close the directory
        closedir(directory);
    }

    // Initializing socket file descriptor and the awaami error code
    int sockFd, awaamiErrorCode;

    // Setting the server IP and checking if it is valid
    int port = 4053;

    // Declaring server address object
    struct sockaddr_in serverAddress;

    // Cleaning/Emptying the server address variable before use
    bzero((char *)&serverAddress, sizeof(serverAddress));

    // Declaring buffer needed for data transfer
    char buffer[2048];

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
        error("\n[!] Error: Could not connect");
    }

    fprintf(stderr, "\n[+] Successfully Connected.\n");

    awaamiErrorCode = 0;

    while (awaamiErrorCode >= 0)
    {
        int halt = 0;

        // Pull directory data and copy it to buffer
        memset(directoryList, 0, strlen(directoryList));
        memset(buffer, 0, strlen(buffer));
        pullDirectoryData();
        strcpy(buffer, directoryList);

        awaamiErrorCode = write(sockFd, buffer, sizeof(buffer));
        fprintf(stderr, "[+] Send this to server:\n%s", buffer);
        fprintf(stderr, "\nDo you want to continue? press 0 if no else 1: ");
        scanf("%d", &halt);

        if (halt)
            break;
    }

    fprintf(stderr, "\n\n");

    close(sockFd);
    return 0;
}
