#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>

	
int main(int argc,char**argv){
	int sock = socket(PF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr("10.13.64.20");
	target.sin_port = htons(10001);
	
	connect(sock,(struct sockaddr*)&target,sizeof(target));
	
	/*printf("sock is %d\n",sock);*/
	
	close(sock);
	return 0;
}