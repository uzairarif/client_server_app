#include <netinet/in.h>

struct client_information{
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;
};