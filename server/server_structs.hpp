#include <netinet/in.h>

struct client {
    int clientid;
    int msgsock;
};

struct server_information {
    int sock;
    int length;
	struct sockaddr_in server;
};

