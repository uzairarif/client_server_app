#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "client_structs.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int createsock ( client_information *cinfo ){
    cinfo->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (cinfo->sock < 0) {
		perror("opening stream socket");
		write(STDOUT_FILENO," -- EXITING CLIENT APP\n",24);
        return -1;
	}
    return 1;
}

int connecting_to_host (client_information *cinfo, char *argv[]){
    cinfo->server.sin_family = AF_INET;
    cinfo->hp = gethostbyname(argv[1]);
    if (cinfo->hp == 0){
        write(STDOUT_FILENO,"Unknown Host",13);
        return -1;
    }
	bcopy(cinfo->hp->h_addr, &cinfo->server.sin_addr, cinfo->hp->h_length);
	cinfo->server.sin_port = htons(atoi(argv[2]));
    if (connect(cinfo->sock,(struct sockaddr *) &cinfo->server,sizeof(cinfo->server)) < 0) {
		perror("connecting stream socket");
		exit(1);
	}
    return 1;
}

