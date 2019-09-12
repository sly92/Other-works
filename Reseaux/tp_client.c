/*
/	Etude d'un serveur ECHO
/	Code du client
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

//#define PORT 6667    /* the port users will be connecting to */


int main(int argc, char *argv[])
{
    int sockfd,n;
    char recvline[256];
    char sendline[256];
    struct sockaddr_in servaddr;
    int port;
    char *host;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            printf("\n\nError : socket creation\n\n");
            exit(1);
        }
    if(argc < 3) {
        printf("\nUsage: ./client host [port]\n\n");
        exit(1);
    }
    port = atoi(argv[2]);
    host = argv[1];

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    inet_pton(AF_INET,host,&(servaddr.sin_addr));

     if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {

            printf("\n\nError : connection\n\n");
            exit(1);
      }

    while(1)
    {
        memset(&sendline, 0, sizeof(sendline));
	      memset(&recvline, 0, sizeof(recvline));

        fgets(sendline,256,stdin); /*stdin pour l'input standard*/

        write(sockfd,sendline,strlen(sendline)+1);
        read(sockfd,recvline,256);
	printf("%s",recvline);
    }

   close(sockfd);
   return 0;

}
