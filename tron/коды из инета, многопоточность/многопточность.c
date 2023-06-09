

/*DATA:         2018-1-17
 *AUTHOR:       wg
 * ОПИСАНИЕ: Многопоточный TCP-сервер
 *  1，int socket(int domain,int type,int protocol);
 *  2, int bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
 *  3, int listen(int sockfd,int backlog);
 *  4, accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
 *  5, read(),write()
 */
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_LISTEN 100
int ad[10];
char buf[128]={0};
struct sockaddr_in server_ip, remote_ip;

void *thread_fun(void *arg)
{
        while(1)
        {
        printf("read data from client : %s\n",inet_ntoa(remote_ip.sin_addr));
        memset(buf,0,128);
        read(ad[(int)arg],buf,128);
        printf("buf =%s\n",buf);
        }
return NULL;
}

int main()
{
        int server_len,remote_len;
        int err,sd;
        pthread_t tid[10];
        int i=0;
        
        sd=socket(AF_INET,SOCK_STREAM,0);
        if(sd == -1)
        {
                printf("create socket failure, errno =%d\n",sd);
                close(sd);
                return -1;
        }
        
        server_ip.sin_family =AF_INET;
        server_ip.sin_port = htons(10086);
        server_ip.sin_addr.s_addr =htonl(INADDR_ANY);
        memset(server_ip.sin_zero,0,8);
        
        err=bind(sd,(struct sockaddr *)(&server_ip),sizeof(struct sockaddr));
        if(err==-1)
        {
                printf("bind error,errno=%d\n",err);
                close(sd);
                return err;
        }
        err=listen(sd,MAX_LISTEN);
        if(err == -1)
        {
        printf("listen error ,errno =%d\n",err);
        close(sd);
        return err;
        }
        
        remote_len=sizeof(struct sockaddr);
        
        while(1)//listen n client quest
        {
        ad[i]=accept(sd,(struct sockaddr *)(&remote_ip),&remote_len);
        if(ad[i] !=0 )
        {
                printf("accept error,errno =%d\n",ad[i]);
                close(sd);
                return -2;
        }
        err=pthread_create(&tid[i],NULL,thread_fun,(void*)i);
        if(err !=0)
        {
        printf("create new thread failure\n");
        close(ad[i]);
        }
        ++i;
        }
        close(sd);
        
        return 0;
}