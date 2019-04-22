#include "serverimport.hpp"
#define TRUE 1

using namespace std;

int main (){

    server_information sinfo;		//server information
	vector <client> c_clients;		//connected clients  
	vector <client> d_clients;		//disconnected clients
    int client_id=0;
	char buf[1024];
	int rval;
	int i;
    int temp_ret;
	char to_check[250];
						

	/* Create socket */
	temp_ret = createsock(&sinfo);
    if (temp_ret == -1){ exit(1);}
	/* Name socket using wildcards */
    temp_ret = namesocketandbind(&sinfo);
    if (temp_ret == -1){ exit(1);}
    /* Find out assigned port number and print it out */
	sinfo.length = sizeof(sinfo.server);
	temp_ret = getsockname(&sinfo);
    if (temp_ret == -1){ exit(1);}    
	/* Start accepting connections */
	listen(sinfo.sock, 10);
	

    do {
		client new_client;
		new_client.msgsock = accept(sinfo.sock, 0, 0);
		if (new_client.msgsock == -1)
			perror("accept");
		else {
			client_id++;
			new_client.clientid = client_id; 
			c_clients.push_back(new_client);
			int c = fork();
			if (c == 0){
				do
				{
					bzero(buf, sizeof(buf));
					if ((rval = read(new_client.msgsock, buf, 1024)) < 0)
						
						perror("reading stream message");
					i = 0;
					if (rval == 0){
						write(STDOUT_FILENO,"Ending connection\n",19);
						close(new_client.msgsock);
					}
					else {
						sprintf(to_check,"id=%i\n",new_client.clientid);
						write(STDOUT_FILENO,to_check,strlen(to_check));
						write(STDOUT_FILENO,buf,strlen(buf));
					}	
				} while (rval != 0);
			}
			if (c > 0){
				close(new_client.msgsock);
			}
			if (c < 0){
				perror("FORK FAILED ");
				exit(1);
			}
		}
	} while (TRUE);

}
