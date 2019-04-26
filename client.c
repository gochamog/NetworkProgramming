#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

void commun(int sock){
	char buf[256];
	int len_r;
	char *message = "この授業が終わったら、俺……ガチャ回すんだ……！";
	send(sock,message,strlen(message),0);
	len_r = recv(sock,buf,256,0);
	buf[len_r]='\n';
	printf("%s\n",buf);
	recv(sock,buf,256,0);
	
}

int main(int argc,char**argv){
	int sock = socket(PF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr("10.13.64.20");
	target.sin_port = htons(10001);
	
	connect(sock,(struct sockaddr*)&target,sizeof(target));
	
	/*printf("sock is %d\n",sock);*/
	
	commun(sock);
	
	close(sock);
	return 0;
}