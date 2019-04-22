#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "server_structs.hpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int createsock ( server_information *sinfo ){
    sinfo->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sinfo->sock < 0) {
		perror("opening stream socket");
		write(STDOUT_FILENO," -- EXITING APP",16);
        return -1;
	}
    return 1;
}

int namesocketandbind(server_information *sinfo){
    sinfo->server.sin_family = AF_INET;
	sinfo->server.sin_addr.s_addr = INADDR_ANY;
	sinfo->server.sin_port = 0;
    if (bind(sinfo->sock, (struct sockaddr *) &sinfo->server, sizeof(sinfo->server))) {
		perror("binding stream socket");
		write(STDOUT_FILENO," -- EXITING APP",16);
        return -1;
	}
    return 1;
}

int getsockname(server_information *sinfo){
    if (getsockname(sinfo->sock, (struct sockaddr *) &sinfo->server, (socklen_t*) &sinfo->length)) {
		perror("getting socket name");
		return -1;
	}
    printf("Socket has port #%d\n", ntohs(sinfo->server.sin_port));
    fflush(stdout);
    return 1;
}

