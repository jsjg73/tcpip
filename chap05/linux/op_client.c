#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define _CRT_SECURE_NO_WARNINGS
#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char* argv[]){
        int sock;
        struct sockaddr_in serv_adr;
        char message[BUF_SIZE];
        int str_len;

        if(argc!=3)
        {
                printf("Usage : %s <IP> <port>\n", argv[0]);
                exit(1);
        }

        sock=socket(PF_INET, SOCK_STREAM, 0);
        if(sock ==-1 )
                error_handling("socket() error!");

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family=AF_INET;
        serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_adr.sin_port=htons(atoi(argv[2]));

        if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
                error_handling("connect() error!");
        else
                puts("Connected............");
	
        int op_cnt;
        printf("Oerand count: ");
        scanf("%d", &op_cnt);

        char num[10];
        for(int j=0; j<op_cnt; j++)
        {
                printf("Operand %d: ", j+1);
                scanf("%s", num);
                if(strlen(message)!=0)
                        strcat(message, ",");
                strcat(message, num);
        }

        char operator[2];
        printf("Operator:");
        scanf("%s", operator);
        strcat(message, ",");
        strcat(message, operator);

        write(sock, message, strlen(message));
        str_len=read(sock, message, BUF_SIZE-1);
        message[str_len]=0;
        printf("Operation result: %s", message);

        close(sock);
        return 0;
}
void error_handling(char *message)
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
