#include "create_and_connect_client.hpp"

#define DATA "Half a league, half a league . . ."

int main(int argc, char *argv[])
	{
    
	client_information cinfo;
    int temp_ret;
    char buf[1024];

	/* Create socket */
    temp_ret = createsock(&cinfo);
	if (temp_ret == -1){
        exit(1);
    }
    /* Connect socket using name specified by command line. */
	temp_ret = connecting_to_host(&cinfo,argv);
    if (temp_ret == -1){
        exit(1);
    }
	while(1) {
	  
	if (write(cinfo.sock, DATA, sizeof(DATA)) < 0)
		perror("writing on stream socket");
	    getchar();
	  
	}
	close(cinfo.sock);
}