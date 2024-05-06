#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>

#define MAX_LEN_BUFFER 1024
#define LEN_DATA 64
#define ECHO_QUERY "ECHO"
#define QUIT_QUERY "QUIT"
#define INFO_QUERY "INFO"
#define LIST_QUERY "LIST"
#define CD_QUERY "CD"
#define UNKNOWN_QUERY "UNKNOWN QUERY"
#define LINK_TO_FILE " --> "
#define LINK_TO_LINK " -->> "
#define EXIT_MESSAGE "The session has ended\n"
#define INVALID_QUERY "Invalid server command\nServer commands: [CD, ECHO, LIST, QUIT, INFO]\n"
#define INVALID_DIRECTORY "The directory could not be opened. Invalid input\n"

enum LOGGER_LEVEL
{
    FATAL_ = 0,
    ERROR_ = 1,
    WARN_ = 2,
    INFO_ = 3,
    DEBUG_ = 4,
    TRACE_ = 5
};

extern const char *infoFileName;
extern char defaultDirectoryPath[MAX_LEN_BUFFER];

char *readDirectoryContent(DIR *directory, char *currentDirectoryPath);
size_t readFileInfo(const char *fileName, char **buffer);
void consoleQueryLog(int clientSocketDescriptor, const char *serverCommand, const char *clientCommand, int loggerLevel);
void *handleClient(void *clientSocketDescriptor_);