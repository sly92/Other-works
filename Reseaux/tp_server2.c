#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#define TOTAL_USER 10     /* how many pending connections queue will hold */


int max(int a, int b)
{
if(a>b)
return a;
return b;
}

int main(int argc,char *argv[])
{

	char buffer[256];
	int listen_fd, accepted_fd,new_fd, n, sock, conn;
	struct sockaddr_in server_addr;
  fd_set rdfs;
	int i=0,j=0,k=0,actif=0;
  int max_fd=0;
	int conn_tab[TOTAL_USER];
	int port;

	if(argc < 1) {
		printf("\nUsage: ./server [port]\n\n");
		exit(1);
	}
	port = atoi(argv[1]);


	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            printf("Error : socket creation");
            exit(1);
        }
				printf("Bienvenue dans mon serveur IRC !\n");

	memset(&server_addr, 0, sizeof(server_addr));

	// = memset de 0 (plus utilisé)
	server_addr.sin_family = AF_INET;
	// human to numeric (1025 en binaire)
	server_addr.sin_port = htons(port);

  server_addr.sin_addr.s_addr = INADDR_ANY;

	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

	// il attend un sockaddr * donc on caste en ça
	if (bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {

            printf("\n\nError : bind file descriptor\n\n");
            exit(1);
        }


	// 10 est le nombre de connection maximum

	if (listen(listen_fd, TOTAL_USER) != 0) {
            printf("\n\nError : listen file descriptor\n\n");
            exit(1);
        }

 printf("\n\nListening ...\n\n");
	// NULL car on ne veut pas des information des clients entrant dans le serveur

	conn_tab[0] = listen_fd;
	actif++;
  max_fd = listen_fd + 1;

    	while(1)
	{
	FD_ZERO(&rdfs);
	for(i=0;i<actif;i++)
      FD_SET(conn_tab[i], &rdfs);

	if( sock = select(max_fd, &rdfs, NULL, NULL, NULL) < 0)
	{
		printf("\n\nError : select file descriptor\n\n");
  }

 	// Gestion des client
	if(FD_ISSET(listen_fd, &rdfs))
	{
		conn_tab[actif] = accept(listen_fd, (struct sockaddr*) NULL, NULL);
		actif++;
		max_fd = max(max_fd, conn_tab[actif])+1;
	}

	// Gestion des messages
	for(j=0;j<actif;j++)
		{
			if(FD_ISSET(conn_tab[j],&rdfs)){
          memset(&buffer, 0, sizeof(buffer));
          	read(conn_tab[j], &buffer, 256);
						for(k=0;k<actif;k++)
		      		write(conn_tab[k], &buffer, sizeof(buffer));
						}

    }

	}


close(accepted_fd);
close(listen_fd);

return 0;
}
