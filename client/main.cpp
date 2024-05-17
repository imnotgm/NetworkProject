#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.cpp"

int main(int argc, char *argv[])
{
    char buf[BUFSIZ];
    char request[BUFSIZ];
    char response[BUFSIZ];

    if(argc != 3)
    {
		(void) fprintf(stderr,"usage: %s id portnum \n",argv[0]);
		exit(1);
	}

    Client user();

    while(1)
    {
        if(!fgets(buf, BUFSIZ - 1, stdin))
        {
            if (ferror(stdin)) {
                perror("stdin");
                exit(1);
            }
            exit(0);
        }
    }
}