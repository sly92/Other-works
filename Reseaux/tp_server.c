#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int max(int a, int b)
{
if(a>b)
return a;
return b;
}

int main()
{

	char str[100];
	int listen_fd, accepted_fd, n;
	struct sockaddr_in servaddr;
	int conn_tab[200];
    fd_set rdfs;
	int i=0,j=0,k=0;
    int max_fd=0;
    int conn;	

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// = memset de 0 (plus utilisé)
	bzero(&servaddr, sizeof(servaddr));

    printf("WTF");
	servaddr.sin_family = AF_INET;
	// human to numeric (1025 en binaire)
	servaddr.sin_port = htons(8888);
	// INADDR_ANY ecoute de n'importe quel adresse
	servaddr.sin_addr.s_addr = INADDR_ANY;
	// il attend un sockaddr * donc on caste en ça
	// inet_pton(AF_INET, servaddr, &listen_fd.sin_addr);

	bind(listen_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	// 10 est le nombre de co max
	listen(listen_fd, 10);   

    i++;
    while(1)
	{
        max_fd = max(max_fd, listen_fd);
		FD_ZERO(&rdfs);
		for(j=0;j<=max_fd;j++){
			FD_SET(conn_tab[j], &rdfs);
		}
		if(select(max_fd+1, &rdfs, NULL, NULL, NULL) != 0)
        {
			
            if(FD_ISSET(listen_fd, &rdfs))
			{
				conn = accept(listen_fd, (struct sockaddr*) NULL, NULL);
				conn_tab[i]=conn;
                FD_SET(conn_tab[i], &rdfs);
				i++;
			}

			for(k=0;k<i;k++)
			{
				if(FD_ISSET(conn_tab[k],&rdfs))
		        {
				    accepted_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
                    bzero(str,100);
                    read(accepted_fd, str, 200);
                    printf("Echoing back - %s", str);
                    write(accepted_fd, str, strlen(str)+1);
                }

			}

		}	

	}

	close(accepted_fd);
    
	close(listen_fd);
	
	return 0;
}
