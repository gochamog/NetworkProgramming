#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#define BUF_SIZE 256

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}

void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
	char *message = "この授業が終わったら、俺……ガチャ回すんだ……！";
	if(send(sock,message,strlen(message),0) != strlen(message)){
		DieWithError("send() sent a message of unexpected bytes");
	}
	if((len_r = recv(sock,buf,BUF_SIZE,0)) <= 0){
		DieWithError("recv() failed");
	}/*0:サーバーが正常終了 負:エラー(多分)*/
	buf[len_r]='\n';
	printf("%s\n",buf);
	recv(sock,buf,BUF_SIZE,0);
}



int main(int argc/*実行時の引数の数*/,char**argv){
	
	if(argc != 3)DieWithError("arguments is not available");
	
	char *server_ipaddr = argv[1]; /*"10.13.64.20"*/
	int server_port = atoi(argv[2]); //10001;
	int sock = socket(PF_INET,SOCK_STREAM,0);
	if(sock <0)DieWithError("socket() failed");/*-1はエラー*/
	
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(server_ipaddr);
	target.sin_port = htons(server_port);
	
	if(connect(sock,(struct sockaddr*)&target,sizeof(target))<0){
		DieWithError("connect() failed");
	}
	
	/*printf("sock is %d\n",sock);*/
	
	commun(sock);
	
	close(sock);
	return 0;
}