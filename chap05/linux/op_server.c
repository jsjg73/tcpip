#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;

	struct sockaddr_in serv_adr,clnt_adr;
	socklen_t clnt_adr_sz;

	char message[BUF_SIZE];
	int str_len, i;

	if(argc!=2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error!");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error!");

	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error!");

	clnt_adr_sz = sizeof(clnt_adr);
	
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	if(clnt_sock==-1)
		error_handling("accept() error!");

	str_len=read(clnt_sock, message, BUF_SIZE);

	message[str_len]=0;
	char *ptr = strtok(message, ",");
	int operator=111;
	int num[100];
	int idx=0;
	while(ptr!=NULL)
        {
                if(strcmp("+",ptr)==0)
                {
                        operator=0;
                }
		else if(strcmp("-",ptr)==0)
                {
                        operator=1;
                }
		else if(strcmp("*",ptr)==0)
                {
                        operator=2;
                }else{
			
			printf("ptr : %s 그리고 idx: %d \n",ptr,idx);
			
                        num[idx]=atoi(ptr);
			idx++;
			
                }
                ptr=strtok(NULL,",");
        }
        int cal=num[0];
	printf("idx의 크기 : %d \n",idx);
	printf("operator : %d \n",operator);
        for(int i=1; i<idx; i++)
        {
		printf("%d에 %d를 연산\n",cal,num[i]);
                if(operator==0)
                        cal+=num[i];
                else if(operator==1)
                        cal-=num[i];
                else if(operator==2)
                        cal*=num[i];
        }
	sprintf(message,"%d",cal);
	printf("operation result : %s \n",message);

	write(clnt_sock, message, str_len);

	close(clnt_sock);
	printf("Close client\n");

	close(serv_sock);
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
