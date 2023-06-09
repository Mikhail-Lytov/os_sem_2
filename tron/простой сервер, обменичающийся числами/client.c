#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "erproc.h"

int main() {
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);//адресс сервера
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr); //подклчаемся
    int i = 1234;
    send(fd, &i,sizeof(int),0);//отдаем число
    //char arr[] = "Hello\n"
    //write(fd, "Hello\n", 6);
    int buf;
    ssize_t nread;
    nread = recv(fd, &buf, sizeof(int),0);//получаем число
    if (nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("EOF occured\n");
    }
    //write(STDOUT_FILENO, buf, nread);
    printf("%d",buf);
    sleep(10);
    printf("я все");
    //sleep(10);
    close(fd);
    return 0;
}