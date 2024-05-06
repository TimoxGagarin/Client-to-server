#include "headers/server_lib.h"

char defaultDirectoryPath[MAX_LEN_BUFFER];
const char *infoFileName;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <port> <path/to/base/directory> <path/to/server/info>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    infoFileName = argv[3];
    DIR *directory = opendir(argv[2]);
    if (!directory)
    {
        printf(INVALID_DIRECTORY);
        exit(EXIT_FAILURE);
    }
    getcwd(defaultDirectoryPath, MAX_LEN_BUFFER);

    struct addrinfo hints;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;

    struct addrinfo *result = NULL;
    int status = getaddrinfo(NULL, argv[1], &hints, &result);
    if (status)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    int serverSocketDescriptor = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    bind(serverSocketDescriptor, result->ai_addr, result->ai_addrlen);

    printf("My server on port %s is ready\n", argv[1]);
    listen(serverSocketDescriptor, SOMAXCONN);
    while (true)
    {
        int clientSocketDescriptor = accept(serverSocketDescriptor, result->ai_addr, &result->ai_addrlen);
        if (clientSocketDescriptor == -1)
        {
            fprintf(stderr, "Accept server error\n");
            exit(EXIT_FAILURE);
        }
        pthread_t thread;
        if (pthread_create(&thread, NULL, handleClient, (void *)&clientSocketDescriptor))
        {
            fprintf(stderr, "Accept client error, client descriptor: %d\n", clientSocketDescriptor);
            exit(EXIT_FAILURE);
        }
        pthread_detach(thread);
    }

    close(serverSocketDescriptor);
    exit(EXIT_SUCCESS);
}