#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <pthread.h>
#include <string.h>
#include "erproc.h"
#include "play.h"

int ad[4];
struct sockaddr_in server_ip, remote_ip;
char buf[128]={0};

void *thread_fun(int *arg)
{
    int j = 0;
    int nread;
        while(1)
        {
        printf("read data from client : %s\n",inet_ntoa(remote_ip.sin_addr));
        nread = recv(ad[arg], &j, sizeof(int),0);//получаем число
        send(ad[arg], &j,sizeof(int),0);//отдаем число
        break;
        //memset(buf,0,128);
        //read(ad[(int)arg],buf,128);
        //printf("buf =%s\n",buf);
        }
return NULL;
}

//теперь наверно надо создать несколько потоков, которые будут рабоать
// нужно распределить данные, типо один пользователь такой, а другой такой-то
//1 создать потоки, но мне не охота, так что сначала создадим игру

int main() {
	pthread_t tid[4];
	int server_len,remote_len;
	int i = 0;
	int err;
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    //server_ip.sin_addr.s_addr =htonl(INADDR_ANY);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 4);

    remote_len=sizeof(struct sockaddr);
    while(1){
    	ad[i] = Accept(server, (struct sockaddr *) &adr, &remote_len);
    
        err=pthread_create(&tid[i],NULL,thread_fun,(int*)i);
        if(err !=0){
            printf("create new thread failure\n");
            close(ad[i]);
        }

        ++i;
    }
    close(server);

    /*socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
    ssize_t nread;
    //char buf[256];
    int i = 0;
    nread = recv(fd, &i, sizeof(int),0);//получаем число
    if (nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("END OF FILE occured\n");
    }
    //write(STDOUT_FILENO, buf, nread);
    send(fd, &i,sizeof(int),0);//отдаем число

    //sleep(15);
    print_1();

    close(fd);
    close(server);
    return 0;
    */
}