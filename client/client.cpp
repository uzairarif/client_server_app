#include "create_and_connect_client.hpp"


int main(int argc, char *argv[])
	{
    
	client_information cinfo;
    int temp_ret;
    char read_buf[1024];
	bool end_connection = false;

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
		
		int read_chars = read(STDIN_FILENO,read_buf,1024);
		if (write(cinfo.sock, read_buf, read_chars-1) < 0){
			perror("writing on stream socket");
		}

	}
	
	close(cinfo.sock);
}