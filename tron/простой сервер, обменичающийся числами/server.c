#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "erproc.h"
#include "play.h"


//теперь наверно надо создать несколько потоков, которые будут рабоать
// нужно распределить данные, типо один пользователь такой, а другой такой-то
//1 создать потоки, но мне не охота, так что сначала создадим игру

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 4);
    socklen_t adrlen = sizeof adr;
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
}